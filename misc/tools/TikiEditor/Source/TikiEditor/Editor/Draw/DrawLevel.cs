using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using TikiEditor.Objects;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Input;

namespace TikiEditor
{
    public class DrawLevel : DrawBasic<BasicTransform>
    {
        #region Vars
        public float Scale = 1.0f;

        private Level _level;
        #endregion

        #region Init
        public DrawLevel()
        {
            _level = GI.ModeLevel.Level;

            pointColors = new Dictionary<string, Color>()
            {
                { "pos", Color.Blue },
                { "size", Color.Green },
                { "rotation", Color.Red },
                { "test", Color.White }
            };
        }
        #endregion

        #region Private Member
        private BasicTransform _getTransformAtPoint(Vector2 point)
        {
            return _level.AllTransforms.FirstOrDefault(t => t.BoundingBox(this.Scale).Contains(point));
        }
        #endregion

        #region Private Member - Draw
        private void _drawBasicTransform(BasicTransform bt)
        {
            Vector2[] vertices = bt.Vertices(this.Scale);
            Color c = new Color(0, 1, 0, 0.5f);

            if (bt is LevelPoint)
            {
                c = new Color(0, 0, 1, 0.5f);
            }

            batch.Draw(vertices, c);

            batch.DrawLine(
                vertices,
                (selected == bt ? Color.Red : Color.Blue)
            );
        }
        #endregion

        #region Member - Abstract
        protected override BasicTransform SelectObjectOnPoint(Vector2 point)
        {
            BasicTransform bt = _getTransformAtPoint(point);

            if (bt != null)
            {
                points.Clear();

                points["pos"] = Vector2.Zero;
                points["size"] = new Vector2(bt.Scale / 2);
                points["rotation"] = new Vector2(
                    (float)Math.Sin(bt.Rotation),
                    (float)Math.Cos(bt.Rotation)
                );

                GI.ModeLevel.Designer.SelectedObject = bt;
                return bt;
            }
            else
            {
                GI.ModeLevel.Designer.SelectedObject = _level;
                return null;
            }
        }

        protected override void TransformSelected(GameTime gameTime)
        {
            if (GI.Control.KeyboardPressed(Keys.Delete))
            {
                _level.RemoveTransform(selected);
                selected = null;
                return;
            }

            Vector2 trans = (new Vector2(
                (GI.Control.KeyboardDown(Keys.Left) ? -1 : 0) + (GI.Control.KeyboardDown(Keys.Right) ? 1 : 0),
                (GI.Control.KeyboardDown(Keys.Up) ? -1 : 0) + (GI.Control.KeyboardDown(Keys.Down) ? 1 : 0)
            ) * ((float)gameTime.ElapsedGameTime.TotalSeconds * (GI.Control.KeyboardDown(Keys.RightShift) ? 5 : 1))) -
            (GI.Control.MouseDown(MouseButtons.Left) && dragPoint == null ? GI.Control.MouseDistanceSim() : Vector2.Zero);

            if (trans == Vector2.Zero)
            {
                if (!selected.DatabaseEnabled && dragPoint == null) selected.DatabaseEnabled = true;
                return;
            }
            else
            {
                if (selected.DatabaseEnabled) selected.DatabaseEnabled = false;
            }

            if (GI.Control.KeyboardDown(Keys.RightControl))
            {
                selected.Scale += trans.Length();
            }
            else if (GI.Control.KeyboardDown(Keys.RightAlt))
            {
                selected.Rotation -= trans.X;
                selected.Rotation -= trans.Y;
            }
            else
            {
                selected.Position += trans;
            }        
        }

        protected override void  SelectedMovePoint(ref Vector2 mouse, ref Vector2 localMouse)
        {
            switch (dragPoint)
            {
                case "pos":
                    selected.Position = mouse;
                    break;
                case "size":
                    selected.Scale = (localMouse.X + localMouse.Y);
                    localMouse = new Vector2(selected.Scale / 2);
                    break;
                case "rotation":
                    selected.Rotation = (float)Math.Atan2(localMouse.Y, localMouse.X);
                    break;
            }
        }

        protected override Matrix World()
        {
            return selected.WorldMatrix;
        }

        protected override Matrix WorldToLocal()
        {
            return Matrix.CreateTranslation(
                -new Vector3(selected.Position, 0)
            ) * Matrix.CreateScale(
                new Vector3(
                    1.0f / selected.Scale
                )
            ) * Matrix.CreateRotationZ(
                -selected.Rotation
            );
        }
        #endregion

        #region Member - Draw
        public override void Draw(GameTime gameTime)
        {
            foreach (BasicTransform transform in _level.AllTransforms)
            {
                _drawBasicTransform(transform);
            }

            if (showBounding)
            {
                foreach (BasicTransform bt in _level.AllTransforms)
                {
                    var rect = bt.BoundingBox(this.Scale);

                    drawRect(
                        rect.Position + (rect.Size / 2),
                        rect.Size,
                        (bt == selected ? Color.Green : Color.Black)
                    );
                }
            }

            base.Draw(gameTime);
        }
        #endregion
    }
}
