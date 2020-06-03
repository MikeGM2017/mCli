/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   cli_input_cpp_conio_main.cpp
 * Author: mike
 *
 * Created on June 3, 2020, 11:58 AM
 */

#include <iostream>

using namespace std;

#include "Cli_Input_conio.h"

int main(int argc, char *argv[]) {

    Cli_Input_conio Cli_Input;

    Cli_Input.Title_Set("cli demo");
    Cli_Input.User_Set("root");
    Cli_Input.Level_Set("top level");
    Cli_Input.Invitation_Set("> ");
    Cli_Input.Divider_L_Set("[");
    Cli_Input.Divider_R_Set("]");
    Cli_Input.Input_Init();

    bool stop = false;
    do {
        cout << Cli_Input.Invitation_Full_Get() + Cli_Input.Input_Str_Get();
        cout.flush();
        Cli_Input_Item input_item = Cli_Input.Input_Item_Get();
        if (input_item.Type_Get() == CLI_INPUT_ITEM_TYPE_STR) {
            string input_str = input_item.Text_Get();
            if (input_str == "Q") {
                cout << endl << "Quit - Processed" << endl;
                stop = true; // Quit
            } else if (!input_str.empty()) {
                cout << endl << input_item.Text_Get()
                        << " - Not Processed" << endl;
            } else {
                cout << endl;
            }
        }
    } while (!stop);

    Cli_Input.Input_Restore();

    return 0;
}
