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

        Cli_Output_CS Cli_Output = null;
        Cli_Input_CS Cli_Input = null;

        Keys KeyCode;
        int KeyValue = 0;
        bool Is_Processed_In_PreviewKeyDown = false;

        Ref_Boolean Cmd_Exit = new Ref_Boolean(false);
        Ref_Boolean Cmd_Quit = new Ref_Boolean(false);
        Ref_Boolean Cmd_Script_Stop = new Ref_Boolean(false);
        Ref_Boolean Cmd_Wait_Stop = new Ref_Boolean(false);
        Ref_Boolean Log_Wait_Enable = new Ref_Boolean(true);

        Cli_CMD_Processor CMD_Processor;
        Cli_TAB_Processor TAB_Processor;

        Cli_History History = new Cli_History();

        bool is_invitation_print = true;

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

            List<Level_Description> Levels = new List<Level_Description>();

            Cmd_Token_Parser Token_Parser = new Cmd_Token_Parser();

            const string Str_Rem_DEF = "$";

            Ref_Cli_Cmd_Privilege_ID User_Privilege = new Ref_Cli_Cmd_Privilege_ID(Cli_Cmd_Privilege_ID.CMD_PRIVILEGE_ROOT_DEF);

            Cli_Modules Modules = new Cli_Modules();

            bool tab_log_is_active = false;

            CMD_Processor = new Cli_CMD_Processor(User_Privilege, Modules, Levels, Token_Parser, Cli_Input, Cli_Output, Str_Rem_DEF);
            TAB_Processor = new Cli_TAB_Processor(User_Privilege, Modules, Levels, Token_Parser, Cli_Input, Cli_Output, Str_Rem_DEF, tab_log_is_active);

            // Modules Add - Begin

            string level_root = "top level";

            Modules.Add(new Cli_Module_Base_Rem(Str_Rem_DEF, Cli_Output));

            Modules.Add(new Cli_Module_Base_Quit(Cmd_Exit, Cmd_Quit));

            char C_Single = '?';
            char C_Multy = '*';
            Str_Filter str_filter = new Str_Filter(C_Single, C_Multy);
            Modules.Add(new Cli_Module_Base_Help(User_Privilege, Modules, str_filter, Cli_Output));
            Modules.Add(new Cli_Module_Base_Modules(User_Privilege, Modules, str_filter, Cli_Output));

            Modules.Add(new Cli_Module_Base_History(History, Cli_Output));
            Modules.Add(new Cli_Module_Base_Log(Cli_Input));

            Ref_String Script_Command_Str = new Ref_String("");
            Ref_String Script_Label_Str = new Ref_String("");
            Modules.Add(new Cli_Module_Base_Script(History, Cli_Input, Cli_Output,
                    Str_Rem_DEF, Cmd_Script_Stop, Cmd_Quit,
                    CMD_Processor, Script_Command_Str, Script_Label_Str));
            Modules.Add(new Cli_Module_Base_Wait(Log_Wait_Enable, Cmd_Wait_Stop, Cli_Input, Cli_Output));

            Modules.Add(new Cli_Module_Test_Tab_Min_Max());
            Modules.Add(new Cli_Module_Test_Terminal(Cli_Input, Cli_Output));

            Modules.Add(new Cli_Module_Base_Debug(User_Privilege, Modules, Levels, CMD_Processor, Cli_Output));

            Dictionary<string, string> Values_Map = new Dictionary<string, string>();

            Modules.Add((new Cli_Module_Check(Modules, Values_Map, str_filter, Cli_Output, Cmd_Script_Stop)));

            Modules.Add((new Cli_Module_Vars(Modules, Values_Map, str_filter, Cli_Output, C_Single, C_Multy)));

            Modules.Add((new Cli_Module_Base_Level(Cli_Input, level_root)));
        }

        void Cli_Input_Item_Process(Cli_Input_Item input_item)
        {
            bool is_cmd_back = false;
            bool is_cmd_delete = false;

            //TextInputControl TextInputObj = (TextInputControl) event.getSource();

            //if (null != TextInputObj) {

            Cli_Output.Caret_Pos_Set(Cli_Input.Input_Str_Get().Length, Cli_Input.Input_Str_Pos_Get());

            //Cli_Input_Item input_item = Cli_Input.On_Key_Pressed(event);

            if (input_item != null)
            {

                switch (input_item.Type_Get())
                {
                    case Input_Cmd_Type.INPUT_CMD_ENTER:

                        if (Cli_Input.Input_Mode_Get() == Input_Mode_Type.INPUT_MODE_NORMAL)
                        {

                            if (input_item.Type_Get() == Input_Cmd_Type.INPUT_CMD_ENTER)
                            {

                                bool is_no_history = false;
                                bool is_debug = false;

                                String s_trim = input_item.Text_Get().Trim();

                                if (!is_no_history && !is_debug && s_trim.Length != 0)
                                {
                                    History.History_Put(s_trim);
                                }

                                Ref_Boolean debug_res = new Ref_Boolean(false);
                                CMD_Processor.Process_Input_Item(input_item, is_debug, debug_res);

                                if (Cli_Input.Input_Mode_Get() == Input_Mode_Type.INPUT_MODE_NORMAL)
                                {
                                    if (!Cmd_Exit.Value && !Cmd_Quit.Value)
                                    {
                                        Cli_Output.Output_NewLine();
                                        Cli_Output.Output_Str(Cli_Input.Invitation_Full_Get());
                                    }
                                    Cli_Input.Input_Str_Set_Empty();
                                }

                            }

                        }
                        else if (Cli_Input.Input_Mode_Get() == Input_Mode_Type.INPUT_MODE_PROMPT)
                        {
                            Cli_Output.Output_NewLine();
                            if (input_item.Text_Get().Equals("Y") || input_item.Text_Get().Equals("y")
                                    || input_item.Text_Get().Equals("YES") || input_item.Text_Get().Equals("Yes") || input_item.Text_Get().Equals("yes"))
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
                            Cli_Output.Output_Str("Password:" + input_item.Text_Get());
                            Cli_Output.Output_NewLine();

                        }
                        else if (Cli_Input.Input_Mode_Get() == Input_Mode_Type.INPUT_MODE_WAIT)
                        {
                            Cmd_Wait_Stop.Value = true;
                            Cli_Input.Wait_Count_Set(-1);
                            Cli_Output.Output_Str("Wait stopped");
                            Cli_Output.Output_NewLine();
                            Cli_Output.Output_Str(Cli_Input.Invitation_Full_Get());
                            Cli_Input.Input_Str_Set_Empty();
                        }

                        break;
                    case Input_Cmd_Type.INPUT_CMD_TAB:
                        Ref_Boolean is_invitation_print_tab = new Ref_Boolean(false);
                        TAB_Processor.Process_Input_Item(input_item, is_invitation_print_tab);
                        is_invitation_print = is_invitation_print_tab.Value;

                        if (is_invitation_print)
                        {
                            Cli_Output.Output_Str(Cli_Input.Invitation_Full_Get());
                            Cli_Output.Output_Str(Cli_Input.Input_Str_Get());
                        }

                        Cli_Input.Input_Str_Pos_Set(Cli_Input.Input_Str_Get().Length);
                        Cli_Output.Caret_Pos_Set(Cli_Input.Input_Str_Get().Length, Cli_Input.Input_Str_Pos_Get());
                        break;
                    case Input_Cmd_Type.INPUT_CMD_UP:
                        String s_prev_up = Cli_Input.Input_Str_Get();
                        Cli_Input.Input_Str_Set(History.History_Up());
                        Cli_Input.Input_Str_Modified_To_Output(s_prev_up);
                        Cli_Input.Input_End();
                        is_invitation_print = false;
                        break;
                    case Input_Cmd_Type.INPUT_CMD_DOWN:
                        String s_prev_down = Cli_Input.Input_Str_Get();
                        Cli_Input.Input_Str_Set(History.History_Down());
                        Cli_Input.Input_Str_Modified_To_Output(s_prev_down);
                        Cli_Input.Input_End();
                        is_invitation_print = false;
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
                            Cmd_Script_Stop.Value = true;
                            Cmd_Wait_Stop.Value = true;
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
                    default:
                        //String s = input_item.Type_Get().toString() + ":\"" + input_item.Text_Get() + "\"";
                        //System.out.println(s);
                        break;
                }

                if (Cmd_Exit.Value)
                {
                    Cli_Output.Output_NewLine();
                    Cli_Output.Output_Str("Exit - Processed");
                    Cli_Output.Output_NewLine();
                    Application.Exit(); // Exit
                    //Cmd_Exit.Value = false; // DEBUG
                }
                if (Cmd_Quit.Value)
                {
                    Cli_Output.Output_NewLine();
                    Cli_Output.Output_Str("Quit - Processed");
                    Cli_Output.Output_NewLine();
                    Application.Exit(); // Quit
                    //Cmd_Quit.Value = false; // DEBUG
                }

            }

            //}

            //if (!is_cmd_back && !is_cmd_delete)
            //{
            //event.consume();
            //}

        }

        protected void Cli_Input_TextBox_KeyDown(object sender, KeyEventArgs e)
        {
            e.Handled = true;
        }

        protected void Cli_Input_TextBox_PreviewKeyDown(object sender, PreviewKeyDownEventArgs e)
        {
            KeyCode = e.KeyCode;
            KeyValue = e.KeyValue;

            if (KeyCode == Keys.ControlKey)
            {
                return;
            }

            bool Is_Ctrl = (e.Modifiers == Keys.Control);
            char Input_Char = '\0';
            Cli_Input_Item input_item = Cli_Input.On_Key_Pressed(KeyCode, Is_Ctrl, Input_Char);

            Is_Processed_In_PreviewKeyDown = false;
            if (input_item != null)
            {
                Cli_Input_Item_Process(input_item);
                Is_Processed_In_PreviewKeyDown = true;
            }
            if (KeyCode == Keys.Back)
            {
                Is_Processed_In_PreviewKeyDown = true;
            }
        }

        protected void Cli_Input_TextBox_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!Is_Processed_In_PreviewKeyDown)
            {
                bool Is_Ctrl = (Control.ModifierKeys & Keys.Control) == Keys.Control;
                char Input_Char = e.KeyChar;
                Cli_Input_Item input_item = Cli_Input.On_Key_Pressed(KeyCode, Is_Ctrl, Input_Char);

                if (input_item != null)
                {
                    Cli_Input_Item_Process(input_item);
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
