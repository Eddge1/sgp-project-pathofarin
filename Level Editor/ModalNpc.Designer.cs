namespace SGP_PoA_LevelEditor
{
    partial class ModalNpc
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
            this.lstNPC = new System.Windows.Forms.ListBox();
            this.label1 = new System.Windows.Forms.Label();
            this.btnAdd = new System.Windows.Forms.Button();
            this.dtnDel = new System.Windows.Forms.Button();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.txtFileName = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.grpUnitList = new System.Windows.Forms.GroupBox();
            this.lstUnits = new System.Windows.Forms.ListBox();
            this.button2 = new System.Windows.Forms.Button();
            this.button1 = new System.Windows.Forms.Button();
            this.lstAddUnit = new System.Windows.Forms.ListBox();
            this.btnConvoDel = new System.Windows.Forms.Button();
            this.txtEvent = new System.Windows.Forms.TextBox();
            this.btnConvoAdd = new System.Windows.Forms.Button();
            this.label5 = new System.Windows.Forms.Label();
            this.txtConvo = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.lstConversation = new System.Windows.Forms.ListBox();
            this.checkBox1 = new System.Windows.Forms.CheckBox();
            this.txtName = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.btnDone = new System.Windows.Forms.Button();
            this.grpUnits = new System.Windows.Forms.GroupBox();
            this.nudSpeed = new System.Windows.Forms.NumericUpDown();
            this.nudExperience = new System.Windows.Forms.NumericUpDown();
            this.nudLevel = new System.Windows.Forms.NumericUpDown();
            this.nudAP = new System.Windows.Forms.NumericUpDown();
            this.nudHealth = new System.Windows.Forms.NumericUpDown();
            this.nudAttack = new System.Windows.Forms.NumericUpDown();
            this.label14 = new System.Windows.Forms.Label();
            this.cmb_AI = new System.Windows.Forms.ComboBox();
            this.txtUnitName = new System.Windows.Forms.TextBox();
            this.label13 = new System.Windows.Forms.Label();
            this.label12 = new System.Windows.Forms.Label();
            this.label11 = new System.Windows.Forms.Label();
            this.label10 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.lstItems = new System.Windows.Forms.ListBox();
            this.btnRemoveItem = new System.Windows.Forms.Button();
            this.cmb_Items = new System.Windows.Forms.ComboBox();
            this.btnAddItem = new System.Windows.Forms.Button();
            this.nudDropChance = new System.Windows.Forms.NumericUpDown();
            this.label6 = new System.Windows.Forms.Label();
            this.button3 = new System.Windows.Forms.Button();
            this.button4 = new System.Windows.Forms.Button();
            this.label15 = new System.Windows.Forms.Label();
            this.lstUnitSelection = new System.Windows.Forms.ListBox();
            this.btnNewUnit = new System.Windows.Forms.Button();
            this.btnNewNPC = new System.Windows.Forms.Button();
            this.groupBox1.SuspendLayout();
            this.grpUnitList.SuspendLayout();
            this.grpUnits.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.nudSpeed)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudExperience)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudLevel)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudAP)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudHealth)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudAttack)).BeginInit();
            this.groupBox2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.nudDropChance)).BeginInit();
            this.SuspendLayout();
            // 
            // lstNPC
            // 
            this.lstNPC.FormattingEnabled = true;
            this.lstNPC.Location = new System.Drawing.Point(12, 29);
            this.lstNPC.Name = "lstNPC";
            this.lstNPC.Size = new System.Drawing.Size(120, 121);
            this.lstNPC.TabIndex = 0;
            this.lstNPC.SelectedIndexChanged += new System.EventHandler(this.lstNPC_SelectedIndexChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(9, 13);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(48, 13);
            this.label1.TabIndex = 1;
            this.label1.Text = "NPC List";
            // 
            // btnAdd
            // 
            this.btnAdd.Location = new System.Drawing.Point(138, 53);
            this.btnAdd.Name = "btnAdd";
            this.btnAdd.Size = new System.Drawing.Size(47, 23);
            this.btnAdd.TabIndex = 2;
            this.btnAdd.Text = "Add";
            this.btnAdd.UseVisualStyleBackColor = true;
            this.btnAdd.Click += new System.EventHandler(this.btnAdd_Click);
            // 
            // dtnDel
            // 
            this.dtnDel.Location = new System.Drawing.Point(138, 127);
            this.dtnDel.Name = "dtnDel";
            this.dtnDel.Size = new System.Drawing.Size(47, 23);
            this.dtnDel.TabIndex = 3;
            this.dtnDel.Text = "Delete";
            this.dtnDel.UseVisualStyleBackColor = true;
            this.dtnDel.Click += new System.EventHandler(this.dtnDel_Click);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.txtFileName);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.grpUnitList);
            this.groupBox1.Controls.Add(this.btnConvoDel);
            this.groupBox1.Controls.Add(this.txtEvent);
            this.groupBox1.Controls.Add(this.btnConvoAdd);
            this.groupBox1.Controls.Add(this.label5);
            this.groupBox1.Controls.Add(this.txtConvo);
            this.groupBox1.Controls.Add(this.label4);
            this.groupBox1.Controls.Add(this.lstConversation);
            this.groupBox1.Controls.Add(this.checkBox1);
            this.groupBox1.Controls.Add(this.txtName);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Location = new System.Drawing.Point(191, 13);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(519, 316);
            this.groupBox1.TabIndex = 5;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "NPC Stats";
            this.groupBox1.Visible = false;
            // 
            // txtFileName
            // 
            this.txtFileName.Location = new System.Drawing.Point(13, 186);
            this.txtFileName.Name = "txtFileName";
            this.txtFileName.Size = new System.Drawing.Size(100, 20);
            this.txtFileName.TabIndex = 15;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(10, 170);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(54, 13);
            this.label2.TabIndex = 14;
            this.label2.Text = "File Name";
            // 
            // grpUnitList
            // 
            this.grpUnitList.Controls.Add(this.lstUnits);
            this.grpUnitList.Controls.Add(this.button2);
            this.grpUnitList.Controls.Add(this.button1);
            this.grpUnitList.Controls.Add(this.lstAddUnit);
            this.grpUnitList.Location = new System.Drawing.Point(167, 162);
            this.grpUnitList.Name = "grpUnitList";
            this.grpUnitList.Size = new System.Drawing.Size(340, 148);
            this.grpUnitList.TabIndex = 13;
            this.grpUnitList.TabStop = false;
            this.grpUnitList.Text = "Units In NPC";
            this.grpUnitList.Visible = false;
            // 
            // lstUnits
            // 
            this.lstUnits.FormattingEnabled = true;
            this.lstUnits.Location = new System.Drawing.Point(6, 21);
            this.lstUnits.Name = "lstUnits";
            this.lstUnits.Size = new System.Drawing.Size(144, 121);
            this.lstUnits.TabIndex = 3;
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(156, 108);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(31, 23);
            this.button2.TabIndex = 2;
            this.button2.Text = "X";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(156, 36);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(31, 23);
            this.button1.TabIndex = 1;
            this.button1.Text = ">>";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // lstAddUnit
            // 
            this.lstAddUnit.FormattingEnabled = true;
            this.lstAddUnit.Location = new System.Drawing.Point(193, 21);
            this.lstAddUnit.Name = "lstAddUnit";
            this.lstAddUnit.Size = new System.Drawing.Size(133, 121);
            this.lstAddUnit.TabIndex = 0;
            // 
            // btnConvoDel
            // 
            this.btnConvoDel.Location = new System.Drawing.Point(160, 104);
            this.btnConvoDel.Name = "btnConvoDel";
            this.btnConvoDel.Size = new System.Drawing.Size(36, 23);
            this.btnConvoDel.TabIndex = 12;
            this.btnConvoDel.Text = "Delete";
            this.btnConvoDel.UseVisualStyleBackColor = true;
            this.btnConvoDel.Click += new System.EventHandler(this.btnConvoDel_Click);
            // 
            // txtEvent
            // 
            this.txtEvent.Location = new System.Drawing.Point(244, 133);
            this.txtEvent.Name = "txtEvent";
            this.txtEvent.Size = new System.Drawing.Size(263, 20);
            this.txtEvent.TabIndex = 11;
            // 
            // btnConvoAdd
            // 
            this.btnConvoAdd.Location = new System.Drawing.Point(160, 35);
            this.btnConvoAdd.Name = "btnConvoAdd";
            this.btnConvoAdd.Size = new System.Drawing.Size(36, 23);
            this.btnConvoAdd.TabIndex = 10;
            this.btnConvoAdd.Text = "Add";
            this.btnConvoAdd.UseVisualStyleBackColor = true;
            this.btnConvoAdd.Click += new System.EventHandler(this.btnConvoAdd_Click);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(199, 136);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(35, 13);
            this.label5.TabIndex = 9;
            this.label5.Text = "Event";
            // 
            // txtConvo
            // 
            this.txtConvo.Location = new System.Drawing.Point(202, 32);
            this.txtConvo.Multiline = true;
            this.txtConvo.Name = "txtConvo";
            this.txtConvo.Size = new System.Drawing.Size(305, 95);
            this.txtConvo.TabIndex = 8;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(199, 16);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(28, 13);
            this.label4.TabIndex = 7;
            this.label4.Text = "Text";
            // 
            // lstConversation
            // 
            this.lstConversation.FormattingEnabled = true;
            this.lstConversation.Location = new System.Drawing.Point(13, 32);
            this.lstConversation.Name = "lstConversation";
            this.lstConversation.Size = new System.Drawing.Size(141, 95);
            this.lstConversation.TabIndex = 6;
            this.lstConversation.SelectedIndexChanged += new System.EventHandler(this.lstConversation_SelectedIndexChanged);
            // 
            // checkBox1
            // 
            this.checkBox1.AutoSize = true;
            this.checkBox1.Location = new System.Drawing.Point(26, 251);
            this.checkBox1.Name = "checkBox1";
            this.checkBox1.Size = new System.Drawing.Size(58, 17);
            this.checkBox1.TabIndex = 4;
            this.checkBox1.Text = "Hostile";
            this.checkBox1.UseVisualStyleBackColor = true;
            this.checkBox1.CheckedChanged += new System.EventHandler(this.checkBox1_CheckedChanged);
            // 
            // txtName
            // 
            this.txtName.Location = new System.Drawing.Point(13, 225);
            this.txtName.Name = "txtName";
            this.txtName.Size = new System.Drawing.Size(100, 20);
            this.txtName.TabIndex = 3;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(10, 209);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(35, 13);
            this.label3.TabIndex = 2;
            this.label3.Text = "Name";
            // 
            // btnDone
            // 
            this.btnDone.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.btnDone.Location = new System.Drawing.Point(12, 306);
            this.btnDone.Name = "btnDone";
            this.btnDone.Size = new System.Drawing.Size(75, 23);
            this.btnDone.TabIndex = 6;
            this.btnDone.Text = "Done";
            this.btnDone.UseVisualStyleBackColor = true;
            this.btnDone.Click += new System.EventHandler(this.btnDone_Click);
            // 
            // grpUnits
            // 
            this.grpUnits.Controls.Add(this.nudSpeed);
            this.grpUnits.Controls.Add(this.nudExperience);
            this.grpUnits.Controls.Add(this.nudLevel);
            this.grpUnits.Controls.Add(this.nudAP);
            this.grpUnits.Controls.Add(this.nudHealth);
            this.grpUnits.Controls.Add(this.nudAttack);
            this.grpUnits.Controls.Add(this.label14);
            this.grpUnits.Controls.Add(this.cmb_AI);
            this.grpUnits.Controls.Add(this.txtUnitName);
            this.grpUnits.Controls.Add(this.label13);
            this.grpUnits.Controls.Add(this.label12);
            this.grpUnits.Controls.Add(this.label11);
            this.grpUnits.Controls.Add(this.label10);
            this.grpUnits.Controls.Add(this.label9);
            this.grpUnits.Controls.Add(this.label8);
            this.grpUnits.Controls.Add(this.label7);
            this.grpUnits.Controls.Add(this.groupBox2);
            this.grpUnits.Location = new System.Drawing.Point(191, 13);
            this.grpUnits.Name = "grpUnits";
            this.grpUnits.Size = new System.Drawing.Size(519, 222);
            this.grpUnits.TabIndex = 8;
            this.grpUnits.TabStop = false;
            this.grpUnits.Text = "Unit Stats";
            this.grpUnits.Visible = false;
            // 
            // nudSpeed
            // 
            this.nudSpeed.Location = new System.Drawing.Point(91, 133);
            this.nudSpeed.Maximum = new decimal(new int[] {
            10000,
            0,
            0,
            0});
            this.nudSpeed.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.nudSpeed.Name = "nudSpeed";
            this.nudSpeed.Size = new System.Drawing.Size(62, 20);
            this.nudSpeed.TabIndex = 23;
            this.nudSpeed.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // nudExperience
            // 
            this.nudExperience.Location = new System.Drawing.Point(91, 107);
            this.nudExperience.Maximum = new decimal(new int[] {
            10000,
            0,
            0,
            0});
            this.nudExperience.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.nudExperience.Name = "nudExperience";
            this.nudExperience.Size = new System.Drawing.Size(62, 20);
            this.nudExperience.TabIndex = 22;
            this.nudExperience.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // nudLevel
            // 
            this.nudLevel.Location = new System.Drawing.Point(91, 79);
            this.nudLevel.Maximum = new decimal(new int[] {
            10000,
            0,
            0,
            0});
            this.nudLevel.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.nudLevel.Name = "nudLevel";
            this.nudLevel.Size = new System.Drawing.Size(62, 20);
            this.nudLevel.TabIndex = 21;
            this.nudLevel.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // nudAP
            // 
            this.nudAP.Location = new System.Drawing.Point(215, 79);
            this.nudAP.Maximum = new decimal(new int[] {
            10000,
            0,
            0,
            0});
            this.nudAP.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.nudAP.Name = "nudAP";
            this.nudAP.Size = new System.Drawing.Size(120, 20);
            this.nudAP.TabIndex = 20;
            this.nudAP.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // nudHealth
            // 
            this.nudHealth.Location = new System.Drawing.Point(215, 53);
            this.nudHealth.Maximum = new decimal(new int[] {
            10000,
            0,
            0,
            0});
            this.nudHealth.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.nudHealth.Name = "nudHealth";
            this.nudHealth.Size = new System.Drawing.Size(120, 20);
            this.nudHealth.TabIndex = 19;
            this.nudHealth.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // nudAttack
            // 
            this.nudAttack.Location = new System.Drawing.Point(215, 25);
            this.nudAttack.Maximum = new decimal(new int[] {
            10000,
            0,
            0,
            0});
            this.nudAttack.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.nudAttack.Name = "nudAttack";
            this.nudAttack.Size = new System.Drawing.Size(120, 20);
            this.nudAttack.TabIndex = 18;
            this.nudAttack.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Location = new System.Drawing.Point(52, 81);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(33, 13);
            this.label14.TabIndex = 17;
            this.label14.Text = "Level";
            // 
            // cmb_AI
            // 
            this.cmb_AI.FormattingEnabled = true;
            this.cmb_AI.Location = new System.Drawing.Point(55, 52);
            this.cmb_AI.Name = "cmb_AI";
            this.cmb_AI.Size = new System.Drawing.Size(100, 21);
            this.cmb_AI.TabIndex = 16;
            // 
            // txtUnitName
            // 
            this.txtUnitName.Location = new System.Drawing.Point(55, 24);
            this.txtUnitName.Name = "txtUnitName";
            this.txtUnitName.Size = new System.Drawing.Size(100, 20);
            this.txtUnitName.TabIndex = 15;
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Location = new System.Drawing.Point(182, 81);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(21, 13);
            this.label13.TabIndex = 14;
            this.label13.Text = "AP";
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(165, 55);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(38, 13);
            this.label12.TabIndex = 13;
            this.label12.Text = "Health";
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(47, 135);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(38, 13);
            this.label11.TabIndex = 12;
            this.label11.Text = "Speed";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(25, 109);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(60, 13);
            this.label10.TabIndex = 11;
            this.label10.Text = "Experience";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(32, 55);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(17, 13);
            this.label9.TabIndex = 10;
            this.label9.Text = "AI";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(14, 27);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(35, 13);
            this.label8.TabIndex = 9;
            this.label8.Text = "Name";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(165, 27);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(38, 13);
            this.label7.TabIndex = 8;
            this.label7.Text = "Attack";
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.lstItems);
            this.groupBox2.Controls.Add(this.btnRemoveItem);
            this.groupBox2.Controls.Add(this.cmb_Items);
            this.groupBox2.Controls.Add(this.btnAddItem);
            this.groupBox2.Controls.Add(this.nudDropChance);
            this.groupBox2.Controls.Add(this.label6);
            this.groupBox2.Location = new System.Drawing.Point(370, 16);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(143, 195);
            this.groupBox2.TabIndex = 6;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Drop Items";
            // 
            // lstItems
            // 
            this.lstItems.FormattingEnabled = true;
            this.lstItems.Location = new System.Drawing.Point(8, 16);
            this.lstItems.Name = "lstItems";
            this.lstItems.Size = new System.Drawing.Size(128, 95);
            this.lstItems.TabIndex = 1;
            this.lstItems.SelectedIndexChanged += new System.EventHandler(this.lstItems_SelectedIndexChanged);
            // 
            // btnRemoveItem
            // 
            this.btnRemoveItem.Location = new System.Drawing.Point(86, 117);
            this.btnRemoveItem.Name = "btnRemoveItem";
            this.btnRemoveItem.Size = new System.Drawing.Size(50, 23);
            this.btnRemoveItem.TabIndex = 5;
            this.btnRemoveItem.Text = "Del";
            this.btnRemoveItem.UseVisualStyleBackColor = true;
            this.btnRemoveItem.Click += new System.EventHandler(this.btnRemoveItem_Click);
            // 
            // cmb_Items
            // 
            this.cmb_Items.FormattingEnabled = true;
            this.cmb_Items.Location = new System.Drawing.Point(8, 143);
            this.cmb_Items.Name = "cmb_Items";
            this.cmb_Items.Size = new System.Drawing.Size(128, 21);
            this.cmb_Items.TabIndex = 0;
            // 
            // btnAddItem
            // 
            this.btnAddItem.Location = new System.Drawing.Point(8, 117);
            this.btnAddItem.Name = "btnAddItem";
            this.btnAddItem.Size = new System.Drawing.Size(50, 23);
            this.btnAddItem.TabIndex = 4;
            this.btnAddItem.Text = "Add";
            this.btnAddItem.UseVisualStyleBackColor = true;
            this.btnAddItem.Click += new System.EventHandler(this.btnAddItem_Click);
            // 
            // nudDropChance
            // 
            this.nudDropChance.Location = new System.Drawing.Point(79, 165);
            this.nudDropChance.Name = "nudDropChance";
            this.nudDropChance.Size = new System.Drawing.Size(57, 20);
            this.nudDropChance.TabIndex = 2;
            this.nudDropChance.ValueChanged += new System.EventHandler(this.nudDropChance_ValueChanged);
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(6, 167);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(67, 13);
            this.label6.TabIndex = 3;
            this.label6.Text = "DropChance";
            // 
            // button3
            // 
            this.button3.Location = new System.Drawing.Point(138, 270);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(47, 23);
            this.button3.TabIndex = 12;
            this.button3.Text = "Delete";
            this.button3.UseVisualStyleBackColor = true;
            this.button3.Click += new System.EventHandler(this.button3_Click);
            // 
            // button4
            // 
            this.button4.Location = new System.Drawing.Point(138, 196);
            this.button4.Name = "button4";
            this.button4.Size = new System.Drawing.Size(47, 23);
            this.button4.TabIndex = 11;
            this.button4.Text = "Add";
            this.button4.UseVisualStyleBackColor = true;
            this.button4.Click += new System.EventHandler(this.button4_Click);
            // 
            // label15
            // 
            this.label15.AutoSize = true;
            this.label15.Location = new System.Drawing.Point(9, 156);
            this.label15.Name = "label15";
            this.label15.Size = new System.Drawing.Size(45, 13);
            this.label15.TabIndex = 10;
            this.label15.Text = "Unit List";
            // 
            // lstUnitSelection
            // 
            this.lstUnitSelection.FormattingEnabled = true;
            this.lstUnitSelection.Location = new System.Drawing.Point(12, 172);
            this.lstUnitSelection.Name = "lstUnitSelection";
            this.lstUnitSelection.Size = new System.Drawing.Size(120, 121);
            this.lstUnitSelection.TabIndex = 9;
            this.lstUnitSelection.SelectedIndexChanged += new System.EventHandler(this.lstUnitSelection_SelectedIndexChanged);
            // 
            // btnNewUnit
            // 
            this.btnNewUnit.Location = new System.Drawing.Point(138, 172);
            this.btnNewUnit.Name = "btnNewUnit";
            this.btnNewUnit.Size = new System.Drawing.Size(47, 23);
            this.btnNewUnit.TabIndex = 13;
            this.btnNewUnit.Text = "New";
            this.btnNewUnit.UseVisualStyleBackColor = true;
            this.btnNewUnit.Click += new System.EventHandler(this.btnNewUnit_Click);
            // 
            // btnNewNPC
            // 
            this.btnNewNPC.Location = new System.Drawing.Point(138, 29);
            this.btnNewNPC.Name = "btnNewNPC";
            this.btnNewNPC.Size = new System.Drawing.Size(47, 23);
            this.btnNewNPC.TabIndex = 14;
            this.btnNewNPC.Text = "New";
            this.btnNewNPC.UseVisualStyleBackColor = true;
            this.btnNewNPC.Click += new System.EventHandler(this.btnNewNPC_Click);
            // 
            // ModalNpc
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.ActiveCaption;
            this.ClientSize = new System.Drawing.Size(719, 335);
            this.Controls.Add(this.btnNewNPC);
            this.Controls.Add(this.btnNewUnit);
            this.Controls.Add(this.button3);
            this.Controls.Add(this.button4);
            this.Controls.Add(this.label15);
            this.Controls.Add(this.lstUnitSelection);
            this.Controls.Add(this.grpUnits);
            this.Controls.Add(this.btnDone);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.dtnDel);
            this.Controls.Add(this.btnAdd);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.lstNPC);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Name = "ModalNpc";
            this.Text = "ModalNpc";
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.grpUnitList.ResumeLayout(false);
            this.grpUnits.ResumeLayout(false);
            this.grpUnits.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.nudSpeed)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudExperience)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudLevel)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudAP)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudHealth)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudAttack)).EndInit();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.nudDropChance)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ListBox lstNPC;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button btnAdd;
        private System.Windows.Forms.Button dtnDel;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Button btnConvoDel;
        private System.Windows.Forms.TextBox txtEvent;
        private System.Windows.Forms.Button btnConvoAdd;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox txtConvo;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.ListBox lstConversation;
        private System.Windows.Forms.CheckBox checkBox1;
        private System.Windows.Forms.TextBox txtName;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Button btnDone;
        private System.Windows.Forms.GroupBox grpUnits;
        private System.Windows.Forms.GroupBox grpUnitList;
        private System.Windows.Forms.ListBox lstUnits;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.ListBox lstAddUnit;
        private System.Windows.Forms.ListBox lstItems;
        private System.Windows.Forms.ComboBox cmb_Items;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.NumericUpDown nudDropChance;
        private System.Windows.Forms.NumericUpDown nudSpeed;
        private System.Windows.Forms.NumericUpDown nudExperience;
        private System.Windows.Forms.NumericUpDown nudLevel;
        private System.Windows.Forms.NumericUpDown nudAP;
        private System.Windows.Forms.NumericUpDown nudHealth;
        private System.Windows.Forms.NumericUpDown nudAttack;
        private System.Windows.Forms.Label label14;
        private System.Windows.Forms.ComboBox cmb_AI;
        private System.Windows.Forms.TextBox txtUnitName;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Button btnRemoveItem;
        private System.Windows.Forms.Button btnAddItem;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.Button button4;
        private System.Windows.Forms.Label label15;
        private System.Windows.Forms.ListBox lstUnitSelection;
        private System.Windows.Forms.Button btnNewUnit;
        private System.Windows.Forms.Button btnNewNPC;
        private System.Windows.Forms.TextBox txtFileName;
        private System.Windows.Forms.Label label2;
    }
}