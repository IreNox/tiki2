namespace TikiEditor
{
    partial class formStartUp
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
            this.buttonLevel = new System.Windows.Forms.Button();
            this.buttonGUI = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // buttonLevel
            // 
            this.buttonLevel.Location = new System.Drawing.Point(12, 12);
            this.buttonLevel.Name = "buttonLevel";
            this.buttonLevel.Size = new System.Drawing.Size(248, 52);
            this.buttonLevel.TabIndex = 0;
            this.buttonLevel.Text = "Level Editor";
            this.buttonLevel.UseVisualStyleBackColor = true;
            this.buttonLevel.Click += new System.EventHandler(this.buttonLevel_Click);
            // 
            // buttonGUI
            // 
            this.buttonGUI.Location = new System.Drawing.Point(12, 82);
            this.buttonGUI.Name = "buttonGUI";
            this.buttonGUI.Size = new System.Drawing.Size(248, 52);
            this.buttonGUI.TabIndex = 1;
            this.buttonGUI.Text = "User Interface";
            this.buttonGUI.UseVisualStyleBackColor = true;
            this.buttonGUI.Click += new System.EventHandler(this.buttonGUI_Click);
            // 
            // formStartUp
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(272, 146);
            this.Controls.Add(this.buttonGUI);
            this.Controls.Add(this.buttonLevel);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.Name = "formStartUp";
            this.ShowIcon = false;
            this.Text = "TikiEditor 2.0";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button buttonLevel;
        private System.Windows.Forms.Button buttonGUI;
    }
}