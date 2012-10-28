using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Database.GDB
{
    public class DataFieldAttribute : Attribute
    {
        #region Vars
        private string _dbFieldname;
        #endregion

        #region Init
        public DataFieldAttribute(string fieldname)
        {
            _dbFieldname = fieldname;
        }
        #endregion

        #region Properties
        public string Fieldname
        {
            get { return _dbFieldname; }
        }
        #endregion
    }
}
