using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace TikiEditor.Designer
{
    internal partial class formMain : Form
    {
        #region Init
        public formMain()
        {
            InitializeComponent();
        }
        #endregion

        #region Member
        public void UpdateGame()
        {
            if (GI.Control != null)
            {
                Point p = this.PointToClient(panelViewport.PointToScreen(Point.Empty));

                GI.Control.MouseOffset = new Microsoft.Xna.Framework.Point(
                    (p.X) * -1,
                    (p.Y) * -1
                );
            }
        }
        #endregion

        #region Member - EventHandler
        private void panelViewport_SizeChanged(object sender, EventArgs e)
        {
            Program.Game.Reset(
                panelViewport.Width,
                panelViewport.Height,
                false
            );
        }

        private void formMain_FormClosed(object sender, FormClosedEventArgs e)
        {
            Program.Game.Exit();
        }
        #endregion

        #region Properties
        public ucDesign Designer
        {
            get { return ucDesign1; }
        }

        public bool DesignShow
        {
            get { return !splitContainer1.Panel1Collapsed; }
            set { splitContainer1.Panel1Collapsed = !value; }
        }
        #endregion
    }
}