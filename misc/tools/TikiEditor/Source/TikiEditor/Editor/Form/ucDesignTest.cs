using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace TikiEditor
{
    public partial class ucDesignTest : UserControl
    {
        public ucDesignTest()
        {
            InitializeComponent();
        }

        public object SelectedObject
        {
            get { return ucProperties1.CurrentObject; }
            set { ucProperties1.CurrentObject = value; }
        }

        private void buttonSave_Click(object sender, EventArgs e)
        {
            ucProperties1.Save();
        }
    }
}
