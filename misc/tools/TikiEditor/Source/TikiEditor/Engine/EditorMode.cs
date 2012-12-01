using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;

namespace TikiEditor
{
    public class EditorMode : DrawableGameComponent
    {
        #region Init
        public EditorMode(Game game)
            : base(game)
        { 
        }
        #endregion

        #region Mebmber
        public virtual void Init()
        {
        }

        public virtual object ResetBefore()
        {
            return null;
        }

        public virtual void ResetAfter(object userData)
        {
        }
        #endregion
    }
}
