using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace termometr_manager
{
    public partial class fMainForm : Form
    {
        private SerialPort ComPort = new SerialPort("COM1", 38400, Parity.Even, 8, StopBits.One);
        private const int CRxBufferLen = 15;
        private byte[] RxBuffer = new byte[CRxBufferLen];
        private System.Timers.Timer TimeoutTimer;
        private const int TimeoutIntervalMs = 1000;
        private const byte C_syncByte = (byte)'^';

        public delegate void FormCloseEventHandler();
        public event FormCloseEventHandler FormCloseRequest;

        private enum ECommands
        {
            CMD_SET_TIME = 1,
            CMD_GET_TIME,
            CMD_SET_DATE,
            CMD_GET_DATE,
            CMD_GET_CURR_TEMP,
            CMD_GET_HOUR_TEMP,
            CMD_GET_MIN_TEMP,
            CMD_GET_MAX_TEMP,
            CMD_GET_DS18B20_HID,
        }

        public fMainForm()
        {
            fComChooseFom comForm = new fComChooseFom();

            // form operations.
            comForm.StartPosition = FormStartPosition.CenterScreen; ;
            comForm.ShowDialog();
            comForm.WindowState = FormWindowState.Normal;

            InitializeComponent();
            FormCloseRequest += fMainForm_formCloseRequest;

            InitComPort(comForm.ChoosenPort);
        }

        void fMainForm_formCloseRequest()
        {
            Invoke(new EventHandler(delegate
            {
                Close();
            }));
        }

        void InitComPort(string comport)
        {
            if (null == comport)
            {
                timerClose.Enabled = true;
            }
            else
            {
                try
                {
                    ComPort.PortName = comport;
                    ComPort.DataReceived += ComPort_DataReceived;

                    TimeoutTimer = new System.Timers.Timer(TimeoutIntervalMs);
                    TimeoutTimer.Enabled = false;
                    TimeoutTimer.Elapsed += TimeoutTimer_Elapsed;
                    TimeoutTimer.AutoReset = true;

                    ComPort.Open();

                    WindowState = FormWindowState.Normal;
                }
                catch (Exception)
                {
                    MessageBox.Show("Selected COM port occupied! Application will halt now.", "COM port error", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                    timerClose.Enabled = true;
                    WindowState = FormWindowState.Minimized;
                }
            }
        }

        void ComPort_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            int receivedBytes = 0;

            if ((receivedBytes = GetBytesByUart()) != 0)
            {

            }
        }

        void TimeoutTimer_Elapsed(object sender, System.Timers.ElapsedEventArgs e)
        {
            TimeoutTimer.Enabled = false;
            ssTransmitData_Received.Text = "Received: Timeout!";
        }

        /// <summary>
        /// Sends the data through uart
        /// </summary>
        /// <param name="command">Command</param>
        /// <param name="buffer">Data</param>
        void SendUartData(ECommands command, byte[] buffer)
        {
            TimeoutTimer.Enabled = true;
            int oldBufLenght = buffer.Length;

            Array.Resize(ref buffer, oldBufLenght + 3);
            Array.Copy(buffer, 0, buffer, 2, oldBufLenght);

            buffer[0] = C_syncByte;
            buffer[1] = (byte)command;
            buffer[buffer.Length - 1] = CalculateCrc(buffer, buffer.Length);
            ComPort.Write(buffer, 0, buffer.Length);

            ssTransmitData_Sent.Text = "Sent: ";
            for (int i = 0; i < buffer.Length; i++)
            {
                ssTransmitData_Sent.Text += buffer[i].ToString("X2") + " ";
            }
        }

        public int GetBytesByUart()
        {
            int bytes2Read = ComPort.BytesToRead;

            if (bytes2Read > CRxBufferLen)
            {
                MessageBox.Show("Serial received data overflow! " + "Received over "
                    + CRxBufferLen.ToString() + "bytes of data", "Error", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
            }

            if (bytes2Read > 0)
            {
                TimeoutTimer.Enabled = false;
                ComPort.Read(RxBuffer, 0, bytes2Read);

                ssTransmitData_Received.Text = "Received: ";
                for (int i = 0; i < bytes2Read; i++)
                {
                    ssTransmitData_Received.Text += RxBuffer[i].ToString("X2") + " ";
                }

                if (CheckCRC(RxBuffer, bytes2Read))
                {
                    byte answer = RxBuffer[1];

                    switch ((ECommands) answer)
                    {
                        case ECommands.CMD_GET_TIME:
                        {
                            Invoke(new EventHandler(delegate
                            {
                                nudSecond.Value = RxBuffer[2];
                                nudMinute.Value = RxBuffer[3];
                                nudHour.Value = RxBuffer[4];
                            }));

                            break;
                        }

                        case ECommands.CMD_GET_DATE:
                        {
                            Invoke(new EventHandler(delegate
                            {
                                cmbDayOfWeek.SelectedIndex = RxBuffer[2] - 1;
                                nudDate.Value = RxBuffer[3];
                                nudMonth.Value = RxBuffer[4];
                                nudYear.Value = RxBuffer[5];
                            }));

                            break;
                        }

                        case ECommands.CMD_GET_HOUR_TEMP:
                        case ECommands.CMD_GET_CURR_TEMP:
                        {
                            string halfCelc = "";
                            Int16 temperature = (Int16)(RxBuffer[2] | (RxBuffer[3] << 8));
                            bool emptyCell = false;

                            if ((temperature & 0x0008) != 0)
                            {
                                halfCelc = ".5";
                            }

                            if ((temperature & 0x0001) != 1)
                            {
                                emptyCell = true;
                            }

                            temperature >>= 4;

                            Invoke(new EventHandler(delegate
                            {
                                if (temperature > 0)
                                {
                                    lTemperature.ForeColor = Color.Crimson;
                                }
                                else
                                {
                                    lTemperature.ForeColor = Color.MediumBlue;
                                }

                                if (false == emptyCell)
                                {
                                    lTemperature.Text = temperature.ToString() + halfCelc + " *C";
                                }
                                else
                                {
                                    lTemperature.ForeColor = Color.Black;
                                    lTemperature.Text = "no data";
                                }
                            }));

                            break;
                        }

                        case ECommands.CMD_SET_TIME:
                        case ECommands.CMD_SET_DATE:
                        {
                            // do nothing
                            break;
                        }

                        case ECommands.CMD_GET_DS18B20_HID:
                        {
                            Invoke(new EventHandler(delegate
                            {
                                lDs18b20Hid.Text = "0x";

                                for (int i = 9; i > 2; i--)
                                {
                                    lDs18b20Hid.Text += RxBuffer[i].ToString("X2");
                                }
                            }));
                            break;
                        }

                        default:
                        {
                            MessageBox.Show("Unknown command received", "Ansfer error", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                            break;
                        }
                    }
                }
                else
                {
                    // invalid crc
                }
            }

            return bytes2Read;
        }

        /// <summary>
        /// Checks CRC
        /// </summary>
        /// <param name="length">Data lenght with command</param>
        /// <param name="buffer">buffer to calculate crc for</param>
        /// <returns>return true if correct</returns>
        private bool CheckCRC(byte[] buffer, int length)
        {
            byte sum = 0;

            for (int i = 0; i < (length - 1); i++)
            {
                sum += buffer[i];
            }
            sum = (byte)~sum;

            return (sum == buffer[length - 1]);
        }

        /// <summary>
        /// Calculates the buffers crc
        /// </summary>
        /// <param name="buffer">CRC</param>
        /// <returns></returns>
        private byte CalculateCrc(byte[] buffer, int length)
        {
            byte sum = 0;

            for (int i = 0; i < (length - 1); i++)
            {
                sum += buffer[i];
            }
            sum = (byte)~sum;

            return sum;
        }

        private void fMainForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            ComPort.Close();
        }

        private void timerClose_Tick(object sender, EventArgs e)
        {
            FormCloseRequest();
        }

        private void btnGetCurrentTemp_Click(object sender, EventArgs e)
        {
            byte[] data = new byte[0];

            Task.Factory.StartNew(() =>
            {
                SendUartData(ECommands.CMD_GET_CURR_TEMP, data);
            });
        }

        private void btnGetHouTemp_Click(object sender, EventArgs e)
        {
            byte[] data = new byte[2];

            data[0] = (byte) nudMinTemp.Value;
            data[1] = (byte) nudHourTemp.Value;

            Task.Factory.StartNew(() =>
            {
                SendUartData(ECommands.CMD_GET_HOUR_TEMP, data);
            });
        }

        private void btnGetTime_Click(object sender, EventArgs e)
        {
            byte[] data = new byte[0];

            Task.Factory.StartNew(() =>
            {
                SendUartData(ECommands.CMD_GET_TIME, data);
            });
        }

        private void btnSetSetTime_Click(object sender, EventArgs e)
        {
            byte[] data = new byte[3];

            data[0] = (byte)nudSecond.Value;
            data[1] = (byte)nudMinute.Value;
            data[2] = (byte)nudHour.Value;

            Task.Factory.StartNew(() =>
            {
                SendUartData(ECommands.CMD_SET_TIME, data);
            });
        }

        private void btnSetSystemTime_Click(object sender, EventArgs e)
        {
            byte[] data = new byte[3];

            data[0] = (byte)DateTime.Now.Second;
            data[1] = (byte)DateTime.Now.Minute;
            data[2] = (byte)DateTime.Now.Hour;

            nudSecond.Value = data[0];
            nudMinute.Value = data[1];
            nudHour.Value = data[2];

            Task.Factory.StartNew(() =>
            {
                SendUartData(ECommands.CMD_SET_TIME, data);
            });
        }

        private void cbConstTempRead_CheckedChanged(object sender, EventArgs e)
        {
            if (true == cbConstTempRead.Checked)
            {
                btnGetCurrentTemp.PerformClick();
                timerConstTempRead.Enabled = true;
            }
            else
            {
                timerConstTempRead.Enabled = false;
            }
        }

        private void timerConstTempRead_Tick(object sender, EventArgs e)
        {
            btnGetCurrentTemp.PerformClick();
        }

        private void btnGetDate_Click(object sender, EventArgs e)
        {
            byte[] data = new byte[0];

            Task.Factory.StartNew(() =>
            {
                SendUartData(ECommands.CMD_GET_DATE, data);
            });
        }

        private void btnSetSetDate_Click(object sender, EventArgs e)
        {
            byte[] data = new byte[4];

            data[0] = (byte)(cmbDayOfWeek.SelectedIndex + 1);
            data[1] = (byte)nudDate.Value;
            data[2] = (byte)nudMonth.Value;
            data[3] = (byte)nudYear.Value;

            Task.Factory.StartNew(() =>
            {
                SendUartData(ECommands.CMD_SET_DATE, data);
            });
        }

        private void btnSetSystemDate_Click(object sender, EventArgs e)
        {
            byte[] data = new byte[4];

            data[0] = (byte)DateTime.Now.DayOfWeek;
            data[1] = (byte)DateTime.Now.Day;
            data[2] = (byte)DateTime.Now.Month;
            data[3] = (byte)(DateTime.Now.Year - 2000);

            cmbDayOfWeek.SelectedIndex = data[0] - 1;
            nudDate.Value = data[1];
            nudMonth.Value = data[2];
            nudYear.Value = data[3];

            Task.Factory.StartNew(() =>
            {
                SendUartData(ECommands.CMD_SET_DATE, data);
            });
        }

        private void btnReadDs18b20Hid_Click(object sender, EventArgs e)
        {
            byte[] data = new byte[0];

            Task.Factory.StartNew(() =>
            {
                SendUartData(ECommands.CMD_GET_DS18B20_HID, data);
            });
        }

    }
}
