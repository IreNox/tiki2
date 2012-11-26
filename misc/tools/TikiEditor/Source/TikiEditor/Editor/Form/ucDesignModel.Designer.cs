namespace TikiEditor
{
    partial class ucDesignModel
    {
        /// <summary> 
        /// Erforderliche Designervariable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary> 
        /// Verwendete Ressourcen bereinigen.
        /// </summary>
        /// <param name="disposing">True, wenn verwaltete Ressourcen gelöscht werden sollen; andernfalls False.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Vom Komponenten-Designer generierter Code

        /// <summary> 
        /// Erforderliche Methode für die Designerunterstützung. 
        /// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
        /// </summary>
        private void InitializeComponent()
        {
            this.label1 = new System.Windows.Forms.Label();
            this.textOutputFilename = new System.Windows.Forms.TextBox();
            this.buttonSearch = new System.Windows.Forms.Button();
            this.buttonExecute = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.textInputPrefix = new System.Windows.Forms.TextBox();
            this.textInputPath = new System.Windows.Forms.TextBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.buttonSearchPath = new System.Windows.Forms.Button();
            this.FolderDialog = new System.Windows.Forms.FolderBrowserDialog();
            this.FileDialog = new System.Windows.Forms.SaveFileDialog();
            this.listAnimations = new System.Windows.Forms.ListBox();
            this.buttonSave = new System.Windows.Forms.Button();
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabAnimations = new System.Windows.Forms.TabPage();
            this.tabMeshes = new System.Windows.Forms.TabPage();
            this.listMeshes = new System.Windows.Forms.ListBox();
            this.buttonLoadMeshes = new System.Windows.Forms.Button();
            this.ucProperties1 = new TikiEditor.Designer.ucProperties();
            this.groupBox1.SuspendLayout();
            this.tabControl1.SuspendLayout();
            this.tabAnimations.SuspendLayout();
            this.tabMeshes.SuspendLayout();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(3, 88);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(42, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "Output:";
            // 
            // textOutputFilename
            // 
            this.textOutputFilename.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.textOutputFilename.Location = new System.Drawing.Point(51, 85);
            this.textOutputFilename.Name = "textOutputFilename";
            this.textOutputFilename.Size = new System.Drawing.Size(149, 20);
            this.textOutputFilename.TabIndex = 1;
            // 
            // buttonSearch
            // 
            this.buttonSearch.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonSearch.Location = new System.Drawing.Point(206, 83);
            this.buttonSearch.Name = "buttonSearch";
            this.buttonSearch.Size = new System.Drawing.Size(75, 23);
            this.buttonSearch.TabIndex = 2;
            this.buttonSearch.Text = "Search..";
            this.buttonSearch.UseVisualStyleBackColor = true;
            this.buttonSearch.Click += new System.EventHandler(this.buttonSearchOutput_Click);
            // 
            // buttonExecute
            // 
            this.buttonExecute.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonExecute.Location = new System.Drawing.Point(206, 422);
            this.buttonExecute.Name = "buttonExecute";
            this.buttonExecute.Size = new System.Drawing.Size(75, 23);
            this.buttonExecute.TabIndex = 5;
            this.buttonExecute.Text = "Execute";
            this.buttonExecute.UseVisualStyleBackColor = true;
            this.buttonExecute.Click += new System.EventHandler(this.buttonExecute_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(6, 22);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(32, 13);
            this.label2.TabIndex = 6;
            this.label2.Text = "Path:";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(6, 48);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(36, 13);
            this.label3.TabIndex = 7;
            this.label3.Text = "Prefix:";
            // 
            // textInputPrefix
            // 
            this.textInputPrefix.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.textInputPrefix.Location = new System.Drawing.Point(48, 45);
            this.textInputPrefix.Name = "textInputPrefix";
            this.textInputPrefix.Size = new System.Drawing.Size(224, 20);
            this.textInputPrefix.TabIndex = 8;
            this.textInputPrefix.TextChanged += new System.EventHandler(this.textInputPrefix_TextChanged);
            // 
            // textInputPath
            // 
            this.textInputPath.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.textInputPath.Location = new System.Drawing.Point(48, 19);
            this.textInputPath.Name = "textInputPath";
            this.textInputPath.Size = new System.Drawing.Size(143, 20);
            this.textInputPath.TabIndex = 9;
            this.textInputPath.TextChanged += new System.EventHandler(this.textInputPath_TextChanged);
            // 
            // groupBox1
            // 
            this.groupBox1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.groupBox1.Controls.Add(this.buttonSearchPath);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.textInputPrefix);
            this.groupBox1.Controls.Add(this.textInputPath);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Location = new System.Drawing.Point(3, 3);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(278, 74);
            this.groupBox1.TabIndex = 10;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Input";
            // 
            // buttonSearchPath
            // 
            this.buttonSearchPath.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonSearchPath.Location = new System.Drawing.Point(197, 17);
            this.buttonSearchPath.Name = "buttonSearchPath";
            this.buttonSearchPath.Size = new System.Drawing.Size(75, 23);
            this.buttonSearchPath.TabIndex = 10;
            this.buttonSearchPath.Text = "Search..";
            this.buttonSearchPath.UseVisualStyleBackColor = true;
            this.buttonSearchPath.Click += new System.EventHandler(this.buttonSearchInput_Click);
            // 
            // FolderDialog
            // 
            this.FolderDialog.ShowNewFolderButton = false;
            // 
            // FileDialog
            // 
            this.FileDialog.DefaultExt = "tiki";
            this.FileDialog.Filter = "TikiModel (*.tiki)|*.tiki|All Files (*.*)|*.*";
            this.FileDialog.SupportMultiDottedExtensions = true;
            // 
            // listAnimations
            // 
            this.listAnimations.Dock = System.Windows.Forms.DockStyle.Fill;
            this.listAnimations.FormattingEnabled = true;
            this.listAnimations.IntegralHeight = false;
            this.listAnimations.Location = new System.Drawing.Point(3, 3);
            this.listAnimations.Name = "listAnimations";
            this.listAnimations.SelectionMode = System.Windows.Forms.SelectionMode.MultiExtended;
            this.listAnimations.Size = new System.Drawing.Size(264, 96);
            this.listAnimations.TabIndex = 14;
            this.listAnimations.SelectedIndexChanged += new System.EventHandler(this.listInputs_SelectedIndexChanged);
            // 
            // buttonSave
            // 
            this.buttonSave.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.buttonSave.Location = new System.Drawing.Point(3, 422);
            this.buttonSave.Name = "buttonSave";
            this.buttonSave.Size = new System.Drawing.Size(75, 23);
            this.buttonSave.TabIndex = 15;
            this.buttonSave.Text = "Save Props";
            this.buttonSave.UseVisualStyleBackColor = true;
            this.buttonSave.Click += new System.EventHandler(this.buttonSave_Click);
            // 
            // tabControl1
            // 
            this.tabControl1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.tabControl1.Controls.Add(this.tabAnimations);
            this.tabControl1.Controls.Add(this.tabMeshes);
            this.tabControl1.Location = new System.Drawing.Point(3, 112);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(278, 128);
            this.tabControl1.TabIndex = 16;
            // 
            // tabAnimations
            // 
            this.tabAnimations.Controls.Add(this.listAnimations);
            this.tabAnimations.Location = new System.Drawing.Point(4, 22);
            this.tabAnimations.Name = "tabAnimations";
            this.tabAnimations.Padding = new System.Windows.Forms.Padding(3);
            this.tabAnimations.Size = new System.Drawing.Size(270, 102);
            this.tabAnimations.TabIndex = 0;
            this.tabAnimations.Text = "Animations";
            this.tabAnimations.UseVisualStyleBackColor = true;
            // 
            // tabMeshes
            // 
            this.tabMeshes.Controls.Add(this.buttonLoadMeshes);
            this.tabMeshes.Controls.Add(this.listMeshes);
            this.tabMeshes.Location = new System.Drawing.Point(4, 22);
            this.tabMeshes.Name = "tabMeshes";
            this.tabMeshes.Padding = new System.Windows.Forms.Padding(3);
            this.tabMeshes.Size = new System.Drawing.Size(270, 102);
            this.tabMeshes.TabIndex = 1;
            this.tabMeshes.Text = "Meshes";
            this.tabMeshes.UseVisualStyleBackColor = true;
            // 
            // listMeshes
            // 
            this.listMeshes.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.listMeshes.FormattingEnabled = true;
            this.listMeshes.IntegralHeight = false;
            this.listMeshes.Location = new System.Drawing.Point(3, 3);
            this.listMeshes.Name = "listMeshes";
            this.listMeshes.SelectionMode = System.Windows.Forms.SelectionMode.MultiExtended;
            this.listMeshes.Size = new System.Drawing.Size(264, 64);
            this.listMeshes.TabIndex = 15;
            // 
            // buttonLoadMeshes
            // 
            this.buttonLoadMeshes.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonLoadMeshes.Location = new System.Drawing.Point(181, 73);
            this.buttonLoadMeshes.Name = "buttonLoadMeshes";
            this.buttonLoadMeshes.Size = new System.Drawing.Size(86, 23);
            this.buttonLoadMeshes.TabIndex = 16;
            this.buttonLoadMeshes.Text = "Load Meshes";
            this.buttonLoadMeshes.UseVisualStyleBackColor = true;
            this.buttonLoadMeshes.Click += new System.EventHandler(this.buttonLoadMeshes_Click);
            // 
            // ucProperties1
            // 
            this.ucProperties1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.ucProperties1.AutoScroll = true;
            this.ucProperties1.CurrentObject = null;
            this.ucProperties1.Location = new System.Drawing.Point(3, 246);
            this.ucProperties1.Name = "ucProperties1";
            this.ucProperties1.Padding = new System.Windows.Forms.Padding(0, 3, 0, 0);
            this.ucProperties1.SettingsChanged = false;
            this.ucProperties1.Size = new System.Drawing.Size(278, 170);
            this.ucProperties1.TabIndex = 12;
            // 
            // ucDesignModel
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.tabControl1);
            this.Controls.Add(this.buttonSave);
            this.Controls.Add(this.ucProperties1);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.buttonExecute);
            this.Controls.Add(this.buttonSearch);
            this.Controls.Add(this.textOutputFilename);
            this.Controls.Add(this.label1);
            this.Name = "ucDesignModel";
            this.Size = new System.Drawing.Size(284, 448);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.tabControl1.ResumeLayout(false);
            this.tabAnimations.ResumeLayout(false);
            this.tabMeshes.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox textOutputFilename;
        private System.Windows.Forms.Button buttonSearch;
        private System.Windows.Forms.Button buttonExecute;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox textInputPrefix;
        private System.Windows.Forms.TextBox textInputPath;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Button buttonSearchPath;
        private System.Windows.Forms.FolderBrowserDialog FolderDialog;
        private System.Windows.Forms.SaveFileDialog FileDialog;
        private Designer.ucProperties ucProperties1;
        private System.Windows.Forms.ListBox listAnimations;
        private System.Windows.Forms.Button buttonSave;
        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tabAnimations;
        private System.Windows.Forms.TabPage tabMeshes;
        private System.Windows.Forms.ListBox listMeshes;
        private System.Windows.Forms.Button buttonLoadMeshes;
    }
}
