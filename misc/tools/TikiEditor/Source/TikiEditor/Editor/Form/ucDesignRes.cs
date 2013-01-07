using System;
using System.IO;
using System.Linq;
using System.Threading;
using System.Collections.Generic;
using System.Windows.Forms;
using TikiEditor.Objects;

namespace TikiEditor
{
    public partial class ucDesignRes : UserControl
    {
        #region Init
        public ucDesignRes()
        {
            InitializeComponent();
        }
        #endregion

        #region Private Member - Thread
        private void _threadWork()
        {
            _threadWorkDir(GI.DataPath, null);


        }

        private void _threadWorkDir(string dir, TreeNode node)
        {
            if (node != null)
            {
                foreach (string file in Directory.GetFiles(dir))
                {
                    ResData res = new ResData();
                    res.LoadFromFile(file);

                    _threadAddNode(file, node);

                    GI.DB.Insert(res);
                }
            }
            else
            {
                node = _threadAddNode(dir, null);
            }

            foreach (string dir2 in Directory.GetDirectories(dir))
            {
                _threadWorkDir(
                    dir2,
                    _threadAddNode(dir2, node)
                );
            }
        }

        private TreeNode _threadAddNode(string fileName, TreeNode parent)
        {
            if (treeView1.InvokeRequired)
            {
                return (TreeNode)treeView1.Invoke(new Func<string, TreeNode, TreeNode>(_threadAddNode), fileName, parent);
            }

            TreeNode node;

            if (parent == null)
            {
                node = treeView1.Nodes.Add(
                    Path.GetFileNameWithoutExtension(fileName)
                );
            }
            else
            {
                node = parent.Nodes.Add(
                    Path.GetFileNameWithoutExtension(fileName)
                );
            }

            treeView1.ExpandAll();
            return node;
        }

        private void _threadFinish()
        {
            if (this.InvokeRequired)
            {
                this.Invoke(new Action(_threadFinish));
                return;
            }

            MessageBox.Show(this, "Resource Convert finish!", "TikiEditor 2.0", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }
        #endregion

        #region Member - EventHandler
        private void buttonDoit_Click(object sender, EventArgs e)
        {
            Thread thread = new Thread(_threadWork);
            thread.Start();
        }
        #endregion
    }
}