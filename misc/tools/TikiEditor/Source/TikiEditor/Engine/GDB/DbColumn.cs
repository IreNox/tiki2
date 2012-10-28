using System;
using System.Reflection;

namespace Database.GDB
{
    public class DbColumn<T>
    {
        #region Vars
        private DbTable<T> _table;

        private string _name;
        private Type _type;

        private PropertyInfo _info;
        #endregion

        #region Init
        public DbColumn(DbTable<T> table, string name, Type type, PropertyInfo info)
        {
            _table = table;

            _name = name;
            _type = type;

            _info = info;
        }
        #endregion
        
        #region Properties
        public DbTable<T> Table
        {
            get { return _table; }
        }

        public string Name
        {
            get { return _name; }
        }

        public Type Type
        {
            get { return _type; }
        }

        public PropertyInfo Info
        {
            get { return _info; }
        }
        #endregion

        #region Operators
        public override bool Equals(object obj)
        {
            if (obj is DbColumn<T>)
            {
                return this == (DbColumn<T>)obj;
            }

            return false;
        }

        public override int GetHashCode()
        {
            return _table.GetHashCode() * _name.GetHashCode() * _type.GetHashCode() * _info.GetHashCode();
        }

        public static bool operator ==(DbColumn<T> o1, DbColumn<T> o2)
        {
            if (((object)o1 == null) && ((object)o2 == null)) return true;
            if (((object)o1 == null) || ((object)o2 == null)) return false;
            
            return (o1._table == o2._table) && (o1._name == o2._name) && (o1._type == o2._type) && (o1._info == o2._info);
        }

        public static bool operator !=(DbColumn<T> o1, DbColumn<T> o2)
        {
            return !(o1 == o2);
        }
        #endregion
    }
}
