﻿using System;
using System.Drawing;
using System.Windows.Forms;
using System.IO;
using System.Text;
using TikiEditor.Objects;

namespace TikiEditor.Designer
{
    internal partial class ucDesign : UserControl
    {
        #region Vars
        private DataBaseObject _object;
        #endregion

        #region Init
        public ucDesign()
        {
            InitializeComponent();
        }
        #endregion

        #region Private Member
        private void _selectObject(DataBaseObject obj)
        {
            _object = obj;
            ucProperties1.CurrentObject = obj;

            if (obj == null) return;

            labelType.Text = obj.GetType().Name;
            labelName.Text = "ID: " + obj.ID.ToString();
        }
        #endregion

        #region Member - EventHandler
        private void buttonNew_Click(object sender, EventArgs e)
        {
            GI.Level.Objects.Add(
                new LevelObject()
            );
        }

        private void buttonSave_Click(object sender, EventArgs e)
        {
            ucProperties1.Save();
        }

        private void buttonAddObject_Click(object sender, EventArgs e)
        {
            GI.Level.Objects.Add(
                new LevelObject()
            );
        }

        private void checkShowPoints_CheckedChanged(object sender, EventArgs e)
        {
            GI.BasicDraw.ShowPoints = checkShowPoints.Checked;
        }

        private void checkShowBoundingBox_CheckedChanged(object sender, EventArgs e)
        {
            GI.BasicDraw.ShowBounding = checkShowBoundingBox.Checked;
        }
        #endregion

        #region Properties
        public DataBaseObject SelectedObject
        {
            get { return _object; }
            set { _selectObject(value); }
        }
        #endregion
    }
}
