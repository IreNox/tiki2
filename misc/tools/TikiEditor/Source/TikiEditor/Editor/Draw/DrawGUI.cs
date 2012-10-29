using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using TikiEditor.Objects;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Input;

namespace TikiEditor
{
    public class DrawGUI : DrawBasic<GUIRect>
    {
        #region Init
        public DrawGUI()
        {
            pointColors = new Dictionary<string, Color>()
            {
                { "top", Color.Blue },
                { "left", Color.Blue },
                { "width", Color.Blue },
                { "height", Color.Blue }
            };
        }
        #endregion

        #region Private Member
        private GUIRect _getRect(Vector2 pos)
        {
            return GI.DB.Select<GUIRect>().ToArray().FirstOrDefault(r => r.Rect.Contains(CU.ToDisplayUnits(pos)));
        }
        #endregion

        #region Private Member - Draw
        private void _drawRect(GUIRect rect)
        {
            Vector2[] vertices = rect.Vertices;

            batch.Draw(
                vertices,
                new Color(0, 0, 1, 0.5f)
            );

            batch.DrawLine(
                vertices,
                (selected == rect ? Color.Red : Color.Blue)
            );
        }
        #endregion

        #region Member - Abstract
        protected override GUIRect SelectObjectOnPoint(Vector2 mouse)
        {
            GUIRect rect = _getRect(mouse);

            if (rect != null)
            {
                points["top"] = CU.ToSimUnits(new Vector2(rect.Left + (rect.Width / 2), rect.Top));
                points["left"] = CU.ToSimUnits(new Vector2(rect.Left, rect.Top + (rect.Height / 2)));
                points["width"] = CU.ToSimUnits(new Vector2(rect.Left + rect.Width, rect.Top + (rect.Height / 2)));
                points["height"] = CU.ToSimUnits(new Vector2(rect.Left + (rect.Width / 2), rect.Top + rect.Height));

                GI.ModeGUI.Designer.SelectedObject = rect;
            }

            return rect;
        }

        protected override void TransformSelected(GameTime gameTime)
        {
            if (GI.Control.KeyboardPressed(Keys.Delete))
            {
                GI.DB.Delete(selected);
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
                selected.Width += (int)trans.X;
                selected.Height += (int)trans.Y;
            }
            else
            {
                selected.Left += (int)trans.X;
                selected.Top += (int)trans.Y;
            }                
        }

        protected override void SelectedMovePoint(ref Vector2 mouse, ref Vector2 localMouse)
        {
            switch (dragPoint)
            { 
                case "top":
                    selected.Top = (int)CU.ToDisplayUnits(localMouse).Y;
                    localMouse.X = CU.ToSimUnits(selected.Left + (selected.Width / 2));
                    break;
                case "left":
                    break;
                case "width":
                    break;
                case "height":
                    break;
            }
        }

        protected override Matrix World()
        {
            return Matrix.Identity;
        }

        protected override Matrix WorldToLocal()
        {
            return Matrix.Identity;
        }
        #endregion

        #region Member - Draw
        public override void Draw(GameTime gameTime)
        {
            foreach (var r in GI.DB.Select<GUIRect>().ToArray())
            {
                _drawRect(r);
            }

            base.Draw(gameTime);
        }
        #endregion
    }
}
