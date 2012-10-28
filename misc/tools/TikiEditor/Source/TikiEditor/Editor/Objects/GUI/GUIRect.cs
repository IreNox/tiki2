using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Database.GDB;
using Microsoft.Xna.Framework;

namespace TikiEditor.Objects
{
    [DataTable("tiki_gui")]
    public class GUIRect : DataBaseObject
    {
        #region Vars
        private int top;
        private int left;
        private int width;
        private int height;
        #endregion

        #region Properties
        [DataField("Top")]
        public int Top
        {
            get { return top; }
            set { SetProperty(ref top, value, "Top"); }
        }

        [DataField("Left")]
        public int Left
        {
            get { return left; }
            set { SetProperty(ref left, value, "Left"); }
        }

        [DataField("Width")]
        public int Width
        {
            get { return width; }
            set { SetProperty(ref width, value, "Width"); }
        }

        [DataField("Height")]
        public int Height
        {
            get { return height; }
            set { SetProperty(ref height, value, "Height"); }
        }
        #endregion

        #region Properties
        public Vector2[] Vertices
        {
            get
            {
                return new Vector2[]
                { 
                    CU.ToSimUnits(new Vector2(left, top)),
                    CU.ToSimUnits(new Vector2(left + width, top)),
                    CU.ToSimUnits(new Vector2(left + width, top + height)),
                    CU.ToSimUnits(new Vector2(left, top + height))
                };            
            }
        }

        public RectangleF Rect
        {
            get { return new RectangleF(left, top, width, height); }
        }
        #endregion
    }
}
