/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cli_core_javafx_test;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

/**
 *
 * @author mike
 */
public class Cli_TAB_Processor {

    protected String Type;
    protected String Version;

    protected Ref_Cli_Cmd_Privilege_ID User_Privilege;
    protected Cli_Modules Modules;
    protected List<Level_Description> Levels;
    protected Cmd_Token_Parser Token_Parser;

    protected Cli_Input_JavaFX Cli_Input;
    protected Cli_Output_JavaFX Cli_Output;

    protected String Str_Rem;

    protected List<String> Log;
    protected boolean Log_Is_Active;

    public Cli_TAB_Processor(Ref_Cli_Cmd_Privilege_ID user_privilege, Cli_Modules modules,
            List<Level_Description> levels, Cmd_Token_Parser parser,
            Cli_Input_JavaFX cli_input, Cli_Output_JavaFX cli_output,
            String str_rem, boolean log_is_active) {

        Type = "Cli_TAB_Processor";
        Version = "0.02";

        User_Privilege = user_privilege;
        Modules = modules;
        Levels = levels;
        Token_Parser = parser;
        Cli_Input = cli_input;
        Cli_Output = cli_output;
        Str_Rem = str_rem;
        Log_Is_Active = log_is_active;
    }

    protected Level_Description Level_Get() {
        if (Levels.size() > 0) {
            return Levels.get(Levels.size() - 1);
        }
        Level_Description level_top = new Level_Description();
        return level_top;
    }

    public int Log_Size_Get() {
        return Log.size();
    }

    public String Log_Item_Get(int index) {
        if (index >= 0 && index < Log.size()) {
            return Log.get(index);
        }
        return "";
    }

    protected boolean TAB_Cmd_Ptr_Check_By_Level(Cli_Cmd cmd_ptr, Cli_Cmd_Privilege_ID user_privilege, String level) {
        if (cmd_ptr != null && user_privilege.ordinal() <= cmd_ptr.Privilege_Get()) {
            if (cmd_ptr.Is_Global_Get()) {
                return true;
            }
            if (cmd_ptr.Level_Get().equals(level)) {
                return true;
            }
        }
        return false;
    }

    protected void TAB_Cmd_Add_By_Level(Cli_Cmd cmd_ptr, String level, List<String> str_list) {
        boolean is_cmd_prt_valid = TAB_Cmd_Ptr_Check_By_Level(cmd_ptr, User_Privilege.Value, level);
        if (is_cmd_prt_valid) {
            String s = cmd_ptr.Items.get(0).Text_Get();
            //if (find(str_list.begin(), str_list.end(), s) == str_list.end()) {
            //    str_list.insert(str_list.end(), s);
            //}
            if (!str_list.contains(s)) {
                str_list.add(s);
            }
        }
    }

    protected String TAB_Help_Get(String level, Cli_Modules modules) {
        List<String> str_list = new ArrayList<>();

        for (int module = 0; module < modules.Get_Size(); module++) {
            Cli_Module module_ptr = modules.Get(module);
            if (module_ptr != null) {
                for (int cmd = 0; cmd < module_ptr.Cmd_Count_Get(); cmd++) {
                    Cli_Cmd cmd_ptr = module_ptr.Cmd_Get(cmd);
                    boolean is_cmd_prt_valid = TAB_Cmd_Ptr_Check_By_Level(cmd_ptr, User_Privilege.Value, level);
                    if (is_cmd_prt_valid) {
                        TAB_Cmd_Add_By_Level(cmd_ptr, level, str_list);
                    }
                }
            }
        }

        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < str_list.size(); i++) {
            sb.append(' ');
            sb.append(str_list.get(i));
        }

