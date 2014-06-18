using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace termometr_manager
{
    public partial class fComChooseFom : Form
    {
        private SerialPort ComPort = new SerialPort("COM1", 38400, Parity.Even, 8, StopBits.One);
        public string ChoosenPort { get; set; }

        public fComChooseFom()
        {
            InitializeComponent();
            InitializeControlValues();
        }

        private void lTitle_Click(object sender, EventArgs e)
        {
            Process.Start("devmgmt.msc");
        }

        private void btnComPortOpen_Click(object sender, EventArgs e)
        {
            ChoosenPort = cmbComPort.Text;

            this.Close();
            this.Dispose();
        }

        /// <summary> Populate the form's controls with default settings. </summary>
        private void InitializeControlValues()
        {
            cmbComPort.Items.Clear();
            try
            {
                foreach (string s in SerialPort.GetPortNames())
                {
                    cmbComPort.Items.Add(s);
                    cmbComPort.Text = s;
                }
            }
            catch
            {
                MessageBox.Show("No COM port found", "Error", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                this.Close();
            }
        }
    }
}
