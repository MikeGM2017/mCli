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
public class Cli_TAB_Processor {

    protected Cli_Cmd_Privilege_ID User_Privilege;
    protected Cli_Modules Modules;
    protected List<Level_Description> Levels;
    protected Cmd_Token_Parser Token_Parser;

    protected Cli_Input_JavaFX Cli_Input;
    protected Cli_Output_JavaFX Cli_Output;

    protected String Str_Rem;

    protected boolean Log_Is_Active;

    public Cli_TAB_Processor(Cli_Cmd_Privilege_ID user_privilege,
            Cli_Modules modules, List<Level_Description> levels, Cmd_Token_Parser token_parser,
            Cli_Input_JavaFX cli_input, Cli_Output_JavaFX cli_output, String str_rem,
            boolean log_is_active) {
        User_Privilege = user_privilege;
        Modules = modules;
        Levels = levels;
        Token_Parser = token_parser;
        Cli_Input = cli_input;
        Cli_Output = cli_output;
        Str_Rem = str_rem;
        Log_Is_Active = log_is_active;
    }

}
