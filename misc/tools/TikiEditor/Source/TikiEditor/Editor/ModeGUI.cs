using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework.Graphics;
using System.IO;
using Microsoft.Xna.Framework;

namespace TikiEditor
{
    public class ModeGUI : EditorMode
    {
        #region Vars
        private Texture2D _texture;

        private DrawGUI _draw;
        private ucDesignGUI _designer;
        #endregion

        #region Init
        public ModeGUI(Game game)
            : base(game)
        {
        }

        public override void Initialize()
        {
            GI.Camera.RealZoom = 1f;
            GI.Camera.CurrentPositionCenter = Vector2.Zero;

            _draw = new DrawGUI();
            _designer = new ucDesignGUI();
            Program.Form.LeftControl = _designer;

            base.Initialize();
        }

        protected override void LoadContent()
        {            
            DDSLib.DDSFromFile("Data/Textures/gui.dds", this.GraphicsDevice, false, out _texture);
            
            base.LoadContent();
        }
        #endregion

        #region Meber - Draw/Update
        public override void Draw(GameTime time)
        {
            if (_texture != null) 
            {
                GI.SpriteBatch.Draw(
                    _texture,
                    new Rectangle(0, 0, 512, 512),
                    Color.White
                );
            }

            _draw.Draw(time);

            base.Draw(time);
        }

        public override void Update(GameTime time)
        {
            _draw.Update(time);
            base.Update(time);
        }
        #endregion

    }
}
