using System;
using System.Collections.Generic;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace TikiEditor
{
    public class TikiButton : DrawableGameComponent
    {
        #region Vars
        private string _text;
        private Vector4 _rect;
        private Action _click;

        private SpriteFont _font;
        private Texture2D _texture;
        #endregion

        #region Init
        public TikiButton(Vector4 rect, string text, Action click)
            : base(GI.Game)
        {
            _rect = rect;
            _text = text;
            _click = click;

            _texture = new Texture2D(GI.Device, 1, 1);
            
            Color[] data = new Color[1];
            data[0] = new Color(1.0f, 1.0f, 1.0f, 0.5f);
            _texture.SetData(data);

            _font = GI.Content.Load<SpriteFont>("font");
        }
        #endregion

        #region Member
        public override void Draw(GameTime gameTime)
        {
            Vector2 size = new Vector2(_rect.Z, _rect.W);
            Vector2 pos = new Vector2(_rect.X, _rect.Y) + (size / 2) + GI.Camera.CurrentPositionNagativ;

            GI.SpriteBatch.Draw(
                _texture,
                pos,
                null,
                Color.White,
                0.0f,
                Vector2.One / 2,
                size,
                SpriteEffects.None,
                1.0f
            );
            
            GI.SpriteBatch.DrawString(
                _font,
                _text,
                pos - (_font.MeasureString(_text) / 2),
                Color.Black
            );

            base.Draw(gameTime);
        }

        public override void Update(GameTime gameTime)
        {
            if (GI.Control.MouseClick(MouseButtons.Left) && _rect.Contains(GI.Control.MouseDisplayPointNoCamera().ToVector2()))
            {
                _click();
            }

            base.Update(gameTime);
        }
        #endregion
    }
}
