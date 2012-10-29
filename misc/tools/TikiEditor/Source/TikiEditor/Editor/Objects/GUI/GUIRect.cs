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
        private int _index;

        private string _key;
        private string _control;

        private float top;
        private float left;
        private float width;
        private float height;
        #endregion

        #region Properties
        [DataField("ArrayIndex")]
        public int ArrayIndex
        {
            get { return _index; }
            set { SetProperty(ref _index, value, "ArrayIndex"); }
        }

        [DataField("Control")]
        public string Control
        {
            get { return _control; }
            set { SetProperty(ref _control, value, "Control"); }
        }
        
        [DataField("Key")]
        public string Key
        {
            get { return _key; }
            set { SetProperty(ref _key, value, "Key"); }
        }

        [DataField("Top")]
        public float Top
        {
            get { return top; }
            set { SetProperty(ref top, value, "Top"); }
        }

        [DataField("Left")]
        public float Left
        {
            get { return left; }
            set { SetProperty(ref left, value, "Left"); }
        }

        [DataField("Width")]
        public float Width
        {
            get { return width; }
            set { SetProperty(ref width, value, "Width"); }
        }

        [DataField("Height")]
        public float Height
        {
            get { return height; }
            set { SetProperty(ref height, value, "Height"); }
        }
        #endregion

        #region Properties - Dynamic
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
