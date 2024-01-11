using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace Cli_Input_Test_Key_Codes_CS
{
    public partial class Cli_Input_Test_Key_Codes_CS_Form : Form
    {
        public Cli_Input_Test_Key_Codes_CS_Form()
        {
            InitializeComponent();
        }

        private void Cli_Input_textBox_KeyDown(object sender, KeyEventArgs e)
        {
            e.Handled = true;
        }

        private void Cli_Input_textBox_KeyPress(object sender, KeyPressEventArgs e)
        {
            e.Handled = true;
        }

        private void Cli_Input_textBox_PreviewKeyDown(object sender, PreviewKeyDownEventArgs e)
        {

            Keys key = e.KeyCode;

            if (key == Keys.ControlKey)
            {
                return;
            }

            Int32 key_code = e.KeyValue;

            String key_text = "";

            bool Is_Ctrl = false;
            if (e.Modifiers == Keys.Control)
            {
                Is_Ctrl = true;
            }

            if (Is_Ctrl && key == Keys.C)
            {
                key_text = "Ctrl+C";
            }
            else if (Is_Ctrl && key == Keys.Z)
            {
                key_text = "Ctrl+Z";
            }
            else if (Is_Ctrl && key == Keys.OemPipe)
            {
                key_text = "Ctrl+BACKSLASH";
            }
            else if (key == Keys.Enter)
            {
                key_text = "ENTER";
            }
            else if (key == Keys.Tab)
            {
                key_text = "TAB";
            }
            else if (key == Keys.Up)
            {
                key_text = "UP";
            }
            else if (key == Keys.Down)
            {
                key_text = "DOWN";
            }
            else if (key == Keys.Left)
            {
                key_text = "LEFT";
            }
            else if (key == Keys.Right)
            {
                key_text = "RIGHT";
            }
            else if (key == Keys.Home)
            {
                key_text = "HOME";
            }
            else if (key == Keys.End)
            {
                key_text = "END";
            }
            else if (key == Keys.Right)
            {
                key_text = "DOWN";
            }
            else if (key == Keys.Delete)
            {
                key_text = "DELETE";
            }
            else if (key == Keys.Back)
            {
                key_text = "BACK";
            }

            String s = "0x" + key_code.ToString("X02");
            if(key_text.Length > 0)
            {
                s += " " + key_text;
            }
            Cli_Input_textBox.AppendText(s + "\r\n");

        }
    }
}
