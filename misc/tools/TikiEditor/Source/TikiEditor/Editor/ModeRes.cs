using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Input;

namespace TikiEditor
{
    public class ModeRes : EditorMode
    {
        #region Vars
        private ucDesignRes _designer;
        #endregion

        #region Init
        public ModeRes(GameMain game)
            : base(game)
        {
            _designer = new ucDesignRes();
        }

        public override void Initialize()
        {
            base.Initialize();

            Program.Form.LeftControl = _designer;            
        }
        #endregion
    }
}
