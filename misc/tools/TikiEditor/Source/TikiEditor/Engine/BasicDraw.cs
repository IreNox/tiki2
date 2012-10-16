using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using TikiEditor.Objects;

namespace TikiEditor
{
    public class BasicDraw : DrawableGameComponent
    {
        #region Vars
        private Level _level;
        private PolygonBatch _batch;

        private bool _showPoints = false;
        private bool _showBounding = false;

        private SpriteFont _font;        

        private string _dragPoint = null;
        private Dictionary<string, Vector2> _points = new Dictionary<string, Vector2>();
        private Dictionary<string, Color> _pointColors = new Dictionary<string, Color>()
        {
            { "pos", Color.Blue },
            { "size", Color.Green },
            { "rotation", Color.Red },
            { "test", Color.White }
        };

        private BasicTransform _selected = null;
        #endregion

        #region Init
        public BasicDraw()
            : base(GI.Game)
        {
            _level = GI.Level;

            this.Reset();
        }
        #endregion

        #region Private Member
        private BasicTransform _getTransformAtPoint(Vector2 point)
        {
            return _level.AllTransforms.FirstOrDefault(t => t.BoundingBox.Contains(point));
        }

        private void _drawRect(Vector2 pos, Vector2 size, Color color)
        {
            Vector2 half = size / 2;

            _batch.DrawLine(new Vector2(pos.X - half.X, pos.Y - half.Y), new Vector2(pos.X + half.X, pos.Y - half.Y), color);
            _batch.DrawLine(new Vector2(pos.X + half.X, pos.Y - half.Y), new Vector2(pos.X + half.X, pos.Y + half.Y), color);
            _batch.DrawLine(new Vector2(pos.X + half.X, pos.Y + half.Y), new Vector2(pos.X - half.X, pos.Y + half.Y), color);
            _batch.DrawLine(new Vector2(pos.X - half.X, pos.Y + half.Y), new Vector2(pos.X - half.X, pos.Y - half.Y), color);
        }
        #endregion

        #region Private Member - Draw
        private void _drawBasicTransform(BasicTransform bt)
        {
            Vector2[] vertices = bt.Vertices;

            _batch.Draw(
                vertices,
                new Color(0, 0, 1, 0.5f)
            );

            _batch.DrawLine(
                vertices,
                (_selected == bt ? Color.Red : Color.Blue)
            );
        }
        #endregion

        #region Private Member - Update - Selection
        private void _updateSelection(GameTime gameTime)
        {
            Vector2 mouse = GI.Control.MouseSimVector();

            if (GI.Control.MouseUp(MouseButtons.Left) && _dragPoint != null)
            {
                _selected.DatabaseEnabled = true;
                _dragPoint = null;
            }

            if (GI.Control.MouseClick(MouseButtons.Left) && _dragPoint == null)
            {
                BasicTransform bt = _getTransformAtPoint(mouse);

                if (bt != null)
                {
                    _points.Clear();

                    _points["pos"] = Vector2.Zero;
                    _points["size"] = new Vector2(bt.Scale / 2);
                    _points["rotation"] = new Vector2(
                        (float)Math.Sin(bt.Rotation),
                        (float)Math.Cos(bt.Rotation)
                    );

                    _selected = bt;
                    Program.Form.Designer.SelectedObject = bt;
                }
                else
                {
                    _selected = null;
                    Program.Form.Designer.SelectedObject = _level;
                }
            }

            if (_showPoints && _selected != null)
            {
                Matrix matrix = Matrix.CreateTranslation(
                    -new Vector3(_selected.Position, 0)
                ) * Matrix.CreateScale(
                    new Vector3(
                        1.0f / _selected.Scale
                    )
                ) * Matrix.CreateRotationZ(
                    -_selected.Rotation
                );

                Vector2 localMouse = Vector2.Transform(mouse, matrix);
                _points["test"] = localMouse;

                if (GI.Control.MouseDown(MouseButtons.Left) && _dragPoint == null)
                {
                    foreach (var kvp in _points)
                    {
                        if (kvp.Value.ToRectangle(Vector2.One / 20).Contains(localMouse) && kvp.Key != "test")
                        {
                            _selected.DatabaseEnabled = false;
                            _dragPoint = kvp.Key;
                        }
                    }
                }
                else if (_dragPoint != null)
                {
                    switch (_dragPoint)
                    {
                        case "pos":
                            _selected.Position = mouse;
                            break;
                        case "size":
                            _selected.Scale = (localMouse.X + localMouse.Y);
                            localMouse = new Vector2(_selected.Scale / 2);
                            break;
                        case "rotation":
                            _selected.Rotation = (float)Math.Atan2(localMouse.Y, localMouse.X);
                            break;
                    }

                    _points[_dragPoint] = localMouse;
                }
            }
        }
        #endregion

