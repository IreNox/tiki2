using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Input;

namespace TikiEditor
{
    public class ModeTest : EditorMode
    {
        #region Vars
        private ucDesignTest _designer;

        private BlendState _blendEdit;
        private BlendState _blendGraphics;

        private SpriteBatch _batch;

        private Vector2 _pos1;
        private Vector2 _pos2;

        private Texture2D _tex;
        #endregion

        #region Init
        public ModeTest(GameMain game)
            : base(game)
        {
            _blendEdit = new BlendState();
            _blendGraphics = new BlendState();
            
            _designer = new ucDesignTest();
            _designer.SelectedObject = _blendEdit;

            _pos1 = new Vector2(25, 25);
        }

        public override void Initialize()
        {
            base.Initialize();

            DDSLib.DDSFromFile(
                "Data/Textures/particle/mg.dds",
                GI.Device,
                false,
                out _tex
            );

            _batch = new SpriteBatch(GI.Device);

            Program.Form.LeftControl = _designer;            
        }
        #endregion

        #region Member - Draw/Update
        public override void Draw(GameTime gameTime)
        {
            _blendGraphics = new BlendState();
            _blendGraphics.AlphaBlendFunction = _blendEdit.AlphaBlendFunction;
            _blendGraphics.AlphaDestinationBlend = _blendEdit.AlphaDestinationBlend;
            _blendGraphics.AlphaSourceBlend = _blendEdit.AlphaSourceBlend;
            _blendGraphics.BlendFactor = _blendEdit.BlendFactor;
            _blendGraphics.ColorBlendFunction = _blendEdit.ColorBlendFunction;
            _blendGraphics.ColorDestinationBlend = _blendEdit.ColorDestinationBlend;
            _blendGraphics.ColorSourceBlend = _blendEdit.ColorSourceBlend;
            //_blendGraphics.ColorWriteChannels = _blendEdit.ColorWriteChannels;
            //_blendGraphics.ColorWriteChannels1 = _blendEdit.ColorWriteChannels1;
            //_blendGraphics.ColorWriteChannels2 = _blendEdit.ColorWriteChannels2;
            //_blendGraphics.ColorWriteChannels3 = _blendEdit.ColorWriteChannels3;
            //_blendGraphics.MultiSampleMask = _blendEdit.MultiSampleMask;

            try
            {
                _batch.Begin(SpriteSortMode.FrontToBack, _blendGraphics);

                _batch.Draw(_tex, _pos1, Color.White);
                _batch.Draw(_tex, _pos2, Color.White);

                _batch.End();
            }
            catch (Exception e)
            {
                GI.SpriteBatch.DrawString(
                    GI.Content.Load<SpriteFont>("font"),
                    e.Message,
                    Vector2.Zero,
                    Color.Black
                );

                _batch.Dispose();
                _batch = new SpriteBatch(GI.Device);
            }

            base.Draw(gameTime);
        }

        public override void Update(GameTime gameTime)
        {
            Vector2 move = new Vector2(
                (GI.Control.KeyboardDown(Keys.A) ? -1 : 0) + (GI.Control.KeyboardDown(Keys.D) ? 1 : 0),
                (GI.Control.KeyboardDown(Keys.W) ? -1 : 0) + (GI.Control.KeyboardDown(Keys.S) ? 1 : 0)
            );

            if (GI.Control.KeyboardDown(Keys.RightShift))
            {
                _pos1 += move * (float)(gameTime.ElapsedGameTime.TotalSeconds * 25);
            }
            else
            {
                _pos2 += move * (float)(gameTime.ElapsedGameTime.TotalSeconds * 25);
            }

            base.Update(gameTime);
        }
        #endregion
    }
}