        return sb.toString();
    }

    protected void TAB_On_OK_CAN_CONTINUE(List<Cli_TAB_Result> tab_result_list, Cli_Cmd cmd_ptr) {
        Cli_TAB_Result tab_result_ptr = new Cli_TAB_Result();
        tab_result_ptr.cmd_ptr = cmd_ptr;
        tab_result_ptr.Is_Enter = true;
        tab_result_ptr.s_log = ",";
        tab_result_ptr.is_space_after_add = false;
        tab_result_list.add(tab_result_ptr);
    }

    protected void TAB_On_OK_STR_WITHOUT_COMMAS_not_last_space(List<Cli_TAB_Result> tab_result_list, Cli_Cmd cmd_ptr, Cmd_Item_Base cmd_item_ptr) {
        Cli_TAB_Result tab_result_ptr = new Cli_TAB_Result();
        tab_result_ptr.cmd_ptr = cmd_ptr;
        tab_result_ptr.Is_Enter = true;
        //is_incomplete_str = true;
        tab_result_ptr.s_log = cmd_item_ptr.Text_Get();
        tab_result_ptr.is_space_after_add = false;
        tab_result_list.add(tab_result_ptr);
    }

    protected void TAB_On_OK_not_last_token(List<Cli_TAB_Result> tab_result_list, Cli_Cmd cmd_ptr, int token, Cmd_Item_Base cmd_item_ptr) {
        Cli_TAB_Result tab_result_ptr = new Cli_TAB_Result();
        tab_result_ptr.cmd_ptr = cmd_ptr;

        //cmd_tab_ptr.is_space_after_add =
        //        cmd_item_ptr.Is_Space_After_Add(token_ptr.Text_Get());
        if (token + 1 < cmd_ptr.Items.size() - 1) {
            tab_result_ptr.is_space_after_add
                    = cmd_item_ptr.Is_Space_After_Add(cmd_ptr.Items.get(token + 1).Text_Get());
        } else {
            tab_result_ptr.is_space_after_add = false; // Next token - last token in cmd list
        }

        //if (is_last_space) {
        tab_result_ptr.s_log = cmd_ptr.Items.get(token + 1).Text_Get();
        //cmd_tab_ptr.s_log_or_add = cmd_ptr.Items[token + 1].Text_Get();
        //} else {
        //    cmd_tab_ptr.s_log = cmd_item_ptr.Text_Get();
        //    cmd_tab_ptr.s_log_or_add = cmd_item_ptr.Text_Get();
        //}

        tab_result_list.add(tab_result_ptr);
    }

    protected void TAB_On_OK_last_token(List<Cli_TAB_Result> tab_result_list, Cli_Cmd cmd_ptr, Cmd_Item_Base cmd_item_ptr, Cmd_Token token_ptr) {
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
        tab_result_list.add(tab_result_ptr);
    }

    protected void TAB_On_INCOMPLETE_STR(List<Cli_TAB_Result> tab_result_list, Cli_Cmd cmd_ptr, Cmd_Item_Base cmd_item_ptr) {
        Cli_TAB_Result tab_result_ptr = new Cli_TAB_Result();
        tab_result_ptr.cmd_ptr = cmd_ptr;

        tab_result_ptr.s_log = cmd_item_ptr.Text_Get() + " - Incomplete";
        tab_result_ptr.is_space_after_add = false;
        tab_result_list.add(tab_result_ptr);
    }

    protected void TAB_On_incomplete_tail_list(List<Cli_TAB_Result> tab_result_list, Cli_Cmd cmd_ptr, int token, Cmd_Item_Base cmd_item_ptr, Cmd_Token token_ptr, String token_str, List<String> s_incomplete_tail_list) {
        Cli_TAB_Result tab_result_ptr = new Cli_TAB_Result();
        tab_result_ptr.cmd_ptr = cmd_ptr;
        tab_result_ptr.s_add_list = s_incomplete_tail_list;

        String s_beg = "";
        if (!token_str.isEmpty()) {
            int pos = token_str.lastIndexOf(','); // @Magic: for Cmd_Item_Word_List
            if (pos < 0) {
                s_beg = token_str;
            } else {
                s_beg = token_str.substring(pos + 1); // @Magic: for Cmd_Item_Word_List
            }
        }

        for (int s_add_index = 0; s_add_index < tab_result_ptr.s_add_list.size(); s_add_index++) {
            String s_add_item = tab_result_ptr.s_add_list.get(s_add_index);
            tab_result_ptr.s_full_list.add(s_beg + s_add_item);
        }

        tab_result_ptr.is_space_after_add
                = cmd_item_ptr.Is_Space_After_Add(token_ptr.Text_Get());

        if (token == cmd_ptr.Items.size() - 1) { // Last token in cmd list
            //cmd_tab_ptr.Is_Enter = true;
            tab_result_ptr.is_space_after_add = false;
        }

        tab_result_list.add(tab_result_ptr);
    }

    protected void TAB_On_incomplete_tail_list_empty(List<Cli_TAB_Result> tab_result_list, boolean is_last_char_space, boolean is_last_char_comma, boolean is_last_char_commas, Cli_Cmd cmd_ptr, Cmd_Item_Base cmd_item_ptr, Cmd_Token token_ptr, String token_str, String cmd_item_str) {
        Cli_TAB_Result tab_result_ptr = new Cli_TAB_Result();
        tab_result_ptr.cmd_ptr = cmd_ptr;
        char last_token_char = (token_str.isEmpty() ? 0 : token_str.charAt(token_str.length() - 1));
        if (!is_last_char_space || last_token_char == ' ' || last_token_char == '\t') {
            tab_result_ptr.s_log = cmd_item_str + " - Incomplete";
        }
        if (!is_last_char_comma && !is_last_char_commas) {
            tab_result_ptr.is_space_after_add
                    = cmd_item_ptr.Is_Space_After_Add(token_ptr.Text_Get());
        } else {
            tab_result_ptr.is_space_after_add = false;
        }
        tab_result_list.add(tab_result_ptr);
    }

    protected void TAB_On_INCOMPLETE(List<Cmd_Token> tokens, List<Cli_TAB_Result> tab_result_list,
            boolean is_last_char_space, boolean is_last_char_comma, boolean is_last_char_commas,
            Cli_Cmd cmd_ptr, int token, Cmd_Item_Base cmd_item_ptr, Cmd_Token token_ptr) {
        String token_str = tokens.get(token).Text_Get();
        String cmd_item_str = cmd_item_ptr.Text_Get();
        List<String> s_incomplete_tail_list = new ArrayList<>();
        if (!is_last_char_space) {
            s_incomplete_tail_list = cmd_item_ptr.Incomplete_Tail_List_Get(token_str);
        }
        if (!s_incomplete_tail_list.isEmpty()) {
            TAB_On_incomplete_tail_list(tab_result_list, cmd_ptr, token, cmd_item_ptr, token_ptr, token_str, s_incomplete_tail_list);
        } else if (s_incomplete_tail_list.isEmpty()) {
            TAB_On_incomplete_tail_list_empty(tab_result_list, is_last_char_space,
                    is_last_char_comma, is_last_char_commas,
                    cmd_ptr, cmd_item_ptr, token_ptr, token_str, cmd_item_str);
        }
    }

    protected void TAB_Result_List_Parse_To_Flags(List<Cmd_Token> tokens, Ref_String s_log, Ref_String s_add,
            Ref_Boolean Is_Log, Ref_Boolean Is_Add, Ref_Boolean Is_Space_After,
            List<Cli_TAB_Result> tab_result_list,
            boolean is_incomplete_str, boolean is_last_char_space, boolean is_last_char_comma, boolean is_last_char_commas) {
        {

            boolean Is_Enter = false;
            Set<String> s_add_set = new HashSet<>();
            Set<String> s_log_set = new HashSet<>();
            String s_add_1 = "";
            String s_log_1 = "";
            boolean is_space_after_add_1 = false;
            boolean is_space_after_log_1 = false;
            List<String> s_add_vector = new ArrayList<>();
            List<String> s_log_vector = new ArrayList<>();
            String s_add_full_1 = "";

            for (int i = 0; i < tab_result_list.size(); i++) {
                Cli_TAB_Result tab_result_ptr = tab_result_list.get(i);
                if (tab_result_ptr.Is_Enter) {
                    Is_Enter = true;
                }
            }

            for (int i = 0; i < tab_result_list.size(); i++) {
                Cli_TAB_Result tab_result_ptr = tab_result_list.get(i);
                if (!tab_result_ptr.s_add_list.isEmpty()) {
                    for (int s_add_index = 0; s_add_index < tab_result_ptr.s_add_list.size(); s_add_index++) {
                        String s_add_item = tab_result_ptr.s_add_list.get(s_add_index);
                        if (!s_add_set.contains(s_add_item)) {
                            s_add_set.add(s_add_item);
                            s_add_1 = s_add_item;
                            s_add_vector.add(tab_result_ptr.s_full_list.get(s_add_index));
                            s_add_full_1 = tab_result_ptr.s_full_list.get(s_add_index);
                        }
                    }
                }
                if (tab_result_ptr.is_space_after_add) {
                    is_space_after_add_1 = true;
                }
            }

            for (int i = 0; i < tab_result_list.size(); i++) {
                Cli_TAB_Result tab_result_ptr = tab_result_list.get(i);
                if (!tab_result_ptr.s_log.isEmpty()) {
                    if (!s_log_set.contains(tab_result_ptr.s_log)) {
                        s_log_set.add(tab_result_ptr.s_log);
                        s_log_1 = tab_result_ptr.s_log;
                        s_log_vector.add(tab_result_ptr.s_log);
                    }
                }
                if (tab_result_ptr.is_space_after_add) {
                    is_space_after_log_1 = true;
                }
            }

            Is_Log.Value = false;
            s_log.Value = "";
            Is_Add.Value = false;
            s_add.Value = "";
            Is_Space_After.Value = false;

            if (s_add_vector.size() == 0 && s_log_vector.size() == 0) {
                s_log.Value = (Is_Enter ? " <Enter>" : " <Error>");
            } else if (!Is_Enter && s_add_vector.size() == 1 && s_log_vector.size() == 0) {
                s_add.Value = s_add_1;
                if (is_space_after_add_1) {
                    Is_Space_After.Value = true;
                } else {
                    Is_Space_After.Value = false;
                }
            } else if (!Is_Enter && s_add_vector.size() == 0 && s_log_vector.size() == 1) {
                if (!s_log_1.isEmpty() && s_log_1.charAt(0) != '<' && s_log_1.charAt(0) != '\"' && s_log_1.charAt(0) != '\'' && s_log_1.charAt(0) != '[') {
                    if (!is_last_char_space) {
                        s_add.Value = " " + s_log_1;
                    } else {
                        s_add.Value = s_log_1;
                    }

                    if (is_space_after_log_1) {
                        Is_Space_After.Value = true;
                    } else {
                        Is_Space_After.Value = false;
                    }
                } else {
                    s_log.Value = " " + s_log_1;
                    if (!is_last_char_comma && !is_last_char_commas) {
                        Is_Space_After.Value = true;
                    }
                }
            } else if (Is_Enter && s_add_vector.size() == 0 && s_log_vector.size() == 1) {
                s_log.Value = " " + s_log_1 + " <Enter>";
                if (is_space_after_log_1) {
                    Is_Space_After.Value = true;
                } else {
                    Is_Space_After.Value = false;
                }
            } else if (!Is_Enter && s_add_vector.size() == 1 && s_log_vector.size() == 1) {
                s_log.Value = " " + s_log_1 + " " + s_add_full_1;
            } else if (Is_Enter && s_add_vector.size() == 1 && s_log_vector.size() == 1) {
                s_add.Value = s_add_1;
                Is_Space_After.Value = true;
            } else if (s_add_vector.size() == 0 && s_log_vector.size() >= 2) {
                s_log.Value = "";
                for (int i = 0; i < s_log_vector.size(); i++) {
                    s_log.Value += " " + s_log_vector.get(i);
                }
                if (Is_Enter) {
                    s_log.Value += " <Enter>";
                }
                Is_Space_After.Value = true;
            } else if (!Is_Enter && s_add_vector.size() >= 2 && s_log_vector.size() == 0) {
                {
                    // Add minimal common part or log full variants
                    int len_min = s_add_vector.get(0).length();
                    for (int i = 0; i < s_add_vector.size(); i++) {
                        if (len_min > s_add_vector.get(i).length()) {
                            len_min = s_add_vector.get(i).length();
                        }
                    }
                    String s_common = "";
                    for (int pos = 0; pos < len_min; pos++) {
                        char c = s_add_vector.get(0).charAt(pos);
                        boolean is_diff = false;
                        for (int i = 0; i < s_add_vector.size(); i++) {
                            if (s_add_vector.get(i).charAt(pos) != c) {
                                is_diff = true;
                                break;
                            }
                        }
                        if (!is_diff) {
                            s_common += c;
                        } else {
                            break;
                        }
                    }
                    String s_last_token1 = tokens.get(tokens.size() - 1).Text_Get();
                    String s_last_token;
                    int pos = s_last_token1.lastIndexOf(','); // @Magic: for Cmd_Item_Word_List
                    if (pos < 0) {
                        s_last_token = s_last_token1;
                    } else {
                        s_last_token = s_last_token1.substring(pos + 1); // @Magic: for Cmd_Item_Word_List
                    }
                    String s_common_part = "";
                    if (!s_common.isEmpty()) {
                        s_common_part = s_common.substring(s_last_token.length());
                    }
                    if (!s_common_part.isEmpty()) {
                        s_add.Value = s_common_part;
                    } else {
                        s_log.Value = "";
                        for (int i = 0; i < s_add_vector.size(); i++) {
                            s_log.Value += " ";
                            s_log.Value += s_add_vector.get(i);
                        }
                    }
                }
            } else if (s_add_vector.size() >= 2 || s_log_vector.size() >= 2) {
                s_log.Value = "";
                for (int i = 0; i < s_log_vector.size(); i++) {
                    s_log.Value += " ";
                    s_log.Value += s_log_vector.get(i);
                }
                for (int i = 0; i < s_add_vector.size(); i++) {
                    s_log.Value += " ";
                    s_log.Value += s_add_vector.get(i);
                }
                if (Is_Enter) {
                    s_log.Value += " <Enter>";
                }
            } else {
                s_log.Value = " <Error>";
            }

            Is_Add.Value = !s_add.Value.isEmpty();
            Is_Log.Value = !s_log.Value.isEmpty();

            if (is_incomplete_str) {
                Is_Space_After.Value = false;
            }
            if (is_last_char_space) {
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
            Ref_Boolean Is_Log, Ref_Boolean Is_Add, Ref_Boolean Is_Space_After) {

        List<Cli_TAB_Result> tab_result_list = new ArrayList<>();
        boolean is_incomplete_str = false;
        char last_char = 0;
        boolean is_last_char_space = false;
        boolean is_last_char_comma = false;
        boolean is_last_char_commas = false;
        if (!s_cmd_in.isEmpty()) {
            last_char = s_cmd_in.charAt(s_cmd_in.length() - 1);
            if (last_char == ' ' || last_char == '\t') {
                is_last_char_space = true;
            } else if (last_char == ',') {
                is_last_char_comma = true;
            } else if (last_char == '\'' || last_char == '\"') {
                is_last_char_commas = true;
            }
        }

        // <editor-fold defaultstate="collapsed" desc="TAB: last cmd item - full/partial . cmd_tab_list">
        for (int module = 0; module < modules.Get_Size(); module++) {
            Cli_Module module_ptr = modules.Get(module);
            if (module_ptr != null) {
                for (int cmd = 0; cmd < module_ptr.Cmd_Count_Get(); cmd++) {
                    Cli_Cmd cmd_ptr = module_ptr.Cmd_Get(cmd);
                    boolean is_cmd_prt_valid = TAB_Cmd_Ptr_Check_By_Level(cmd_ptr, User_Privilege.Value, level);
                    if (is_cmd_prt_valid) {
                        if (tokens.size() <= cmd_ptr.Items.size()) {
                            for (int token = 0; token < tokens.size(); token++) {
                                Cmd_Item_Base cmd_item_ptr = cmd_ptr.Items.get(token);
                                Cmd_Token token_ptr = tokens.get(token);
                                Cmd_Item_Valid_Result res_parse = cmd_item_ptr.Parse(token_ptr.Text_Get());

                                if (res_parse == Cmd_Item_Valid_Result.CMD_ITEM_OK_CAN_CONTINUE && is_last_char_space) {
                                    res_parse = Cmd_Item_Valid_Result.CMD_ITEM_OK;
                                }
                                if (res_parse == Cmd_Item_Valid_Result.CMD_ITEM_OK_CAN_CONTINUE && (token < tokens.size() - 1)) {
                                    res_parse = Cmd_Item_Valid_Result.CMD_ITEM_OK;
                                }

                                if (res_parse == Cmd_Item_Valid_Result.CMD_ITEM_OK_CAN_CONTINUE) {
                                    TAB_On_OK_CAN_CONTINUE(tab_result_list, cmd_ptr);
                                } else if (token < tokens.size() - 1) { // Not last token in token list, but not OK . not valid
                                    if (res_parse != Cmd_Item_Valid_Result.CMD_ITEM_OK
                                            && res_parse != Cmd_Item_Valid_Result.CMD_ITEM_OK_CAN_CONTINUE
                                            && res_parse != Cmd_Item_Valid_Result.CMD_ITEM_OK_STR_WITHOUT_COMMAS) {
                                        break;
                                    }
                                } else if (token == tokens.size() - 1) { // Last token in token list
                                    if (res_parse == Cmd_Item_Valid_Result.CMD_ITEM_OK || res_parse == Cmd_Item_Valid_Result.CMD_ITEM_OK_STR_WITHOUT_COMMAS) {
                                        if (res_parse == Cmd_Item_Valid_Result.CMD_ITEM_OK_STR_WITHOUT_COMMAS && !is_last_char_space) {
                                            TAB_On_OK_STR_WITHOUT_COMMAS_not_last_space(tab_result_list, cmd_ptr, cmd_item_ptr);
                                        } else if (token < cmd_ptr.Items.size() - 1) { // Not last token in cmd list
                                            TAB_On_OK_not_last_token(tab_result_list, cmd_ptr, token, cmd_item_ptr);
                                        } else if (token == cmd_ptr.Items.size() - 1) { // Last token in cmd list
                                            TAB_On_OK_last_token(tab_result_list, cmd_ptr, cmd_item_ptr, token_ptr);
                                        }
                                    } else if (res_parse == Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE || res_parse == Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE_STR) {
                                        if (res_parse == Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE_STR) {
                                            TAB_On_INCOMPLETE_STR(tab_result_list, cmd_ptr, cmd_item_ptr);
                                            is_incomplete_str = true;
                                        } else {
                                            TAB_On_INCOMPLETE(tokens, tab_result_list, is_last_char_space, is_last_char_comma, is_last_char_commas, cmd_ptr, token, cmd_item_ptr, token_ptr);
                                        }
                                    } else {
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
            String level, String s_cmd_in, String s_cmd_in_trim, List<Cmd_Token> tokens) {
        List<TAB_Cmd> tab_cmd_list = new ArrayList<>();

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

        if (Is_Log.Value) {
            tab_cmd_list.add(new TAB_Cmd(TAB_Cmd_ID.TAB_CMD_ID_LOG_PRINT, s_log.Value));
        }
        if (Is_Add.Value) {
            tab_cmd_list.add(new TAB_Cmd(TAB_Cmd_ID.TAB_CMD_ID_INPUT_ADD, s_add.Value));
        }
        if (Is_Space_After.Value) {
            tab_cmd_list.add(new TAB_Cmd(TAB_Cmd_ID.TAB_CMD_ID_INPUT_CHECK_SPACE, ""));
        }

        return tab_cmd_list;
    }

    public void Process_Input_Item(Cli_Input_Item input_item, Ref_Boolean is_invitation_print) {
        List<TAB_Cmd> tab_cmd_list = new ArrayList<>();
        String s_trim = input_item.Text_Get().trim();
        Level_Description level_description = Level_Get();
        String level = level_description.Level;
        String s_help;
        if (s_trim.length() == 0) {
            s_help = TAB_Help_Get(level, Modules);
            tab_cmd_list.add(new TAB_Cmd(TAB_Cmd_ID.TAB_CMD_ID_LOG_PRINT, s_help));
        } else {
            Cmd_Token_Parser_Result parse_res = Cmd_Token_Parser_Result.CMD_TOKEN_PARSER_ERROR;
            List<Cmd_Token> tokens = Token_Parser.Parse(s_trim, Str_Rem, parse_res);
            tab_cmd_list = TAB_Cmd_List_Get(User_Privilege.Value, Modules, level, input_item.Text_Get(), s_trim, tokens);
        }

        if (tab_cmd_list.size() > 0) {
            boolean is_prev_newline = false;
            for (int tab_cmd = 0; tab_cmd < tab_cmd_list.size(); tab_cmd++) {
                TAB_Cmd tab_cmd_ptr = tab_cmd_list.get(tab_cmd);
                if (tab_cmd_ptr != null) {
                    switch (tab_cmd_ptr.ID) {
                        case TAB_CMD_ID_LOG_PRINT:
                            Cli_Output.Output_NewLine();
                            Cli_Output.Output_Str(tab_cmd_ptr.Text);
                            Cli_Output.Output_NewLine();
                            is_invitation_print.Value = true;
                            if (Log_Is_Active) {
                                Log.add(tab_cmd_ptr.Text);
                            }
                            Cli_Input.Input_Str_Pos_Set(Cli_Input.Input_Str_Get().length());
                            is_prev_newline = true;
                            break;
                        case TAB_CMD_ID_INPUT_ADD: {
                            String s_prev = Cli_Input.Input_Str_Get();
                            int s_pos_prev = Cli_Input.Input_Str_Pos_Get();
                            if (s_pos_prev == s_prev.length()) {
                                Cli_Input.Input_Str_Set(s_prev + tab_cmd_ptr.Text);
                                Cli_Input.Input_Str_Pos_Set(Cli_Input.Input_Str_Get().length());
                                Cli_Output.Output_Str(tab_cmd_ptr.Text);
                            } else {
                                Cli_Input.Input_Str_Set(s_prev + tab_cmd_ptr.Text);
                                Cli_Input.Input_End();
                            }
                            is_invitation_print.Value = false;
                            if (Log_Is_Active) {
                                Log.add(tab_cmd_ptr.Text);
                            }
                            is_prev_newline = false;
                        }
                        break;
                        case TAB_CMD_ID_INPUT_CHECK_SPACE: {
                            String s_prev = Cli_Input.Input_Str_Get();
                            int s_pos_prev = Cli_Input.Input_Str_Pos_Get();
                            boolean is_changed = false;
                            if (s_prev.isEmpty() || s_prev.charAt(s_prev.length() - 1) != ' ') {
                                Cli_Input.Input_Str_Set(s_prev + " ");
                                is_changed = true;
                                if (Log_Is_Active) {
                                    Log.add(" ");
                                }
                            }
                            if (is_changed && s_pos_prev == s_prev.length() && !is_prev_newline) {
                                Cli_Input.Input_Str_Pos_Set(Cli_Input.Input_Str_Get().length());
                                Cli_Output.Output_Str(" ");
                            } else {
                                Cli_Input.Input_End();
                            }
                            //is_invitation_print.Value = false; //@Warning
                            is_prev_newline = false;
                        }
                        break;
                    }
                }
            }

        } else {
            Cli_Output.Output_NewLine();
        }

    }

    public String Type_Get() {
        return Type;
    }

    public String Version_Get() {
        return Version;
    }

}
