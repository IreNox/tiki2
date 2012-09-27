namespace TikiEditor.Designer
{
    partial class formMain
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.panelViewport = new System.Windows.Forms.UserControl();
            this.splitContainer1 = new System.Windows.Forms.SplitContainer();
            this.ucDesign1 = new TikiEditor.Designer.ucDesign();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).BeginInit();
            this.splitContainer1.Panel1.SuspendLayout();
            this.splitContainer1.Panel2.SuspendLayout();
            this.splitContainer1.SuspendLayout();
            this.SuspendLayout();
            // 
            // panelViewport
            // 
            this.panelViewport.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panelViewport.Location = new System.Drawing.Point(0, 0);
            this.panelViewport.Name = "panelViewport";
            this.panelViewport.Size = new System.Drawing.Size(657, 544);
            this.panelViewport.TabIndex = 0;
            this.panelViewport.SizeChanged += new System.EventHandler(this.panelViewport_SizeChanged);
            // 
            // splitContainer1
            // 
            this.splitContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer1.Location = new System.Drawing.Point(0, 0);
            this.splitContainer1.Name = "splitContainer1";
            // 
            // splitContainer1.Panel1
            // 
            this.splitContainer1.Panel1.Controls.Add(this.ucDesign1);
            // 
            // splitContainer1.Panel2
            // 
            this.splitContainer1.Panel2.Controls.Add(this.panelViewport);
            this.splitContainer1.Size = new System.Drawing.Size(961, 544);
            this.splitContainer1.SplitterDistance = 300;
            this.splitContainer1.TabIndex = 2;
            // 
            // ucDesign1
            // 
            this.ucDesign1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.ucDesign1.Location = new System.Drawing.Point(0, 0);
            this.ucDesign1.Name = "ucDesign1";
            this.ucDesign1.Size = new System.Drawing.Size(300, 544);
            this.ucDesign1.TabIndex = 1;
            // 
            // formMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(961, 544);
            this.Controls.Add(this.splitContainer1);
            this.Name = "formMain";
            this.Text = "TikiEditor";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.formMain_FormClosed);
            this.splitContainer1.Panel1.ResumeLayout(false);
            this.splitContainer1.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).EndInit();
            this.splitContainer1.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        internal System.Windows.Forms.UserControl panelViewport;
        private ucDesign ucDesign1;
        private System.Windows.Forms.SplitContainer splitContainer1;

    }
}