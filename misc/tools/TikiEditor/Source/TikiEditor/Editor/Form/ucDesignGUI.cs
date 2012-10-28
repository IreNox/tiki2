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
    public partial class ucDesignGUI : UserControl
    {
        #region Init
        public ucDesignGUI()
        {
            InitializeComponent();
        }
        #endregion

        #region Member - EventHandler
        private void buttonSave_Click(object sender, EventArgs e)
        {
            ucProperties1.Save();
        }
        #endregion

        #region Properties
        public object SelectedObject
        {
            get { return ucProperties1.CurrentObject; }
            set { ucProperties1.CurrentObject = value; }
        }
        #endregion
    }
}
