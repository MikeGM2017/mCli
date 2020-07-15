/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Cli_Input_pdcurses.h"

bool Cli_Input_pdcurses::Input_Init() {
    return Cli_Output.Output_Init();
}

bool Cli_Input_pdcurses::Input_Restore() {
    return Cli_Output.Output_Close();
}

Cli_Input_Item Cli_Input_pdcurses::Input_Item_Get() {
    bool stop = false;

    Cli_Input_Item Input_Item(CLI_INPUT_ITEM_TYPE_NO, "");

    do {
        unsigned int c = getch();
        switch (c) {
            case '\n': // Enter - NCurses
            case '\r': // Enter - PDCurses
            case KEY_ENTER:
                Input_Item.Text_Set(Input_Str);
                Input_Item.Type_Set(CLI_INPUT_ITEM_TYPE_STR);
                Input_Str_Clear();
                stop = true;
                break;
            case 0x03: // Ctrl+C
                Input_Str_Clear();
                Cli_Output.Output_NewLine();
                Cli_Output.Output_Str(Invitation_Full_Get());
                break;
            case 0x1C: // Ctrl+"\" - NCurses
            case 0x5C: // Ctrl+"\" - PDCurses
                Input_Item.Text_Set(Input_Str);
                Input_Item.Type_Set(CLI_INPUT_ITEM_TYPE_QUIT);
                Input_Str_Clear();
                Cli_Output.Output_NewLine();
                Cli_Output.Output_Str("Ctrl+\\");
                Cli_Output.Output_NewLine();
                stop = true;
                break;
            case 8: // BACK
            case KEY_BACKSPACE:
                Input_Back();
                break;
            case 9: // Tab
                Input_Item.Text_Set(Input_Str);
                Input_Item.Type_Set(CLI_INPUT_ITEM_TYPE_TAB);
                stop = true;
                break;
            case KEY_DC:
                Input_Delete();
                break;
            case KEY_HOME:
                Input_Home();
                break;
            case KEY_END:
                Input_End();
                break;
            case KEY_LEFT:
                Input_Left();
                break;
            case KEY_RIGHT:
                Input_Right();
                break;
            case KEY_UP:
                Input_Item.Text_Set(Input_Str);
                Input_Item.Type_Set(CLI_INPUT_ITEM_TYPE_UP);
                stop = true;
                break;
            case KEY_DOWN:
                Input_Item.Text_Set(Input_Str);
                Input_Item.Type_Set(CLI_INPUT_ITEM_TYPE_DOWN);
                stop = true;
                break;
            default:
                Input_Add(c);
        }
    } while (!stop);

    return Input_Item;
}