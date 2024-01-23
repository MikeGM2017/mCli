using System;
using System.Threading;
using System.Windows.Forms;

namespace Cli_Core_CS
{
    class Cli_Input_CS
    {

        static String Invitation_DEF = "> ";
        static String Divider_L_DEF = "[";
        static String Divider_R_DEF = "]";

        protected String Title = "";
        protected String User = "";
        protected String Level = "";
        protected String Invitation = Invitation_DEF;
        protected String Divider_L = Divider_L_DEF;
        protected String Divider_R = Divider_R_DEF;
        protected String Input_Str = "";

        protected String Prompt_Str = "";

        protected bool Is_Echo = true;

        protected int Input_Str_Pos = 0;

        Cli_Output_CS Cli_Output = null;

        String Chars_Not_Allowed_Str = "";

        protected bool Is_Input_Str_Pos_Too_Left = false;

        protected Input_Mode_Type Input_Mode = Input_Mode_Type.INPUT_MODE_NORMAL;

        static Thread Wait_Thread = null;
        protected int Wait_Count = -1;

        public void Wait_Count_Set(int v)
        {
            Wait_Count = v;
        }

        public int Wait_Count_Get()
        {
            return Wait_Count;
        }

        static public void Wait_Thread_Func(object data)
        {
            Cli_Input_CS main_obj = (Cli_Input_CS)data;
            while (true)
            {
                if (main_obj != null)
                {
                    if (main_obj.Wait_Count > 0)
                    {
                        main_obj.Cli_Output.Output_Str("Wait " + main_obj.Wait_Count.ToString() + "...");
                        main_obj.Cli_Output.Output_NewLine();
                        main_obj.Wait_Count--;
                    }
                    else if (main_obj.Wait_Count == 0)
                    {
                        main_obj.Cli_Output.Output_Str(main_obj.Invitation_Full_Get());
                        main_obj.Wait_Count--;
                        main_obj.Input_Mode_Set(Input_Mode_Type.INPUT_MODE_NORMAL);
                    }
                }
                System.Threading.Thread.Sleep(1000);
            }
        }

        public Cli_Input_CS(Cli_Output_CS cli_output, String chars_not_allowed)
        {
            Cli_Output = cli_output;
            Chars_Not_Allowed_Str = chars_not_allowed;

            Is_Echo = true;
            Input_Str = "";
            Input_Str_Pos = 0;
            Prompt_Str = "";

            Is_Input_Str_Pos_Too_Left = false;

            Input_Mode = Input_Mode_Type.INPUT_MODE_NORMAL;
            Wait_Count = -1;
        }

        ~Cli_Input_CS()
        {
            Input_Restore();
        }

        public void Title_Set(String s)
        {
            Title = s;
        }

        public String Title_Get()
        {
            return Title;
        }

        public void User_Set(String s)
        {
            User = s;
        }

        public String User_Get()
        {
            return User;
        }

        public void Level_Set(String s)
        {
            Level = s;
        }

        public String Level_Get()
        {
            return Level;
        }

        public void Invitation_Set(String s)
        {
            Invitation = s;
        }

        public String Invitation_Get()
        {
            return Invitation;
        }

        public void Divider_L_Set(String s)
        {
            Divider_L = s;
        }

        public String Divider_L_Get()
        {
            return Divider_L;
        }

        public void Divider_R_Set(String s)
        {
            Divider_R = s;
        }

        public String Divider_R_Get()
        {
            return Divider_R;
        }

        public void Prompt_Str_Set(String s)
        {
            Prompt_Str = s;
        }

        public String Prompt_Str_Get()
        {
            return Prompt_Str;
        }

        public void Is_Echo_Set(bool v)
        {
            Is_Echo = v;
        }

        public bool Is_Echo_Get()
        {
            return Is_Echo;
        }

        public void Input_Str_Pos_Set(int v)
        {
            Input_Str_Pos = v;
        }

        public int Input_Str_Pos_Get()
        {
            return Input_Str_Pos;
        }

        public void Chars_Not_Allowed_Str_Set(String s)
        {
            Chars_Not_Allowed_Str = s;
        }

        public String Chars_Not_Allowed_Str_Get()
        {
            return Chars_Not_Allowed_Str;
        }

        public void Input_Mode_Set(Input_Mode_Type input_mode)
        {
            Input_Mode = input_mode;
            if (Input_Mode == Input_Mode_Type.INPUT_MODE_PASSWD)
            {
                Is_Echo_Set(false);
            }
            else
            {
                Is_Echo_Set(true);
            }
        }

        public Input_Mode_Type Input_Mode_Get()
        {
            return Input_Mode;
        }

        public bool Input_Init()
        {
            bool cli_ouput_init_res = Cli_Output.Output_Init();

            Wait_Thread = new Thread(Wait_Thread_Func);
            Wait_Thread.IsBackground = true; //@Warning
            Wait_Thread.Start(this);

            return cli_ouput_init_res;
        }

        public bool Input_Restore()
        {
            if (Wait_Thread != null)
            {
                Wait_Thread.Abort();
                return true;
            }
            return false;
        }

