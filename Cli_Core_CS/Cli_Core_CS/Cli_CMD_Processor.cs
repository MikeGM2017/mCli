using System.Collections.Generic;

namespace Cli_Core_CS
{
    class Cli_CMD_Processor
    {

        protected Ref_Cli_Cmd_Privilege_ID User_Privilege;
        protected Cli_Modules Modules;

        protected List<Level_Description> Levels;
        protected Cmd_Token_Parser Token_Parser;

        Cli_Input_CS Cli_Input;
        protected Cli_Output_CS Cli_Output;

        protected string Str_Rem;

        public Cli_CMD_Processor(Ref_Cli_Cmd_Privilege_ID user_privilege, Cli_Modules modules,
            List<Level_Description> levels, Cmd_Token_Parser parser,
            Cli_Input_CS cli_input, Cli_Output_CS cli_output,
            string str_rem)
        {
            User_Privilege = user_privilege;
            Modules = modules;
            Levels = levels;
            Token_Parser = parser;
            Cli_Input = cli_input;
            Cli_Output = cli_output;
            Str_Rem = str_rem;
        }

        public virtual Level_Description Level_Get()
        {
            if (Levels.Count > 0)
            {
                return Levels[Levels.Count - 1];
            }
            Level_Description level_top = new Level_Description();
            return level_top;
        }

        public virtual bool TAB_Cmd_Ptr_Check_By_Level(Cli_Cmd cmd_ptr, Cli_Cmd_Privilege_ID user_privilege, string level)
        {
            if (cmd_ptr != null && (int)user_privilege <= cmd_ptr.Privilege_Get())
            {
                if (cmd_ptr.Is_Global_Get()) return true;
                if (cmd_ptr.Level_Get() == level) return true;
            }
            return false;
        }

        public virtual bool Process_Input_Item(Cli_Input_Item input_item, bool is_debug, Ref_Boolean debug_res)
        {
            string s_trim = input_item.Text_Get().Trim();

            debug_res.Value = false;

            if (s_trim.Length == 0)
            {
                return false;
            }

            if (s_trim.Length != 0)
            {

                Level_Description level_description = Level_Get();
                string level = level_description.Level;

                bool is_processed = false;
                bool stop = false;
                Cmd_Token_Parser_Result parse_res = Cmd_Token_Parser_Result.CMD_TOKEN_PARSER_ERROR;
                List<Cmd_Token> tokens = Token_Parser.Parse(s_trim, Str_Rem, out parse_res);
                for (int module = 0; module < Modules.Get_Size(); module++)
                {
                    Cli_Module module_ptr = Modules.Get(module);
                    if (module_ptr != null)
                    {
                        for (int cmd = 0; cmd < module_ptr.Cmd_Count_Get() && !stop; cmd++)
                        {
                            Cli_Cmd cmd_ptr = module_ptr.Cmd_Get(cmd);
                            bool is_cmd_prt_valid = TAB_Cmd_Ptr_Check_By_Level(cmd_ptr, User_Privilege.Value, level);
                            if (is_cmd_prt_valid)
                            {
                                Cmd_Item_Valid_Result res_cmd_valid = cmd_ptr.Is_Valid(tokens);
                                switch (res_cmd_valid)
                                {
                                    case Cmd_Item_Valid_Result.CMD_ITEM_OK:
                                    case Cmd_Item_Valid_Result.CMD_ITEM_OK_CAN_CONTINUE:
                                    case Cmd_Item_Valid_Result.CMD_ITEM_OK_STR_WITHOUT_COMMAS:
                                        {
                                            if (!is_debug)
                                                Cli_Output.Output_NewLine();
                                            bool res_execute = module_ptr.Execute(cmd_ptr, Levels, is_debug);
                                            if (!res_execute)
                                            {
                                                if (!is_debug)
                                                {
                                                    Cli_Output.Output_NewLine();
                                                    Cli_Output.Output_Str(s_trim + " - Not Implemented (Module \"" + module_ptr.Name_Get() + "\")");
                                                    Cli_Output.Output_NewLine();
                                                }
                                            }
                                            else
                                            {
                                                debug_res.Value = true;
                                            }
                                            is_processed = true;
                                            stop = true;
                                        }
                                        break;
                                    case Cmd_Item_Valid_Result.CMD_ITEM_ERROR:
                                    case Cmd_Item_Valid_Result.CMD_ITEM_NOT_MATCH:
                                        break;
                                    default:
                                        //Cli_Output.Output_NewLine();
                                        //Cli_Output.Output_Str("ERROR: " + s_trim + " - " + Cmd_Item_Valid_Result_Func::To_String(res_cmd_valid));
                                        break;
                                }
                            }
                        }
                    }
                }
                if (!is_processed)
                {
                    Cli_Output.Output_NewLine();
                    Cli_Output.Output_NewLine();
                    Cli_Output.Output_Str(s_trim + " - Not Processed");
                    Cli_Output.Output_NewLine();
                }
            }
            else
            {
                Cli_Output.Output_NewLine();
            }
            return true; // Ok
        }

    }
}
