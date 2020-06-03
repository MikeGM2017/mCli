/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Cli_Input_conio.h"

Cli_Input_Abstract *Cli_Input_conio::Cli_Input_Object = NULL;
Cli_Output_Abstract *Cli_Input_conio::Cli_Output_Object = NULL;

void Cli_Input_conio::SIGINT_Handler(int sig) { // Ctrl+C
    if (Cli_Input_Object) {
        Cli_Input_Object->Input_Str_Clear();
    }
    if (Cli_Output_Object) {
        Cli_Output_Object->Output_NewLine();
        Cli_Output_Object->Output_Str(Cli_Input_Object->Invitation_Full_Get());
    }
}

bool Cli_Input_conio::Input_Init() {
    Cli_Input_Object = this;
    Cli_Output_Object = &Cli_Output;

    signal(SIGINT, SIGINT_Handler); // Ctrl+C

    return Cli_Output.Output_Init();
}

bool Cli_Input_conio::Input_Restore() {
    return Cli_Output.Output_Close();
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
                Cli_Output.Output_Char(c);
        }
    } while (!stop);

    return Input_Item;
};
