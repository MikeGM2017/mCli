/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Cli_Input_ncurses.h"

bool Cli_Input_ncurses::Input_Init() {

    initscr();

    noecho();
    keypad(stdscr, TRUE);

    raw();

    scrollok(stdscr, TRUE);

    clear();
    refresh();

    return true;
}

bool Cli_Input_ncurses::Input_Restore() {

    endwin();

    return true;
}

Cli_Input_Item Cli_Input_ncurses::Input_Item_Get() {
    bool stop = false;

    Cli_Input_Item Input_Item(CLI_INPUT_ITEM_TYPE_NO, "");

    do {
        unsigned int c = getch();
        switch (c) {
            case '\n':
            case KEY_ENTER:
                Input_Item.Text_Set(Input_Str);
                Input_Item.Type_Set(CLI_INPUT_ITEM_TYPE_STR);
                Input_Str_Clear();
                stop = true;
                break;
            case 0x03: // Ctrl+C
                Input_Str_Clear();
                printw("\n");
                printw("%s", Invitation_Full_Get().c_str());
                break;
            case 0x1C: // Ctrl+"\"
                Input_Item.Text_Set(Input_Str);
                Input_Item.Type_Set(CLI_INPUT_ITEM_TYPE_QUIT);
                Input_Str_Clear();
                printw("\n");
                printw("Ctrl+\\");
                printw("\n");
                stop = true;
                break;
            default:
                Input_Str += c;
                printw("%c", c);
        }
    } while (!stop);

    return Input_Item;
}
