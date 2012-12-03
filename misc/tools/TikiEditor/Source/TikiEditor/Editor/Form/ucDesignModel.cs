using System;
using System.IO;
using System.Linq;
using System.Windows.Forms;
using System.Collections.Generic;
using TikiEditor.Designer;

namespace TikiEditor
{
    public partial class ucDesignModel : UserControl
    {
        #region Vars
        private List<INAnimation> _inputs = new List<INAnimation>();
        private List<INAnimation> _inputsSelected = new List<INAnimation>();

        private List<INMesh> _inputMeshes = new List<INMesh>();
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
        private List<INAnimation> getFiles()
        {
            if (!Directory.Exists(textInputPath.Text))
            {
                return new List<INAnimation>();
            }

            _inputsSelected = _inputs.Where(
                i => Path.GetFileName(i.FileName).StartsWith(textInputPrefix.Text, StringComparison.CurrentCultureIgnoreCase)
            ).ToList();

            return _inputsSelected;
        }

        private void checkMeshTab()
        {
            if (listAnimations.SelectedItems.Count != 0)
            {
                if (!tabControl1.TabPages.Contains(tabMeshes)) tabControl1.TabPages.Add(tabMeshes);
            }
            else
            {
                tabControl1.TabPages.Remove(tabMeshes);
            }
        }
        #endregion

        #region Member - EventHandler
        private void textInputPath_TextChanged(object sender, EventArgs e)
        {
            _inputs.Clear();

            foreach (string file in Directory.GetFiles(textInputPath.Text))
            {
                _inputs.Add(
                    new INAnimation("", file)
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

            checkMeshTab();
        }

        private void listInputs_SelectedIndexChanged(object sender, EventArgs e)
        {
            checkMeshTab();

            ucProperties1.CurrentObject = listAnimations.SelectedValue;
        }

        private void listMeshes_SelectedIndexChanged(object sender, EventArgs e)
        {
            ucProperties1.CurrentObject = listMeshes.SelectedItem;
        }
        #endregion

        #region Member - EventHandler - Click
        private void buttonSearchOutput_Click(object sender, EventArgs e)
        {
            if (!String.IsNullOrEmpty(textInputPrefix.Text))
            {
                FileDialog.FileName = textInputPrefix.Text.Trim('-', ' ', '_');
            }
            else if (listAnimations.SelectedItems.Count != 0)
            {
                FileDialog.FileName = ((INAnimation)listAnimations.SelectedItem).Name.Trim('-', ' ', '_');
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

        private void buttonLoadMeshes_Click(object sender, EventArgs e)
        {
            tabControl1.TabPages.Remove(tabAnimations);

            FBXImport import = new FBXImport();
            var meshes = import.GetNames(listAnimations.SelectedItems.Cast<INAnimation>().First().FileName);

            string name = Path.GetFileNameWithoutExtension(textOutputFilename.Text);

            _inputMeshes = meshes.Select(m => new INMesh(name, m)).ToList();

            listMeshes.DataSource = _inputMeshes;
            listMeshes.DisplayMember = "Name";
        }

        private void buttonSave_Click(object sender, EventArgs e)
        {
            ucProperties1.Save();
            textInputPrefix_TextChanged(null, null);
        }

        private void buttonExecute_Click(object sender, EventArgs e)
        {
            FBXImport import = new FBXImport();

            foreach (INMesh m in _inputMeshes)
            {
                import.InputMaterials.Add(
                    new MeshMaterial() { Name = m.Name, TextureDiffuse = m.MatDiffuse, TextureNormal = m.MatNormal, TextureSpec = m.MatSpec, TextureLight = m.MatLight }
                );
            }

            foreach (INAnimation i in listAnimations.SelectedItems)
            {
                import.InputFilenames.Add(i.Name, i.FileName);
            }

            import.OutputFilename = textOutputFilename.Text;
            import.Execute();
        }
        #endregion

        #region Class - INAnimation
        public class INAnimation
        {
            #region Vars
            private string _name;
            private string _fileName;

            private bool _nameChanged = false;
            #endregion

            #region Init
            public INAnimation(string name, string fileName)
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

        #region Class - INMesh
        public class INMesh
        { 
            #region Vars
            private string _name;

            private string _matDiffuse;
            private string _matNormal;
            private string _matSpec;
            private string _matLight;
            #endregion

            #region Init
            public INMesh(string model, string name)
            {
                _name = name;

                _matDiffuse = String.Format("{0}/{1}_diff",   model, name);
                _matNormal  = String.Format("{0}/{1}_normal", model, name);
                _matSpec    = String.Format("{0}/{1}_spec",   model, name);
                _matLight   = String.Format("{0}/{1}_light",  model, name);
            }
            #endregion

            #region Properties
            [System.ComponentModel.Browsable(false)]
            public string Name
            {
                get { return _name; }
                set { _name = value; }
            }

            [SearchFile("Texture2D", "*.dds")]
            public string MatDiffuse
            {
                get { return _matDiffuse; }
                set { _matDiffuse = value; }
            }

            [SearchFile("Texture2D", "*.dds")]
            public string MatNormal
            {
                get { return _matNormal; }
                set { _matNormal = value; }
            }

            [SearchFile("Texture2D", "*.dds")]
            public string MatSpec
            {
                get { return _matSpec; }
                set { _matSpec = value; }
            }

            [SearchFile("Texture2D", "*.dds")]
            public string MatLight
            {
                get { return _matLight; }
                set { _matLight = value; }
            }
            #endregion
        }
        #endregion
    }
}
