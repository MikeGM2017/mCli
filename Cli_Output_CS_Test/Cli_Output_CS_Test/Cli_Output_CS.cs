using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;

namespace Cli_Output_CS_Test
{
    class Cli_Output_CS
    {
        TextBox Output_TextBox = null;

        public Cli_Output_CS(TextBox textBox)
        {
            Output_TextBox = textBox;
        }

        public bool Output_Clear()
        {
            if (Output_TextBox != null)
            {
                Output_TextBox.Clear();
                return true;
            }
            return false;
        }

        public void Output_Char(char c)
        {
            if (Output_TextBox != null)
            {
                string s = "";
                s += c;
                Output_TextBox.AppendText(s);
            }
        }

        public void Output_Str(string s)
        {
            if (Output_TextBox != null)
            {
                Output_TextBox.AppendText(s);
            }
        }

        public void Output_NewLine()
        {
            if (Output_TextBox != null)
            {
                Output_TextBox.AppendText("\r\n");
            }
        }

        public void Output_Return()
        {
            if (Output_TextBox != null)
            {
                //Output_TextBox.AppendText("\r");
                char[] c_arr = Output_TextBox.Text.ToCharArray();
                int pos = c_arr.Length - 1;
                for (pos = c_arr.Length - 1; pos >= 0; pos--)
                {
                    char c = c_arr[pos];
                    if (c == '\n')
                    {
                        pos++;
                        break;
                    }
                }
                Output_TextBox.Select(pos, 0);
            }
        }

    }
}
