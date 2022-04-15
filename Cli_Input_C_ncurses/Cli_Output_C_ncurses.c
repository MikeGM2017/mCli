/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Cli_Output_C_ncurses.h"

static int Cli_Output_Init_ncurses(struct Cli_Output_C *obj) {
    initscr();

    noecho();
    keypad(stdscr, TRUE);

    raw();

    scrollok(stdscr, TRUE);

    clear();
    refresh();

    return 1; // Ok
}

static int Cli_Output_Close_ncurses(struct Cli_Output_C *obj) {
    endwin();
    return 1; // Ok
}

static int Cli_Output_Clear_ncurses(struct Cli_Output_C *obj) {
    clear();
    return 1; // Ok
}

static void Cli_Output_NewLine_ncurses(struct Cli_Output_C *obj) {
    printw("\n");
}

static void Cli_Output_Char_ncurses(struct Cli_Output_C *obj, char c) {
    printw("%c", c);
}

static void Cli_Output_Str_ncurses(struct Cli_Output_C *obj, char *s) {
    printw("%s", s);
}

static void Cli_Output_Return_ncurses(struct Cli_Output_C *obj) {
    printw("\r");
}

struct Cli_Output_C Cli_Output_C_ncurses(void) {
    struct Cli_Output_C Cli_Output = {
        .Output_Init = Cli_Output_Init_ncurses,
        .Output_Close = Cli_Output_Close_ncurses,
        .Output_Clear = Cli_Output_Clear_ncurses,
        .Output_NewLine = Cli_Output_NewLine_ncurses,
        .Output_Char = Cli_Output_Char_ncurses,
        .Output_Str = Cli_Output_Str_ncurses,
        .Output_Return = Cli_Output_Return_ncurses,
    };
    return Cli_Output;
}
