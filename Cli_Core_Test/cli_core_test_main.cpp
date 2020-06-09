/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   cli_core_test_main.cpp
 * Author: mike
 *
 * Created on June 5, 2020, 10:03 AM
 */

#include "Cli_Input_termios.h"

#include "Cli_Output_printf.h"

#include "Cli_Core.h"

#include "Cli_Modules.h"

#include "Cli_Module_Base_Rem.h"
#include "Cli_Module_Base_Quit.h"
#include "Cli_Module_Base_Help.h"
#include "Cli_Module_Base_Modules.h"

#include "Str_Filter.h"

int main(int argc, char *argv[]) {

    const string Version = "0.01";

    Cli_Output_printf Cli_Output;

    Cli_Input_termios Cli_Input(Cli_Output);

    Cmd_Token_Parser Token_Parser;

    Cli_Cmd_Privilege_ID User_Privilege = CMD_PRIVILEGE_ROOT_DEF;
    Cli_Core Cli(User_Privilege, Token_Parser, Cli_Input, Cli_Output);

    Cli_Modules Modules;

    // Modules Add - Begin

    const string str_rem_def = "$";
    Modules.Add(new Cli_Module_Base_Rem(str_rem_def, Cli_Output));

    bool Cmd_Quit = false;
    Modules.Add(new Cli_Module_Base_Quit(Cmd_Quit));

    Str_Filter str_filter('?', '*');
    Modules.Add(new Cli_Module_Base_Help(User_Privilege, Modules, str_filter, Cli_Output));
    Modules.Add(new Cli_Module_Base_Modules(Modules, str_filter, Cli_Output));

    // Modules Add - End

    Cli_Input.Title_Set("Cli Core Test");
    Cli_Input.User_Set("root");
    Cli_Input.Level_Set("top level");
    Cli_Input.Invitation_Set("> ");
    Cli_Input.Divider_L_Set("[");
    Cli_Input.Divider_R_Set("]");
    Cli_Input.Input_Init();

    Cli_Output.Output_NewLine();
    Cli_Output.Output_Str("mCli: Cli Core Test");
    Cli_Output.Output_Str(" V");
    Cli_Output.Output_Str(Version);
    Cli_Output.Output_NewLine();
    Cli_Output.Output_NewLine();

    bool stop = false;
    bool is_invitation_print = true;
    do {
        if (is_invitation_print) {
            Cli_Output.Output_Str(Cli_Input.Invitation_Full_Get());
            Cli_Output.Output_Str(Cli_Input.Input_Str_Get());
        }
        is_invitation_print = true;
        Cli_Input_Item input_item = Cli_Input.Input_Item_Get();
        switch (input_item.Type_Get()) {
            case CLI_INPUT_ITEM_TYPE_STR:
            {
                bool res_process_input_item = Cli.Process_Input_Item(Modules, input_item, str_rem_def);
                if (!res_process_input_item) {
                    Cli_Output.Output_NewLine();
                }
            }
                break;
            case CLI_INPUT_ITEM_TYPE_TAB:
            {
                //Cli_Output.Output_NewLine();
                //Cli_Output.Output_Str("TAB: ");
                //Cli_Output.Output_Str(input_item.Text_Get());
                //Cli_Output.Output_NewLine();
                Cli.Process_Tab(Modules, input_item, str_rem_def, is_invitation_print);
                //Cli_Output.Output_NewLine();
            }
                break;
            case CLI_INPUT_ITEM_TYPE_UP:
            {
                Cli_Output.Output_NewLine();
                Cli_Output.Output_Str("UP: ");
                Cli_Output.Output_Str(input_item.Text_Get());
                Cli_Output.Output_NewLine();
            }
                break;
            case CLI_INPUT_ITEM_TYPE_DOWN:
            {
                Cli_Output.Output_NewLine();
                Cli_Output.Output_Str("DOWN: ");
                Cli_Output.Output_Str(input_item.Text_Get());
                Cli_Output.Output_NewLine();
            }
                break;
            case CLI_INPUT_ITEM_TYPE_QUIT:
            {
                Cli_Output.Output_NewLine();
                Cli_Output.Output_Str("Quit - Processed");
                Cli_Output.Output_NewLine();
                stop = true; // Quit
            }
                break;
        }

        if (Cmd_Quit) {
            Cli_Output.Output_NewLine();
            Cli_Output.Output_Str("Quit - Processed");
            Cli_Output.Output_NewLine();
            stop = true; // Quit
        }

    } while (!stop);

    Cli_Input.Input_Restore();

    return 0;
}
