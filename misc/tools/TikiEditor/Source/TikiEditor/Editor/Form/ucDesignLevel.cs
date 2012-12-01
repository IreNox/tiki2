using System;
using System.Drawing;
using System.Windows.Forms;
using System.IO;
using System.Text;
using TikiEditor.Objects;

namespace TikiEditor.Designer
{
    internal partial class ucDesignLevel : UserControl
    {
        #region Vars
        private DataBaseObject _object;
        #endregion

        #region Init
        public ucDesignLevel()
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
            GI.ModeLevel.Level.Objects.Add(
                new LevelObject()
            );
        }

        private void buttonSave_Click(object sender, EventArgs e)
        {
            ucProperties1.Save();
        }

        private void checkShowPoints_CheckedChanged(object sender, EventArgs e)
        {
            GI.ModeLevel.LevelDraw.ShowPoints = checkShowPoints.Checked;
        }

        private void checkShowBoundingBox_CheckedChanged(object sender, EventArgs e)
        {
            GI.ModeLevel.LevelDraw.ShowBounding = checkShowBoundingBox.Checked;
        }
        #endregion

        #region Member - EventHandler - Add
        private void buttonAddObject_Click(object sender, EventArgs e)
        {
            GI.ModeLevel.Level.Objects.Add(
                new LevelObject()
            );
        }
        
        private void buttonAddPoint_Click(object sender, EventArgs e)
        {
            GI.ModeLevel.Level.Points.Add(
                new LevelPoint()
            );
        }

        private void buttonAddEnemyBasic_Click(object sender, EventArgs e)
        {
            GI.ModeLevel.Level.Enemies.Add(
                new LevelEnemy()
            );
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
