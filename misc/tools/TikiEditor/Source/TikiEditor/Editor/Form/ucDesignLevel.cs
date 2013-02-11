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

        private void _addObjectByType(int type)
        {
            LevelObject obj = new LevelObject();
            obj.Type = type;
            obj.Position = CU.ToSimUnits(GI.Camera.CurrentPositionCenter);

            GI.ModeLevel.Level.Objects.Add(obj);
        }

        private void _addPointByType(int type)
        {
            LevelPoint p = new LevelPoint();
            p.Type = type;
            p.Position = CU.ToSimUnits(GI.Camera.CurrentPositionCenter);

            GI.ModeLevel.Level.Points.Add(p);
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

        private void trackBar1_Scroll(object sender, EventArgs e)
        {
            GI.ModeLevel.LevelDraw.Scale = (float)trackBar1.Value / 100.0f;
        }
        #endregion

        #region Member - EventHandler - Add - Objects
        private void buttonAddObject_Click(object sender, EventArgs e)
        {
            _addObjectByType(0);
        }
        
        private void buttonAddPlayerBuilding_Click(object sender, EventArgs e)
        {
            _addObjectByType(11);
        }

        private void buttonAddEnemyBuilding_Click(object sender, EventArgs e)
        {
            _addObjectByType(10);
        }

        private void buttonAddPlayerMop_Click(object sender, EventArgs e)
        {
            _addObjectByType(1);
        }

        private void buttonAddEnvRock03_Click(object sender, EventArgs e)
        {
            _addObjectByType(8);
        }

        private void buttonAddEnvRock02_Click(object sender, EventArgs e)
        {
            _addObjectByType(7);
        }

        private void buttonAddEnvRock01_Click(object sender, EventArgs e)
        {
            _addObjectByType(6);
        }

        private void buttonAddEnvPipes_Click(object sender, EventArgs e)
        {
            _addObjectByType(5);
        }

        private void buttonAddEnvBuilding_Click(object sender, EventArgs e)
        {
            _addObjectByType(4);
        }

        private void buttonAddEnemyMop_Click(object sender, EventArgs e)
        {
            _addObjectByType(2);
        }

        private void buttonAddPlayerHero_Click(object sender, EventArgs e)
        {
            _addObjectByType(3);
        }
        #endregion

        #region Member - EventHandler - Add - Points
        private void buttonAddPoint_Click(object sender, EventArgs e)
        {
            _addPointByType(1);
        }

        private void buttonAddPointWaypoint_Click(object sender, EventArgs e)
        {
            _addPointByType(2);
        }

        private void buttonAddPointSpawnpoint_Click(object sender, EventArgs e)
        {
            _addPointByType(3);
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
