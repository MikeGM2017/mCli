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

int main(int argc, char *argv[]) {

    Cli_Input_ncurses Cli_Input;

    Cli_Input.Title_Set("cli demo");
    Cli_Input.User_Set("root");
    Cli_Input.Level_Set("top level");
    Cli_Input.Invitation_Set("> ");
    Cli_Input.Divider_L_Set("[");
    Cli_Input.Divider_R_Set("]");
    Cli_Input.Input_Init();

    bool stop = false;
    do {
        printw("\r%s%s", Cli_Input.Invitation_Full_Get().c_str(), Cli_Input.Input_Str_Get().c_str());
        Cli_Input_Item input_item = Cli_Input.Input_Item_Get();
        if (input_item.Type_Get() == CLI_INPUT_ITEM_TYPE_STR) {
            string input_str = input_item.Text_Get();
            if (input_str == "Q") {
                printw("\n");
                printw("Quit - Processed");
                printw("\n");
                stop = true; // Quit
            } else if (!input_str.empty()) {
                printw("\n");
                printw("%s", input_item.Text_Get().c_str());
                printw(" - Not Processed");
                printw("\n");
            } else {
                printw("\n");
            }
        } else if (input_item.Type_Get() == CLI_INPUT_ITEM_TYPE_QUIT) {
            printw("\n");
            printw("Quit - Processed");
            printw("\n");
            stop = true; // Quit
        }
    } while (!stop);

    Cli_Input.Input_Restore();

    return 0;
}
