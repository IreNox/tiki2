using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;

namespace TikiEditor
{
    public struct RectangleF
    {
        #region Vars
        public float X;
        public float Y;

        public float Width;
        public float Height;
        #endregion

        #region Init
        public RectangleF(float top, float left, float width, float height)
        {
            this.X = top;
            this.Y = left;

            this.Width = width;
            this.Height = height;
        }
        #endregion

        #region Member
        public bool Contains(Vector2 point)
        {
            return (point.X > this.X) &&
                   (point.Y > this.Y) &&
                   (point.X < this.Right) &&
                   (point.Y < this.Bottom);
        }
        #endregion

        #region Properties
        public float Top
        {
            get { return this.X; }
        }

        public float Left
        {
            get { return this.Y; }
        }

        public float Right
        {
            get { return this.X + this.Width; }
        }

        public float Bottom
        {
            get { return this.Y + this.Height; }
        }

        public Vector2 Position
        {
            get { return new Vector2(this.X, this.Y); }
        }

        public Vector2 Size
        {
            get { return new Vector2(this.Width, this.Height); }
        }

        //public Vector2[] Vertices
        //{
        //    get
        //    {
        //        return new Vector2[]
        //        {
        //            new Vector2(this.X,              this.Y),
        //            new Vector2(this.X + this.Width, this.Y),
        //            new Vector2(this.X + this.Width, this.Y + this.Height),
        //            new Vector2(this.X,              this.Y + this.Height)
        //        };
        //    }
        //}
        #endregion

        #region Operators
        public static implicit operator Rectangle(RectangleF rect)
        {
            return new Rectangle(
                (int)rect.X,
                (int)rect.Y,
                (int)rect.Width,
                (int)rect.Height
            );
        }
        #endregion
    }
}
