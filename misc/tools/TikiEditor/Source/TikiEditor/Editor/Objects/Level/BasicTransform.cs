using System.Linq;
using Microsoft.Xna.Framework;
using Database.GDB;

namespace TikiEditor.Objects
{
    public abstract class BasicTransform : DataBaseObject
    {
        #region Vars
        private float _x;
        private float _y;

        private float _scale = 1.0f;

        private float _rotation;
        #endregion

        #region Init
        public BasicTransform()
        { 
        }

        public BasicTransform(Vector2 pos)
        {
            _x = pos.X;
            _y = pos.Y;
        }
        #endregion

        #region Properties
        [DataField("PositionX")]
        public float PositionX
        {
            get { return _x; }
            set { SetProperty(ref _x, value, "PositionX"); }
        }

        [DataField("PositionY")]
        public float PositionY
        {
            get { return _y; }
            set { SetProperty(ref _y, value, "PositionY"); }
        }

        [DataField("Rotation")]
        public virtual float Rotation
        {
            get { return _rotation; }
            set { SetProperty(ref _rotation, value, "Rotation"); }
        }

        [DataField("Scale")]
        public virtual float Scale
        {
            get { return _scale; }
            set { SetProperty(ref _scale, value, "Scale"); }
        }
        #endregion

        #region Properties - Convert
        public Vector2 Position
        {
            get { return new Vector2(_x, _y); }
            set
            {
                this.PositionX = value.X;
                this.PositionY = value.Y;
            }
        }
      
        #endregion

        #region Properties - Dynamic
        public Matrix WorldMatrix
        {
            get
            {
                return Matrix.CreateScale(
                    new Vector3(this.Scale)
                ) * Matrix.CreateRotationZ(
                    _rotation
                ) * Matrix.CreateTranslation(
                    new Vector3(this.Position, 0)
                );
            }
        }

        public RectangleF BoundingBox
        {
            get
            {
                Vector2[] vertices = this.Vertices;

                float x = vertices.Min(v => v.X);
                float y = vertices.Min(v => v.Y);

                return new RectangleF(
                    x,
                    y,
                    vertices.Max(v => v.X) - x,
                    vertices.Max(v => v.Y) - y
                );
            }
        }

        public Vector2[] Vertices
        {
            get
            {
                Matrix world = this.WorldMatrix;
                Vector2[] vertices = new Vector2[]
                {
                    new Vector2(-0.5f, -0.5f),
                    new Vector2( 0.5f, -0.5f),
                    new Vector2( 0.5f,  0.5f),
                    new Vector2(-0.5f,  0.5f)
                };

                return vertices.Select(v => Vector2.Transform(v, world)).ToArray();
            }
        }
        #endregion
    }
}
