namespace SGP_PoA_LevelEditor
{
    partial class Form1
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
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.newMapToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.saveMapToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.saveAsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
            this.loadToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator3 = new System.Windows.Forms.ToolStripSeparator();
            this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.optionsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.loadTilesetToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.panel1 = new System.Windows.Forms.Panel();
            this.panel2 = new System.Windows.Forms.Panel();
            this.button1 = new System.Windows.Forms.Button();
            this.lblTileWidth = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.nudTileWidth = new System.Windows.Forms.NumericUpDown();
            this.nudTileHeight = new System.Windows.Forms.NumericUpDown();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.nudMapWidth = new System.Windows.Forms.NumericUpDown();
            this.nudMapHeight = new System.Windows.Forms.NumericUpDown();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.radWarp = new System.Windows.Forms.RadioButton();
            this.button3 = new System.Windows.Forms.Button();
            this.label6 = new System.Windows.Forms.Label();
            this.button2 = new System.Windows.Forms.Button();
            this.radNPC = new System.Windows.Forms.RadioButton();
            this.radBlock = new System.Windows.Forms.RadioButton();
            this.radMap = new System.Windows.Forms.RadioButton();
            this.grpWarp = new System.Windows.Forms.GroupBox();
            this.lstMaps = new System.Windows.Forms.ListBox();
            this.btnWarpCancel = new System.Windows.Forms.Button();
            this.nudWarpY = new System.Windows.Forms.NumericUpDown();
            this.nudWarpX = new System.Windows.Forms.NumericUpDown();
            this.btnWarp = new System.Windows.Forms.Button();
            this.label11 = new System.Windows.Forms.Label();
            this.label10 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.grpNPC = new System.Windows.Forms.GroupBox();
            this.btnNPCMove = new System.Windows.Forms.Button();
            this.btnNPCUnits = new System.Windows.Forms.Button();
            this.btnNpcAdd = new System.Windows.Forms.Button();
            this.btnNpcApply = new System.Windows.Forms.Button();
            this.btnNpcCancel = new System.Windows.Forms.Button();
            this.chkMoves = new System.Windows.Forms.CheckBox();
            this.label8 = new System.Windows.Forms.Label();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.chkHostile = new System.Windows.Forms.CheckBox();
            this.label7 = new System.Windows.Forms.Label();
            this.lstNpcs = new System.Windows.Forms.ListBox();
            this.grpWayPoints = new System.Windows.Forms.GroupBox();
            this.label12 = new System.Windows.Forms.Label();
            this.radWPMove = new System.Windows.Forms.RadioButton();
            this.radWPAdd = new System.Windows.Forms.RadioButton();
            this.lstWaypoints = new System.Windows.Forms.ListBox();
            this.lstLayers = new System.Windows.Forms.ListBox();
            this.btnNewLayer = new System.Windows.Forms.Button();
            this.btnDelete = new System.Windows.Forms.Button();
            this.btnShiftUp = new System.Windows.Forms.Button();
            this.btnShiftDown = new System.Windows.Forms.Button();
            this.btnClear = new System.Windows.Forms.Button();
            this.menuStrip1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.nudTileWidth)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudTileHeight)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudMapWidth)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudMapHeight)).BeginInit();
            this.groupBox1.SuspendLayout();
            this.grpWarp.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.nudWarpY)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudWarpX)).BeginInit();
            this.grpNPC.SuspendLayout();
            this.grpWayPoints.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem,
            this.optionsToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(1153, 24);
            this.menuStrip1.TabIndex = 0;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.newMapToolStripMenuItem,
            this.toolStripSeparator1,
            this.saveMapToolStripMenuItem,
            this.saveAsToolStripMenuItem,
            this.toolStripSeparator2,
            this.loadToolStripMenuItem,
            this.toolStripSeparator3,
            this.exitToolStripMenuItem});
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(37, 20);
            this.fileToolStripMenuItem.Text = "&File";
            // 
            // newMapToolStripMenuItem
            // 
            this.newMapToolStripMenuItem.Name = "newMapToolStripMenuItem";
            this.newMapToolStripMenuItem.Size = new System.Drawing.Size(125, 22);
            this.newMapToolStripMenuItem.Text = "&New Map";
            this.newMapToolStripMenuItem.Click += new System.EventHandler(this.newMapToolStripMenuItem_Click);
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(122, 6);
            // 
            // saveMapToolStripMenuItem
            // 
            this.saveMapToolStripMenuItem.Name = "saveMapToolStripMenuItem";
            this.saveMapToolStripMenuItem.Size = new System.Drawing.Size(125, 22);
            this.saveMapToolStripMenuItem.Text = "&Save Map";
            this.saveMapToolStripMenuItem.Click += new System.EventHandler(this.saveMapToolStripMenuItem_Click);
            // 
            // saveAsToolStripMenuItem
            // 
            this.saveAsToolStripMenuItem.Name = "saveAsToolStripMenuItem";
            this.saveAsToolStripMenuItem.Size = new System.Drawing.Size(125, 22);
            this.saveAsToolStripMenuItem.Text = "Save As";
            this.saveAsToolStripMenuItem.Click += new System.EventHandler(this.saveAsToolStripMenuItem_Click);
            // 
            // toolStripSeparator2
            // 
            this.toolStripSeparator2.Name = "toolStripSeparator2";
            this.toolStripSeparator2.Size = new System.Drawing.Size(122, 6);
            // 
            // loadToolStripMenuItem
            // 
            this.loadToolStripMenuItem.Name = "loadToolStripMenuItem";
            this.loadToolStripMenuItem.Size = new System.Drawing.Size(125, 22);
            this.loadToolStripMenuItem.Text = "&Load";
            this.loadToolStripMenuItem.Click += new System.EventHandler(this.loadToolStripMenuItem_Click);
            // 
            // toolStripSeparator3
            // 
            this.toolStripSeparator3.Name = "toolStripSeparator3";
            this.toolStripSeparator3.Size = new System.Drawing.Size(122, 6);
            // 
            // exitToolStripMenuItem
            // 
            this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
            this.exitToolStripMenuItem.Size = new System.Drawing.Size(125, 22);
            this.exitToolStripMenuItem.Text = "E&xit";
            this.exitToolStripMenuItem.Click += new System.EventHandler(this.exitToolStripMenuItem_Click);
            // 
            // optionsToolStripMenuItem
            // 
            this.optionsToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.loadTilesetToolStripMenuItem});
            this.optionsToolStripMenuItem.Name = "optionsToolStripMenuItem";
            this.optionsToolStripMenuItem.Size = new System.Drawing.Size(61, 20);
            this.optionsToolStripMenuItem.Text = "&Options";
            // 
            // loadTilesetToolStripMenuItem
            // 
            this.loadTilesetToolStripMenuItem.Name = "loadTilesetToolStripMenuItem";
            this.loadTilesetToolStripMenuItem.Size = new System.Drawing.Size(137, 22);
            this.loadTilesetToolStripMenuItem.Text = "Load Tileset";
            this.loadTilesetToolStripMenuItem.Click += new System.EventHandler(this.loadTilesetToolStripMenuItem_Click);
            // 
            // panel1
            // 
            this.panel1.AutoScroll = true;
            this.panel1.Location = new System.Drawing.Point(0, 27);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(288, 376);
            this.panel1.TabIndex = 1;
            this.panel1.Scroll += new System.Windows.Forms.ScrollEventHandler(this.panel1_Scroll);
            this.panel1.MouseClick += new System.Windows.Forms.MouseEventHandler(this.panel1_MouseClick);
            this.panel1.MouseMove += new System.Windows.Forms.MouseEventHandler(this.panel1_MouseMove);
            this.panel1.MouseUp += new System.Windows.Forms.MouseEventHandler(this.panel1_MouseUp);
            this.panel1.Resize += new System.EventHandler(this.panel1_Resize);
            // 
            // panel2
            // 
            this.panel2.AutoScroll = true;
            this.panel2.Location = new System.Drawing.Point(294, 27);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(618, 532);
            this.panel2.TabIndex = 2;
            this.panel2.Scroll += new System.Windows.Forms.ScrollEventHandler(this.panel2_Scroll);
            this.panel2.MouseClick += new System.Windows.Forms.MouseEventHandler(this.panel2_MouseClick);
            this.panel2.MouseDown += new System.Windows.Forms.MouseEventHandler(this.panel2_MouseDown);
            this.panel2.MouseMove += new System.Windows.Forms.MouseEventHandler(this.panel2_MouseMove);
            this.panel2.MouseUp += new System.Windows.Forms.MouseEventHandler(this.panel2_MouseUp);
            this.panel2.Resize += new System.EventHandler(this.panel2_Resize);
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(198, 416);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(90, 23);
            this.button1.TabIndex = 4;
            this.button1.Text = "ShowGrid";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.MouseClick += new System.Windows.Forms.MouseEventHandler(this.button1_MouseClick);
            // 
            // lblTileWidth
            // 
            this.lblTileWidth.AutoSize = true;
            this.lblTileWidth.Location = new System.Drawing.Point(6, 21);
            this.lblTileWidth.Name = "lblTileWidth";
            this.lblTileWidth.Size = new System.Drawing.Size(55, 13);
            this.lblTileWidth.TabIndex = 7;
            this.lblTileWidth.Text = "Tile Width";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(5, 42);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(58, 13);
            this.label2.TabIndex = 8;
            this.label2.Text = "Tile Height";
            // 
            // nudTileWidth
            // 
            this.nudTileWidth.InterceptArrowKeys = false;
            this.nudTileWidth.Location = new System.Drawing.Point(76, 14);
            this.nudTileWidth.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.nudTileWidth.Name = "nudTileWidth";
            this.nudTileWidth.Size = new System.Drawing.Size(47, 20);
            this.nudTileWidth.TabIndex = 9;
            this.nudTileWidth.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // nudTileHeight
            // 
            this.nudTileHeight.InterceptArrowKeys = false;
            this.nudTileHeight.Location = new System.Drawing.Point(76, 40);
            this.nudTileHeight.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.nudTileHeight.Name = "nudTileHeight";
            this.nudTileHeight.Size = new System.Drawing.Size(47, 20);
            this.nudTileHeight.TabIndex = 10;
            this.nudTileHeight.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(6, 68);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(59, 13);
            this.label4.TabIndex = 13;
            this.label4.Text = "Map Width";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(6, 94);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(62, 13);
            this.label5.TabIndex = 14;
            this.label5.Text = "Map Height";
            // 
            // nudMapWidth
            // 
            this.nudMapWidth.Location = new System.Drawing.Point(76, 66);
            this.nudMapWidth.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.nudMapWidth.Name = "nudMapWidth";
            this.nudMapWidth.Size = new System.Drawing.Size(47, 20);
            this.nudMapWidth.TabIndex = 15;
            this.nudMapWidth.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // nudMapHeight
            // 
            this.nudMapHeight.Location = new System.Drawing.Point(76, 92);
            this.nudMapHeight.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.nudMapHeight.Name = "nudMapHeight";
            this.nudMapHeight.Size = new System.Drawing.Size(47, 20);
            this.nudMapHeight.TabIndex = 16;
            this.nudMapHeight.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.btnClear);
            this.groupBox1.Controls.Add(this.radWarp);
            this.groupBox1.Controls.Add(this.button3);
            this.groupBox1.Controls.Add(this.label6);
            this.groupBox1.Controls.Add(this.button2);
            this.groupBox1.Controls.Add(this.radNPC);
            this.groupBox1.Controls.Add(this.radBlock);
            this.groupBox1.Controls.Add(this.radMap);
            this.groupBox1.Controls.Add(this.lblTileWidth);
            this.groupBox1.Controls.Add(this.nudMapHeight);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.nudMapWidth);
            this.groupBox1.Controls.Add(this.nudTileWidth);
            this.groupBox1.Controls.Add(this.label5);
            this.groupBox1.Controls.Add(this.nudTileHeight);
            this.groupBox1.Controls.Add(this.label4);
            this.groupBox1.Location = new System.Drawing.Point(918, 24);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(223, 149);
            this.groupBox1.TabIndex = 18;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Map Data";
            // 
            // radWarp
            // 
            this.radWarp.AutoSize = true;
            this.radWarp.Location = new System.Drawing.Point(139, 83);
            this.radWarp.Name = "radWarp";
            this.radWarp.Size = new System.Drawing.Size(51, 17);
            this.radWarp.TabIndex = 22;
            this.radWarp.TabStop = true;
            this.radWarp.Text = "Warp";
            this.radWarp.UseVisualStyleBackColor = true;
            this.radWarp.CheckedChanged += new System.EventHandler(this.radWarp_CheckedChanged);
            // 
            // button3
            // 
            this.button3.Location = new System.Drawing.Point(80, 120);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(36, 23);
            this.button3.TabIndex = 21;
            this.button3.Text = "Fill";
            this.button3.UseVisualStyleBackColor = true;
            this.button3.Click += new System.EventHandler(this.button3_Click);
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(95, -2);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(0, 13);
            this.label6.TabIndex = 20;
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(122, 120);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(95, 23);
            this.button2.TabIndex = 19;
            this.button2.Text = "Transparency";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // radNPC
            // 
            this.radNPC.AutoSize = true;
            this.radNPC.Location = new System.Drawing.Point(139, 60);
            this.radNPC.Name = "radNPC";
            this.radNPC.Size = new System.Drawing.Size(47, 17);
            this.radNPC.TabIndex = 20;
            this.radNPC.Text = "NPC";
            this.radNPC.UseVisualStyleBackColor = true;
            this.radNPC.CheckedChanged += new System.EventHandler(this.radNPC_CheckedChanged);
            // 
            // radBlock
            // 
            this.radBlock.AutoSize = true;
            this.radBlock.Location = new System.Drawing.Point(139, 37);
            this.radBlock.Name = "radBlock";
            this.radBlock.Size = new System.Drawing.Size(52, 17);
            this.radBlock.TabIndex = 18;
            this.radBlock.Text = "Block";
            this.radBlock.UseVisualStyleBackColor = true;
            // 
            // radMap
            // 
            this.radMap.AutoSize = true;
            this.radMap.Checked = true;
            this.radMap.Location = new System.Drawing.Point(139, 14);
            this.radMap.Name = "radMap";
            this.radMap.Size = new System.Drawing.Size(67, 17);
            this.radMap.TabIndex = 17;
            this.radMap.TabStop = true;
            this.radMap.Text = "Edit Map";
            this.radMap.UseVisualStyleBackColor = true;
            // 
            // grpWarp
            // 
            this.grpWarp.Controls.Add(this.lstMaps);
            this.grpWarp.Controls.Add(this.btnWarpCancel);
            this.grpWarp.Controls.Add(this.nudWarpY);
            this.grpWarp.Controls.Add(this.nudWarpX);
            this.grpWarp.Controls.Add(this.btnWarp);
            this.grpWarp.Controls.Add(this.label11);
            this.grpWarp.Controls.Add(this.label10);
            this.grpWarp.Controls.Add(this.label9);
            this.grpWarp.Location = new System.Drawing.Point(919, 179);
            this.grpWarp.Name = "grpWarp";
            this.grpWarp.Size = new System.Drawing.Size(223, 201);
            this.grpWarp.TabIndex = 21;
            this.grpWarp.TabStop = false;
            this.grpWarp.Text = "Warp Data";
            this.grpWarp.Visible = false;
            // 
            // lstMaps
            // 
            this.lstMaps.FormattingEnabled = true;
            this.lstMaps.Location = new System.Drawing.Point(42, 21);
            this.lstMaps.Name = "lstMaps";
            this.lstMaps.Size = new System.Drawing.Size(164, 121);
            this.lstMaps.TabIndex = 8;
            this.lstMaps.SelectedIndexChanged += new System.EventHandler(this.txtWarp_TextChanged);
            // 
            // btnWarpCancel
            // 
            this.btnWarpCancel.Enabled = false;
            this.btnWarpCancel.Location = new System.Drawing.Point(9, 172);
            this.btnWarpCancel.Name = "btnWarpCancel";
            this.btnWarpCancel.Size = new System.Drawing.Size(75, 23);
            this.btnWarpCancel.TabIndex = 7;
            this.btnWarpCancel.Text = "Cancel";
            this.btnWarpCancel.UseVisualStyleBackColor = true;
            this.btnWarpCancel.Click += new System.EventHandler(this.btnWarpCancel_Click);
            // 
            // nudWarpY
            // 
            this.nudWarpY.Location = new System.Drawing.Point(160, 149);
            this.nudWarpY.Name = "nudWarpY";
            this.nudWarpY.Size = new System.Drawing.Size(46, 20);
            this.nudWarpY.TabIndex = 6;
            this.nudWarpY.ValueChanged += new System.EventHandler(this.txtWarp_TextChanged);
            // 
            // nudWarpX
            // 
            this.nudWarpX.Location = new System.Drawing.Point(56, 149);
            this.nudWarpX.Name = "nudWarpX";
            this.nudWarpX.Size = new System.Drawing.Size(46, 20);
            this.nudWarpX.TabIndex = 5;
            this.nudWarpX.ValueChanged += new System.EventHandler(this.txtWarp_TextChanged);
            // 
            // btnWarp
            // 
            this.btnWarp.Enabled = false;
            this.btnWarp.Location = new System.Drawing.Point(131, 172);
            this.btnWarp.Name = "btnWarp";
            this.btnWarp.Size = new System.Drawing.Size(75, 23);
            this.btnWarp.TabIndex = 4;
            this.btnWarp.Text = "Apply";
            this.btnWarp.UseVisualStyleBackColor = true;
            this.btnWarp.Click += new System.EventHandler(this.btnWarp_Click);
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(111, 151);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(43, 13);
            this.label11.TabIndex = 3;
            this.label11.Text = "Warp Y";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(7, 151);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(43, 13);
            this.label10.TabIndex = 2;
            this.label10.Text = "Warp X";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(7, 20);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(28, 13);
            this.label9.TabIndex = 0;
            this.label9.Text = "Map";
            // 
            // grpNPC
            // 
            this.grpNPC.Controls.Add(this.btnNPCMove);
            this.grpNPC.Controls.Add(this.btnNPCUnits);
            this.grpNPC.Controls.Add(this.btnNpcAdd);
            this.grpNPC.Controls.Add(this.btnNpcApply);
            this.grpNPC.Controls.Add(this.btnNpcCancel);
            this.grpNPC.Controls.Add(this.chkMoves);
            this.grpNPC.Controls.Add(this.label8);
            this.grpNPC.Controls.Add(this.textBox1);
            this.grpNPC.Controls.Add(this.chkHostile);
            this.grpNPC.Controls.Add(this.label7);
            this.grpNPC.Controls.Add(this.lstNpcs);
            this.grpNPC.Location = new System.Drawing.Point(918, 179);
            this.grpNPC.Name = "grpNPC";
            this.grpNPC.Size = new System.Drawing.Size(223, 212);
            this.grpNPC.TabIndex = 22;
            this.grpNPC.TabStop = false;
            this.grpNPC.Text = "NPC Tool";
            this.grpNPC.Visible = false;
            // 
            // btnNPCMove
            // 
            this.btnNPCMove.Enabled = false;
            this.btnNPCMove.Location = new System.Drawing.Point(122, 182);
            this.btnNPCMove.Name = "btnNPCMove";
            this.btnNPCMove.Size = new System.Drawing.Size(45, 23);
            this.btnNPCMove.TabIndex = 11;
            this.btnNPCMove.Text = "Move";
            this.btnNPCMove.UseVisualStyleBackColor = true;
            this.btnNPCMove.Click += new System.EventHandler(this.btnNPCMove_Click);
            // 
            // btnNPCUnits
            // 
            this.btnNPCUnits.Enabled = false;
            this.btnNPCUnits.Location = new System.Drawing.Point(67, 181);
            this.btnNPCUnits.Name = "btnNPCUnits";
            this.btnNPCUnits.Size = new System.Drawing.Size(49, 23);
            this.btnNPCUnits.TabIndex = 10;
            this.btnNPCUnits.Text = "Units";
            this.btnNPCUnits.UseVisualStyleBackColor = true;
            // 
            // btnNpcAdd
            // 
            this.btnNpcAdd.Enabled = false;
            this.btnNpcAdd.Location = new System.Drawing.Point(173, 154);
            this.btnNpcAdd.Name = "btnNpcAdd";
            this.btnNpcAdd.Size = new System.Drawing.Size(40, 23);
            this.btnNpcAdd.TabIndex = 9;
            this.btnNpcAdd.Text = "Add";
            this.btnNpcAdd.UseVisualStyleBackColor = true;
            this.btnNpcAdd.Click += new System.EventHandler(this.btnNpcAdd_Click);
            // 
            // btnNpcApply
            // 
            this.btnNpcApply.Enabled = false;
            this.btnNpcApply.Location = new System.Drawing.Point(173, 181);
            this.btnNpcApply.Name = "btnNpcApply";
            this.btnNpcApply.Size = new System.Drawing.Size(44, 23);
            this.btnNpcApply.TabIndex = 8;
            this.btnNpcApply.Text = "Apply";
            this.btnNpcApply.UseVisualStyleBackColor = true;
            this.btnNpcApply.Click += new System.EventHandler(this.btnNpcApply_Click);
            // 
            // btnNpcCancel
            // 
            this.btnNpcCancel.Enabled = false;
            this.btnNpcCancel.Location = new System.Drawing.Point(8, 181);
            this.btnNpcCancel.Name = "btnNpcCancel";
            this.btnNpcCancel.Size = new System.Drawing.Size(53, 23);
            this.btnNpcCancel.TabIndex = 7;
            this.btnNpcCancel.Text = "Cancel";
            this.btnNpcCancel.UseVisualStyleBackColor = true;
            this.btnNpcCancel.Click += new System.EventHandler(this.btnNpcCancel_Click);
            // 
            // chkMoves
            // 
            this.chkMoves.AutoSize = true;
            this.chkMoves.Location = new System.Drawing.Point(109, 158);
            this.chkMoves.Name = "chkMoves";
            this.chkMoves.Size = new System.Drawing.Size(58, 17);
            this.chkMoves.TabIndex = 5;
            this.chkMoves.Text = "Moves";
            this.chkMoves.UseVisualStyleBackColor = true;
            this.chkMoves.CheckedChanged += new System.EventHandler(this.chkMoves_CheckedChanged);
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(11, 131);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(35, 13);
            this.label8.TabIndex = 4;
            this.label8.Text = "Name";
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(57, 128);
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(152, 20);
            this.textBox1.TabIndex = 3;
            this.textBox1.TextChanged += new System.EventHandler(this.textBox1_TextChanged);
            // 
            // chkHostile
            // 
            this.chkHostile.AutoSize = true;
            this.chkHostile.Location = new System.Drawing.Point(37, 158);
            this.chkHostile.Name = "chkHostile";
            this.chkHostile.Size = new System.Drawing.Size(65, 17);
            this.chkHostile.TabIndex = 2;
            this.chkHostile.Text = "isHostile";
            this.chkHostile.UseVisualStyleBackColor = true;
            this.chkHostile.CheckedChanged += new System.EventHandler(this.chkHostile_CheckedChanged);
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(7, 16);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(44, 13);
            this.label7.TabIndex = 1;
            this.label7.Text = "Created";
            // 
            // lstNpcs
            // 
            this.lstNpcs.FormattingEnabled = true;
            this.lstNpcs.Location = new System.Drawing.Point(10, 32);
            this.lstNpcs.Name = "lstNpcs";
            this.lstNpcs.Size = new System.Drawing.Size(199, 95);
            this.lstNpcs.TabIndex = 0;
            // 
            // grpWayPoints
            // 
            this.grpWayPoints.Controls.Add(this.label12);
            this.grpWayPoints.Controls.Add(this.radWPMove);
            this.grpWayPoints.Controls.Add(this.radWPAdd);
            this.grpWayPoints.Controls.Add(this.lstWaypoints);
            this.grpWayPoints.Location = new System.Drawing.Point(918, 397);
            this.grpWayPoints.Name = "grpWayPoints";
            this.grpWayPoints.Size = new System.Drawing.Size(222, 146);
            this.grpWayPoints.TabIndex = 23;
            this.grpWayPoints.TabStop = false;
            this.grpWayPoints.Text = "Waypoints";
            this.grpWayPoints.Visible = false;
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(59, 117);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(157, 13);
            this.label12.TabIndex = 15;
            this.label12.Text = "Right click on the map to delete";
            // 
            // radWPMove
            // 
            this.radWPMove.AutoSize = true;
            this.radWPMove.Location = new System.Drawing.Point(8, 123);
            this.radWPMove.Name = "radWPMove";
            this.radWPMove.Size = new System.Drawing.Size(52, 17);
            this.radWPMove.TabIndex = 14;
            this.radWPMove.Text = "Move";
            this.radWPMove.UseVisualStyleBackColor = true;
            // 
            // radWPAdd
            // 
            this.radWPAdd.AutoSize = true;
            this.radWPAdd.Checked = true;
            this.radWPAdd.Location = new System.Drawing.Point(9, 107);
            this.radWPAdd.Name = "radWPAdd";
            this.radWPAdd.Size = new System.Drawing.Size(44, 17);
            this.radWPAdd.TabIndex = 12;
            this.radWPAdd.TabStop = true;
            this.radWPAdd.Text = "Add";
            this.radWPAdd.UseVisualStyleBackColor = true;
            // 
            // lstWaypoints
            // 
            this.lstWaypoints.FormattingEnabled = true;
            this.lstWaypoints.Location = new System.Drawing.Point(9, 19);
            this.lstWaypoints.Name = "lstWaypoints";
            this.lstWaypoints.Size = new System.Drawing.Size(204, 82);
            this.lstWaypoints.TabIndex = 11;
            // 
            // lstLayers
            // 
            this.lstLayers.FormattingEnabled = true;
            this.lstLayers.Location = new System.Drawing.Point(12, 409);
            this.lstLayers.Name = "lstLayers";
            this.lstLayers.Size = new System.Drawing.Size(179, 108);
            this.lstLayers.TabIndex = 0;
            this.lstLayers.SelectedIndexChanged += new System.EventHandler(this.lstLayers_SelectedIndexChanged);
            // 
            // btnNewLayer
            // 
            this.btnNewLayer.Location = new System.Drawing.Point(120, 520);
            this.btnNewLayer.Name = "btnNewLayer";
            this.btnNewLayer.Size = new System.Drawing.Size(71, 23);
            this.btnNewLayer.TabIndex = 24;
            this.btnNewLayer.Text = "New Layer";
            this.btnNewLayer.UseVisualStyleBackColor = true;
            this.btnNewLayer.Click += new System.EventHandler(this.btnNewLayer_Click);
            // 
            // btnDelete
            // 
            this.btnDelete.Enabled = false;
            this.btnDelete.Location = new System.Drawing.Point(12, 520);
            this.btnDelete.Name = "btnDelete";
            this.btnDelete.Size = new System.Drawing.Size(56, 23);
            this.btnDelete.TabIndex = 25;
            this.btnDelete.Text = "Delete";
            this.btnDelete.UseVisualStyleBackColor = true;
            this.btnDelete.Click += new System.EventHandler(this.btnDelete_Click);
            // 
            // btnShiftUp
            // 
            this.btnShiftUp.Enabled = false;
            this.btnShiftUp.Location = new System.Drawing.Point(198, 464);
            this.btnShiftUp.Name = "btnShiftUp";
            this.btnShiftUp.Size = new System.Drawing.Size(90, 23);
            this.btnShiftUp.TabIndex = 26;
            this.btnShiftUp.Text = "Move Up";
            this.btnShiftUp.UseVisualStyleBackColor = true;
            // 
            // btnShiftDown
            // 
            this.btnShiftDown.Enabled = false;
            this.btnShiftDown.Location = new System.Drawing.Point(198, 493);
            this.btnShiftDown.Name = "btnShiftDown";
            this.btnShiftDown.Size = new System.Drawing.Size(90, 23);
            this.btnShiftDown.TabIndex = 27;
            this.btnShiftDown.Text = "Move Down";
            this.btnShiftDown.UseVisualStyleBackColor = true;
            this.btnShiftDown.Click += new System.EventHandler(this.btnShiftDown_Click);
            // 
            // btnClear
            // 
            this.btnClear.Location = new System.Drawing.Point(8, 119);
            this.btnClear.Name = "btnClear";
            this.btnClear.Size = new System.Drawing.Size(57, 23);
            this.btnClear.TabIndex = 23;
            this.btnClear.Text = "Clear";
            this.btnClear.UseVisualStyleBackColor = true;
            this.btnClear.Click += new System.EventHandler(this.btnClear_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.ActiveCaption;
            this.ClientSize = new System.Drawing.Size(1153, 564);
            this.Controls.Add(this.btnShiftDown);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.btnShiftUp);
            this.Controls.Add(this.btnDelete);
            this.Controls.Add(this.btnNewLayer);
            this.Controls.Add(this.lstLayers);
            this.Controls.Add(this.grpWayPoints);
            this.Controls.Add(this.grpNPC);
            this.Controls.Add(this.grpWarp);
            this.Controls.Add(this.panel2);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.menuStrip1);
            this.Controls.Add(this.groupBox1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "Form1";
            this.Text = "Path of Arin - Level Editor";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.nudTileWidth)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudTileHeight)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudMapWidth)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudMapHeight)).EndInit();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.grpWarp.ResumeLayout(false);
            this.grpWarp.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.nudWarpY)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudWarpX)).EndInit();
            this.grpNPC.ResumeLayout(false);
            this.grpNPC.PerformLayout();
            this.grpWayPoints.ResumeLayout(false);
            this.grpWayPoints.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem optionsToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem newMapToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripMenuItem saveMapToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem saveAsToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
        private System.Windows.Forms.ToolStripMenuItem loadToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator3;
        private System.Windows.Forms.ToolStripMenuItem exitToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem loadTilesetToolStripMenuItem;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Panel panel2;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Label lblTileWidth;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.NumericUpDown nudTileWidth;
        private System.Windows.Forms.NumericUpDown nudTileHeight;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.NumericUpDown nudMapWidth;
        private System.Windows.Forms.NumericUpDown nudMapHeight;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.RadioButton radNPC;
        private System.Windows.Forms.RadioButton radBlock;
        private System.Windows.Forms.RadioButton radMap;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.RadioButton radWarp;
        private System.Windows.Forms.GroupBox grpWarp;
        private System.Windows.Forms.NumericUpDown nudWarpY;
        private System.Windows.Forms.NumericUpDown nudWarpX;
        private System.Windows.Forms.Button btnWarp;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Button btnWarpCancel;
        private System.Windows.Forms.ListBox lstMaps;
        private System.Windows.Forms.GroupBox grpNPC;
        private System.Windows.Forms.Button btnNpcAdd;
        private System.Windows.Forms.Button btnNpcApply;
        private System.Windows.Forms.Button btnNpcCancel;
        private System.Windows.Forms.CheckBox chkMoves;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.CheckBox chkHostile;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.ListBox lstNpcs;
        private System.Windows.Forms.Button btnNPCMove;
        private System.Windows.Forms.Button btnNPCUnits;
        private System.Windows.Forms.GroupBox grpWayPoints;
        private System.Windows.Forms.RadioButton radWPMove;
        private System.Windows.Forms.RadioButton radWPAdd;
        private System.Windows.Forms.ListBox lstWaypoints;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.ListBox lstLayers;
        private System.Windows.Forms.Button btnNewLayer;
        private System.Windows.Forms.Button btnDelete;
        private System.Windows.Forms.Button btnShiftUp;
        private System.Windows.Forms.Button btnShiftDown;
        private System.Windows.Forms.Button btnClear;
    }
}

