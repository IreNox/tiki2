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
            this.buttonTest = new System.Windows.Forms.Button();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.buttonModel = new System.Windows.Forms.Button();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.label1 = new System.Windows.Forms.Label();
            this.textLevelId = new System.Windows.Forms.TextBox();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.SuspendLayout();
            // 
            // buttonLevel
            // 
            this.buttonLevel.Location = new System.Drawing.Point(6, 50);
            this.buttonLevel.Name = "buttonLevel";
            this.buttonLevel.Size = new System.Drawing.Size(237, 36);
            this.buttonLevel.TabIndex = 0;
            this.buttonLevel.Text = "Start";
            this.buttonLevel.UseVisualStyleBackColor = true;
            this.buttonLevel.Click += new System.EventHandler(this.buttonLevel_Click);
            // 
            // buttonGUI
            // 
            this.buttonGUI.Location = new System.Drawing.Point(6, 19);
            this.buttonGUI.Name = "buttonGUI";
            this.buttonGUI.Size = new System.Drawing.Size(237, 36);
            this.buttonGUI.TabIndex = 1;
            this.buttonGUI.Text = "User Interface";
            this.buttonGUI.UseVisualStyleBackColor = true;
            this.buttonGUI.Click += new System.EventHandler(this.buttonGUI_Click);
            // 
            // buttonTest
            // 
            this.buttonTest.Location = new System.Drawing.Point(6, 61);
            this.buttonTest.Name = "buttonTest";
            this.buttonTest.Size = new System.Drawing.Size(237, 36);
            this.buttonTest.TabIndex = 2;
            this.buttonTest.Text = "Test Area";
            this.buttonTest.UseVisualStyleBackColor = true;
            this.buttonTest.Click += new System.EventHandler(this.buttonTest_Click);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.buttonModel);
            this.groupBox1.Controls.Add(this.buttonGUI);
            this.groupBox1.Controls.Add(this.buttonTest);
            this.groupBox1.Location = new System.Drawing.Point(12, 111);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(249, 146);
            this.groupBox1.TabIndex = 4;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Other Editors";
            // 
            // buttonModel
            // 
            this.buttonModel.Location = new System.Drawing.Point(6, 103);
            this.buttonModel.Name = "buttonModel";
            this.buttonModel.Size = new System.Drawing.Size(237, 36);
            this.buttonModel.TabIndex = 3;
            this.buttonModel.Text = "Model Converter";
            this.buttonModel.UseVisualStyleBackColor = true;
            this.buttonModel.Click += new System.EventHandler(this.buttonModel_Click);
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.label1);
            this.groupBox2.Controls.Add(this.textLevelId);
            this.groupBox2.Controls.Add(this.buttonLevel);
            this.groupBox2.Location = new System.Drawing.Point(12, 12);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(249, 93);
            this.groupBox2.TabIndex = 5;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Level Editor";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(6, 27);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(50, 13);
            this.label1.TabIndex = 2;
            this.label1.Text = "Level ID:";
            // 
            // textLevelId
            // 
            this.textLevelId.Location = new System.Drawing.Point(62, 24);
            this.textLevelId.Name = "textLevelId";
            this.textLevelId.Size = new System.Drawing.Size(181, 20);
            this.textLevelId.TabIndex = 1;
            this.textLevelId.Text = "1";
            // 
            // formStartUp
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(273, 270);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.Name = "formStartUp";
            this.ShowIcon = false;
            this.Text = "TikiEditor 2.0";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.formStartUp_FormClosed);
            this.groupBox1.ResumeLayout(false);
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button buttonLevel;
        private System.Windows.Forms.Button buttonGUI;
        private System.Windows.Forms.Button buttonTest;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox textLevelId;
        private System.Windows.Forms.Button buttonModel;
    }
}