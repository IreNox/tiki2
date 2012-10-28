using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;

namespace TikiEditor
{
    public class EditorMode : DrawableGameComponent
    {
        #region Vars
        //private List<
        #endregion

        #region Init
        public EditorMode(Game game)
            : base(game)
        { 
        }
        #endregion

        #region Mebmber
        public virtual object ResetBefore()
        {
            return null;
        }

        public virtual void ResetAfter(object userData)
        {
        }
        #endregion

        #region Member - Draw/Update
        public override void Draw(GameTime time)
        {
            
        }

        public override void Update(GameTime time)
        {
        }
        #endregion
    }
}
