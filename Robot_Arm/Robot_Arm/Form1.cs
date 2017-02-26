using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;

namespace Robot_Arm
{
    public partial class Form1 : Form
    {

        static bool[] boxFound = new bool[6];
        public Form1()
        {
            InitializeComponent();

            arduinoPort.PortName = "COM6";
            arduinoPort.BaudRate = 9600;
            arduinoPort.Open();
            arduinoPort.DataReceived += new SerialDataReceivedEventHandler(DataReceivedHandler);

            label1.Visible = false;
            label2.Visible = false;
            label3.Visible = false;
            label4.Visible = false;
            label5.Visible = false;
            label6.Visible = false;

        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                resetSettings();
                arduinoPort.Write("1");
                label7.Text = "Shuffle Mode";
            }
            catch
            {
                MessageBox.Show("Serial port may not be connected");
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            try
            {
                resetSettings();
                arduinoPort.Write("2");
                label7.Text = "Stack Mode";
            }
            catch
            {
                MessageBox.Show("Serial port may not be connected");
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            try
            {
                resetSettings();
                arduinoPort.Write("3");
                label7.Text = "Scan Mode";
            }
            catch
            {
                MessageBox.Show("Serial port may not be connected");
            }
            
        }

        private void button4_Click(object sender, EventArgs e)
        {
            resetSettings();
        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {

        }

        private static void DataReceivedHandler(object sender,SerialDataReceivedEventArgs e)
        {
            SerialPort s = (SerialPort)sender;
            int data = s.ReadChar();
            Console.Write(data);

            if(data < boxFound.Length)
            {
                boxFound[data] = true;
            }
            

            if(data > 5)
            {
                for (int i = 0; i < boxFound.Length; i++)
                {
                    boxFound[i] = false;
                }
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            Timer timer = new Timer();
            timer.Interval = 20;
            timer.Tick += new EventHandler(timer1_Tick);
            timer.Start();
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            if (boxFound[5] == true)
            {
                label1.Visible = true;
            } 
            if (boxFound[4] == true)
            {
                label2.Visible = true;
            }

            if (boxFound[3] == true)
            {
                label3.Visible = true;
            }
            if (boxFound[2] == true)
            {
                label4.Visible = true;
            }
            
            if (boxFound[1] == true)
            {
                label5.Visible = true;
            }
           
            if (boxFound[0] == true)
            {
                label6.Visible = true;
            } 
            
        }

        private void resetSettings()
        {
            for (int i = 0; i < boxFound.Length; i++)
            {
                boxFound[i] = false;
            }

            label1.Visible = false;
            label2.Visible = false;
            label3.Visible = false;
            label4.Visible = false;
            label5.Visible = false;
            label6.Visible = false;
            arduinoPort.Write("0");
            label7.Text = "Autonomous Robot Arm";
        }

        

    }

 
}