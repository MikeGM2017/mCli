using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace Cli_Core_CS
{
    public partial class Cli_Core_CS_Test : Form
    {

        const string Version = "0.01";

        private Cli_Output_CS Cli_Output = null;
        private Cli_Input_CS Cli_Input = null;

        private Keys Key_Code;
        private bool Is_Ctrl = false;
        private bool Is_Processed_In_PreviewKeyDown = false;

        public Cli_Core_CS_Test()
        {
            InitializeComponent();

            // Cli_Input / Cli_Output - Beg

            Cli_Output = new Cli_Output_CS(Cli_Input_TextBox);
            string Chars_Not_Allowed_Str = "@`|";
            Cli_Input = new Cli_Input_CS(Cli_Output, Chars_Not_Allowed_Str);

            Cli_Output.Output_Clear();

            Cli_Output.Output_NewLine();
            Cli_Output.Output_Str("Cli Core C#");
            Cli_Output.Output_Str(" V");
            Cli_Output.Output_Str(Version);
            Cli_Output.Output_Str(" started");
            Cli_Output.Output_NewLine();
            Cli_Output.Output_NewLine();

            Cli_Input.Title_Set("cli demo");
            Cli_Input.User_Set("root");
            Cli_Input.Level_Set("top level");
            Cli_Input.Invitation_Set("> ");
            Cli_Input.Divider_L_Set("[");
            Cli_Input.Divider_R_Set("]");
            Cli_Input.Input_Init();

            Cli_Output.Output_Str(Cli_Input.Invitation_Full_Get());

            // Cli_Input / Cli_Output - End

        }

        ~Cli_Core_CS_Test()
        {
            Cli_Input.Input_Restore();
        }

        private void Cli_Input_Item_Process(Cli_Input_Item item)
        {
            bool is_cmd_back = false;
            bool is_cmd_delete = false;

            switch (item.Type_Get())
            {

                case Input_Cmd_Type.INPUT_CMD_ENTER:

                    if (Cli_Input.Input_Mode_Get() == Input_Mode_Type.INPUT_MODE_NORMAL)
                    {

                        Cli_Output.Output_NewLine();

                        if (item.Text_Get() == "Q" || item.Text_Get() == "quit")
                        {
                            Application.Exit();
                        }
                        else if (item.Text_Get() == "C" || item.Text_Get() == "clear")
                        {
                            Cli_Output.Output_Clear();
                            Cli_Output.Output_Str("Clear - Processed");
                            Cli_Output.Output_NewLine();
                        }
                        else if (item.Text_Get() == "A" || item.Text_Get() == "ask")
                        {
                            Cli_Output.Output_Str("Is it right?(yes/no) ");
                            Cli_Input.Input_Str_Set_Empty();
                            Cli_Input.Input_Mode_Set(Input_Mode_Type.INPUT_MODE_PROMPT);
                            break;
                        }
                        else if (item.Text_Get() == "P" || item.Text_Get() == "passwd")
                        {
                            Cli_Output.Output_Str("Password:");
                            Cli_Input.Input_Str_Set_Empty();
                            Cli_Input.Input_Mode_Set(Input_Mode_Type.INPUT_MODE_PASSWD);
                            break;
                        }
                        else if (item.Text_Get() == "W" || item.Text_Get() == "wait")
                        {
                            Cli_Output.Output_Str("Wait (Press Enter to stop):");
                            Cli_Output.Output_NewLine();
                            Cli_Input.Input_Str_Set_Empty();
                            Cli_Input.Input_Mode_Set(Input_Mode_Type.INPUT_MODE_WAIT);
                            Cli_Input.Wait_Count_Set(10);
                            break;
                        }
                        else if (item.Text_Get() == "H" || item.Text_Get() == "help")
                        {
                            Help_Print();
                            Cli_Output.Output_NewLine();
                        }
                        else if (item.Text_Get().Length > 0)
                        {
                            String s = item.Text_Get();
                            Cli_Output.Output_Str(item.Text_Get() + " - Not Processed");
                            Cli_Output.Output_NewLine();
                        }

                    }
                    else if (Cli_Input.Input_Mode_Get() == Input_Mode_Type.INPUT_MODE_PROMPT)
                    {
                        Cli_Output.Output_NewLine();
                        if (item.Text_Get() == "Y" || item.Text_Get() == "y"
                                || item.Text_Get() == "YES" || item.Text_Get() == "Yes" || item.Text_Get() == "yes")
                        {
                            Cli_Output.Output_Str("Answer: Yes");
                        }
                        else
                        {
                            Cli_Output.Output_Str("Answer: No");
                        }
                        Cli_Output.Output_NewLine();

                    }
                    else if (Cli_Input.Input_Mode_Get() == Input_Mode_Type.INPUT_MODE_PASSWD)
                    {
                        Cli_Output.Output_NewLine();
                        Cli_Output.Output_Str("Password:" + item.Text_Get());
                        Cli_Output.Output_NewLine();

                    }
                    else if (Cli_Input.Input_Mode_Get() == Input_Mode_Type.INPUT_MODE_WAIT)
                    {
                        Cli_Input.Wait_Count_Set(-1);
                        Cli_Output.Output_Str("Wait stopped");
                        Cli_Output.Output_NewLine();
                    }

                    Cli_Output.Output_Str(Cli_Input.Invitation_Full_Get());
                    Cli_Input.Input_Str_Set_Empty();
                    Cli_Input.Input_Mode_Set(Input_Mode_Type.INPUT_MODE_NORMAL);

                    break;

                case Input_Cmd_Type.INPUT_CMD_TAB:
                    Cli_Output.Output_NewLine();
                    //Cli_Output.Output_Str("TAB: \"" + item.Text_Get() + "\" - Not Processed");
                    Help_Print();

                    Cli_Input.Input_Str_Pos_Set(Cli_Input.Input_Str_Get().Length);

                    Cli_Output.Output_NewLine();
                    Cli_Output.Output_Str(Cli_Input.Invitation_Full_Get());
                    Cli_Output.Output_Str(Cli_Input.Input_Str_Get());
                    break;
                case Input_Cmd_Type.INPUT_CMD_UP:
                    Cli_Output.Output_NewLine();
                    Cli_Output.Output_Str("UP: \"" + item.Text_Get() + "\" - Not Processed");
                    Cli_Output.Output_NewLine();
                    Cli_Output.Output_Str(Cli_Input.Invitation_Full_Get());
                    Cli_Output.Output_Str(Cli_Input.Input_Str_Get());
                    break;
                case Input_Cmd_Type.INPUT_CMD_DOWN:
                    Cli_Output.Output_NewLine();
                    Cli_Output.Output_Str("DOWN: \"" + item.Text_Get() + "\" - Not Processed");
                    Cli_Output.Output_NewLine();
                    Cli_Output.Output_Str(Cli_Input.Invitation_Full_Get());
                    Cli_Output.Output_Str(Cli_Input.Input_Str_Get());
                    break;
                case Input_Cmd_Type.INPUT_CMD_BACK:
                    is_cmd_back = true;
                    break;
                case Input_Cmd_Type.INPUT_CMD_DELETE:
                    is_cmd_delete = true;
                    break;
                case Input_Cmd_Type.INPUT_CMD_CTRL_C:
                case Input_Cmd_Type.INPUT_CMD_CTRL_Z:
                case Input_Cmd_Type.INPUT_CMD_CTRL_BACKSLASH:
                    if (Cli_Input.Input_Mode_Get() == Input_Mode_Type.INPUT_MODE_WAIT)
                    {
                        Cli_Input.Wait_Count_Set(-1);
                        Cli_Output.Output_Str("Wait stopped");
                        Cli_Output.Output_NewLine();
                        Cli_Output.Output_Str(Cli_Input.Invitation_Full_Get());
                        Cli_Input.Input_Str_Set_Empty();
                        Cli_Input.Input_Mode_Set(Input_Mode_Type.INPUT_MODE_NORMAL);
                    }
                    else
                    {
                        Cli_Output.Output_NewLine();
                        Cli_Output.Output_Str(Cli_Input.Invitation_Full_Get());
                        Cli_Input.Input_Str_Set_Empty();
                    }
                    break;
            }
        }

        private void Cli_Input_TextBox_KeyDown(object sender, KeyEventArgs e)
        {
            e.Handled = true;
        }

        private void Cli_Input_TextBox_PreviewKeyDown(object sender, PreviewKeyDownEventArgs e)
        {
            Cli_Output.Caret_Pos_Set(Cli_Input.Input_Str_Get().Length, Cli_Input.Input_Str_Pos_Get());

            Key_Code = e.KeyCode;

            Is_Ctrl = (e.Modifiers == Keys.Control);

            if (Key_Code == Keys.ControlKey)
            {
                return;
            }

            char Input_Char = '\0';
            Cli_Input_Item item = Cli_Input.On_Key_Pressed(Key_Code, Is_Ctrl, Input_Char);

            Is_Processed_In_PreviewKeyDown = false;
            if (item != null)
            {
                //Is_Processed_In_PreviewKeyDown = Cli_Input_Item_Process(item);
                Cli_Input_Item_Process(item);
                Is_Processed_In_PreviewKeyDown = true;
            }
        }

        private void Cli_Input_TextBox_KeyPress(object sender, KeyPressEventArgs e)
        {
            char Input_Char = e.KeyChar;
            if (!Is_Processed_In_PreviewKeyDown)
            {
                Cli_Input_Item item = Cli_Input.On_Key_Pressed(Key_Code, Is_Ctrl, Input_Char);

                if (item != null)
                {
                    //Is_Processed_In_PreviewKeyDown = Cli_Input_Item_Process(item);
                    Cli_Input_Item_Process(item);
                }
            }
            Is_Processed_In_PreviewKeyDown = false;

            e.Handled = true;
        }

        protected void Help_Print()
        {
            Cli_Output.Output_Str("Help: Q - quit, C - clear, H - help, A - ask(y/n), P - passwd(no echo), W - wait");
        }

    }
}
