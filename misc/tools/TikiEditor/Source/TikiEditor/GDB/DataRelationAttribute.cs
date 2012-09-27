using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Database.GDB
{
    public class DataRelationAttribute : Attribute
    {
        #region Vars
        private Type _typeChild;

        private string _baseFieldname;
        private string _childFieldname;
        #endregion

        #region Init
        public DataRelationAttribute(string baseFieldname, Type childType, string childFilename)
        {
            _typeChild = childType;

            _baseFieldname = baseFieldname;
            _childFieldname = childFilename;
        }
        #endregion

        #region Properties
        public Type TypeChild
        {
            get { return _typeChild; }
        }

        public string BaseFieldname
        {
            get { return _baseFieldname; }
            set { _baseFieldname = value; }
        }

        public string ChildFieldname
        {
            get { return _childFieldname; }
        }
        #endregion
    }
}
