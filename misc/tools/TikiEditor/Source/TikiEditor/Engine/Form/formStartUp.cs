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
        public formStartUp()
        {
            InitializeComponent();
        }

        private void buttonLevel_Click(object sender, EventArgs e)
        {
            GI.ModeLevel = new ModeLevel(GI.Game);
            this.Close();
        }

        private void buttonGUI_Click(object sender, EventArgs e)
        {
            GI.ModeGUI = new ModeGUI(GI.Game);
            this.Close();
        }

        private void buttonTest_Click(object sender, EventArgs e)
        {
            GI.ModeTest = new ModeTest(GI.Game);
            this.Close();
        }
    }
}
