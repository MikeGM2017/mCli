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

        protected Cli_Input_CS Cli_Input;
        protected Cli_Output_CS Cli_Output;

        protected String Str_Rem;

        protected List<String> Log = new List<String>();
        protected bool Log_Is_Active;

        public Cli_TAB_Processor(Ref_Cli_Cmd_Privilege_ID user_privilege, Cli_Modules modules,
                List<Level_Description> levels, Cmd_Token_Parser parser,
                Cli_Input_CS cli_input, Cli_Output_CS cli_output,
                String str_rem, bool log_is_active)
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

        protected void TAB_On_OK_CAN_CONTINUE(List<Cli_TAB_Result> tab_result_list, Cli_Cmd cmd_ptr)
        {
            Cli_TAB_Result tab_result_ptr = new Cli_TAB_Result();
            tab_result_ptr.cmd_ptr = cmd_ptr;
            tab_result_ptr.Is_Enter = true;
            tab_result_ptr.s_log = ",";
            tab_result_ptr.is_space_after_add = false;
            tab_result_list.Add(tab_result_ptr);
        }

        protected void TAB_On_OK_STR_WITHOUT_COMMAS_not_last_space(List<Cli_TAB_Result> tab_result_list, Cli_Cmd cmd_ptr, Cmd_Item_Base cmd_item_ptr)
        {
            Cli_TAB_Result tab_result_ptr = new Cli_TAB_Result();
            tab_result_ptr.cmd_ptr = cmd_ptr;
            tab_result_ptr.Is_Enter = true;
            //is_incomplete_str = true;
            tab_result_ptr.s_log = cmd_item_ptr.Text_Get();
            tab_result_ptr.is_space_after_add = false;
            tab_result_list.Add(tab_result_ptr);
        }

        protected void TAB_On_OK_not_last_token(List<Cli_TAB_Result> tab_result_list, Cli_Cmd cmd_ptr, int token, Cmd_Item_Base cmd_item_ptr)
        {
            Cli_TAB_Result tab_result_ptr = new Cli_TAB_Result();
            tab_result_ptr.cmd_ptr = cmd_ptr;

            //cmd_tab_ptr.is_space_after_add =
            //        cmd_item_ptr.Is_Space_After_Add(token_ptr.Text_Get());
            if (token + 1 < cmd_ptr.Items.Count - 1)
            {
                tab_result_ptr.is_space_after_add
                        = cmd_item_ptr.Is_Space_After_Add(cmd_ptr.Items[token + 1].Text_Get());
            }
            else
            {
                tab_result_ptr.is_space_after_add = false; // Next token - last token in cmd list
            }

            //if (is_last_space) {
            tab_result_ptr.s_log = cmd_ptr.Items[token + 1].Text_Get();
            //cmd_tab_ptr.s_log_or_add = cmd_ptr.Items[token + 1].Text_Get();
            //} else {
            //    cmd_tab_ptr.s_log = cmd_item_ptr.Text_Get();
            //    cmd_tab_ptr.s_log_or_add = cmd_item_ptr.Text_Get();
            //}

            tab_result_list.Add(tab_result_ptr);
        }

        protected void TAB_On_OK_last_token(List<Cli_TAB_Result> tab_result_list, Cli_Cmd cmd_ptr, Cmd_Item_Base cmd_item_ptr, Cmd_Token token_ptr)
        {
            Cli_TAB_Result tab_result_ptr = new Cli_TAB_Result();
            tab_result_ptr.cmd_ptr = cmd_ptr;
            tab_result_ptr.Is_Enter = true;
            ////cmd_tab_ptr.s_log = cmd_item_ptr.Text_Get();

            //if (cmd_item_ptr.Type_Get() == "Str") {
            //    cmd_tab_ptr.s_log = cmd_item_ptr.Text_Get();
            //}
            //cmd_tab_ptr.s_log_or_add = cmd_item_ptr.Text_Get();
            tab_result_ptr.is_space_after_add
                    = cmd_item_ptr.Is_Space_After_Add(token_ptr.Text_Get());
            //cmd_tab_ptr.is_space_after_add = false;
            tab_result_list.Add(tab_result_ptr);
        }

        protected void TAB_On_INCOMPLETE_STR(List<Cli_TAB_Result> tab_result_list, Cli_Cmd cmd_ptr, Cmd_Item_Base cmd_item_ptr)
        {
            Cli_TAB_Result tab_result_ptr = new Cli_TAB_Result();
            tab_result_ptr.cmd_ptr = cmd_ptr;

            tab_result_ptr.s_log = cmd_item_ptr.Text_Get() + " - Incomplete";
            tab_result_ptr.is_space_after_add = false;
            tab_result_list.Add(tab_result_ptr);
        }

        protected void TAB_On_incomplete_tail_list(List<Cli_TAB_Result> tab_result_list, Cli_Cmd cmd_ptr, int token, Cmd_Item_Base cmd_item_ptr, Cmd_Token token_ptr, String token_str, List<String> s_incomplete_tail_list)
        {
            Cli_TAB_Result tab_result_ptr = new Cli_TAB_Result();
            tab_result_ptr.cmd_ptr = cmd_ptr;
            tab_result_ptr.s_add_list = s_incomplete_tail_list;

            String s_beg = "";
            if (token_str.Length > 0)
            {
                int pos = token_str.LastIndexOf(','); // @Magic: for Cmd_Item_Word_List
                if (pos < 0)
                {
                    s_beg = token_str;
                }
                else
                {
                    s_beg = token_str.Substring(pos + 1); // @Magic: for Cmd_Item_Word_List
                }
            }

            for (int s_add_index = 0; s_add_index < tab_result_ptr.s_add_list.Count; s_add_index++)
            {
                String s_add_item = tab_result_ptr.s_add_list[s_add_index];
                tab_result_ptr.s_full_list.Add(s_beg + s_add_item);
            }

            tab_result_ptr.is_space_after_add
                    = cmd_item_ptr.Is_Space_After_Add(token_ptr.Text_Get());

            if (token == cmd_ptr.Items.Count - 1)
            { // Last token in cmd list
              //cmd_tab_ptr.Is_Enter = true;
                tab_result_ptr.is_space_after_add = false;
            }

            tab_result_list.Add(tab_result_ptr);
        }

        protected void TAB_On_incomplete_tail_list_empty(List<Cli_TAB_Result> tab_result_list, bool is_last_char_space, bool is_last_char_comma, bool is_last_char_commas, Cli_Cmd cmd_ptr, Cmd_Item_Base cmd_item_ptr, Cmd_Token token_ptr, String token_str, String cmd_item_str)
        {
            Cli_TAB_Result tab_result_ptr = new Cli_TAB_Result();
            tab_result_ptr.cmd_ptr = cmd_ptr;
            char last_token_char = ((token_str.Length == 0) ? '\0' : token_str[token_str.Length - 1]);
            if (!is_last_char_space || last_token_char == ' ' || last_token_char == '\t')
            {
                tab_result_ptr.s_log = cmd_item_str + " - Incomplete";
            }
            if (!is_last_char_comma && !is_last_char_commas)
            {
                tab_result_ptr.is_space_after_add
                        = cmd_item_ptr.Is_Space_After_Add(token_ptr.Text_Get());
            }
            else
            {
                tab_result_ptr.is_space_after_add = false;
            }
            tab_result_list.Add(tab_result_ptr);
        }

        protected void TAB_On_INCOMPLETE(List<Cmd_Token> tokens, List<Cli_TAB_Result> tab_result_list,
                bool is_last_char_space, bool is_last_char_comma, bool is_last_char_commas,
                Cli_Cmd cmd_ptr, int token, Cmd_Item_Base cmd_item_ptr, Cmd_Token token_ptr)
        {
            String token_str = tokens[token].Text_Get();
            String cmd_item_str = cmd_item_ptr.Text_Get();
            List<String> s_incomplete_tail_list = new List<String>();
            if (!is_last_char_space)
            {
                s_incomplete_tail_list = cmd_item_ptr.Incomplete_Tail_List_Get(token_str);
            }
            if (s_incomplete_tail_list.Count > 0)
            {
                TAB_On_incomplete_tail_list(tab_result_list, cmd_ptr, token, cmd_item_ptr, token_ptr, token_str, s_incomplete_tail_list);
            }
            else if (s_incomplete_tail_list.Count == 0)
            {
                TAB_On_incomplete_tail_list_empty(tab_result_list, is_last_char_space,
                        is_last_char_comma, is_last_char_commas,
                        cmd_ptr, cmd_item_ptr, token_ptr, token_str, cmd_item_str);
            }
        }

        protected void TAB_Result_List_Parse_To_Flags(List<Cmd_Token> tokens, Ref_String s_log, Ref_String s_add,
                Ref_Boolean Is_Log, Ref_Boolean Is_Add, Ref_Boolean Is_Space_After,
                List<Cli_TAB_Result> tab_result_list,
                bool is_incomplete_str, bool is_last_char_space, bool is_last_char_comma, bool is_last_char_commas)
        {
            {

                bool Is_Enter = false;
                List<String> s_add_set = new List<String>();
                List<String> s_log_set = new List<String>();
                String s_add_1 = "";
                String s_log_1 = "";
                bool is_space_after_add_1 = false;
                bool is_space_after_log_1 = false;
                List<String> s_add_vector = new List<String>();
                List<String> s_log_vector = new List<String>();
                String s_add_full_1 = "";

                for (int i = 0; i < tab_result_list.Count; i++)
                {
                    Cli_TAB_Result tab_result_ptr = tab_result_list[i];
                    if (tab_result_ptr.Is_Enter)
                    {
                        Is_Enter = true;
                    }
                }

                for (int i = 0; i < tab_result_list.Count; i++)
                {
                    Cli_TAB_Result tab_result_ptr = tab_result_list[i];
                    if (tab_result_ptr.s_add_list.Count > 0)
                    {
                        for (int s_add_index = 0; s_add_index < tab_result_ptr.s_add_list.Count; s_add_index++)
                        {
                            String s_add_item = tab_result_ptr.s_add_list[s_add_index];
                            if (!s_add_set.Contains(s_add_item))
                            {
                                s_add_set.Add(s_add_item);
                                s_add_1 = s_add_item;
                                s_add_vector.Add(tab_result_ptr.s_full_list[s_add_index]);
                                s_add_full_1 = tab_result_ptr.s_full_list[s_add_index];
                            }
                        }
                    }
                    if (tab_result_ptr.is_space_after_add)
                    {
                        is_space_after_add_1 = true;
                    }
                }

                for (int i = 0; i < tab_result_list.Count; i++)
                {
                    Cli_TAB_Result tab_result_ptr = tab_result_list[i];
                    if (tab_result_ptr.s_log.Length != 0)
                    {
                        if (!s_log_set.Contains(tab_result_ptr.s_log))
                        {
                            s_log_set.Add(tab_result_ptr.s_log);
                            s_log_1 = tab_result_ptr.s_log;
                            s_log_vector.Add(tab_result_ptr.s_log);
                        }
                    }
                    if (tab_result_ptr.is_space_after_add)
                    {
                        is_space_after_log_1 = true;
                    }
                }

                Is_Log.Value = false;
                s_log.Value = "";
                Is_Add.Value = false;
                s_add.Value = "";
                Is_Space_After.Value = false;

                if (s_add_vector.Count == 0 && s_log_vector.Count == 0)
                {
                    s_log.Value = (Is_Enter ? " <Enter>" : " <Error>");
                }
                else if (!Is_Enter && s_add_vector.Count == 1 && s_log_vector.Count == 0)
                {
                    s_add.Value = s_add_1;
                    if (is_space_after_add_1)
                    {
                        Is_Space_After.Value = true;
                    }
                    else
                    {
                        Is_Space_After.Value = false;
                    }
                }
                else if (!Is_Enter && s_add_vector.Count == 0 && s_log_vector.Count == 1)
                {
                    if (s_log_1.Length != 0 && s_log_1[0] != '<' && s_log_1[0] != '\"' && s_log_1[0] != '\'' && s_log_1[0] != '[')
                    {
                        if (!is_last_char_space)
                        {
                            s_add.Value = " " + s_log_1;
                        }
                        else
                        {
                            s_add.Value = s_log_1;
                        }

                        if (is_space_after_log_1)
                        {
                            Is_Space_After.Value = true;
                        }
                        else
                        {
                            Is_Space_After.Value = false;
                        }
                    }
                    else
                    {
                        s_log.Value = " " + s_log_1;
                        if (!is_last_char_comma && !is_last_char_commas)
                        {
                            Is_Space_After.Value = true;
                        }
                    }
                }
                else if (Is_Enter && s_add_vector.Count == 0 && s_log_vector.Count == 1)
                {
                    s_log.Value = " " + s_log_1 + " <Enter>";
                    if (is_space_after_log_1)
                    {
                        Is_Space_After.Value = true;
                    }
                    else
                    {
                        Is_Space_After.Value = false;
                    }
                }
                else if (!Is_Enter && s_add_vector.Count == 1 && s_log_vector.Count == 1)
                {
                    s_log.Value = " " + s_log_1 + " " + s_add_full_1;
                }
                else if (Is_Enter && s_add_vector.Count == 1 && s_log_vector.Count == 1)
                {
                    s_add.Value = s_add_1;
                    Is_Space_After.Value = true;
                }
                else if (s_add_vector.Count == 0 && s_log_vector.Count >= 2)
                {
                    s_log.Value = "";
                    for (int i = 0; i < s_log_vector.Count; i++)
                    {
                        s_log.Value += " " + s_log_vector[i];
                    }
                    if (Is_Enter)
                    {
                        s_log.Value += " <Enter>";
                    }
                    Is_Space_After.Value = true;
                }
                else if (!Is_Enter && s_add_vector.Count >= 2 && s_log_vector.Count == 0)
                {
                    {
                        // Add minimal common part or log full variants
                        int len_min = s_add_vector[0].Length;
                        for (int i = 0; i < s_add_vector.Count; i++)
                        {
                            if (len_min > s_add_vector[i].Length)
                            {
                                len_min = s_add_vector[i].Length;
                            }
                        }
                        String s_common = "";
                        for (int pos = 0; pos < len_min; pos++)
                        {
                            char c = s_add_vector[0][pos];
                            bool is_diff = false;
                            for (int i = 0; i < s_add_vector.Count; i++)
                            {
                                if (s_add_vector[i][pos] != c)
                                {
                                    is_diff = true;
                                    break;
                                }
                            }
                            if (!is_diff)
                            {
                                s_common += c;
                            }
                            else
                            {
                                break;
                            }
                        }
                        String s_last_token1 = tokens[tokens.Count - 1].Text_Get();
                        String s_last_token;
                        int comma_pos = s_last_token1.LastIndexOf(','); // @Magic: for Cmd_Item_Word_List
                        if (comma_pos < 0)
                        {
                            s_last_token = s_last_token1;
                        }
                        else
                        {
                            s_last_token = s_last_token1.Substring(comma_pos + 1); // @Magic: for Cmd_Item_Word_List
                        }
                        String s_common_part = "";
                        if (s_common.Length != 0)
                        {
                            s_common_part = s_common.Substring(s_last_token.Length);
                        }
                        if (s_common_part.Length != 0)
                        {
                            s_add.Value = s_common_part;
                        }
                        else
                        {
                            s_log.Value = "";
                            for (int i = 0; i < s_add_vector.Count; i++)
                            {
                                s_log.Value += " ";
                                s_log.Value += s_add_vector[i];
                            }
                        }
                    }
                }
                else if (s_add_vector.Count >= 2 || s_log_vector.Count >= 2)
                {
                    s_log.Value = "";
                    for (int i = 0; i < s_log_vector.Count; i++)
                    {
                        s_log.Value += " ";
                        s_log.Value += s_log_vector[i];
                    }
                    for (int i = 0; i < s_add_vector.Count; i++)
                    {
                        s_log.Value += " ";
                        s_log.Value += s_add_vector[i];
                    }
                    if (Is_Enter)
                    {
                        s_log.Value += " <Enter>";
                    }
                }
                else
                {
                    s_log.Value = " <Error>";
                }

                Is_Add.Value = (s_add.Value.Length != 0);
                Is_Log.Value = (s_log.Value.Length != 0);

                if (is_incomplete_str)
                {
                    Is_Space_After.Value = false;
                }
                if (is_last_char_space)
                {
                    Is_Space_After.Value = false;
                }

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
            if (s_cmd_in.Length != 0)
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

            // <editor-fold defaultstate="collapsed" desc="TAB: last cmd item - full/partial . cmd_tab_list">
            for (int module = 0; module < modules.Get_Size(); module++)
            {
                Cli_Module module_ptr = modules.Get(module);
                if (module_ptr != null)
                {
                    for (int cmd = 0; cmd < module_ptr.Cmd_Count_Get(); cmd++)
                    {
                        Cli_Cmd cmd_ptr = module_ptr.Cmd_Get(cmd);

                        bool debug_found = false;
                        if (cmd_ptr.Text_Get() == "help module \"<module_name>\" verbose")
                        {
                            debug_found = true;
                        }

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

                                    if (res_parse == Cmd_Item_Valid_Result.CMD_ITEM_OK_CAN_CONTINUE && is_last_char_space)
                                    {
                                        res_parse = Cmd_Item_Valid_Result.CMD_ITEM_OK;
                                    }
                                    if (res_parse == Cmd_Item_Valid_Result.CMD_ITEM_OK_CAN_CONTINUE && (token < tokens.Count - 1))
                                    {
                                        res_parse = Cmd_Item_Valid_Result.CMD_ITEM_OK;
                                    }

                                    if (res_parse == Cmd_Item_Valid_Result.CMD_ITEM_OK_CAN_CONTINUE)
                                    {
                                        TAB_On_OK_CAN_CONTINUE(tab_result_list, cmd_ptr);
                                    }
                                    else if (token < tokens.Count - 1)
                                    { // Not last token in token list, but not OK . not valid
                                        if (res_parse != Cmd_Item_Valid_Result.CMD_ITEM_OK
                                                && res_parse != Cmd_Item_Valid_Result.CMD_ITEM_OK_CAN_CONTINUE
                                                && res_parse != Cmd_Item_Valid_Result.CMD_ITEM_OK_STR_WITHOUT_COMMAS)
                                        {
                                            break;
                                        }
                                    }
                                    else if (token == tokens.Count - 1)
                                    { // Last token in token list
                                        if (res_parse == Cmd_Item_Valid_Result.CMD_ITEM_OK || res_parse == Cmd_Item_Valid_Result.CMD_ITEM_OK_STR_WITHOUT_COMMAS)
                                        {
                                            if (res_parse == Cmd_Item_Valid_Result.CMD_ITEM_OK_STR_WITHOUT_COMMAS && !is_last_char_space)
                                            {
                                                TAB_On_OK_STR_WITHOUT_COMMAS_not_last_space(tab_result_list, cmd_ptr, cmd_item_ptr);
                                            }
                                            else if (token < cmd_ptr.Items.Count - 1)
                                            { // Not last token in cmd list
                                                TAB_On_OK_not_last_token(tab_result_list, cmd_ptr, token, cmd_item_ptr);
                                            }
                                            else if (token == cmd_ptr.Items.Count - 1)
                                            { // Last token in cmd list
                                                TAB_On_OK_last_token(tab_result_list, cmd_ptr, cmd_item_ptr, token_ptr);
                                            }
                                        }
                                        else if (res_parse == Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE || res_parse == Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE_STR)
                                        {
                                            if (res_parse == Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE_STR)
                                            {
                                                TAB_On_INCOMPLETE_STR(tab_result_list, cmd_ptr, cmd_item_ptr);
                                                is_incomplete_str = true;
                                            }
                                            else
                                            {
                                                TAB_On_INCOMPLETE(tokens, tab_result_list, is_last_char_space, is_last_char_comma, is_last_char_commas, cmd_ptr, token, cmd_item_ptr, token_ptr);
                                            }
                                        }
                                        else
                                        {
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            // </editor-fold>

            TAB_Result_List_Parse_To_Flags(tokens, s_log, s_add, Is_Log, Is_Add, Is_Space_After,
                    tab_result_list, is_incomplete_str, is_last_char_space, is_last_char_comma, is_last_char_commas);

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
                                    if (s_prev.Length == 0 || s_prev[s_prev.Length - 1] != ' ')
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
                                    //is_invitation_print.Value = false; //@Warning
                                    is_prev_newline = false;
                                }
                                break;
                        }
                    }
                }

            }
            else
            {
                Cli_Output.Output_NewLine();
            }

        }

    }

}
