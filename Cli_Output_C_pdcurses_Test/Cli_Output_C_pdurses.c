/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Cli_Output_C_pdcurses.h"

static int Cli_Output_Init_pdcurses(void) {
    initscr();

    noecho();
    keypad(stdscr, TRUE);

    raw();

    scrollok(stdscr, TRUE);

    clear();
    refresh();

    return 1; // Ok
}

static int Cli_Output_Close_pdcurses(void) {
    endwin();
    return 1; // Ok
}

static void Cli_Output_NewLine_pdcurses(void) {
    printw("\n");
}

static void Cli_Output_Char_pdcurses(char c) {
    printw("%c", c);
}

static void Cli_Output_Str_pdcurses(char *s) {
    printw("%s", s);
}

static void Cli_Output_Return_pdcurses(void) {
    printw("\r");
}

struct Cli_Output_C Cli_Output_C_pdcurses(void) {
    struct Cli_Output_C Cli_Output = {
        .Output_Init = Cli_Output_Init_pdcurses,
        .Output_Close = Cli_Output_Close_pdcurses,
        .Output_NewLine = Cli_Output_NewLine_pdcurses,
        .Output_Char = Cli_Output_Char_pdcurses,
        .Output_Str = Cli_Output_Str_pdcurses,
        .Output_Return = Cli_Output_Return_pdcurses,
    };
    return Cli_Output;
}
