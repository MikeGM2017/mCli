/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   cli_input_cpp_ncurses_main.cpp
 * Author: mike
 *
 * Created on June 2, 2020, 12:16 PM
 */

#include "Cli_Input_ncurses.h"

#include "Cli_Output_ncurses.h"

int main(int argc, char *argv[]) {

    Cli_Output_ncurses Cli_Output;

    Cli_Input_ncurses Cli_Input(Cli_Output);

    Cli_Input.Title_Set("cli demo");
    Cli_Input.User_Set("root");
    Cli_Input.Level_Set("top level");
    Cli_Input.Invitation_Set("> ");
    Cli_Input.Divider_L_Set("[");
    Cli_Input.Divider_R_Set("]");
    Cli_Input.Input_Init();

    bool stop = false;
    do {
        Cli_Output.Output_Str(Cli_Input.Invitation_Full_Get());
        Cli_Output.Output_Str(Cli_Input.Input_Str_Get());
        Cli_Input_Item input_item = Cli_Input.Input_Item_Get();
        if (input_item.Type_Get() == CLI_INPUT_ITEM_TYPE_STR) {
            string input_str = input_item.Text_Get();
            if (input_str == "Q") {
                Cli_Output.Output_NewLine();
                Cli_Output.Output_Str("Quit - Processed");
                Cli_Output.Output_NewLine();
                stop = true; // Quit
            } else if (input_str == "C") {
                Cli_Input.Input_Clear();
                Cli_Output.Output_NewLine();
                Cli_Output.Output_Str("Clear - Processed");
                Cli_Output.Output_NewLine();
            } else if (!input_str.empty()) {
                Cli_Output.Output_NewLine();
                Cli_Output.Output_Str(input_item.Text_Get());
                Cli_Output.Output_Str(" - Not Processed");
                Cli_Output.Output_NewLine();
            } else {
                Cli_Output.Output_NewLine();
            }
        } else if (input_item.Type_Get() == CLI_INPUT_ITEM_TYPE_TAB) {
            Cli_Output.Output_NewLine();
            Cli_Output.Output_Str("TAB: ");
            Cli_Output.Output_Str(input_item.Text_Get());
            Cli_Output.Output_NewLine();
            Cli_Input.Input_Str_Pos_Set(Cli_Input.Input_Str_Get().size());
        } else if (input_item.Type_Get() == CLI_INPUT_ITEM_TYPE_UP) {
            Cli_Output.Output_NewLine();
            Cli_Output.Output_Str("UP: ");
            Cli_Output.Output_Str(input_item.Text_Get());
            Cli_Output.Output_NewLine();
        } else if (input_item.Type_Get() == CLI_INPUT_ITEM_TYPE_DOWN) {
            Cli_Output.Output_NewLine();
            Cli_Output.Output_Str("DOWN: ");
            Cli_Output.Output_Str(input_item.Text_Get());
            Cli_Output.Output_NewLine();
        } else if (input_item.Type_Get() == CLI_INPUT_ITEM_TYPE_QUIT) {
            Cli_Output.Output_NewLine();
            Cli_Output.Output_Str("Quit - Processed");
            Cli_Output.Output_NewLine();
            stop = true; // Quit
        }
    } while (!stop);

    Cli_Output.Output_NewLine();
    do {
        Cli_Output.Output_Str("Press Any Key to stop");
        Cli_Output.Output_NewLine();
        Cli_Input.Input_sleep(1);
    } while (!Cli_Input.Input_kbhit());

    Cli_Output.Output_Str("Press Any Key to exit");
    Cli_Output.Output_NewLine();
    Cli_Input_Item input_item = Cli_Input.Input_Item_Get();

    Cli_Input.Input_Restore();

    return 0;
}
