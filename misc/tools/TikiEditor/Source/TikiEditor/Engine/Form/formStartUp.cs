using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace TikiEditor
{
    public partial class formStartUp : Form
    {
        #region Init
        public formStartUp()
        {
            InitializeComponent();
            this.DialogResult = DialogResult.Cancel;
        }
        #endregion

        #region Private Member
        private void closeThis()
        {
            this.DialogResult = DialogResult.OK;
            this.Close();
        }
        #endregion

        #region Member - EventHandler
        private void buttonLevel_Click(object sender, EventArgs e)
        {
            GI.ModeLevel = new ModeLevel(
                GI.Game,
                Int32.Parse(textLevelId.Text)
            );
            closeThis();
        }

        private void buttonGUI_Click(object sender, EventArgs e)
        {
            GI.ModeGUI = new ModeGUI(GI.Game);
            closeThis();
        }

        private void buttonTest_Click(object sender, EventArgs e)
        {
            GI.ModeTest = new ModeTest(GI.Game);
            closeThis();
        }

        private void buttonModel_Click(object sender, EventArgs e)
        {
            GI.ModeModel = new ModeModel(GI.Game);
            closeThis();
        }

        private void formStartUp_FormClosed(object sender, FormClosedEventArgs e)
        {
            if (this.DialogResult == DialogResult.Cancel)
            {
                Program.Game.Exit();
            }
        }
        #endregion
    }
}
