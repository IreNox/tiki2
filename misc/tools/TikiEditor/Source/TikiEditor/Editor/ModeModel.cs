using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;

namespace TikiEditor
{
    public class ModeModel : EditorMode
    {
        #region Vars
        private ucDesignModel _designer;
        #endregion

        #region Init
        public ModeModel(Game game)
            : base(game)
        {
            _designer = new ucDesignModel();
        }

        public override void Initialize()
        {
            Program.Form.LeftControl = _designer;
        }
        #endregion
    }
}
