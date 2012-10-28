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
    public abstract class DrawBasic<T> : DrawableGameComponent
        where T : DataBaseObject
    {
        #region Vars
        protected PolygonBatch batch;

        protected bool showPoints = false;
        protected bool showBounding = false;

        protected string dragPoint = null;
        protected Dictionary<string, Vector2> points = new Dictionary<string, Vector2>();
        protected Dictionary<string, Color> pointColors = new Dictionary<string, Color>();

        protected T selected = null;
        #endregion

        #region Init
        public DrawBasic()
            : base(GI.Game)
        {
            this.Reset();
        }
        #endregion

        #region Protected Member
        protected void drawRect(Vector2 pos, Vector2 size, Color color)
        {
            Vector2 half = size / 2;

            batch.DrawLine(new Vector2(pos.X - half.X, pos.Y - half.Y), new Vector2(pos.X + half.X, pos.Y - half.Y), color);
            batch.DrawLine(new Vector2(pos.X + half.X, pos.Y - half.Y), new Vector2(pos.X + half.X, pos.Y + half.Y), color);
            batch.DrawLine(new Vector2(pos.X + half.X, pos.Y + half.Y), new Vector2(pos.X - half.X, pos.Y + half.Y), color);
            batch.DrawLine(new Vector2(pos.X - half.X, pos.Y + half.Y), new Vector2(pos.X - half.X, pos.Y - half.Y), color);
        }
        #endregion
        
        #region Private Member - Update - Selection
        private void _updateSelection(GameTime gameTime)
        {
            Vector2 mouse = GI.Control.MouseSimVector();

            if (GI.Control.MouseUp(MouseButtons.Left) && dragPoint != null)
            {
                selected.DatabaseEnabled = true;
                dragPoint = null;
            }

            if (GI.Control.MouseClick(MouseButtons.Left) && dragPoint == null)
            {
                selected = this.SelectObjectOnPoint(mouse);
            }

            if (showPoints && selected != null)
            {
                Matrix matrix = this.WorldToLocal();
                Vector2 localMouse = Vector2.Transform(mouse, matrix);

                if (GI.Control.MouseDown(MouseButtons.Left) && dragPoint == null)
                {
                    foreach (var kvp in points)
                    {
                        if (kvp.Value.ToRectangle(Vector2.One / 20).Contains(localMouse) && kvp.Key != "test")
                        {
                            selected.DatabaseEnabled = false;
                            dragPoint = kvp.Key;
                        }
                    }
                }
                else if (dragPoint != null)
                {
                    this.SelectedMovePoint(ref mouse, ref localMouse);
                    points[dragPoint] = localMouse;
                }
            }
        }
        #endregion

        #region Private Member - Update - Transform
        private void _updateTransform(GameTime gameTime)
        {
            if (selected != null)
            {
                this.TransformSelected(gameTime);
            }
        }
        #endregion

        #region Member
        public void Reset()
        {
            batch = GI.PolygonBatch;
        }
        #endregion

        #region Member - Abstract
        protected abstract T SelectObjectOnPoint(Vector2 mouse);
        protected abstract void TransformSelected(GameTime gameTime);
        protected abstract void SelectedMovePoint(ref Vector2 mouse, ref Vector2 localMouse);

        protected abstract Matrix World();
        protected abstract Matrix WorldToLocal();
        #endregion

        #region Member - XNA - Draw
        public override void Draw(GameTime gameTime)
        {
            drawRect(
                GI.Control.MouseSimVector(),
                Vector2.One / 20,
                Color.Black
            );

            if (showPoints && selected != null)
            {
                foreach (var kvp in points)
                {
                    drawRect(
                        Vector2.Transform(kvp.Value, this.World()),
                        Vector2.One / 20,
                        (pointColors.ContainsKey(kvp.Key) ? pointColors[kvp.Key] : Color.Black)
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
            get { return showPoints; }
            set { showPoints = value; }
        }

        public bool ShowBounding
        {
            get { return showBounding; }
            set { showBounding = value; }
        }
        #endregion
    }
}
