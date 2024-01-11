using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace Cli_Output_CS_Test
{
    public partial class Cli_Output_CS_Test_Form : System.Windows.Forms.Form
    {
        private Cli_Output_CS Cli_Output;

        int State = 0;

        private void Test_State_0()
        {
            Cli_Output.Output_Char('X');
            Cli_Output.Output_NewLine();
            Cli_Output.Output_Str(" - Ok");
            Cli_Output.Output_NewLine();
            Cli_Output.Output_Str("End");
            Cli_Output.Output_Return();
        }

        private void Test_State_1()
        {
            bool res_clear;
            res_clear = Cli_Output.Output_Clear();
            if (res_clear)
            {
                Cli_Output.Output_Str("Cleared");
            }
            else
            {
                Cli_Output.Output_Str("Not Cleared");
            }
        }

        private void Test_State_2()
        {
            Cli_Output.Output_NewLine();
            Cli_Output.Output_Str("Finished");
            Cli_Output.Output_NewLine();
        }

        private void Test_State_3()
        {
            Cli_Output.Output_NewLine();
            Cli_Output.Output_Str("Exit");
            Cli_Output.Output_NewLine();

            Application.Exit();
        }

        public Cli_Output_CS_Test_Form()
        {
            InitializeComponent();

            Cli_Output = new Cli_Output_CS(Cli_Input_textBox);

            Test_State_0();
            State = 1;
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
            switch (State)
            {
                case 0:
                    Test_State_0();
                    State = 1;
                    break;
                case 1:
                    Test_State_1();
                    State = 2;
                    break;
                case 2:
                    Test_State_2();
                    State = 3;
                    break;
                case 3:
                    Test_State_3();
                    State = 0;
                    break;
            }
        }

        private void Cli_Input_textBox_TextChanged(object sender, EventArgs e)
        {

        }
    }
}
