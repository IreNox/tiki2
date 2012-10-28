using System;
using System.ComponentModel;
using System.Collections.Generic;
using System.Reflection;

namespace Database.GDB
{
    public class DbRow<T>
    {
        #region Vars
        private DbTable<T> _table;

        private Dictionary<DbColumn<T>, object> _items = new Dictionary<DbColumn<T>, object>();
        private Dictionary<DbRelation<T>, object> _relations = new Dictionary<DbRelation<T>, object>();
        #endregion

        #region Init
        public DbRow(DbTable<T> table)
        {
            _table = table;

            foreach (DbColumn<T> col in table.Columns)
            {
                _items[col] = null;
            }
        }

        public DbRow(DB db, T obj)
            : this(db.GetBaseTable<T>())
        {
            foreach (DbColumn<T> col in _table.Columns)
            {
                _items[col] = col.Info.GetValue(obj, null);
            }

            foreach (DbRelation<T> relation in _table.Relations)
            {
                switch (relation.BasePropertyType)
                { 
                    case DbRelation<T>.PropertyType.Array:
                        _relations[relation] = relation.Info.GetValue(obj, null);
                        break;
                    case DbRelation<T>.PropertyType.IList:
                        // TODO: in array convertieren
                        _relations[relation] = relation.Info.GetValue(obj, null);
                        break;
                }               
            }
        }
        #endregion

        #region Private Member
        private int _getId()
        {
            if (_table.PrimaryColumn != null)
            {
                return this[_table.PrimaryColumn].GetHashCode();
            }

            return (new Random()).Next(Int32.MinValue, Int32.MaxValue);
        }
        #endregion

        #region Member
        public T ToObject()
        {
            Type type = _table.Type;
            T obj = Activator.CreateInstance<T>();

            foreach (var kvp in _items)
            {
                this.SetProperty(obj, kvp.Key, kvp.Value);
            }

            foreach (var kvp in _relations)
            {
                this.SetRelation(obj, kvp.Key);
            }

            INotifyPropertyChanged npc = obj as INotifyPropertyChanged;

            if (npc != null)
            {
                npc.PropertyChanged += new PropertyChangedEventHandler(_table.Db.Object_PropertyChanged);
            }

            return obj;
        }

        public void SetRelation(T obj, DbRelation<T> relation)
        {
            object data = null;

            switch (relation.BasePropertyType)
            {
                case DbRelation<T>.PropertyType.Array:
                    data =  _relations[relation];
                    break;
                case DbRelation<T>.PropertyType.IList:
                    data = relation.GetType().GetMethod("CreateList").MakeGenericMethod(
                        relation.InfoChild.ReflectedType
                    ).Invoke(
                        relation,
                        new object[] { obj, _relations[relation] }
                    );
                    break;
            }

            if (data != null)
            {
                relation.Info.SetValue(obj, data, null);
            }
        }

        public void SetProperty(T obj, DbColumn<T> col, object value)
        {
            if (!Object.Equals(this[col], value))
            {
                this[col] = value;
            }

            col.Info.SetValue(
                obj,
                Convert.ChangeType(value, col.Type),
                null
            );
        }
        #endregion

        #region Properties
        public DbTable<T> Table
        {
            get { return _table; }
        }

        public Dictionary<DbRelation<T>, object> Relations
        {
            get { return _relations; }
        }

        public object this[string key]
        {
            get { return this[_table.GetColumn(key)]; }
            set { this[_table.GetColumn(key)] = value; }
        }

        public object this[DbColumn<T> column]
        {
            get
            {
                if (!_items.ContainsKey(column))
                {
                    throw new Exception("Column not for this Table.");
                }

                return _items[column];
            }
            set
            {
                if (!_items.ContainsKey(column))
                {
                    throw new Exception("Column not for this Table.");
                }

                _items[column] = value;
            }
        }
        #endregion

        #region Operators
        public override bool Equals(object obj)
        {
            if (obj is DbRow<T>)
            {
                return this == (DbRow<T>)obj;
            }

            return false;
        }

        public override int GetHashCode()
        {
            return _table.GetHashCode() * _getId();
        }

        public static bool operator ==(DbRow<T> o1, DbRow<T> o2)
        {
            if (((object)o1 == null) && ((object)o2 == null)) return true;
            if (((object)o1 == null) || ((object)o2 == null)) return false;

            return (o1._getId() == o2._getId()) && (o1._table == o2._table);
        }

        public static bool operator !=(DbRow<T> o1, DbRow<T> o2)
        {
            return !(o1 == o2);
        }
        #endregion
    }
}
