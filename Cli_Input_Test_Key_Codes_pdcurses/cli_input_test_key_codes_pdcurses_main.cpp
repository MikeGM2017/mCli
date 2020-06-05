/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   cli_input_test_key_codes_pdcurses_main.cpp
 * Author: mike
 *
 * Created on June 5, 2020, 9:25 AM
 */

#include <curses.h>

bool Input_Init() {
    initscr();

    noecho();
    keypad(stdscr, TRUE);

    raw();

    scrollok(stdscr, TRUE);

    clear();
    refresh();

    return true; // Ok
}

bool Input_Restore() {
    endwin();
    return true; // Ok
}

int Input_Char_Get() {
    return getch();
}

int main(int argc, char** argv) {

    Input_Init();
    
    printw("Test Key Codes: PDCurses\n");

    bool stop = false;
    do {
        int c = Input_Char_Get();
        printw("0x%02X\n", c);
    } while (!stop);

    Input_Restore();

    return 0;
}
