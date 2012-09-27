using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Database.GDB
{
    public class DataFieldPrimaryAttribute : Attribute
    {
        #region Vars
        private int _start = 1;
        private int _increment = 1;
        #endregion

        #region Init
        public DataFieldPrimaryAttribute(int start = 1, int increment = 1)
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
