using System;
using System.Windows.Forms;

namespace Cli_Input_Test_Key_Codes_CS
{
    public partial class Cli_Input_Test_Key_Codes_CS_Form : Form
    {

        private Keys Key_Code;
        private bool Is_Ctrl = false;
        private bool Is_Processed_In_PreviewKeyDown = false;

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
            if (!Is_Ctrl && !Is_Processed_In_PreviewKeyDown)
            {
                Cli_Input_textBox.AppendText(" Char: '" + e.KeyChar + "'\r\n");
            }
            e.Handled = true;
        }

        String Key_Text_Get(Keys key, bool Is_Ctrl)
        {
            String key_text = "";

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

            return key_text;
        }

        private void Cli_Input_textBox_PreviewKeyDown(object sender, PreviewKeyDownEventArgs e)
        {
            Is_Processed_In_PreviewKeyDown = false;

            Is_Ctrl = (e.Modifiers == Keys.Control);

            Key_Code = e.KeyCode;
            if (Key_Code == Keys.ControlKey)
            {
                return;
            }

            Int32 key_value = e.KeyValue;
            String s = "0x" + key_value.ToString("X02");
            String key_text = Key_Text_Get(Key_Code, Is_Ctrl);
            if (key_text.Length > 0)
            {
                s += " " + key_text;
                Is_Processed_In_PreviewKeyDown = true;
            }

            Cli_Input_textBox.AppendText(s + "\r\n");

        }
    }
}
