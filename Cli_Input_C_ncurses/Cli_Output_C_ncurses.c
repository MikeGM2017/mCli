/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Cli_Output_C_ncurses.h"

static int Cli_Output_Init_ncurses(void) {
    initscr();

    noecho();
    keypad(stdscr, TRUE);

    raw();

    scrollok(stdscr, TRUE);

    clear();
    refresh();

    return 1; // Ok
}

static int Cli_Output_Close_ncurses(void) {
    endwin();
    return 1; // Ok
}

static void Cli_Output_NewLine_ncurses(void) {
    printw("\n");
}

static void Cli_Output_Char_ncurses(char c) {
    printw("%c", c);
}

static void Cli_Output_Str_ncurses(char *s) {
    printw("%s", s);
}

static void Cli_Output_Return_ncurses(void) {
    printw("\r");
}

struct Cli_Output_C Cli_Output_C_ncurses(void) {
    struct Cli_Output_C Cli_Output = {
        .Output_Init = Cli_Output_Init_ncurses,
        .Output_Close = Cli_Output_Close_ncurses,
        .Output_NewLine = Cli_Output_NewLine_ncurses,
        .Output_Char = Cli_Output_Char_ncurses,
        .Output_Str = Cli_Output_Str_ncurses,
        .Output_Return = Cli_Output_Return_ncurses,
    };
    return Cli_Output;
}
