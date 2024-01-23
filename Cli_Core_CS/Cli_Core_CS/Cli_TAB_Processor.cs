using System;
using System.Collections.Generic;
using System.Text;

namespace Cli_Core_CS
{
    class Cli_TAB_Processor
    {
        protected Ref_Cli_Cmd_Privilege_ID User_Privilege;
        protected Cli_Modules Modules;

        protected List<Level_Description> Levels;
        protected Cmd_Token_Parser Token_Parser;

        Cli_Input_CS Cli_Input;
        protected Cli_Output_CS Cli_Output;

        protected string Str_Rem;

        protected List<String> Log = new List<string>();
        protected bool Log_Is_Active;

        public Cli_TAB_Processor(Ref_Cli_Cmd_Privilege_ID user_privilege, Cli_Modules modules,
               List<Level_Description> levels, Cmd_Token_Parser parser,
               Cli_Input_CS cli_input, Cli_Output_CS cli_output,
               string str_rem,
            bool log_is_active)
        {
            User_Privilege = user_privilege;
            Modules = modules;
            Levels = levels;
            Token_Parser = parser;
            Cli_Input = cli_input;
            Cli_Output = cli_output;
            Str_Rem = str_rem;
            Log_Is_Active = log_is_active;
        }

        protected Level_Description Level_Get()
        {
            if (Levels.Count > 0)
            {
                return Levels[Levels.Count - 1];
            }
            Level_Description level_top = new Level_Description();
            return level_top;
        }

        public int Log_Size_Get()
        {
            return Log.Count;
        }

        public String Log_Item_Get(int index)
        {
            if (index >= 0 && index < Log.Count)
            {
                return Log[index];
            }
            return "";
        }

        protected bool TAB_Cmd_Ptr_Check_By_Level(Cli_Cmd cmd_ptr, Cli_Cmd_Privilege_ID user_privilege, String level)
        {
            if (cmd_ptr != null && (int)user_privilege <= cmd_ptr.Privilege_Get())
            {
                if (cmd_ptr.Is_Global_Get())
                {
                    return true;
                }
                if (cmd_ptr.Level_Get().Equals(level))
                {
                    return true;
                }
            }
            return false;
        }

        protected void TAB_Cmd_Add_By_Level(Cli_Cmd cmd_ptr, String level, List<String> str_list)
        {
            bool is_cmd_prt_valid = TAB_Cmd_Ptr_Check_By_Level(cmd_ptr, User_Privilege.Value, level);
            if (is_cmd_prt_valid)
            {
                String s = cmd_ptr.Items[0].Text_Get();
                //if (find(str_list.begin(), str_list.end(), s) == str_list.end()) {
                //    str_list.insert(str_list.end(), s);
                //}
                if (!str_list.Contains(s))
                {
                    str_list.Add(s);
                }
            }
        }

        protected String TAB_Help_Get(String level, Cli_Modules modules)
        {
            List<String> str_list = new List<String>();

            for (int module = 0; module < modules.Get_Size(); module++)
            {
                Cli_Module module_ptr = modules.Get(module);
                if (module_ptr != null)
                {
                    for (int cmd = 0; cmd < module_ptr.Cmd_Count_Get(); cmd++)
                    {
                        Cli_Cmd cmd_ptr = module_ptr.Cmd_Get(cmd);
                        bool is_cmd_prt_valid = TAB_Cmd_Ptr_Check_By_Level(cmd_ptr, User_Privilege.Value, level);
                        if (is_cmd_prt_valid)
                        {
                            TAB_Cmd_Add_By_Level(cmd_ptr, level, str_list);
                        }
                    }
                }
            }

            StringBuilder sb = new StringBuilder();
            for (int i = 0; i < str_list.Count; i++)
            {
                sb.Append(' ');
                sb.Append(str_list[i]);
            }

            return sb.ToString();
        }

