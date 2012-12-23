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
            this.buttonAddPointWaypoint = new System.Windows.Forms.Button();
            this.buttonAddPointSpawnpoint = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.buttonAddPlayerBuilding = new System.Windows.Forms.Button();
            this.buttonAddEnemyBuilding = new System.Windows.Forms.Button();
            this.label3 = new System.Windows.Forms.Label();
            this.buttonAddPlayerMop = new System.Windows.Forms.Button();
            this.buttonAddEnvRock03 = new System.Windows.Forms.Button();
            this.buttonAddEnvRock02 = new System.Windows.Forms.Button();
            this.buttonAddEnvRock01 = new System.Windows.Forms.Button();
            this.buttonAddEnvPipes = new System.Windows.Forms.Button();
            this.buttonAddEnvBuilding = new System.Windows.Forms.Button();
            this.buttonAddEnemyMop = new System.Windows.Forms.Button();
            this.buttonAddPointCamera = new System.Windows.Forms.Button();
            this.buttonAddPlayerHero = new System.Windows.Forms.Button();
            this.buttonAddObject = new System.Windows.Forms.Button();
            this.tabEdit = new System.Windows.Forms.TabPage();
            this.tabView = new System.Windows.Forms.TabPage();
            this.trackBar1 = new System.Windows.Forms.TrackBar();
            this.label1 = new System.Windows.Forms.Label();
            this.checkShowBoundingBox = new System.Windows.Forms.CheckBox();
            this.checkShowPoints = new System.Windows.Forms.CheckBox();
            this.groupBox1.SuspendLayout();
            this.tabControl1.SuspendLayout();
            this.tabAdd.SuspendLayout();
            this.panelButtons.SuspendLayout();
            this.tabEdit.SuspendLayout();
            this.tabView.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.trackBar1)).BeginInit();
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
            this.ucProperties1.Size = new System.Drawing.Size(225, 424);
            this.ucProperties1.TabIndex = 0;
            // 
            // buttonSave
            // 
            this.buttonSave.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonSave.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
            this.buttonSave.Location = new System.Drawing.Point(140, 433);
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
            this.tabControl1.Size = new System.Drawing.Size(239, 488);
            this.tabControl1.TabIndex = 6;
            // 
            // tabAdd
            // 
            this.tabAdd.Controls.Add(this.panelButtons);
            this.tabAdd.Location = new System.Drawing.Point(4, 22);
            this.tabAdd.Name = "tabAdd";
            this.tabAdd.Padding = new System.Windows.Forms.Padding(3);
            this.tabAdd.Size = new System.Drawing.Size(231, 462);
            this.tabAdd.TabIndex = 0;
            this.tabAdd.Text = "Add";
            this.tabAdd.UseVisualStyleBackColor = true;
            // 
            // panelButtons
            // 
            this.panelButtons.AutoScroll = true;
            this.panelButtons.Controls.Add(this.buttonAddPointWaypoint);
            this.panelButtons.Controls.Add(this.buttonAddPointSpawnpoint);
            this.panelButtons.Controls.Add(this.label2);
            this.panelButtons.Controls.Add(this.buttonAddPlayerBuilding);
            this.panelButtons.Controls.Add(this.buttonAddEnemyBuilding);
            this.panelButtons.Controls.Add(this.label3);
            this.panelButtons.Controls.Add(this.buttonAddPlayerMop);
            this.panelButtons.Controls.Add(this.buttonAddEnvRock03);
            this.panelButtons.Controls.Add(this.buttonAddEnvRock02);
            this.panelButtons.Controls.Add(this.buttonAddEnvRock01);
            this.panelButtons.Controls.Add(this.buttonAddEnvPipes);
            this.panelButtons.Controls.Add(this.buttonAddEnvBuilding);
            this.panelButtons.Controls.Add(this.buttonAddEnemyMop);
            this.panelButtons.Controls.Add(this.buttonAddPointCamera);
            this.panelButtons.Controls.Add(this.buttonAddPlayerHero);
            this.panelButtons.Controls.Add(this.buttonAddObject);
            this.panelButtons.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panelButtons.Location = new System.Drawing.Point(3, 3);
            this.panelButtons.Name = "panelButtons";
            this.panelButtons.Size = new System.Drawing.Size(225, 456);
            this.panelButtons.TabIndex = 0;
            // 
            // buttonAddPointWaypoint
            // 
            this.buttonAddPointWaypoint.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonAddPointWaypoint.Location = new System.Drawing.Point(3, 407);
            this.buttonAddPointWaypoint.Name = "buttonAddPointWaypoint";
            this.buttonAddPointWaypoint.Size = new System.Drawing.Size(219, 23);
            this.buttonAddPointWaypoint.TabIndex = 19;
            this.buttonAddPointWaypoint.Text = "Enemy: Waypoint";
            this.buttonAddPointWaypoint.UseVisualStyleBackColor = true;
            this.buttonAddPointWaypoint.Click += new System.EventHandler(this.buttonAddPointWaypoint_Click);
            // 
            // buttonAddPointSpawnpoint
            // 
            this.buttonAddPointSpawnpoint.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonAddPointSpawnpoint.Location = new System.Drawing.Point(3, 433);
            this.buttonAddPointSpawnpoint.Name = "buttonAddPointSpawnpoint";
            this.buttonAddPointSpawnpoint.Size = new System.Drawing.Size(219, 23);
            this.buttonAddPointSpawnpoint.TabIndex = 18;
            this.buttonAddPointSpawnpoint.Text = "Enemy: Spawnpoint";
            this.buttonAddPointSpawnpoint.UseVisualStyleBackColor = true;
            this.buttonAddPointSpawnpoint.Click += new System.EventHandler(this.buttonAddPointSpawnpoint_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(3, 362);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(39, 13);
            this.label2.TabIndex = 17;
            this.label2.Text = "Points:";
            // 
            // buttonAddPlayerBuilding
            // 
            this.buttonAddPlayerBuilding.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonAddPlayerBuilding.Location = new System.Drawing.Point(3, 322);
            this.buttonAddPlayerBuilding.Name = "buttonAddPlayerBuilding";
            this.buttonAddPlayerBuilding.Size = new System.Drawing.Size(219, 23);
            this.buttonAddPlayerBuilding.TabIndex = 16;
            this.buttonAddPlayerBuilding.Text = "Player: Main Building";
            this.buttonAddPlayerBuilding.UseVisualStyleBackColor = true;
            this.buttonAddPlayerBuilding.Click += new System.EventHandler(this.buttonAddPlayerBuilding_Click);
            // 
            // buttonAddEnemyBuilding
            // 
            this.buttonAddEnemyBuilding.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonAddEnemyBuilding.Location = new System.Drawing.Point(3, 293);
            this.buttonAddEnemyBuilding.Name = "buttonAddEnemyBuilding";
            this.buttonAddEnemyBuilding.Size = new System.Drawing.Size(219, 23);
            this.buttonAddEnemyBuilding.TabIndex = 15;
            this.buttonAddEnemyBuilding.Text = "Enemy: Gate Control";
            this.buttonAddEnemyBuilding.UseVisualStyleBackColor = true;
            this.buttonAddEnemyBuilding.Click += new System.EventHandler(this.buttonAddEnemyBuilding_Click);
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
            // buttonAddPlayerMop
            // 
            this.buttonAddPlayerMop.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonAddPlayerMop.Location = new System.Drawing.Point(3, 61);
            this.buttonAddPlayerMop.Name = "buttonAddPlayerMop";
            this.buttonAddPlayerMop.Size = new System.Drawing.Size(219, 23);
            this.buttonAddPlayerMop.TabIndex = 12;
            this.buttonAddPlayerMop.Text = "Player: Mop";
            this.buttonAddPlayerMop.UseVisualStyleBackColor = true;
            this.buttonAddPlayerMop.Click += new System.EventHandler(this.buttonAddPlayerMop_Click);
            // 
            // buttonAddEnvRock03
            // 
            this.buttonAddEnvRock03.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonAddEnvRock03.Location = new System.Drawing.Point(3, 264);
            this.buttonAddEnvRock03.Name = "buttonAddEnvRock03";
            this.buttonAddEnvRock03.Size = new System.Drawing.Size(219, 23);
            this.buttonAddEnvRock03.TabIndex = 11;
            this.buttonAddEnvRock03.Text = "Environment: Rock 03";
            this.buttonAddEnvRock03.UseVisualStyleBackColor = true;
            this.buttonAddEnvRock03.Click += new System.EventHandler(this.buttonAddEnvRock03_Click);
            // 
            // buttonAddEnvRock02
            // 
            this.buttonAddEnvRock02.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonAddEnvRock02.Location = new System.Drawing.Point(3, 235);
            this.buttonAddEnvRock02.Name = "buttonAddEnvRock02";
            this.buttonAddEnvRock02.Size = new System.Drawing.Size(219, 23);
            this.buttonAddEnvRock02.TabIndex = 10;
            this.buttonAddEnvRock02.Text = "Environment: Rock 02";
            this.buttonAddEnvRock02.UseVisualStyleBackColor = true;
            this.buttonAddEnvRock02.Click += new System.EventHandler(this.buttonAddEnvRock02_Click);
            // 
            // buttonAddEnvRock01
            // 
            this.buttonAddEnvRock01.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonAddEnvRock01.Location = new System.Drawing.Point(3, 206);
            this.buttonAddEnvRock01.Name = "buttonAddEnvRock01";
            this.buttonAddEnvRock01.Size = new System.Drawing.Size(219, 23);
            this.buttonAddEnvRock01.TabIndex = 9;
            this.buttonAddEnvRock01.Text = "Environment: Rock 01";
            this.buttonAddEnvRock01.UseVisualStyleBackColor = true;
            this.buttonAddEnvRock01.Click += new System.EventHandler(this.buttonAddEnvRock01_Click);
            // 
            // buttonAddEnvPipes
            // 
            this.buttonAddEnvPipes.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonAddEnvPipes.Location = new System.Drawing.Point(3, 177);
            this.buttonAddEnvPipes.Name = "buttonAddEnvPipes";
            this.buttonAddEnvPipes.Size = new System.Drawing.Size(219, 23);
            this.buttonAddEnvPipes.TabIndex = 8;
            this.buttonAddEnvPipes.Text = "Environment: Pipes";
            this.buttonAddEnvPipes.UseVisualStyleBackColor = true;
            this.buttonAddEnvPipes.Click += new System.EventHandler(this.buttonAddEnvPipes_Click);
            // 
            // buttonAddEnvBuilding
            // 
            this.buttonAddEnvBuilding.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonAddEnvBuilding.Location = new System.Drawing.Point(3, 148);
            this.buttonAddEnvBuilding.Name = "buttonAddEnvBuilding";
            this.buttonAddEnvBuilding.Size = new System.Drawing.Size(219, 23);
            this.buttonAddEnvBuilding.TabIndex = 7;
            this.buttonAddEnvBuilding.Text = "Environment: Building";
            this.buttonAddEnvBuilding.UseVisualStyleBackColor = true;
            this.buttonAddEnvBuilding.Click += new System.EventHandler(this.buttonAddEnvBuilding_Click);
            // 
            // buttonAddEnemyMop
            // 
            this.buttonAddEnemyMop.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonAddEnemyMop.Location = new System.Drawing.Point(3, 90);
            this.buttonAddEnemyMop.Name = "buttonAddEnemyMop";
            this.buttonAddEnemyMop.Size = new System.Drawing.Size(219, 23);
            this.buttonAddEnemyMop.TabIndex = 3;
            this.buttonAddEnemyMop.Text = "Enemy: Mop";
            this.buttonAddEnemyMop.UseVisualStyleBackColor = true;
            this.buttonAddEnemyMop.Click += new System.EventHandler(this.buttonAddEnemyMop_Click);
            // 
            // buttonAddPointCamera
            // 
            this.buttonAddPointCamera.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonAddPointCamera.Location = new System.Drawing.Point(3, 378);
            this.buttonAddPointCamera.Name = "buttonAddPointCamera";
            this.buttonAddPointCamera.Size = new System.Drawing.Size(219, 23);
            this.buttonAddPointCamera.TabIndex = 2;
            this.buttonAddPointCamera.Text = "Camera Start";
            this.buttonAddPointCamera.UseVisualStyleBackColor = true;
            this.buttonAddPointCamera.Click += new System.EventHandler(this.buttonAddPoint_Click);
            // 
            // buttonAddPlayerHero
            // 
            this.buttonAddPlayerHero.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonAddPlayerHero.Location = new System.Drawing.Point(3, 119);
            this.buttonAddPlayerHero.Name = "buttonAddPlayerHero";
            this.buttonAddPlayerHero.Size = new System.Drawing.Size(219, 23);
            this.buttonAddPlayerHero.TabIndex = 1;
            this.buttonAddPlayerHero.Text = "Player: Hero";
            this.buttonAddPlayerHero.UseVisualStyleBackColor = true;
            this.buttonAddPlayerHero.Click += new System.EventHandler(this.buttonAddPlayerHero_Click);
            // 
            // buttonAddObject
            // 
            this.buttonAddObject.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonAddObject.Location = new System.Drawing.Point(3, 32);
            this.buttonAddObject.Name = "buttonAddObject";
            this.buttonAddObject.Size = new System.Drawing.Size(219, 23);
            this.buttonAddObject.TabIndex = 0;
            this.buttonAddObject.Text = "Replace Me Cube";
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
            this.tabEdit.Size = new System.Drawing.Size(231, 462);
            this.tabEdit.TabIndex = 1;
            this.tabEdit.Text = "Edit";
            this.tabEdit.UseVisualStyleBackColor = true;
            // 
            // tabView
            // 
            this.tabView.Controls.Add(this.trackBar1);
            this.tabView.Controls.Add(this.label1);
            this.tabView.Controls.Add(this.checkShowBoundingBox);
            this.tabView.Controls.Add(this.checkShowPoints);
            this.tabView.Location = new System.Drawing.Point(4, 22);
            this.tabView.Name = "tabView";
            this.tabView.Size = new System.Drawing.Size(231, 462);
            this.tabView.TabIndex = 2;
            this.tabView.Text = "View/Help";
            this.tabView.UseVisualStyleBackColor = true;
            // 
            // trackBar1
            // 
            this.trackBar1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.trackBar1.LargeChange = 750;
            this.trackBar1.Location = new System.Drawing.Point(5, 53);
            this.trackBar1.Maximum = 10000;
            this.trackBar1.Minimum = 100;
            this.trackBar1.Name = "trackBar1";
            this.trackBar1.Size = new System.Drawing.Size(223, 45);
            this.trackBar1.TabIndex = 3;
            this.trackBar1.TickStyle = System.Windows.Forms.TickStyle.None;
            this.trackBar1.Value = 100;
            this.trackBar1.Scroll += new System.EventHandler(this.trackBar1_Scroll);
            // 
            // label1
            // 
            this.label1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.label1.Location = new System.Drawing.Point(3, 108);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(225, 354);
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
            this.Size = new System.Drawing.Size(245, 558);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.tabControl1.ResumeLayout(false);
            this.tabAdd.ResumeLayout(false);
            this.panelButtons.ResumeLayout(false);
            this.panelButtons.PerformLayout();
            this.tabEdit.ResumeLayout(false);
            this.tabView.ResumeLayout(false);
            this.tabView.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.trackBar1)).EndInit();
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
        private System.Windows.Forms.Button buttonAddPlayerMop;
        private System.Windows.Forms.Button buttonAddEnvRock03;
        private System.Windows.Forms.Button buttonAddEnvRock02;
        private System.Windows.Forms.Button buttonAddEnvRock01;
        private System.Windows.Forms.Button buttonAddEnvPipes;
        private System.Windows.Forms.Button buttonAddEnvBuilding;
        private System.Windows.Forms.Button buttonAddEnemyMop;
        private System.Windows.Forms.Button buttonAddPointCamera;
        private System.Windows.Forms.Button buttonAddPlayerHero;
        private System.Windows.Forms.Button buttonAddObject;
        private System.Windows.Forms.TabPage tabView;
        private System.Windows.Forms.CheckBox checkShowBoundingBox;
        private System.Windows.Forms.CheckBox checkShowPoints;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TrackBar trackBar1;
        private System.Windows.Forms.Button buttonAddPlayerBuilding;
        private System.Windows.Forms.Button buttonAddEnemyBuilding;
        private System.Windows.Forms.Button buttonAddPointWaypoint;
        private System.Windows.Forms.Button buttonAddPointSpawnpoint;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
    }
}