namespace TikiEditor.Designer
{
    partial class ucDesignLevel
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(ucDesignLevel));
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.labelName = new System.Windows.Forms.Label();
            this.labelType = new System.Windows.Forms.Label();
            this.ucProperties1 = new TikiEditor.Designer.ucProperties();
            this.buttonSave = new System.Windows.Forms.Button();
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabAdd = new System.Windows.Forms.TabPage();
            this.panelButtons = new System.Windows.Forms.Panel();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.button7 = new System.Windows.Forms.Button();
            this.button8 = new System.Windows.Forms.Button();
            this.button9 = new System.Windows.Forms.Button();
            this.button10 = new System.Windows.Forms.Button();
            this.button11 = new System.Windows.Forms.Button();
            this.button12 = new System.Windows.Forms.Button();
            this.buttonAddEnemyBasic = new System.Windows.Forms.Button();
            this.button3 = new System.Windows.Forms.Button();
            this.buttonAddPoint = new System.Windows.Forms.Button();
            this.button1 = new System.Windows.Forms.Button();
            this.buttonAddObject = new System.Windows.Forms.Button();
            this.tabEdit = new System.Windows.Forms.TabPage();
            this.tabView = new System.Windows.Forms.TabPage();
            this.label1 = new System.Windows.Forms.Label();
            this.checkShowBoundingBox = new System.Windows.Forms.CheckBox();
            this.checkShowPoints = new System.Windows.Forms.CheckBox();
            this.groupBox1.SuspendLayout();
            this.tabControl1.SuspendLayout();
            this.tabAdd.SuspendLayout();
            this.panelButtons.SuspendLayout();
            this.tabEdit.SuspendLayout();
            this.tabView.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBox1
            // 
            this.groupBox1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.groupBox1.Controls.Add(this.labelName);
            this.groupBox1.Controls.Add(this.labelType);
            this.groupBox1.Location = new System.Drawing.Point(3, 3);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(239, 58);
            this.groupBox1.TabIndex = 1;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Current Element";
            // 
            // labelName
            // 
            this.labelName.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.labelName.AutoSize = true;
            this.labelName.Location = new System.Drawing.Point(6, 34);
            this.labelName.Name = "labelName";
            this.labelName.Size = new System.Drawing.Size(45, 13);
            this.labelName.TabIndex = 2;
            this.labelName.Text = "ID: ###";
            // 
            // labelType
            // 
            this.labelType.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.labelType.AutoSize = true;
            this.labelType.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.labelType.Location = new System.Drawing.Point(5, 14);
            this.labelType.Name = "labelType";
            this.labelType.Size = new System.Drawing.Size(94, 20);
            this.labelType.TabIndex = 1;
            this.labelType.Text = "## TYPE ##";
            // 
            // ucProperties1
            // 
            this.ucProperties1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.ucProperties1.AutoScroll = true;
            this.ucProperties1.CurrentObject = null;
            this.ucProperties1.Location = new System.Drawing.Point(3, 3);
            this.ucProperties1.Name = "ucProperties1";
            this.ucProperties1.Padding = new System.Windows.Forms.Padding(0, 3, 0, 0);
            this.ucProperties1.SettingsChanged = false;
            this.ucProperties1.Size = new System.Drawing.Size(225, 285);
            this.ucProperties1.TabIndex = 0;
            // 
            // buttonSave
            // 
            this.buttonSave.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonSave.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
            this.buttonSave.Location = new System.Drawing.Point(137, 294);
            this.buttonSave.Name = "buttonSave";
            this.buttonSave.Size = new System.Drawing.Size(88, 23);
            this.buttonSave.TabIndex = 2;
            this.buttonSave.Text = "Save";
            this.buttonSave.UseVisualStyleBackColor = true;
            this.buttonSave.Click += new System.EventHandler(this.buttonSave_Click);
            // 
            // tabControl1
            // 
            this.tabControl1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.tabControl1.Controls.Add(this.tabAdd);
            this.tabControl1.Controls.Add(this.tabEdit);
            this.tabControl1.Controls.Add(this.tabView);
            this.tabControl1.Location = new System.Drawing.Point(3, 67);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(239, 351);
            this.tabControl1.TabIndex = 6;
            // 
            // tabAdd
            // 
            this.tabAdd.Controls.Add(this.panelButtons);
            this.tabAdd.Location = new System.Drawing.Point(4, 22);
            this.tabAdd.Name = "tabAdd";
            this.tabAdd.Padding = new System.Windows.Forms.Padding(3);
            this.tabAdd.Size = new System.Drawing.Size(231, 325);
            this.tabAdd.TabIndex = 0;
            this.tabAdd.Text = "Add";
            this.tabAdd.UseVisualStyleBackColor = true;
            // 
            // panelButtons
            // 
            this.panelButtons.AutoScroll = true;
            this.panelButtons.Controls.Add(this.label3);
            this.panelButtons.Controls.Add(this.label2);
            this.panelButtons.Controls.Add(this.button7);
            this.panelButtons.Controls.Add(this.button8);
            this.panelButtons.Controls.Add(this.button9);
            this.panelButtons.Controls.Add(this.button10);
            this.panelButtons.Controls.Add(this.button11);
            this.panelButtons.Controls.Add(this.button12);
            this.panelButtons.Controls.Add(this.buttonAddEnemyBasic);
            this.panelButtons.Controls.Add(this.button3);
            this.panelButtons.Controls.Add(this.buttonAddPoint);
            this.panelButtons.Controls.Add(this.button1);
            this.panelButtons.Controls.Add(this.buttonAddObject);
            this.panelButtons.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panelButtons.Location = new System.Drawing.Point(3, 3);
            this.panelButtons.Name = "panelButtons";
            this.panelButtons.Size = new System.Drawing.Size(225, 319);
            this.panelButtons.TabIndex = 0;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(3, 16);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(46, 13);
            this.label3.TabIndex = 14;
            this.label3.Text = "Objects:";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(3, 161);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(50, 13);
            this.label2.TabIndex = 13;
            this.label2.Text = "Enemies:";
            // 
            // button7
            // 
            this.button7.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.button7.Enabled = false;
            this.button7.Location = new System.Drawing.Point(3, 351);
            this.button7.Name = "button7";
            this.button7.Size = new System.Drawing.Size(168, 23);
            this.button7.TabIndex = 12;
            this.button7.Text = "-none-";
            this.button7.UseVisualStyleBackColor = true;
            // 
            // button8
            // 
            this.button8.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.button8.Enabled = false;
            this.button8.Location = new System.Drawing.Point(3, 322);
            this.button8.Name = "button8";
            this.button8.Size = new System.Drawing.Size(168, 23);
            this.button8.TabIndex = 11;
            this.button8.Text = "-none-";
            this.button8.UseVisualStyleBackColor = true;
            // 
            // button9
            // 
            this.button9.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.button9.Enabled = false;
            this.button9.Location = new System.Drawing.Point(3, 293);
            this.button9.Name = "button9";
            this.button9.Size = new System.Drawing.Size(168, 23);
            this.button9.TabIndex = 10;
            this.button9.Text = "-none-";
            this.button9.UseVisualStyleBackColor = true;
            // 
            // button10
            // 
            this.button10.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.button10.Enabled = false;
            this.button10.Location = new System.Drawing.Point(3, 264);
            this.button10.Name = "button10";
            this.button10.Size = new System.Drawing.Size(168, 23);
            this.button10.TabIndex = 9;
            this.button10.Text = "-none-";
            this.button10.UseVisualStyleBackColor = true;
            // 
            // button11
            // 
            this.button11.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.button11.Enabled = false;
            this.button11.Location = new System.Drawing.Point(3, 235);
            this.button11.Name = "button11";
            this.button11.Size = new System.Drawing.Size(168, 23);
            this.button11.TabIndex = 8;
            this.button11.Text = "-none-";
            this.button11.UseVisualStyleBackColor = true;
            // 
            // button12
            // 
            this.button12.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.button12.Enabled = false;
            this.button12.Location = new System.Drawing.Point(3, 206);
            this.button12.Name = "button12";
            this.button12.Size = new System.Drawing.Size(168, 23);
            this.button12.TabIndex = 7;
            this.button12.Text = "-none-";
            this.button12.UseVisualStyleBackColor = true;
            // 
            // buttonAddEnemyBasic
            // 
            this.buttonAddEnemyBasic.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonAddEnemyBasic.Enabled = false;
            this.buttonAddEnemyBasic.Location = new System.Drawing.Point(3, 177);
            this.buttonAddEnemyBasic.Name = "buttonAddEnemyBasic";
            this.buttonAddEnemyBasic.Size = new System.Drawing.Size(168, 23);
            this.buttonAddEnemyBasic.TabIndex = 6;
            this.buttonAddEnemyBasic.Text = "Basic Enemy";
            this.buttonAddEnemyBasic.UseVisualStyleBackColor = true;
            this.buttonAddEnemyBasic.Click += new System.EventHandler(this.buttonAddEnemyBasic_Click);
            // 
            // button3
            // 
            this.button3.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.button3.Enabled = false;
            this.button3.Location = new System.Drawing.Point(3, 90);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(168, 23);
            this.button3.TabIndex = 3;
            this.button3.Text = "-none-";
            this.button3.UseVisualStyleBackColor = true;
            // 
            // buttonAddPoint
            // 
            this.buttonAddPoint.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonAddPoint.Location = new System.Drawing.Point(3, 61);
            this.buttonAddPoint.Name = "buttonAddPoint";
            this.buttonAddPoint.Size = new System.Drawing.Size(168, 23);
            this.buttonAddPoint.TabIndex = 2;
            this.buttonAddPoint.Text = "Point";
            this.buttonAddPoint.UseVisualStyleBackColor = true;
            this.buttonAddPoint.Click += new System.EventHandler(this.buttonAddPoint_Click);
            // 
            // button1
            // 
            this.button1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.button1.Enabled = false;
            this.button1.Location = new System.Drawing.Point(3, 119);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(168, 23);
            this.button1.TabIndex = 1;
            this.button1.Text = "-none-";
            this.button1.UseVisualStyleBackColor = true;
            // 
            // buttonAddObject
            // 
            this.buttonAddObject.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonAddObject.Location = new System.Drawing.Point(3, 32);
            this.buttonAddObject.Name = "buttonAddObject";
            this.buttonAddObject.Size = new System.Drawing.Size(168, 23);
            this.buttonAddObject.TabIndex = 0;
            this.buttonAddObject.Text = "Object";
            this.buttonAddObject.UseVisualStyleBackColor = true;
            this.buttonAddObject.Click += new System.EventHandler(this.buttonAddObject_Click);
            // 
            // tabEdit
            // 
            this.tabEdit.Controls.Add(this.ucProperties1);
            this.tabEdit.Controls.Add(this.buttonSave);
            this.tabEdit.Location = new System.Drawing.Point(4, 22);
            this.tabEdit.Name = "tabEdit";
            this.tabEdit.Padding = new System.Windows.Forms.Padding(3);
            this.tabEdit.Size = new System.Drawing.Size(231, 325);
            this.tabEdit.TabIndex = 1;
            this.tabEdit.Text = "Edit";
            this.tabEdit.UseVisualStyleBackColor = true;
            // 
            // tabView
            // 
            this.tabView.Controls.Add(this.label1);
            this.tabView.Controls.Add(this.checkShowBoundingBox);
            this.tabView.Controls.Add(this.checkShowPoints);
            this.tabView.Location = new System.Drawing.Point(4, 22);
            this.tabView.Name = "tabView";
            this.tabView.Size = new System.Drawing.Size(231, 325);
            this.tabView.TabIndex = 2;
            this.tabView.Text = "View/Help";
            this.tabView.UseVisualStyleBackColor = true;
            // 
            // label1
            // 
            this.label1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.label1.Location = new System.Drawing.Point(3, 50);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(264, 270);
            this.label1.TabIndex = 2;
            this.label1.Text = resources.GetString("label1.Text");
            // 
            // checkShowBoundingBox
            // 
            this.checkShowBoundingBox.AutoSize = true;
            this.checkShowBoundingBox.Location = new System.Drawing.Point(5, 30);
            this.checkShowBoundingBox.Name = "checkShowBoundingBox";
            this.checkShowBoundingBox.Size = new System.Drawing.Size(133, 17);
            this.checkShowBoundingBox.TabIndex = 1;
            this.checkShowBoundingBox.Text = "Show Bounding Boxes";
            this.checkShowBoundingBox.UseVisualStyleBackColor = true;
            this.checkShowBoundingBox.CheckedChanged += new System.EventHandler(this.checkShowBoundingBox_CheckedChanged);
            // 
            // checkShowPoints
            // 
            this.checkShowPoints.AutoSize = true;
            this.checkShowPoints.Location = new System.Drawing.Point(5, 7);
            this.checkShowPoints.Name = "checkShowPoints";
            this.checkShowPoints.Size = new System.Drawing.Size(85, 17);
            this.checkShowPoints.TabIndex = 0;
            this.checkShowPoints.Text = "Show Points";
            this.checkShowPoints.UseVisualStyleBackColor = true;
            this.checkShowPoints.CheckedChanged += new System.EventHandler(this.checkShowPoints_CheckedChanged);
            // 
            // ucDesignLevel
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.tabControl1);
            this.Location = new System.Drawing.Point(1300, 100);
            this.Name = "ucDesignLevel";
            this.Size = new System.Drawing.Size(245, 421);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.tabControl1.ResumeLayout(false);
            this.tabAdd.ResumeLayout(false);
            this.panelButtons.ResumeLayout(false);
            this.panelButtons.PerformLayout();
            this.tabEdit.ResumeLayout(false);
            this.tabView.ResumeLayout(false);
            this.tabView.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label labelName;
        private System.Windows.Forms.Label labelType;
        private System.Windows.Forms.Button buttonSave;
        private ucProperties ucProperties1;
        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tabAdd;
        private System.Windows.Forms.TabPage tabEdit;
        private System.Windows.Forms.Panel panelButtons;
        private System.Windows.Forms.Button button7;
        private System.Windows.Forms.Button button8;
        private System.Windows.Forms.Button button9;
        private System.Windows.Forms.Button button10;
        private System.Windows.Forms.Button button11;
        private System.Windows.Forms.Button button12;
        private System.Windows.Forms.Button buttonAddEnemyBasic;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.Button buttonAddPoint;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button buttonAddObject;
        private System.Windows.Forms.TabPage tabView;
        private System.Windows.Forms.CheckBox checkShowBoundingBox;
        private System.Windows.Forms.CheckBox checkShowPoints;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label2;
    }
}