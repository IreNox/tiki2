using System;
using System.Linq;
using System.Reflection;
using System.Linq.Expressions;
using System.Collections.Generic;

namespace Database.GDB
{
    public enum DbRelationType
    { 
        OneToOne,
        OneToMany
    }

    public class DbRelation<T>
    {
        #region Vars
        private DbTable<T> _table;

        private PropertyInfo _infoProperty;

        private PropertyInfo _infoBase;
        private PropertyInfo _infoChild;

        private PropertyType _propertyTypeBase;

        private MethodInfo _methodInsert;
        private MethodInfo _methodExecute;
        #endregion

        #region Vars - Enum
        public enum PropertyType
        { 
            Array,
            IList
        }
        #endregion

        #region Init
        public DbRelation(DbTable<T> table, PropertyInfo propertyInfo, PropertyInfo baseInfo, PropertyInfo childInfo)
        {
            _table = table;

            _infoBase = baseInfo;
            _infoChild = childInfo;

            _infoProperty = propertyInfo;

            _checkType();

            _methodInsert = typeof(DbRelation<T>).GetMethod(
                "_insertInternal",
                BindingFlags.NonPublic | BindingFlags.Instance
            ).MakeGenericMethod(_infoChild.ReflectedType);

            _methodExecute = typeof(DbRelation<T>).GetMethod(
                "_executeInternal",
                BindingFlags.NonPublic | BindingFlags.Instance
            ).MakeGenericMethod(_infoChild.ReflectedType);
        }

        public DbRelation(DbTable<T> table, PropertyInfo propertyInfo, string baseField, Type childType, string childField)
            : this(table, propertyInfo, typeof(T).GetProperty(baseField), childType.GetProperty(childField))
        {
        }
        #endregion

        #region Private Member - Check
        private void _checkType()
        {
            Type bt = _infoProperty.PropertyType;
            Type ct = _infoChild.ReflectedType;

            Type typeArr = ct.MakeArrayType();
            Type typeList = typeof(IList<>).MakeGenericType(ct);

            if (bt == typeArr)
            {
                _propertyTypeBase = PropertyType.Array;
            }
            else if (bt.GetInterfaces().Contains(typeList))
            {
                _propertyTypeBase = PropertyType.IList;
            }
            else
            {
                throw new Exception("DbRelation: BaseType property wrong");
            }
        }
        #endregion

        #region Private Member - Insert
        private void _insertInternal<T2>(T parent)
        {
            object id = _infoBase.GetValue(parent, null);
            IEnumerable<T2> list = (IEnumerable<T2>)_infoProperty.GetValue(parent, null);

            foreach (T2 child in list)
            {
                _infoChild.SetValue(child, id, null);
                _table.Db.Insert(child);
            }
        }
        #endregion

        #region Private Member - Execute
        private void _executeInternal<T2>(DbRow<T> row, DbReader<T> reader)
        {
            DbColumn<T> colBase = reader.Db.GetBaseTable<T>().Columns.First(
                c => c.Info == _infoBase
            );

            DbColumn<T2> colChild = reader.Db.GetBaseTable<T2>().Columns.First(
                c => c.Info == _infoChild
            );

            row.Relations[this] = reader.Db.Select<T2>(colChild, row[colBase]).ToArray();
        }
        #endregion

        #region Member
        public void Execute(DbRow<T> row, DbReader<T> reader)
        {
            _methodExecute.Invoke(
                this,
                new object[] { row, reader }
            );
        }

        public void Insert(T parent)
        {
            _methodInsert.Invoke(
                this,
                new object[] { parent }
            );            
        }

        public DbList<T2> CreateList<T2>(T obj, T2[] array)
        {
            return new DbList<T2>(obj, _infoProperty, array);
        }
        #endregion

        #region Properties
        public DbTable<T> Table
        {
            get { return _table; }
        }

        public PropertyInfo Info
        {
            get { return _infoProperty; }
        }

        public PropertyInfo InfoChild
        {
            get { return _infoChild; }
        }

        public PropertyType BasePropertyType
        {
            get { return _propertyTypeBase; }
        }
        #endregion
    }
}
