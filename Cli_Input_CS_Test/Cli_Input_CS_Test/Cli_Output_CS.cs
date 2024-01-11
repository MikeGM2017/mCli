using System.Windows.Forms;

namespace Cli_Input_CS_Test
{
    class Cli_Output_CS
    {
        public TextBox textInputControl = null;

        public Cli_Output_CS(TextBox textBox)
        {
            textInputControl = textBox;
        }

        public bool Output_Init()
        {
            return false;
        }

        public bool Output_Clear()
        {
            if (textInputControl != null)
            {
                if (textInputControl.InvokeRequired)
                {
                    textInputControl.Invoke((MethodInvoker)delegate { textInputControl.Clear(); });
                    return true;
                }
                textInputControl.Clear();
                return true;
            }
            return false;
        }

        public void Output_Char(char c)
        {
            if (textInputControl != null)
            {
                string s = "";
                s += c;
                if (textInputControl.InvokeRequired)
                {
                    textInputControl.Invoke((MethodInvoker)delegate { textInputControl.AppendText(s); });
                    return;
                }
                textInputControl.AppendText(s);
            }
        }

        public void Output_Str(string s)
        {
            if (textInputControl != null)
            {
                if (textInputControl.InvokeRequired)
                {
                    textInputControl.Invoke((MethodInvoker)delegate { textInputControl.AppendText(s); });
                    return;
                }
                textInputControl.AppendText(s);
            }
        }

        public void Output_NewLine()
        {
            if (textInputControl != null)
            {
                string s = "\r\n";
                if (textInputControl.InvokeRequired)
                {
                    textInputControl.Invoke((MethodInvoker)delegate { textInputControl.AppendText(s); });
                    return;
                }
                textInputControl.AppendText(s);
            }
        }

        public void Output_Return()
        {
            if (textInputControl != null)
            {
                char[] c_arr = textInputControl.Text.ToCharArray();
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
                if (textInputControl.InvokeRequired)
                {
                    textInputControl.Invoke((MethodInvoker)delegate { textInputControl.Select(pos, 0); });
                    return;
                }
                textInputControl.Select(pos, 0);
            }
        }

        public void Caret_Pos_Set(int input_str_len, int input_str_pos)
        {
            if (textInputControl != null)
            {
                int output_text_len = textInputControl.Text.Length;
                int caret_pos = output_text_len - input_str_len + input_str_pos;
                if (caret_pos < 0)
                {
                    caret_pos = 0;
                }
                if (textInputControl.InvokeRequired)
                {
                    textInputControl.Invoke((MethodInvoker)delegate { textInputControl.Select(caret_pos, 0); });
                    return;
                }
                textInputControl.Select(caret_pos, 0);
            }
        }

    }
}
