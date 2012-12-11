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
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabAnimations = new System.Windows.Forms.TabPage();
            this.buttonNextToMeshes = new System.Windows.Forms.Button();
            this.tabMeshes = new System.Windows.Forms.TabPage();
            this.buttonBackToAnimations = new System.Windows.Forms.Button();
            this.buttonNextToOverview = new System.Windows.Forms.Button();
            this.listMeshes = new System.Windows.Forms.ListBox();
            this.tabOverview = new System.Windows.Forms.TabPage();
            this.buttonBackToMeshes = new System.Windows.Forms.Button();
            this.ucProperties1 = new TikiEditor.Designer.ucProperties();
            this.label4 = new System.Windows.Forms.Label();
            this.groupBox1.SuspendLayout();
            this.tabControl1.SuspendLayout();
            this.tabAnimations.SuspendLayout();
            this.tabMeshes.SuspendLayout();
            this.tabOverview.SuspendLayout();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(4, 83);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(31, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "Files:";
            // 
            // textOutputFilename
            // 
            this.textOutputFilename.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.textOutputFilename.Location = new System.Drawing.Point(54, 240);
            this.textOutputFilename.Name = "textOutputFilename";
            this.textOutputFilename.Size = new System.Drawing.Size(129, 20);
            this.textOutputFilename.TabIndex = 1;
            // 
            // buttonSearch
            // 
            this.buttonSearch.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonSearch.Location = new System.Drawing.Point(189, 238);
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
            this.buttonExecute.Location = new System.Drawing.Point(192, 271);
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
            this.textInputPrefix.Size = new System.Drawing.Size(204, 20);
            this.textInputPrefix.TabIndex = 8;
            this.textInputPrefix.TextChanged += new System.EventHandler(this.textInputPrefix_TextChanged);
            // 
            // textInputPath
            // 
            this.textInputPath.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.textInputPath.Location = new System.Drawing.Point(48, 19);
            this.textInputPath.Name = "textInputPath";
            this.textInputPath.Size = new System.Drawing.Size(123, 20);
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
            this.groupBox1.Location = new System.Drawing.Point(6, 6);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(258, 74);
            this.groupBox1.TabIndex = 10;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Input";
            // 
            // buttonSearchPath
            // 
            this.buttonSearchPath.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonSearchPath.Location = new System.Drawing.Point(177, 17);
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
            this.listAnimations.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.listAnimations.FormattingEnabled = true;
            this.listAnimations.IntegralHeight = false;
            this.listAnimations.Location = new System.Drawing.Point(6, 99);
            this.listAnimations.Name = "listAnimations";
            this.listAnimations.SelectionMode = System.Windows.Forms.SelectionMode.MultiExtended;
            this.listAnimations.Size = new System.Drawing.Size(258, 133);
            this.listAnimations.TabIndex = 14;
            this.listAnimations.SelectedIndexChanged += new System.EventHandler(this.listInputs_SelectedIndexChanged);
            // 
            // tabControl1
            // 
            this.tabControl1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.tabControl1.Controls.Add(this.tabAnimations);
            this.tabControl1.Controls.Add(this.tabMeshes);
            this.tabControl1.Controls.Add(this.tabOverview);
            this.tabControl1.Location = new System.Drawing.Point(3, 3);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(278, 323);
            this.tabControl1.TabIndex = 16;
            // 
            // tabAnimations
            // 
            this.tabAnimations.Controls.Add(this.label4);
            this.tabAnimations.Controls.Add(this.buttonNextToMeshes);
            this.tabAnimations.Controls.Add(this.listAnimations);
            this.tabAnimations.Controls.Add(this.buttonSearch);
            this.tabAnimations.Controls.Add(this.textOutputFilename);
            this.tabAnimations.Controls.Add(this.groupBox1);
            this.tabAnimations.Controls.Add(this.label1);
            this.tabAnimations.Location = new System.Drawing.Point(4, 22);
            this.tabAnimations.Name = "tabAnimations";
            this.tabAnimations.Padding = new System.Windows.Forms.Padding(3);
            this.tabAnimations.Size = new System.Drawing.Size(270, 297);
            this.tabAnimations.TabIndex = 0;
            this.tabAnimations.Text = "Animations";
            this.tabAnimations.UseVisualStyleBackColor = true;
            // 
            // buttonNextToMeshes
            // 
            this.buttonNextToMeshes.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonNextToMeshes.Location = new System.Drawing.Point(189, 267);
            this.buttonNextToMeshes.Name = "buttonNextToMeshes";
            this.buttonNextToMeshes.Size = new System.Drawing.Size(75, 23);
            this.buttonNextToMeshes.TabIndex = 15;
            this.buttonNextToMeshes.Text = "Next >";
            this.buttonNextToMeshes.UseVisualStyleBackColor = true;
            this.buttonNextToMeshes.Click += new System.EventHandler(this.buttonNextToMeshes_Click);
            // 
            // tabMeshes
            // 
            this.tabMeshes.Controls.Add(this.buttonBackToAnimations);
            this.tabMeshes.Controls.Add(this.buttonNextToOverview);
            this.tabMeshes.Controls.Add(this.listMeshes);
            this.tabMeshes.Location = new System.Drawing.Point(4, 22);
            this.tabMeshes.Name = "tabMeshes";
            this.tabMeshes.Padding = new System.Windows.Forms.Padding(3);
            this.tabMeshes.Size = new System.Drawing.Size(270, 297);
            this.tabMeshes.TabIndex = 1;
            this.tabMeshes.Text = "Meshes";
            this.tabMeshes.UseVisualStyleBackColor = true;
            // 
            // buttonBackToAnimations
            // 
            this.buttonBackToAnimations.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.buttonBackToAnimations.Location = new System.Drawing.Point(6, 268);
            this.buttonBackToAnimations.Name = "buttonBackToAnimations";
            this.buttonBackToAnimations.Size = new System.Drawing.Size(86, 23);
            this.buttonBackToAnimations.TabIndex = 17;
            this.buttonBackToAnimations.Text = "< Back";
            this.buttonBackToAnimations.UseVisualStyleBackColor = true;
            this.buttonBackToAnimations.Click += new System.EventHandler(this.buttonBackToAnimations_Click);
            // 
            // buttonNextToOverview
            // 
            this.buttonNextToOverview.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonNextToOverview.Location = new System.Drawing.Point(178, 268);
            this.buttonNextToOverview.Name = "buttonNextToOverview";
            this.buttonNextToOverview.Size = new System.Drawing.Size(86, 23);
            this.buttonNextToOverview.TabIndex = 16;
            this.buttonNextToOverview.Text = "Next >";
            this.buttonNextToOverview.UseVisualStyleBackColor = true;
            this.buttonNextToOverview.Click += new System.EventHandler(this.buttonNextToOverview_Click);
            // 
            // listMeshes
            // 
            this.listMeshes.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.listMeshes.FormattingEnabled = true;
            this.listMeshes.IntegralHeight = false;
            this.listMeshes.Location = new System.Drawing.Point(6, 6);
            this.listMeshes.Name = "listMeshes";
            this.listMeshes.SelectionMode = System.Windows.Forms.SelectionMode.MultiExtended;
            this.listMeshes.Size = new System.Drawing.Size(258, 256);
            this.listMeshes.TabIndex = 15;
            this.listMeshes.SelectedIndexChanged += new System.EventHandler(this.listMeshes_SelectedIndexChanged);
            // 
            // tabOverview
            // 
            this.tabOverview.Controls.Add(this.buttonBackToMeshes);
            this.tabOverview.Controls.Add(this.buttonExecute);
            this.tabOverview.Location = new System.Drawing.Point(4, 22);
            this.tabOverview.Name = "tabOverview";
            this.tabOverview.Size = new System.Drawing.Size(270, 297);
            this.tabOverview.TabIndex = 2;
            this.tabOverview.Text = "Overview";
            this.tabOverview.UseVisualStyleBackColor = true;
            // 
            // buttonBackToMeshes
            // 
            this.buttonBackToMeshes.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.buttonBackToMeshes.Location = new System.Drawing.Point(3, 271);
            this.buttonBackToMeshes.Name = "buttonBackToMeshes";
            this.buttonBackToMeshes.Size = new System.Drawing.Size(75, 23);
            this.buttonBackToMeshes.TabIndex = 6;
            this.buttonBackToMeshes.Text = "< Back";
            this.buttonBackToMeshes.UseVisualStyleBackColor = true;
            this.buttonBackToMeshes.Click += new System.EventHandler(this.buttonBackToMeshes_Click);
            // 
            // ucProperties1
            // 
            this.ucProperties1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.ucProperties1.AutoScroll = true;
            this.ucProperties1.CurrentObject = null;
            this.ucProperties1.Location = new System.Drawing.Point(3, 332);
            this.ucProperties1.Name = "ucProperties1";
            this.ucProperties1.Padding = new System.Windows.Forms.Padding(0, 3, 0, 0);
            this.ucProperties1.SettingsChanged = false;
            this.ucProperties1.Size = new System.Drawing.Size(278, 113);
            this.ucProperties1.TabIndex = 12;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(6, 243);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(42, 13);
            this.label4.TabIndex = 16;
            this.label4.Text = "Output:";
            // 
            // ucDesignModel
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.tabControl1);
            this.Controls.Add(this.ucProperties1);
            this.Name = "ucDesignModel";
            this.Size = new System.Drawing.Size(284, 448);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.tabControl1.ResumeLayout(false);
            this.tabAnimations.ResumeLayout(false);
            this.tabAnimations.PerformLayout();
            this.tabMeshes.ResumeLayout(false);
            this.tabOverview.ResumeLayout(false);
            this.ResumeLayout(false);

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
        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tabAnimations;
        private System.Windows.Forms.TabPage tabMeshes;
        private System.Windows.Forms.ListBox listMeshes;
        private System.Windows.Forms.Button buttonNextToOverview;
        private System.Windows.Forms.Button buttonNextToMeshes;
        private System.Windows.Forms.TabPage tabOverview;
        private System.Windows.Forms.Button buttonBackToAnimations;
        private System.Windows.Forms.Button buttonBackToMeshes;
        private System.Windows.Forms.Label label4;
    }
}
