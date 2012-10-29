using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using TikiEditor.Objects;

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

        private void buttonCreate_Click(object sender, EventArgs e)
        {
            GUIRect rect = new GUIRect();

            rect.Top = 256;
            rect.Left = 256;
            rect.Width = 100;
            rect.Height = 100;

            GI.DB.Insert(rect);
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