        #region Private Member - Update - Transform
        private void _updateTransform(GameTime gameTime)
        {
            if (_selected != null)
            {
                if (GI.Control.KeyboardPressed(Keys.Delete))
                {
                    GI.Level.RemoveTransform(_selected);
                    _selected = null;
                    return;
                }

                Vector2 trans = (new Vector2(
                    (GI.Control.KeyboardDown(Keys.Left) ? -1 : 0) + (GI.Control.KeyboardDown(Keys.Right) ? 1 : 0),
                    (GI.Control.KeyboardDown(Keys.Up) ? -1 : 0) + (GI.Control.KeyboardDown(Keys.Down) ? 1 : 0)
                ) * ((float)gameTime.ElapsedGameTime.TotalSeconds * (GI.Control.KeyboardDown(Keys.RightShift) ? 5 : 1))) -
                (GI.Control.MouseDown(MouseButtons.Left) && _dragPoint == null ? GI.Control.MouseDistanceSim() : Vector2.Zero);

                if (trans == Vector2.Zero)
                {
                    if (!_selected.DatabaseEnabled && _dragPoint == null) _selected.DatabaseEnabled = true;
                    return;
                }
                else
                {
                    if (_selected.DatabaseEnabled) _selected.DatabaseEnabled = false;
                }

                if (GI.Control.KeyboardDown(Keys.RightControl))
                {
                    _selected.Scale += trans.Length();
                }
                else if (GI.Control.KeyboardDown(Keys.RightAlt))
                {
                    _selected.Rotation -= trans.X;
                    _selected.Rotation -= trans.Y;
                }
                else
                {
                    _selected.Position += trans;
                }
            }
        }
        #endregion

        #region Member
        public void Reset()
        {
            _batch = GI.PolygonBatch;

            _font = GI.Content.Load<SpriteFont>("font");
        }
        #endregion

        #region Member - XNA - Draw
        public override void Draw(GameTime gameTime)
        {
            //string text = String.Format("Mouse: {0}\nActive: {1}\n", GI.Control.MouseSimVector(), Program.Form.panelViewport.Focused);

            //if (_selected != null)
            //{
            //    text += String.Format(
            //        "Position: {0}\nScale:{1}\nRotation: {2}",
            //        _selected.Position,
            //        _selected.Scale,
            //        _selected.Rotation
            //    );
            //}

            //GI.SpriteBatch.DrawString(
            //    _font,
            //    text,
            //    GI.Camera.CurrentPositionNagativ,
            //    Color.White
            //);

            foreach (BasicTransform transform in _level.AllTransforms)
            {
                _drawBasicTransform(transform);
            }

            if (_showBounding)
            {
                foreach (BasicTransform bt in _level.AllTransforms)
                {
                    var rect = bt.BoundingBox;

                    _drawRect(
                        rect.Position + (rect.Size / 2),
                        rect.Size,
                        (bt == _selected ? Color.Green : Color.Black)
                    );
                }
            }

            _drawRect(
                GI.Control.MouseSimVector(),
                Vector2.One / 20,
                Color.Black
            );

            if (_showPoints && _selected != null)
            {
                foreach (var kvp in _points)
                {
                    _drawRect(
                        Vector2.Transform(kvp.Value, _selected.WorldMatrix),
                        Vector2.One / 20,
                        (_pointColors.ContainsKey(kvp.Key) ? _pointColors[kvp.Key] : Color.Black)
                    );
                }
            }
        }
        #endregion

        #region Member - XNA - Update
        public override void Update(GameTime gameTime)
        {
            _updateSelection(gameTime);
            _updateTransform(gameTime);
        }
        #endregion

        #region Properties
        public bool ShowPoints
        {
            get { return _showPoints; }
            set { _showPoints = value; }
        }

        public bool ShowBounding
        {
            get { return _showBounding; }
            set { _showBounding = value; }
        }
        #endregion
    }
}