        protected void String_List_Add_Unique(List<String> s_list, String s)
        {
            bool found = false;
            for (int i = 0; i < s_list.Count; i++)
            {
                if (s_list[i].Equals(s))
                {
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                s_list.Add(s);
            }
        }

        protected void TAB_Cmd_List_Get_With_Flags(
                // in
                Cli_Cmd_Privilege_ID user_privilege, Cli_Modules modules,
                String level, String s_cmd_in, String s_cmd_in_trim, List<Cmd_Token> tokens,
                // out
                Ref_String s_log, Ref_String s_add,
                Ref_Boolean Is_Log, Ref_Boolean Is_Add, Ref_Boolean Is_Space_After)
        {

            List<Cli_TAB_Result> tab_result_list = new List<Cli_TAB_Result>();

            bool is_incomplete_str = false;
            char last_char = '\0';
            bool is_last_char_space = false;
            bool is_last_char_comma = false;
            bool is_last_char_commas = false;
            if (!String.IsNullOrEmpty(s_cmd_in))
            {
                last_char = s_cmd_in[s_cmd_in.Length - 1];
                if (last_char == ' ' || last_char == '\t')
                {
                    is_last_char_space = true;
                }
                else if (last_char == ',')
                {
                    is_last_char_comma = true;
                }
                else if (last_char == '\'' || last_char == '\"')
                {
                    is_last_char_commas = true;
                }
            }

            bool is_enter = false;
            List<String> s_log_list = new List<String>();
            List<String> s_add_list = new List<String>();
            List<String> s_add_list_full = new List<String>();
            for (int module = 0; module < modules.Get_Size(); module++)
            {
                Cli_Module module_ptr = modules.Get(module);

                for (int cmd = 0; cmd < module_ptr.Cmd_Count_Get(); cmd++)
                {
                    Cli_Cmd cmd_ptr = module_ptr.Cmd_Get(cmd);

                    bool is_cmd_prt_valid = TAB_Cmd_Ptr_Check_By_Level(cmd_ptr, User_Privilege.Value, level);
                    if (is_cmd_prt_valid)
                    {
                        if (tokens.Count <= cmd_ptr.Items.Count)
                        {
                            for (int token = 0; token < tokens.Count; token++)
                            {
                                Cmd_Item_Base cmd_item_ptr = cmd_ptr.Items[token];
                                Cmd_Token token_ptr = tokens[token];
                                Cmd_Item_Valid_Result res_parse = cmd_item_ptr.Parse(token_ptr.Text_Get());
                                int token_index_last = tokens.Count - 1;
                                bool is_token_last = (token == token_index_last);
                                int cmd_token_index_last = cmd_ptr.Items.Count - 1;
                                bool is_cmd_token_last = (token == cmd_token_index_last);

                                if (is_token_last && is_cmd_token_last && res_parse == Cmd_Item_Valid_Result.CMD_ITEM_OK)
                                {
                                    is_enter = true;
                                }
                                else if (is_token_last && is_cmd_token_last && res_parse == Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE)
                                {
                                    String_List_Add_Unique(s_add_list, cmd_ptr.Items[token].Text_Get().Substring(token_ptr.Text_Get().Length));
                                    String_List_Add_Unique(s_add_list_full, cmd_ptr.Items[token].Text_Get());

                                }
                                else if (is_token_last && !is_cmd_token_last && res_parse == Cmd_Item_Valid_Result.CMD_ITEM_OK)
                                {
                                    String s_log_new = cmd_ptr.Items[token + 1].Text_Get();
                                    String_List_Add_Unique(s_log_list, s_log_new);
                                    Is_Space_After.Value = true;
                                }
                                else if (is_token_last && !is_cmd_token_last && res_parse == Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE)
                                {
                                    String_List_Add_Unique(s_add_list, cmd_ptr.Items[token].Text_Get().Substring(token_ptr.Text_Get().Length));
                                    String_List_Add_Unique(s_add_list_full, cmd_ptr.Items[token].Text_Get());
                                    Is_Space_After.Value = true;

                                }
                                else if (is_token_last && is_cmd_token_last && res_parse == Cmd_Item_Valid_Result.CMD_ITEM_OK_STR_WITHOUT_COMMAS)
                                {
                                    is_enter = true;
                                }
                                else if (is_token_last && !is_cmd_token_last && res_parse == Cmd_Item_Valid_Result.CMD_ITEM_OK_STR_WITHOUT_COMMAS)
                                {
                                    String s_log_new = cmd_ptr.Items[token + 1].Text_Get();
                                    String_List_Add_Unique(s_log_list, s_log_new);
                                    Is_Space_After.Value = true;

                                }
                                else if (is_cmd_token_last)
                                {
                                    break; // Cmd not match
                                }
                                else if (res_parse == Cmd_Item_Valid_Result.CMD_ITEM_ERROR)
                                {
                                    break; // Cmd not match
                                }

                            }
                        }
                    }

                }

            }
            // s_add_list -> s_add (one variant) / s_log_list (many variants)
            if (s_add_list.Count > 0)
            {
                if (s_add_list.Count == 1)
                {
                    if (!is_enter)
                    {
                        s_add.Value = s_add_list[0];
                    }
                    else
                    {
                        String_List_Add_Unique(s_log_list, s_add_list_full[0]);
                    }
                }
                else
                {
                    String s_common = "";
                    int j = 0;
                    bool is_diff = false;
                    do
                    {
                        char c = '\0';
                        for (int i = 0; i < s_add_list.Count; i++)
                        {
                            if (j < s_add_list[i].Length)
                            {
                                if (i == 0)
                                {
                                    c = s_add_list[i][j];
                                }
                                else if (c != s_add_list[i][j])
                                {
                                    is_diff = true;
                                    break;
                                }
                            }
                            else
                            {
                                if (i > 0)
                                {
                                    is_diff = true;
                                }
                                break;
                            }
                        }
                        if (!is_diff)
                        {
                            s_common += c;
                            j++;
                        }
                    } while (!is_diff);
                    if (!String.IsNullOrEmpty(s_common) && !is_enter)
                    {
                        s_add.Value = s_common;
                        Is_Space_After.Value = false; // "Add" blocks "Is_Space_After"
                    }
                    else
                    {
                        // s_add_list_full -> s_log_list
                        for (int i = 0; i < s_add_list_full.Count; i++)
                        {
                            String_List_Add_Unique(s_log_list, s_add_list_full[i]);
                        }
                        Is_Space_After.Value = false; // "Add Full" blocks "Is_Space_After"
                    }
                }
            }
            // s_log_list -> s_log
            for (int i = 0; i < s_log_list.Count; i++)
            {
                s_log.Value += " " + s_log_list[i];
            }
            // Postprocessing: Add <Enter>
            if (is_enter)
            {
                s_log.Value += " <Enter>";
            }
            // "Add" blocks "Log"
            if (!String.IsNullOrEmpty(s_add.Value))
            {
                s_log.Value = "";
            }
            // Postprocessing: Set flags
            Is_Log.Value = !String.IsNullOrEmpty(s_log.Value);
            Is_Add.Value = !String.IsNullOrEmpty(s_add.Value);
            // Postprocessing: Check for Error
            if (!Is_Log.Value && !Is_Add.Value && !Is_Space_After.Value)
            {
                s_log.Value += " <Error>";
                Is_Log.Value = true;
                s_add.Value = "";
                Is_Add.Value = false;
            }

        }

        protected List<TAB_Cmd> TAB_Cmd_List_Get(
                // in
                Cli_Cmd_Privilege_ID user_privilege, Cli_Modules modules,
                String level, String s_cmd_in, String s_cmd_in_trim, List<Cmd_Token> tokens)
        {
            List<TAB_Cmd> tab_cmd_list = new List<TAB_Cmd>();

            Ref_String s_log = new Ref_String("");
            Ref_String s_add = new Ref_String("");

            Ref_Boolean Is_Log = new Ref_Boolean(false);
            Ref_Boolean Is_Add = new Ref_Boolean(false);
            Ref_Boolean Is_Space_After = new Ref_Boolean(false);

            TAB_Cmd_List_Get_With_Flags(
                    // in
                    user_privilege, modules, level, s_cmd_in, s_cmd_in_trim, tokens,
                    // out
                    s_log, s_add,
                    Is_Log, Is_Add, Is_Space_After);

            if (Is_Log.Value)
            {
                tab_cmd_list.Add(new TAB_Cmd(TAB_Cmd_ID.TAB_CMD_ID_LOG_PRINT, s_log.Value));
            }
            if (Is_Add.Value)
            {
                tab_cmd_list.Add(new TAB_Cmd(TAB_Cmd_ID.TAB_CMD_ID_INPUT_ADD, s_add.Value));
            }
            if (Is_Space_After.Value)
            {
                tab_cmd_list.Add(new TAB_Cmd(TAB_Cmd_ID.TAB_CMD_ID_INPUT_CHECK_SPACE, ""));
            }

            return tab_cmd_list;
        }

        public void Process_Input_Item(Cli_Input_Item input_item, Ref_Boolean is_invitation_print)
        {
            List<TAB_Cmd> tab_cmd_list = new List<TAB_Cmd>();
            String s_trim = input_item.Text_Get().Trim();
            Level_Description level_description = Level_Get();
            String level = level_description.Level;
            String s_help;
            if (s_trim.Length == 0)
            {
                s_help = TAB_Help_Get(level, Modules);
                tab_cmd_list.Add(new TAB_Cmd(TAB_Cmd_ID.TAB_CMD_ID_LOG_PRINT, s_help));
            }
            else
            {
                Cmd_Token_Parser_Result parse_res = Cmd_Token_Parser_Result.CMD_TOKEN_PARSER_ERROR;
                List<Cmd_Token> tokens = Token_Parser.Parse(s_trim, Str_Rem, out parse_res);

                tab_cmd_list = TAB_Cmd_List_Get(User_Privilege.Value, Modules, level, input_item.Text_Get(), s_trim, tokens);

                //for (int i = 0; i < tokens.Count; i++)
                //    delete tokens[i];
                //tokens.clear();
            }

            if (tab_cmd_list.Count > 0)
            {
                bool is_prev_newline = false;
                for (int tab_cmd = 0; tab_cmd < tab_cmd_list.Count; tab_cmd++)
                {
                    TAB_Cmd tab_cmd_ptr = tab_cmd_list[tab_cmd];
                    if (tab_cmd_ptr != null)
                    {
                        switch (tab_cmd_ptr.ID)
                        {
                            case TAB_Cmd_ID.TAB_CMD_ID_LOG_PRINT:
                                Cli_Output.Output_NewLine();
                                Cli_Output.Output_Str(tab_cmd_ptr.Text);
                                Cli_Output.Output_NewLine();
                                is_invitation_print.Value = true;
                                if (Log_Is_Active)
                                {
                                    Log.Add(tab_cmd_ptr.Text);
                                }
                                Cli_Input.Input_Str_Pos_Set(Cli_Input.Input_Str_Get().Length);
                                is_prev_newline = true;
                                break;
                            case TAB_Cmd_ID.TAB_CMD_ID_INPUT_ADD:
                                {
                                    String s_prev = Cli_Input.Input_Str_Get();
                                    int s_pos_prev = Cli_Input.Input_Str_Pos_Get();
                                    if (s_pos_prev == s_prev.Length)
                                    {
                                        Cli_Input.Input_Str_Set(s_prev + tab_cmd_ptr.Text);
                                        Cli_Input.Input_Str_Pos_Set(Cli_Input.Input_Str_Get().Length);
                                        Cli_Output.Output_Str(tab_cmd_ptr.Text);
                                    }
                                    else
                                    {
                                        Cli_Input.Input_Str_Set(s_prev + tab_cmd_ptr.Text);
                                        Cli_Input.Input_End();
                                    }
                                    is_invitation_print.Value = false;
                                    if (Log_Is_Active)
                                    {
                                        Log.Add(tab_cmd_ptr.Text);
                                    }
                                    is_prev_newline = false;
                                }
                                break;
                            case TAB_Cmd_ID.TAB_CMD_ID_INPUT_CHECK_SPACE:
                                {
                                    String s_prev = Cli_Input.Input_Str_Get();
                                    int s_pos_prev = Cli_Input.Input_Str_Pos_Get();
                                    bool is_changed = false;
                                    if (String.IsNullOrEmpty(s_prev) || s_prev[s_prev.Length - 1] != ' ')
                                    {
                                        Cli_Input.Input_Str_Set(s_prev + " ");
                                        is_changed = true;
                                        if (Log_Is_Active)
                                        {
                                            Log.Add(" ");
                                        }
                                    }
                                    if (is_changed && s_pos_prev == s_prev.Length && !is_prev_newline)
                                    {
                                        Cli_Input.Input_Str_Pos_Set(Cli_Input.Input_Str_Get().Length);
                                        Cli_Output.Output_Str(" ");
                                    }
                                    else
                                    {
                                        Cli_Input.Input_End();
                                    }
                                    //is_invitation_print.Value = false;
                                    is_prev_newline = false;
                                }
                                break;
                        }
                    }
                }

                //for (int i = 0; i < tab_cmd_list.Count; i++)
                //    delete tab_cmd_list[i];
                //tab_cmd_list.clear();
            }
            else
            {
                Cli_Output.Output_NewLine();
            }

        }

    }
}
