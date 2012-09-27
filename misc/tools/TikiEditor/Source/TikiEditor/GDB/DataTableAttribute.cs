using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Database.GDB
{
    public class DataTableAttribute : Attribute
    {
        #region Vars
        private string _dbTablename;
        #endregion

        #region Init
        public DataTableAttribute(string tablename)
        {
            _dbTablename = tablename;
        }
        #endregion

        #region Properties
        public string Tablename
        {
            get { return _dbTablename; }
        }
        #endregion
    }
}
