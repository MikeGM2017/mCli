using System;
using System.Windows.Forms;

namespace Cli_Input_Test_Key_Codes_CS
{
    public partial class Cli_Input_Test_Key_Codes_CS_Form : Form
    {
        private Keys KeyCode;
        private int KeyValue = 0;
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
            bool Is_Ctrl = (Control.ModifierKeys & Keys.Control) == Keys.Control;
            if (!Is_Ctrl && !Is_Processed_In_PreviewKeyDown)
            {
                String keyvalue_s = "0x" + KeyValue.ToString("X2");
                Cli_Input_textBox.AppendText("KeyPress: " + keyvalue_s + " Char: '" + e.KeyChar + "'\r\n");
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

            if (e.KeyCode == Keys.ControlKey)
            {
                return;
            }

            KeyCode = e.KeyCode;
            KeyValue = e.KeyValue;

            bool Is_Ctrl = (e.Modifiers == Keys.Control);

            String keycode_s = Key_Text_Get(KeyCode, Is_Ctrl);
            if (keycode_s.Length > 0)
            {
                String keyvalue_s = "0x" + KeyValue.ToString("X2");
                Cli_Input_textBox.AppendText("PreviewKeyDown: " + keyvalue_s + " " + keycode_s + "\r\n");
                Is_Processed_In_PreviewKeyDown = true;
            }

        }
    }
}
