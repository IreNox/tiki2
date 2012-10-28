using System;
using System.Linq;
using System.Data;
using System.Reflection;
using System.Collections.Generic;
using System.Text;

namespace Database.GDB
{
    public class DbTable<T>
    {
        #region Vars
        private DB _db;

        private string _name;
        private Type _type;

        private DbColumn<T>[] _columns;
        private DbColumnPrimary<T> _primary;

        private DbRelation<T>[] _relations;

        private List<DbRow<T>> _rows = new List<DbRow<T>>();
        #endregion

        #region Init
        public DbTable(DB db)
        {
            _db = db;
            _type = typeof(T);
            DataTableAttribute attTable = (DataTableAttribute)_type.GetCustomAttributes(typeof(DataTableAttribute), true).FirstOrDefault();

            if (attTable == null)
            {
                throw new Exception(_type.FullName + " has no DataTableAttribute");
            }

            _name = attTable.Tablename;

            List<DbColumn<T>> columns = new List<DbColumn<T>>();
            List<DbRelation<T>> relations = new List<DbRelation<T>>();
            foreach (PropertyInfo info in _type.GetProperties(BindingFlags.Public | BindingFlags.Instance))
            {
                if (!info.CanRead || !info.CanWrite) continue;

                DataFieldAttribute attField = (DataFieldAttribute)info.GetCustomAttributes(typeof(DataFieldAttribute), true).FirstOrDefault();
                DataRelationAttribute attRelation = (DataRelationAttribute)info.GetCustomAttributes(typeof(DataRelationAttribute), true).FirstOrDefault();
                
                if (attField != null)
                {
                    DbColumn<T> col;
                    DataFieldPrimaryAttribute attPrimary = (DataFieldPrimaryAttribute)info.GetCustomAttributes(typeof(DataFieldPrimaryAttribute), false).FirstOrDefault();

                    if (attPrimary != null)
                    {                        
                        _primary = new DbColumnPrimary<T>(
                            this,
                            attField.Fieldname,
                            info.PropertyType,
                            info,
                            attPrimary.Start,
                            attPrimary.Increment
                        );
                        col = _primary;
                    }
                    else
                    {
                        col = new DbColumn<T>(
                            this,
                            attField.Fieldname,
                            info.PropertyType,
                            info
                        );
                    }

                    columns.Add(col);
                }
                else if (attRelation != null)
                {
                    relations.Add(
                        new DbRelation<T>(
                            this,
                            info,
                            attRelation.BaseFieldname,
                            attRelation.TypeChild,
                            attRelation.ChildFieldname
                        )
                    );
                }
            }

            _columns = columns.ToArray();
            _relations = relations.ToArray();

            if (_primary == null)
            {
                throw new Exception("Table has no Primary-Column");
            }
        }

        public DbTable(DbTable<T> copy)
        {
            _db = copy._db;
            _type = copy._type;
            _name = copy._name;
            _columns = copy._columns;
            _relations = copy._relations;
        }

        public DbTable(DbTable<T> copy, DbReader<T> reader)
            : this(copy)
        {
            Dictionary<int, DbColumn<T>> cols = new Dictionary<int, DbColumn<T>>();

            for (int i = 0; i < reader.FieldCount; i++)
            {
                DbColumn<T> col = _columns.FirstOrDefault(
                    c => c.Name == reader.GetFieldName(i) && c.Type == reader.GetFieldType(i)
                );

                if (col != null)
                {
                    cols[i] = col;
                }
            }

            foreach (var arr in reader.Data)
            {
                DbRow<T> row = new DbRow<T>(this);

                foreach (var kvp in cols)
                {
                    row[kvp.Value] = arr[kvp.Key];
                }

                foreach (DbRelation<T> relation in _relations)
                {
                    relation.Execute(row, reader);
                }

                _rows.Add(row);
            }
        }
        #endregion

        #region Member
        public DbColumn<T> GetColumn(string name)
        {
            return _columns.FirstOrDefault(
                c => c.Name == name
            );
        }

        public T[] ToArray()
        {
            return _rows.Select(
                r => r.ToObject()               
            ).ToArray();
        }
        #endregion

        #region Properties
        public DB Db
        {
            get { return _db; }
        }

        public string Name
        {
            get { return _name; }
        }

        public Type Type
        {
            get { return _type; }
        }

        public DbColumnPrimary<T> PrimaryColumn
        {
            get { return _primary; }
        }

        public DbColumn<T>[] Columns
        {
            get { return _columns; }
        }

        public DbRelation<T>[] Relations
        {
            get { return _relations; }
        }

        public List<DbRow<T>> Rows
        {
            get { return _rows; }
        }
        #endregion

        #region Operators
        public override bool Equals(object obj)
        {
            if (obj is DbTable<T>)
            {
                return this == (DbTable<T>)obj;
            }

            return false;
        }

        public override int GetHashCode()
        {
            return _name.GetHashCode() * _type.GetHashCode();
        }

        public static bool operator ==(DbTable<T> o1, DbTable<T> o2)
        {
            if (((object)o1 == null) && ((object)o2 == null)) return true;
            if (((object)o1 == null) || ((object)o2 == null)) return false;

            return (o1._name == o2._name) && (o1._type == o2._type);
        }

        public static bool operator !=(DbTable<T> o1, DbTable<T> o2)
        {
            return !(o1 == o2);
        }
        #endregion
    }
}
