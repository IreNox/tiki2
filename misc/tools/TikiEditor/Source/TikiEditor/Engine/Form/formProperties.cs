using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace TikiEditor.Designer
{
    public partial class formProperties : Form
    {
        #region Init
        public formProperties()
        {
            InitializeComponent();
        }
        #endregion

        #region Member - EventHandler
        private void buttonOk_Click(object sender, EventArgs e)
        {
            ucProperties1.Save();

            this.DialogResult = DialogResult.OK;
            this.Close();
        }

        private void buttonCancel_Click(object sender, EventArgs e)
        {
            this.DialogResult = DialogResult.Cancel;
            this.Close();
        }
        #endregion

        #region Properties
        public object Object
        {
            get { return ucProperties1.CurrentObject; }
            set { ucProperties1.CurrentObject = value; }
        }
        #endregion
    }
}
