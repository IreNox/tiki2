namespace TikiEditor
{
    partial class ucDesignRes
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
            this.buttonDoit = new System.Windows.Forms.Button();
            this.treeView1 = new System.Windows.Forms.TreeView();
            this.SuspendLayout();
            // 
            // buttonDoit
            // 
            this.buttonDoit.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonDoit.Location = new System.Drawing.Point(155, 310);
            this.buttonDoit.Name = "buttonDoit";
            this.buttonDoit.Size = new System.Drawing.Size(75, 23);
            this.buttonDoit.TabIndex = 1;
            this.buttonDoit.Text = "Do it!";
            this.buttonDoit.UseVisualStyleBackColor = true;
            this.buttonDoit.Click += new System.EventHandler(this.buttonDoit_Click);
            // 
            // treeView1
            // 
            this.treeView1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.treeView1.Location = new System.Drawing.Point(3, 3);
            this.treeView1.Name = "treeView1";
            this.treeView1.Size = new System.Drawing.Size(227, 301);
            this.treeView1.TabIndex = 2;
            // 
            // ucDesignRes
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.treeView1);
            this.Controls.Add(this.buttonDoit);
            this.Name = "ucDesignRes";
            this.Size = new System.Drawing.Size(233, 336);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button buttonDoit;
        private System.Windows.Forms.TreeView treeView1;
    }
}
