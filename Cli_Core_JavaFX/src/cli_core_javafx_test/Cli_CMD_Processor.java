/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cli_core_javafx_test;

import java.util.List;

/**
 *
 * @author mike
 */
public class Cli_CMD_Processor {

    protected String Type = "";
    protected String Version = "";

    protected Ref_Cli_Cmd_Privilege_ID User_Privilege;
    protected Cli_Modules Modules;

    protected List<Level_Description> Levels;
    protected Cmd_Token_Parser Token_Parser;

    protected Cli_Input_JavaFX Cli_Input;
    protected Cli_Output_JavaFX Cli_Output;

    protected String Str_Rem;

    public Cli_CMD_Processor(Ref_Cli_Cmd_Privilege_ID user_privilege,
            Cli_Modules modules, List<Level_Description> levels, Cmd_Token_Parser token_parser,
            Cli_Input_JavaFX cli_input, Cli_Output_JavaFX cli_output, String str_rem) {

        Type = "Cli_CMD_Processor";
        Version = "0.02";

        User_Privilege = user_privilege;
        Modules = modules;
        Levels = levels;
        Token_Parser = token_parser;
        Cli_Input = cli_input;
        Cli_Output = cli_output;
        Str_Rem = str_rem;
    }

    Level_Description Level_Get() {
        if (Levels.size() > 0) {
            return Levels.get(Levels.size() - 1);
        }
        Level_Description level_top = new Level_Description();
        return level_top;
    }

    boolean TAB_Cmd_Ptr_Check_By_Level(Cli_Cmd cmd_ptr, Cli_Cmd_Privilege_ID user_privilege, String level) {
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

    public boolean Process_Input_Item(Cli_Input_Item input_item, boolean is_debug, Ref_Boolean debug_res) {

        String s_trim = input_item.Text_Get().trim();

        if (s_trim.length() == 0) {
            return false;
        }

        if (!s_trim.isEmpty()) {

            Level_Description level_description = Level_Get();
            String level = level_description.Level;

            boolean is_processed = false;
            boolean stop = false;
            Cmd_Token_Parser_Result parse_res = Cmd_Token_Parser_Result.CMD_TOKEN_PARSER_ERROR;
            List<Cmd_Token> tokens = Token_Parser.Parse(s_trim, Str_Rem, parse_res);
            for (int module = 0; module < Modules.Get_Size(); module++) {
                Cli_Module module_ptr = Modules.Get(module);
                if (module_ptr != null) {
                    for (int cmd = 0; cmd < module_ptr.Module_Cmd_List.size() && !stop; cmd++) {
                        Cli_Cmd cmd_ptr = module_ptr.Module_Cmd_List.get(cmd);
                        boolean is_cmd_prt_valid = TAB_Cmd_Ptr_Check_By_Level(cmd_ptr, User_Privilege.Value, level);
                        if (is_cmd_prt_valid) {
                            Cmd_Item_Valid_Result res_cmd_valid = cmd_ptr.Is_Valid(tokens);
                            switch (res_cmd_valid) {
                                case CMD_ITEM_OK:
                                case CMD_ITEM_OK_CAN_CONTINUE:
                                case CMD_ITEM_OK_STR_WITHOUT_COMMAS: {
                                    if (!is_debug) {
                                        Cli_Output.Output_NewLine();
                                    }
                                    boolean res_execute = module_ptr.Execute(cmd_ptr, Levels, is_debug);
                                    if (!res_execute) {
                                        if (!is_debug) {
                                            Cli_Output.Output_NewLine();
                                            Cli_Output.Output_Str(s_trim + " - Not Implemented (Module \"" + module_ptr.Name_Get() + "\")");
                                            Cli_Output.Output_NewLine();
                                        }
                                    } else {
                                        debug_res.Value = true;
                                    }
                                    is_processed = true;
                                    stop = true;
                                }
                                break;
                                case CMD_ITEM_ERROR:
                                case CMD_ITEM_NOT_MATCH:
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
            if (!is_processed) {
                Cli_Output.Output_NewLine();
                Cli_Output.Output_NewLine();
                Cli_Output.Output_Str(s_trim + " - Not Processed");
                Cli_Output.Output_NewLine();
            }
        } else {
            Cli_Output.Output_NewLine();
        }

        return true; // Ok
    }

    public String Type_Get() {
        return Type;
    }

    public String Version_Get() {
        return Version;
    }

}
