/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Cli_Input_conio.h"

Cli_Input_Abstract *Cli_Input_conio::CliInput_Object = NULL;

void Cli_Input_conio::SIGINT_Handler(int sig) { // Ctrl+C
    if (CliInput_Object) {
        CliInput_Object->Input_Str_Clear();
        cout << endl << CliInput_Object->Invitation_Full_Get();
        cout.flush();
    }
}

bool Cli_Input_conio::Input_Init() {
    CliInput_Object = this;

    signal(SIGINT, SIGINT_Handler); // Ctrl+C

    return true; // Ok
}

bool Cli_Input_conio::Input_Restore() {
    return true; // Ok
}

Cli_Input_Item Cli_Input_conio::Input_Item_Get() {
    bool stop = false;

    Cli_Input_Item Input_Item(CLI_INPUT_ITEM_TYPE_NO, "");

    do {
        int c = getch();
        switch (c) {
            case '\n':
            case '\r':
                Input_Item.Text_Set(Input_Str);
                Input_Item.Type_Set(CLI_INPUT_ITEM_TYPE_STR);
                Input_Str_Clear();
                stop = true;
                break;
            default:
                Input_Str += c;
                cout << (char) c;
                cout.flush();
        }
    } while (!stop);

    return Input_Item;
};
