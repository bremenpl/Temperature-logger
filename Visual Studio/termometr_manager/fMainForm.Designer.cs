namespace termometr_manager
{
    partial class fMainForm
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
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(fMainForm));
            this.ssTransmitData = new System.Windows.Forms.StatusStrip();
            this.ssTransmitData_Bytes = new System.Windows.Forms.ToolStripStatusLabel();
            this.ssTransmitData_Sent = new System.Windows.Forms.ToolStripStatusLabel();
            this.ssTransmitData_Received = new System.Windows.Forms.ToolStripStatusLabel();
            this.timerClose = new System.Windows.Forms.Timer(this.components);
            this.nudHour = new System.Windows.Forms.NumericUpDown();
            this.nudMinute = new System.Windows.Forms.NumericUpDown();
            this.nudSecond = new System.Windows.Forms.NumericUpDown();
            this.gbTime = new System.Windows.Forms.GroupBox();
            this.btnSetSystemTime = new System.Windows.Forms.Button();
            this.btnSetSetTime = new System.Windows.Forms.Button();
            this.btnGetTime = new System.Windows.Forms.Button();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.gbTemperature = new System.Windows.Forms.GroupBox();
            this.cbConstTempRead = new System.Windows.Forms.CheckBox();
            this.btnGetCurrentTemp = new System.Windows.Forms.Button();
            this.lTemperature = new System.Windows.Forms.Label();
            this.timerConstTempRead = new System.Windows.Forms.Timer(this.components);
            this.gbDate = new System.Windows.Forms.GroupBox();
            this.btnSetSystemDate = new System.Windows.Forms.Button();
            this.label4 = new System.Windows.Forms.Label();
            this.btnSetSetDate = new System.Windows.Forms.Button();
            this.cmbDayOfWeek = new System.Windows.Forms.ComboBox();
            this.btnGetDate = new System.Windows.Forms.Button();
            this.nudDate = new System.Windows.Forms.NumericUpDown();
            this.nudMonth = new System.Windows.Forms.NumericUpDown();
            this.label5 = new System.Windows.Forms.Label();
            this.nudYear = new System.Windows.Forms.NumericUpDown();
            this.label6 = new System.Windows.Forms.Label();
            this.gbDs18b20Hid = new System.Windows.Forms.GroupBox();
            this.btnReadDs18b20Hid = new System.Windows.Forms.Button();
            this.lDs18b20Hid = new System.Windows.Forms.Label();
            this.btnGetHouTemp = new System.Windows.Forms.Button();
            this.nudHourTemp = new System.Windows.Forms.NumericUpDown();
            this.label7 = new System.Windows.Forms.Label();
            this.nudMinTemp = new System.Windows.Forms.NumericUpDown();
            this.label8 = new System.Windows.Forms.Label();
            this.ssTransmitData.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.nudHour)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudMinute)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudSecond)).BeginInit();
            this.gbTime.SuspendLayout();
            this.gbTemperature.SuspendLayout();
            this.gbDate.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.nudDate)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudMonth)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudYear)).BeginInit();
            this.gbDs18b20Hid.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.nudHourTemp)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudMinTemp)).BeginInit();
            this.SuspendLayout();
            // 
            // ssTransmitData
            // 
            this.ssTransmitData.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.ssTransmitData_Bytes,
            this.ssTransmitData_Sent,
            this.ssTransmitData_Received});
            this.ssTransmitData.Location = new System.Drawing.Point(0, 324);
            this.ssTransmitData.Name = "ssTransmitData";
            this.ssTransmitData.Size = new System.Drawing.Size(593, 22);
            this.ssTransmitData.TabIndex = 0;
            this.ssTransmitData.Text = "statusStrip1";
            // 
            // ssTransmitData_Bytes
            // 
            this.ssTransmitData_Bytes.Font = new System.Drawing.Font("Consolas", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.ssTransmitData_Bytes.Name = "ssTransmitData_Bytes";
            this.ssTransmitData_Bytes.Size = new System.Drawing.Size(84, 17);
            this.ssTransmitData_Bytes.Text = "Bytes[Hex]:";
            // 
            // ssTransmitData_Sent
            // 
            this.ssTransmitData_Sent.Font = new System.Drawing.Font("Consolas", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.ssTransmitData_Sent.ForeColor = System.Drawing.Color.Blue;
            this.ssTransmitData_Sent.Name = "ssTransmitData_Sent";
            this.ssTransmitData_Sent.Size = new System.Drawing.Size(56, 17);
            this.ssTransmitData_Sent.Text = "Sent: 0";
            // 
            // ssTransmitData_Received
            // 
            this.ssTransmitData_Received.Font = new System.Drawing.Font("Consolas", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.ssTransmitData_Received.ForeColor = System.Drawing.Color.Green;
            this.ssTransmitData_Received.Name = "ssTransmitData_Received";
            this.ssTransmitData_Received.Size = new System.Drawing.Size(84, 17);
            this.ssTransmitData_Received.Text = "Received: 0";
            // 
            // timerClose
            // 
            this.timerClose.Interval = 1;
            this.timerClose.Tick += new System.EventHandler(this.timerClose_Tick);
            // 
            // nudHour
            // 
            this.nudHour.Location = new System.Drawing.Point(6, 38);
            this.nudHour.Maximum = new decimal(new int[] {
            23,
            0,
            0,
            0});
            this.nudHour.Name = "nudHour";
            this.nudHour.Size = new System.Drawing.Size(38, 20);
            this.nudHour.TabIndex = 1;
            this.nudHour.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // nudMinute
            // 
            this.nudMinute.Location = new System.Drawing.Point(50, 38);
            this.nudMinute.Maximum = new decimal(new int[] {
            60,
            0,
            0,
            0});
            this.nudMinute.Name = "nudMinute";
            this.nudMinute.Size = new System.Drawing.Size(38, 20);
            this.nudMinute.TabIndex = 2;
            this.nudMinute.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // nudSecond
            // 
            this.nudSecond.Location = new System.Drawing.Point(94, 38);
            this.nudSecond.Maximum = new decimal(new int[] {
            60,
            0,
            0,
            0});
            this.nudSecond.Name = "nudSecond";
            this.nudSecond.Size = new System.Drawing.Size(38, 20);
            this.nudSecond.TabIndex = 3;
            this.nudSecond.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // gbTime
            // 
            this.gbTime.Controls.Add(this.btnSetSystemTime);
            this.gbTime.Controls.Add(this.btnSetSetTime);
            this.gbTime.Controls.Add(this.btnGetTime);
            this.gbTime.Controls.Add(this.label3);
            this.gbTime.Controls.Add(this.nudHour);
            this.gbTime.Controls.Add(this.label2);
            this.gbTime.Controls.Add(this.nudMinute);
            this.gbTime.Controls.Add(this.label1);
            this.gbTime.Controls.Add(this.nudSecond);
            this.gbTime.Location = new System.Drawing.Point(13, 13);
            this.gbTime.Name = "gbTime";
            this.gbTime.Size = new System.Drawing.Size(137, 180);
            this.gbTime.TabIndex = 4;
            this.gbTime.TabStop = false;
            this.gbTime.Text = "Time";
            // 
            // btnSetSystemTime
            // 
            this.btnSetSystemTime.Location = new System.Drawing.Point(6, 149);
            this.btnSetSystemTime.Name = "btnSetSystemTime";
            this.btnSetSystemTime.Size = new System.Drawing.Size(125, 23);
            this.btnSetSystemTime.TabIndex = 10;
            this.btnSetSystemTime.Text = "Set system time";
            this.btnSetSystemTime.UseVisualStyleBackColor = true;
            this.btnSetSystemTime.Click += new System.EventHandler(this.btnSetSystemTime_Click);
            // 
            // btnSetSetTime
            // 
            this.btnSetSetTime.Location = new System.Drawing.Point(6, 120);
            this.btnSetSetTime.Name = "btnSetSetTime";
            this.btnSetSetTime.Size = new System.Drawing.Size(125, 23);
            this.btnSetSetTime.TabIndex = 9;
            this.btnSetSetTime.Text = "Set set time";
            this.btnSetSetTime.UseVisualStyleBackColor = true;
            this.btnSetSetTime.Click += new System.EventHandler(this.btnSetSetTime_Click);
            // 
            // btnGetTime
            // 
            this.btnGetTime.Location = new System.Drawing.Point(6, 91);
            this.btnGetTime.Name = "btnGetTime";
            this.btnGetTime.Size = new System.Drawing.Size(125, 23);
            this.btnGetTime.TabIndex = 8;
            this.btnGetTime.Text = "Read time";
            this.btnGetTime.UseVisualStyleBackColor = true;
            this.btnGetTime.Click += new System.EventHandler(this.btnGetTime_Click);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(91, 22);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(21, 13);
            this.label3.TabIndex = 7;
            this.label3.Text = "SS";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(47, 22);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(25, 13);
            this.label2.TabIndex = 6;
            this.label2.Text = "MM";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(3, 22);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(23, 13);
            this.label1.TabIndex = 5;
            this.label1.Text = "HH";
            // 
            // gbTemperature
            // 
            this.gbTemperature.Controls.Add(this.nudHourTemp);
            this.gbTemperature.Controls.Add(this.label7);
            this.gbTemperature.Controls.Add(this.btnGetHouTemp);
            this.gbTemperature.Controls.Add(this.nudMinTemp);
            this.gbTemperature.Controls.Add(this.cbConstTempRead);
            this.gbTemperature.Controls.Add(this.label8);
            this.gbTemperature.Controls.Add(this.btnGetCurrentTemp);
            this.gbTemperature.Controls.Add(this.lTemperature);
            this.gbTemperature.Location = new System.Drawing.Point(300, 13);
            this.gbTemperature.Name = "gbTemperature";
            this.gbTemperature.Size = new System.Drawing.Size(137, 180);
            this.gbTemperature.TabIndex = 5;
            this.gbTemperature.TabStop = false;
            this.gbTemperature.Text = "Temperature";
            // 
            // cbConstTempRead
            // 
            this.cbConstTempRead.AutoSize = true;
            this.cbConstTempRead.Location = new System.Drawing.Point(6, 153);
            this.cbConstTempRead.Name = "cbConstTempRead";
            this.cbConstTempRead.Size = new System.Drawing.Size(102, 17);
            this.cbConstTempRead.TabIndex = 10;
            this.cbConstTempRead.Text = "const temp read";
            this.cbConstTempRead.UseVisualStyleBackColor = true;
            this.cbConstTempRead.CheckedChanged += new System.EventHandler(this.cbConstTempRead_CheckedChanged);
            // 
            // btnGetCurrentTemp
            // 
            this.btnGetCurrentTemp.Location = new System.Drawing.Point(6, 120);
            this.btnGetCurrentTemp.Name = "btnGetCurrentTemp";
            this.btnGetCurrentTemp.Size = new System.Drawing.Size(125, 23);
            this.btnGetCurrentTemp.TabIndex = 9;
            this.btnGetCurrentTemp.Text = "Read current temp";
            this.btnGetCurrentTemp.UseVisualStyleBackColor = true;
            this.btnGetCurrentTemp.Click += new System.EventHandler(this.btnGetCurrentTemp_Click);
            // 
            // lTemperature
            // 
            this.lTemperature.AutoSize = true;
            this.lTemperature.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.lTemperature.Location = new System.Drawing.Point(35, 65);
            this.lTemperature.Name = "lTemperature";
            this.lTemperature.Size = new System.Drawing.Size(40, 20);
            this.lTemperature.TabIndex = 0;
            this.lTemperature.Text = "-- *C";
            // 
            // timerConstTempRead
            // 
            this.timerConstTempRead.Interval = 1000;
            this.timerConstTempRead.Tick += new System.EventHandler(this.timerConstTempRead_Tick);
            // 
            // gbDate
            // 
            this.gbDate.Controls.Add(this.btnSetSystemDate);
            this.gbDate.Controls.Add(this.label4);
            this.gbDate.Controls.Add(this.btnSetSetDate);
            this.gbDate.Controls.Add(this.cmbDayOfWeek);
            this.gbDate.Controls.Add(this.btnGetDate);
            this.gbDate.Controls.Add(this.nudDate);
            this.gbDate.Controls.Add(this.nudMonth);
            this.gbDate.Controls.Add(this.label5);
            this.gbDate.Controls.Add(this.nudYear);
            this.gbDate.Controls.Add(this.label6);
            this.gbDate.Location = new System.Drawing.Point(157, 13);
            this.gbDate.Name = "gbDate";
            this.gbDate.Size = new System.Drawing.Size(137, 180);
            this.gbDate.TabIndex = 6;
            this.gbDate.TabStop = false;
            this.gbDate.Text = "Date";
            // 
            // btnSetSystemDate
            // 
            this.btnSetSystemDate.Location = new System.Drawing.Point(6, 149);
            this.btnSetSystemDate.Name = "btnSetSystemDate";
            this.btnSetSystemDate.Size = new System.Drawing.Size(125, 23);
            this.btnSetSystemDate.TabIndex = 13;
            this.btnSetSystemDate.Text = "Set system date";
            this.btnSetSystemDate.UseVisualStyleBackColor = true;
            this.btnSetSystemDate.Click += new System.EventHandler(this.btnSetSystemDate_Click);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(91, 22);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(21, 13);
            this.label4.TabIndex = 16;
            this.label4.Text = "YY";
            // 
            // btnSetSetDate
            // 
            this.btnSetSetDate.Location = new System.Drawing.Point(6, 120);
            this.btnSetSetDate.Name = "btnSetSetDate";
            this.btnSetSetDate.Size = new System.Drawing.Size(125, 23);
            this.btnSetSetDate.TabIndex = 12;
            this.btnSetSetDate.Text = "Set set date";
            this.btnSetSetDate.UseVisualStyleBackColor = true;
            this.btnSetSetDate.Click += new System.EventHandler(this.btnSetSetDate_Click);
            // 
            // cmbDayOfWeek
            // 
            this.cmbDayOfWeek.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cmbDayOfWeek.FormattingEnabled = true;
            this.cmbDayOfWeek.Items.AddRange(new object[] {
            "Monday",
            "Tuesday",
            "Wednesday",
            "Thursday",
            "Friday",
            "Saturday",
            "Sunday"});
            this.cmbDayOfWeek.Location = new System.Drawing.Point(7, 64);
            this.cmbDayOfWeek.Name = "cmbDayOfWeek";
            this.cmbDayOfWeek.Size = new System.Drawing.Size(124, 21);
            this.cmbDayOfWeek.TabIndex = 0;
            // 
            // btnGetDate
            // 
            this.btnGetDate.Location = new System.Drawing.Point(6, 91);
            this.btnGetDate.Name = "btnGetDate";
            this.btnGetDate.Size = new System.Drawing.Size(125, 23);
            this.btnGetDate.TabIndex = 11;
            this.btnGetDate.Text = "Read date";
            this.btnGetDate.UseVisualStyleBackColor = true;
            this.btnGetDate.Click += new System.EventHandler(this.btnGetDate_Click);
            // 
            // nudDate
            // 
            this.nudDate.Location = new System.Drawing.Point(6, 38);
            this.nudDate.Maximum = new decimal(new int[] {
            31,
            0,
            0,
            0});
            this.nudDate.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.nudDate.Name = "nudDate";
            this.nudDate.Size = new System.Drawing.Size(38, 20);
            this.nudDate.TabIndex = 4;
            this.nudDate.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.nudDate.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // nudMonth
            // 
            this.nudMonth.Location = new System.Drawing.Point(50, 38);
            this.nudMonth.Maximum = new decimal(new int[] {
            12,
            0,
            0,
            0});
            this.nudMonth.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.nudMonth.Name = "nudMonth";
            this.nudMonth.Size = new System.Drawing.Size(38, 20);
            this.nudMonth.TabIndex = 5;
            this.nudMonth.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.nudMonth.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(47, 22);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(25, 13);
            this.label5.TabIndex = 15;
            this.label5.Text = "MM";
            // 
            // nudYear
            // 
            this.nudYear.Location = new System.Drawing.Point(94, 38);
            this.nudYear.Maximum = new decimal(new int[] {
            99,
            0,
            0,
            0});
            this.nudYear.Name = "nudYear";
            this.nudYear.Size = new System.Drawing.Size(38, 20);
            this.nudYear.TabIndex = 6;
            this.nudYear.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(3, 22);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(23, 13);
            this.label6.TabIndex = 14;
            this.label6.Text = "DD";
            // 
            // gbDs18b20Hid
            // 
            this.gbDs18b20Hid.Controls.Add(this.btnReadDs18b20Hid);
            this.gbDs18b20Hid.Controls.Add(this.lDs18b20Hid);
            this.gbDs18b20Hid.Location = new System.Drawing.Point(443, 13);
            this.gbDs18b20Hid.Name = "gbDs18b20Hid";
            this.gbDs18b20Hid.Size = new System.Drawing.Size(137, 180);
            this.gbDs18b20Hid.TabIndex = 7;
            this.gbDs18b20Hid.TabStop = false;
            this.gbDs18b20Hid.Text = "DS18B20 Rom";
            // 
            // btnReadDs18b20Hid
            // 
            this.btnReadDs18b20Hid.Location = new System.Drawing.Point(6, 120);
            this.btnReadDs18b20Hid.Name = "btnReadDs18b20Hid";
            this.btnReadDs18b20Hid.Size = new System.Drawing.Size(125, 23);
            this.btnReadDs18b20Hid.TabIndex = 11;
            this.btnReadDs18b20Hid.Text = "Read ROM";
            this.btnReadDs18b20Hid.UseVisualStyleBackColor = true;
            this.btnReadDs18b20Hid.Click += new System.EventHandler(this.btnReadDs18b20Hid_Click);
            // 
            // lDs18b20Hid
            // 
            this.lDs18b20Hid.AutoSize = true;
            this.lDs18b20Hid.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.lDs18b20Hid.Location = new System.Drawing.Point(7, 40);
            this.lDs18b20Hid.Name = "lDs18b20Hid";
            this.lDs18b20Hid.Size = new System.Drawing.Size(28, 16);
            this.lDs18b20Hid.TabIndex = 0;
            this.lDs18b20Hid.Text = "0x0";
            // 
            // btnGetHouTemp
            // 
            this.btnGetHouTemp.Location = new System.Drawing.Point(6, 91);
            this.btnGetHouTemp.Name = "btnGetHouTemp";
            this.btnGetHouTemp.Size = new System.Drawing.Size(125, 23);
            this.btnGetHouTemp.TabIndex = 11;
            this.btnGetHouTemp.Text = "Read hour temp";
            this.btnGetHouTemp.UseVisualStyleBackColor = true;
            this.btnGetHouTemp.Click += new System.EventHandler(this.btnGetHouTemp_Click);
            // 
            // nudHourTemp
            // 
            this.nudHourTemp.Location = new System.Drawing.Point(6, 38);
            this.nudHourTemp.Maximum = new decimal(new int[] {
            23,
            0,
            0,
            0});
            this.nudHourTemp.Name = "nudHourTemp";
            this.nudHourTemp.Size = new System.Drawing.Size(38, 20);
            this.nudHourTemp.TabIndex = 11;
            this.nudHourTemp.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(47, 22);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(25, 13);
            this.label7.TabIndex = 14;
            this.label7.Text = "MM";
            // 
            // nudMinTemp
            // 
            this.nudMinTemp.Increment = new decimal(new int[] {
            10,
            0,
            0,
            0});
            this.nudMinTemp.Location = new System.Drawing.Point(50, 38);
            this.nudMinTemp.Maximum = new decimal(new int[] {
            60,
            0,
            0,
            0});
            this.nudMinTemp.Name = "nudMinTemp";
            this.nudMinTemp.Size = new System.Drawing.Size(38, 20);
            this.nudMinTemp.TabIndex = 12;
            this.nudMinTemp.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(3, 22);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(23, 13);
            this.label8.TabIndex = 13;
            this.label8.Text = "HH";
            // 
            // fMainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(593, 346);
            this.Controls.Add(this.gbDs18b20Hid);
            this.Controls.Add(this.gbDate);
            this.Controls.Add(this.gbTemperature);
            this.Controls.Add(this.gbTime);
            this.Controls.Add(this.ssTransmitData);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.Fixed3D;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "fMainForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Thermometer Manager";
            this.WindowState = System.Windows.Forms.FormWindowState.Minimized;
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.fMainForm_FormClosing);
            this.ssTransmitData.ResumeLayout(false);
            this.ssTransmitData.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.nudHour)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudMinute)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudSecond)).EndInit();
            this.gbTime.ResumeLayout(false);
            this.gbTime.PerformLayout();
            this.gbTemperature.ResumeLayout(false);
            this.gbTemperature.PerformLayout();
            this.gbDate.ResumeLayout(false);
            this.gbDate.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.nudDate)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudMonth)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudYear)).EndInit();
            this.gbDs18b20Hid.ResumeLayout(false);
            this.gbDs18b20Hid.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.nudHourTemp)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudMinTemp)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.StatusStrip ssTransmitData;
        private System.Windows.Forms.ToolStripStatusLabel ssTransmitData_Sent;
        private System.Windows.Forms.ToolStripStatusLabel ssTransmitData_Bytes;
        private System.Windows.Forms.ToolStripStatusLabel ssTransmitData_Received;
        private System.Windows.Forms.Timer timerClose;
        private System.Windows.Forms.NumericUpDown nudHour;
        private System.Windows.Forms.NumericUpDown nudMinute;
        private System.Windows.Forms.NumericUpDown nudSecond;
        private System.Windows.Forms.GroupBox gbTime;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button btnSetSystemTime;
        private System.Windows.Forms.Button btnSetSetTime;
        private System.Windows.Forms.Button btnGetTime;
        private System.Windows.Forms.GroupBox gbTemperature;
        private System.Windows.Forms.Button btnGetCurrentTemp;
        private System.Windows.Forms.Label lTemperature;
        private System.Windows.Forms.CheckBox cbConstTempRead;
        private System.Windows.Forms.Timer timerConstTempRead;
        private System.Windows.Forms.GroupBox gbDate;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.ComboBox cmbDayOfWeek;
        private System.Windows.Forms.NumericUpDown nudDate;
        private System.Windows.Forms.NumericUpDown nudMonth;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.NumericUpDown nudYear;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Button btnSetSystemDate;
        private System.Windows.Forms.Button btnSetSetDate;
        private System.Windows.Forms.Button btnGetDate;
        private System.Windows.Forms.GroupBox gbDs18b20Hid;
        private System.Windows.Forms.Button btnReadDs18b20Hid;
        private System.Windows.Forms.Label lDs18b20Hid;
        private System.Windows.Forms.Button btnGetHouTemp;
        private System.Windows.Forms.NumericUpDown nudHourTemp;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.NumericUpDown nudMinTemp;
        private System.Windows.Forms.Label label8;
    }
}

