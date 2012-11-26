using System;
using System.IO;
using System.Linq;
using System.Windows.Forms;
using System.Collections.Generic;

namespace TikiEditor
{
    public partial class ucDesignModel : UserControl
    {
        #region Vars
        private List<InputModel> _inputs = new List<InputModel>();
        private List<InputModel> _inputsSelected = new List<InputModel>();
        #endregion

        #region Init
        public ucDesignModel()
        {
            InitializeComponent();

            if (String.IsNullOrEmpty(Properties.Settings.Default.ModelOutput))
            {
                FileDialog.InitialDirectory = Path.Combine(Path.GetDirectoryName(Path.GetDirectoryName(Application.ExecutablePath)), "Data/Models");
            }

            textInputPrefix.Text = Properties.Settings.Default.ModelPrefix;
            FolderDialog.SelectedPath = Properties.Settings.Default.ModelInputPath;
            textInputPath.Text = Properties.Settings.Default.ModelInputPath;
            textOutputFilename.Text = Properties.Settings.Default.ModelOutput;
        }
        #endregion

        #region Private Member
        private List<InputModel> getFiles()
        {
            if (!Directory.Exists(textInputPath.Text))
            {
                return new List<InputModel>();
            }

            _inputsSelected = _inputs.Where(
                i => Path.GetFileName(i.FileName).StartsWith(textInputPrefix.Text, StringComparison.CurrentCultureIgnoreCase)
            ).ToList();

            return _inputsSelected;
        }
        #endregion

        #region Member - EventHandler
        private void buttonSearchOutput_Click(object sender, EventArgs e)
        {
            if (!String.IsNullOrEmpty(textInputPrefix.Text))
            {
                FileDialog.FileName = textInputPrefix.Text.Trim('-', ' ', '_');
            }
            else if (listAnimations.SelectedItems.Count != 0)
            {
                FileDialog.FileName = ((InputModel)listAnimations.SelectedItem).Name.Trim('-', ' ', '_');
            }

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

        private void textInputPath_TextChanged(object sender, EventArgs e)
        {
            _inputs.Clear();

            foreach (string file in Directory.GetFiles(textInputPath.Text))
            {
                _inputs.Add(
                    new InputModel("", file)
                );
            }

            textInputPrefix_TextChanged(null, null);
        }

        private void textInputPrefix_TextChanged(object sender, EventArgs e)
        {
            foreach (var i in getFiles())
            {
                if (!i.NameChanged)
                {
                    i.Name = Path.GetFileNameWithoutExtension(i.FileName).ToLower().Substring(textInputPrefix.Text.Length);
                    i.NameChanged = false;
                }
            }

            listAnimations.DataSource = getFiles();
            listAnimations.DisplayMember = "Name";

            Properties.Settings.Default.ModelPrefix = textInputPrefix.Text;
            Properties.Settings.Default.Save();
        }

        private void listInputs_SelectedIndexChanged(object sender, EventArgs e)
        {
            ucProperties1.CurrentObject = listAnimations.SelectedValue;
        }

        private void buttonLoadMeshes_Click(object sender, EventArgs e)
        {

        }

        private void buttonSave_Click(object sender, EventArgs e)
        {
            ucProperties1.Save();
            textInputPrefix_TextChanged(null, null);
        }

        private void buttonExecute_Click(object sender, EventArgs e)
        {
            FBXImport import = new FBXImport();

            foreach (InputModel i in listAnimations.SelectedItems)
            {
                import.InputFilenames.Add(i.Name, i.FileName);
            }

            import.OutputFilename = textOutputFilename.Text;
            import.Execute();
        }
        #endregion

        #region Class - InputModel
        public class InputModel
        {
            #region Vars
            private string _name;
            private string _fileName;

            private bool _nameChanged = false;
            #endregion

            #region Init
            public InputModel(string name, string fileName)
            {
                _name = name;
                _fileName = fileName;
            }
            #endregion

            #region Properties
            public string Name
            {
                get { return _name; }
                set
                {
                    _name = value;
                    _nameChanged = true;
                }
            }

            public string FileName
            {
                get { return _fileName; }
            }

            [System.ComponentModel.Browsable(false)]
            public bool NameChanged
            {
                get { return _nameChanged; }
                set { _nameChanged = value; }
            }
            #endregion
        }
        #endregion
    }
}
