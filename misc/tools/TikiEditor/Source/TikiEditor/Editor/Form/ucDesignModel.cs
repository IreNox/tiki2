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

            textInputPrefix.Text = Properties.Settings.Default.ModelPrefix;

            if (String.IsNullOrEmpty(Properties.Settings.Default.ModelInputPath))
            {
                FolderDialog.SelectedPath = Properties.Settings.Default.ModelInputPath;
                FileDialog.InitialDirectory = Path.Combine(Path.GetDirectoryName(Path.GetDirectoryName(Application.ExecutablePath)), "Data/Models");
                textInputPath.Text = FolderDialog.SelectedPath;
            }
            else
            {
                textInputPath.Text = Properties.Settings.Default.ModelInputPath;
            }
            textOutputFilename.Text = Properties.Settings.Default.ModelOutput;
        }
        #endregion

        #region Private Member
        private List<string> getFiles(bool fullPath)
        {
            if (!Directory.Exists(textInputPath.Text))
            {
                return new List<string>();
            }

            var a = Directory.GetFiles(textInputPath.Text).Where(
                f => Path.GetFileName(f).StartsWith(textInputPrefix.Text, StringComparison.CurrentCultureIgnoreCase)
            );

            if (fullPath)
            {
                return a.ToList();
            }

            return a.Select(
                f => Path.GetFileNameWithoutExtension(f).ToLower().Substring(textInputPrefix.Text.Length)
            ).ToList();
        }
        #endregion

        #region Member - EventHandler
        private void buttonSearchOutput_Click(object sender, EventArgs e)
        {
            FileDialog.FileName = textInputPrefix.Text.Trim('-', ' ', '_');

            if (FileDialog.ShowDialog() != DialogResult.Cancel)
            {
                textOutputFilename.Text = FileDialog.FileName;

                Properties.Settings.Default.ModelOutput = FileDialog.FileName;
                Properties.Settings.Default.Save();

            }
        }

        private void buttonSearchInput_Click(object sender, EventArgs e)
        {
            if (FolderDialog.ShowDialog() != DialogResult.Cancel)
            {
                textInputPath.Text = FolderDialog.SelectedPath;

                Properties.Settings.Default.ModelInputPath = FolderDialog.SelectedPath;
                Properties.Settings.Default.Save();
            }
        }

        private void textInputPrefix_TextChanged(object sender, EventArgs e)
        {
            listInputs.DataSource = getFiles(false);

            Properties.Settings.Default.ModelPrefix = textInputPrefix.Text;
            Properties.Settings.Default.Save();
        }

        private void buttonExecute_Click(object sender, EventArgs e)
        {
            FBXImport import = new FBXImport();
            import.InputFilenames.AddRange(
                getFiles(true)
            );
            import.OutputFilename = textOutputFilename.Text;

            import.Execute();
        }
        #endregion
    }
}