        public bool Input_Clear()
        {
            return Cli_Output.Output_Clear();
        }

        public String Invitation_Full_Get()
        { // Attention: Should be used for print cli invitation

            if (!String.IsNullOrEmpty(Prompt_Str))
            {
                return Prompt_Str;
            }

            String s = "";
            if (!String.IsNullOrEmpty(Title))
            {
                s += Divider_L + Title + Divider_R;
            }

            if (!String.IsNullOrEmpty(User))
            {
                s += Divider_L + User + Divider_R;
            }

            if (!String.IsNullOrEmpty(Level))
            {
                s += Divider_L + Level + Divider_R;
            }

            if (!String.IsNullOrEmpty(Invitation))
            {
                s += Invitation;
            }

            return s;
        }

        public void Invitation_Print()
        {
            Cli_Output.Output_Str(Invitation_Full_Get());
        }

        public String Input_Str_Get()
        {
            return Input_Str;
        }

        public void Input_Str_Set(String s)
        {
            Input_Str = s;
        }

        public void Input_Str_Set_Empty()
        {
            Input_Str = "";
            Input_Str_Pos = 0;
        }

        public void Input_Add_Char_To_End(String s)
        {
            Input_Str += s;
            Input_Str_Pos = Input_Str.Length;
        }

        public void Input_Add_Char_Middle(String s)
        {
            String s1 = "";
            if (Input_Str_Pos > 0)
            {
                s1 = Input_Str.Substring(0, Input_Str_Pos);
            }

            String s2 = "";
            if (Input_Str_Pos < Input_Str.Length)
            {
                s2 = Input_Str.Substring(Input_Str_Pos, Input_Str.Length);
            }

            Input_Str = s1 + s + s2;
            Input_Str_Pos++;
        }

        public void Input_Back()
        {
            if (Input_Str_Pos == 0)
            {
                Is_Input_Str_Pos_Too_Left = true;
            }
            else
            {
                Is_Input_Str_Pos_Too_Left = false;
            }
            if (Input_Str_Pos < 0)
            {
                Input_Str_Pos = 0;
            }
            if (Input_Str_Pos > Input_Str.Length)
            {
                Input_Str_Pos = Input_Str.Length;
            }
            if (Input_Str.Length > 0 && Input_Str_Pos > 0)
            {
                String s_prev = Input_Str_Get();
                if (Input_Str_Pos == Input_Str.Length)
                {
                    Input_Str = Input_Str.Substring(0, Input_Str_Pos - 1);
                    Input_Str_Pos = Input_Str.Length;
                }
                else
                {

                    String s1 = Input_Str.Substring(0, Input_Str_Pos - 1);
                    String s2 = Input_Str.Substring(Input_Str_Pos, Input_Str.Length - Input_Str_Pos);
                    Input_Str = s1 + s2;
                    Input_Str_Pos--;
                }
                if (Is_Echo_Get())
                {
                    Input_Str_Modified_To_Output(s_prev);
                }
            }
        }

        public void Input_Delete()
        {
            if (Input_Str_Pos < 0)
            {
                Input_Str_Pos = 0;
            }
            if (Input_Str_Pos > Input_Str.Length)
            {
                Input_Str_Pos = Input_Str.Length;
            }
            if (Input_Str.Length > 0 && Input_Str_Pos < Input_Str.Length)
            {
                String s_prev = Input_Str_Get();
                String s1 = Input_Str.Substring(0, Input_Str_Pos);
                String s2 = Input_Str.Substring(Input_Str_Pos + 1, Input_Str.Length - (Input_Str_Pos + 1));
                Input_Str = s1 + s2;
                //Input_Str_Pos = Input_Str_Pos_prev; // Not changed
                if (Is_Echo_Get())
                {
                    Input_Str_Modified_To_Output(s_prev);
                }
            }
        }

        public void Input_Str_To_Output()
        {
            if (Is_Echo_Get())
            {
                Cli_Output.Output_Return();
                Cli_Output.Output_Str(Invitation_Full_Get());
                if (Input_Str_Pos > 0)
                {
                    Cli_Output.Output_Str(Input_Str.Substring(0, Input_Str_Pos));
                }
                Cli_Output.Caret_Pos_Set(Input_Str.Length, Input_Str_Pos);
            }
        }

        public void Input_Str_Modified_To_Output(String s_prev)
        {
            if (Is_Echo_Get())
            {
                int text_len = Cli_Output.textInputControl.Text.Length;
                Cli_Output.textInputControl.SelectionStart = text_len - s_prev.Length;
                Cli_Output.textInputControl.SelectionLength = text_len;
                Cli_Output.textInputControl.SelectedText = Input_Str;
                Cli_Output.Caret_Pos_Set(Input_Str.Length, Input_Str_Pos);
            }
        }

        public void Input_End()
        {
            Input_Str_Pos = Input_Str.Length;
            //Input_Str_To_Output();
            Cli_Output.Caret_Pos_Set(Input_Str.Length, Input_Str_Pos);
        }

