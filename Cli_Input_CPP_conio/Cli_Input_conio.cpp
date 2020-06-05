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
        switch (Input_State) {

            case 0:
                switch (c) {
                    case '\n':
                    case '\r':
                        Input_Item.Text_Set(Input_Str);
                        Input_Item.Type_Set(CLI_INPUT_ITEM_TYPE_STR);
                        Input_Str_Clear();
                        stop = true;
                        break;
                    case 8: // BACK
                        Input_Back();
                        break;
                    case 9: // TAB
                        Input_Str_Pos = Input_Str.size();
                        Input_Item.Text_Set(Input_Str);
                        Input_Item.Type_Set(CLI_INPUT_ITEM_TYPE_TAB);
                        stop = true;
                        break;
                    case 0xE0: // Начало последовательности
                        Input_State = 1;
                        break;
                    default:
                        Input_Add(c);
                }
                break;

            case 1:
                switch(c) {
                    case 0x47: // Home
                        Input_Home();
                        Input_State = 0;
                        break;
                    case 0x4F: // End
                        Input_End();
                        Input_State = 0;
                        break;
                    case 0x4B: // Left
                        Input_Left();
                        Input_State = 0;
                        break;
                    case 0x4D: // Right
                        Input_Right();
                        Input_State = 0;
                        break;
                    case 0x53: // Delete
                        Input_Delete();
                        Input_State = 0;
                        break;
                    case 0x48: // Up
                        Input_Item.Text_Set(Input_Str);
                        Input_Item.Type_Set(CLI_INPUT_ITEM_TYPE_UP);
                        stop = true;
                        Input_State = 0;
                        break;
                    case 0x50: // Down
                        Input_Item.Text_Set(Input_Str);
                        Input_Item.Type_Set(CLI_INPUT_ITEM_TYPE_DOWN);
                        stop = true;
                        Input_State = 0;
                        break;
                    default:
                        Input_State = 0;
                }
                break;

            default:
                Input_State = 0;

        }
    } while (!stop);

    return Input_Item;
};
