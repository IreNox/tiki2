using System;
using System.IO;
using System.Linq;
using System.Text;
using System.Collections.Generic;
using Database.GDB;
using Microsoft.Xna.Framework;

namespace TikiEditor.Objects
{
    [DataTable("tiki_res")]
    public class ResData : DataBaseObject
    {
        #region Vars
        private string _name;
        private byte[] _data;
        #endregion    

        #region Member
        public void LoadFromFile(string fileName)
        {
            _name = fileName.Replace(GI.DataPath, "");
            _data = File.ReadAllBytes(fileName);
        }
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
