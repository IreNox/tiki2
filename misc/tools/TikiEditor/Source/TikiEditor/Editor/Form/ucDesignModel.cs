using System;
using System.IO;
using System.Linq;
using System.Windows.Forms;
using System.Collections.Generic;

namespace TikiEditor
{
    public partial class ucDesignModel : UserControl
    {
        #region Init
        public ucDesignModel()
        {
            InitializeComponent();
        }
        #endregion

        #region Member - EventHandler
        private void buttonSearchOutput_Click(object sender, EventArgs e)
        {
            if (FileDialog.ShowDialog() != DialogResult.Cancel)
            {
                textOutputFilename.Text = FileDialog.FileName;
            }
        }

        private void buttonSearchInput_Click(object sender, EventArgs e)
        {
            if (FolderDialog.ShowDialog() != DialogResult.Cancel)
            {
                textInputPath.Text = FolderDialog.SelectedPath;
            }
        }

        private void textInputPrefix_TextChanged(object sender, EventArgs e)
        {
            listInputs.DataSource = Directory.GetFiles(textInputPath.Text).Where(f => f.IndexOf(textInputPrefix.Text, StringComparison.CurrentCultureIgnoreCase) != -1).Select(f => Path.GetFileNameWithoutExtension(f).ToLower().Replace(textInputPrefix.Text.ToLower(), "")).ToList();
        }

        private void buttonExecute_Click(object sender, EventArgs e)
        {
            FBXImport import = new FBXImport();
            import.InputFilenames.AddRange(
                Directory.GetFiles(textInputPath.Text).Where(f => f.IndexOf(textInputPrefix.Text, StringComparison.CurrentCultureIgnoreCase) != -1)
            );
            import.OutputFilename = textOutputFilename.Text;

            import.Execute();
        }
        #endregion
    }
}
