using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Database.GDB;

namespace TikiEditor.Objects
{
    [DataTable("tiki_level_points")]
    public class LevelPoint : BasicTransform
    {
        #region Vars
        private long _levelId;

        private int _type;
        private string _name;
        #endregion

        #region Properties
        [DataField("LevelID")]
        public long LevelID
        {
            get { return _levelId; }
            set { SetProperty(ref _levelId, value, "LevelID"); }
        }

        [DataField("Type")]
        public int Type
        {
            get { return _type; }
            set { SetProperty(ref _type, value, "Type"); }
        }

        [DataField("Name")]
        public string Name
        {
            get { return _name; }
            set { SetProperty(ref _name, value, "Name"); }
        }

        public override float Rotation
        {
            get { return base.Rotation; }
            set { }
        }
        #endregion
    }
}
