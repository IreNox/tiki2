using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Database.GDB;

namespace TikiEditor.Objects
{
    [DataTable("tiki_level_objects")]
    public class LevelObject : BasicTransform
    {
        #region Vars
        private long _levelId;

        private int _type;
        private int _assignment;
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

        [DataField("Assignment")]
        public int Assignment
        {
            get { return _assignment; }
            set { SetProperty(ref _assignment, value, "Assignment"); }
        }
        #endregion
    }
}