        protected void On_Key_RIGHT()
        {
            if (Input_Str_Pos < Input_Str.Length)
            {
                Input_Str_Pos++;
            }
            Cli_Output.Caret_Pos_Set(Input_Str.Length, Input_Str_Pos);
        }

        protected void On_Key_LEFT()
        {
            if (Input_Str_Pos > 0)
            {
                Input_Str_Pos--;
            }
            Cli_Output.Caret_Pos_Set(Input_Str.Length, Input_Str_Pos);
        }

        protected void On_Key_HOME()
        {
            Input_Str_Pos = 0;
            Cli_Output.Caret_Pos_Set(Input_Str.Length, Input_Str_Pos);
        }

        protected void On_Key_END()
        {
            Input_Str_Pos = Input_Str.Length;
            Cli_Output.Caret_Pos_Set(Input_Str.Length, Input_Str_Pos);
        }

        protected void On_Key_BACK()
        {
            Input_Back();
        }

        protected void On_Key_DELETE()
        {
            Input_Delete();
        }

        public bool Is_Char_Valid(String char_str)
        {
            if (!String.IsNullOrEmpty(Chars_Not_Allowed_Str))
            {
                if (Chars_Not_Allowed_Str.Contains(char_str))
                {
                    return false;
                }
            }
            return true;
        }

        protected bool On_Key_Any(String s)
        {
            if (Is_Char_Valid(s))
            {
                if (Input_Str_Get().Length == Input_Str_Pos_Get())
                {
                    Input_Add_Char_To_End(s);
                    if (Is_Echo_Get())
                    {
                        Cli_Output.Output_Str(s);
                    }
                }
                else
                {
                    Input_Add_Char_Middle(s);
                }
                return true;
            }
            return false;
        }

        protected virtual void Input_Str_Clear()
        {
            Input_Str_Pos = 0;
            Input_Str = "";
        }

        protected bool On_Key_CTRL_C()
        {
            Input_Str_Clear();

            if (Cli_Output != null)
            {
                Cli_Output.Output_NewLine();
                Cli_Output.Output_Str(Invitation_Full_Get());
            }
            return true;
        }

        protected bool On_Key_CTRL_Z()
        {
            Input_Str_Clear();

            if (Cli_Output != null)
            {
                Cli_Output.Output_NewLine();
                Cli_Output.Output_Str(Invitation_Full_Get());
            }
            return true;
        }

        public Cli_Input_Item On_Key_Pressed(Keys Key_Code, bool Is_Ctrl, char input_char)
        {
            Cli_Input_Item item = null;

            if (Is_Ctrl && Key_Code == Keys.C)
            {
                //On_Key_CTRL_C();
                item = new Cli_Input_Item(Input_Cmd_Type.INPUT_CMD_CTRL_C, Input_Str_Get());
            }
            else if (Is_Ctrl && Key_Code == Keys.Z)
            {
                //On_Key_CTRL_Z();
                item = new Cli_Input_Item(Input_Cmd_Type.INPUT_CMD_CTRL_Z, Input_Str_Get());
            }
            else if (Is_Ctrl && Key_Code == Keys.OemPipe) // BACKSLASH
            {
                //On_Key_CTRL_Backslash();
                //item = new Cli_Input_Item(Input_Cmd_Type.INPUT_CMD_CTRL_BACKSLASH, Input_Str_Get());
            }
            else
            {

                switch (Key_Code)
                {
                    case Keys.Enter:
                        item = new Cli_Input_Item(Input_Cmd_Type.INPUT_CMD_ENTER, Input_Str_Get());
                        break;
                    case Keys.Tab:
                        item = new Cli_Input_Item(Input_Cmd_Type.INPUT_CMD_TAB, Input_Str_Get());
                        break;
                    case Keys.Up:
                        item = new Cli_Input_Item(Input_Cmd_Type.INPUT_CMD_UP, Input_Str_Get());
                        break;
                    case Keys.Down:
                        item = new Cli_Input_Item(Input_Cmd_Type.INPUT_CMD_DOWN, Input_Str_Get());
                        break;
                    case Keys.Right:
                        On_Key_RIGHT();
                        break;
                    case Keys.Left:
                        On_Key_LEFT();
                        break;
                    case Keys.Home:
                        On_Key_HOME();
                        break;
                    case Keys.End:
                        On_Key_END();
                        break;
                    case Keys.Back:
                        On_Key_BACK();
                        //if (!Is_Input_Str_Pos_Too_Left)
                        //{
                        //    item = new Cli_Input_Item(Input_Cmd_Type.INPUT_CMD_BACK, Input_Str_Get());
                        //}
                        break;
                    case Keys.Delete:
                        On_Key_DELETE();
                        //item = new Cli_Input_Item(Input_Cmd_Type.INPUT_CMD_DELETE, Input_Str_Get());
                        break;
                    default:
                        if (input_char != '\0')
                        {

                            switch (Key_Code)
                            {
                                //case Keys.Enter:
                                case Keys.Back:
                                    // nothing
                                    break;
                                default:
                                    String s = "";
                                    s += input_char;
                                    On_Key_Any(s);
                                    break;
                            }

                        }
                        break;
                }

            }

            return item;
        }

    }
}