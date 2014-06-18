namespace termometr_manager
{
    partial class fComChooseFom
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(fComChooseFom));
            this.cmbComPort = new System.Windows.Forms.ComboBox();
            this.btnComPortOpen = new System.Windows.Forms.Button();
            this.lTitle = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // cmbComPort
            // 
            this.cmbComPort.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cmbComPort.FormattingEnabled = true;
            this.cmbComPort.Location = new System.Drawing.Point(12, 73);
            this.cmbComPort.Name = "cmbComPort";
            this.cmbComPort.Size = new System.Drawing.Size(121, 21);
            this.cmbComPort.TabIndex = 0;
            // 
            // btnComPortOpen
            // 
            this.btnComPortOpen.Location = new System.Drawing.Point(139, 71);
            this.btnComPortOpen.Name = "btnComPortOpen";
            this.btnComPortOpen.Size = new System.Drawing.Size(75, 23);
            this.btnComPortOpen.TabIndex = 1;
            this.btnComPortOpen.Text = "Open";
            this.btnComPortOpen.UseVisualStyleBackColor = true;
            this.btnComPortOpen.Click += new System.EventHandler(this.btnComPortOpen_Click);
            // 
            // lTitle
            // 
            this.lTitle.AutoSize = true;
            this.lTitle.Location = new System.Drawing.Point(12, 13);
            this.lTitle.Name = "lTitle";
            this.lTitle.Size = new System.Drawing.Size(200, 39);
            this.lTitle.TabIndex = 2;
            this.lTitle.Text = "Go to device manager and check which \r\nCOM port is assigned to your device \r\nand " +
    "then open it (click this text).";
            this.lTitle.Click += new System.EventHandler(this.lTitle_Click);
            // 
            // fComChooseFom
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(226, 122);
            this.Controls.Add(this.lTitle);
            this.Controls.Add(this.btnComPortOpen);
            this.Controls.Add(this.cmbComPort);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.Fixed3D;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "fComChooseFom";
            this.Text = "Open COM port";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ComboBox cmbComPort;
        private System.Windows.Forms.Button btnComPortOpen;
        private System.Windows.Forms.Label lTitle;
    }
}