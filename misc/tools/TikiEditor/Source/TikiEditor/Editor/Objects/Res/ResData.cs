using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Database.GDB;
using Microsoft.Xna.Framework;

namespace TikiEditor.Objects
{
    [DataTable("tiki_res")]
    public class GUIRect : DataBaseObject
    {
        #region Vars
        private string _name;
        private byte[] _data;
        #endregion
               

        #region Properties
        [DataField("Name")]
        public string Name
        {
            get { return _name; }
            set { _name = value; }
        }

        [DataField("Data")]
        public byte[] Data
        {
            get { return _data; }
            set { _data = value; }
        }
        #endregion
    }
}
