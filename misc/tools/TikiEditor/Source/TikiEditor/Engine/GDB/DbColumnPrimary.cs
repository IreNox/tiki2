using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Reflection;

namespace Database.GDB
{
    public class DbColumnPrimary<T> : DbColumn<T>
    {
        #region Vars
        private int _start = 1;
        private int _increment = 1;
        #endregion

        #region Init
        public DbColumnPrimary(DbTable<T> table, string name, Type type, PropertyInfo info, int start, int increment) 
            : base(table, name, type, info)
        {
            _start = start;
            _increment = increment;
        }
        #endregion

        #region Properties
        public int Start
        {
            get { return _start; }
        }

        public int Increment
        {
            get { return _increment; }
        }
        #endregion
    }
}
