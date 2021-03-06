/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_Output_ncurses.h
 * Author: mike
 *
 * Created on June 3, 2020, 12:25 PM
 */

#ifndef CLI_OUTPUT_NCURSES_H
#define CLI_OUTPUT_NCURSES_H

#include <curses.h>

#include "Cli_Output_Abstract.h"

class Cli_Output_ncurses : public Cli_Output_Abstract {
public:

    virtual bool Output_Init() {
        initscr();

        noecho();
        keypad(stdscr, TRUE);

        raw();

        scrollok(stdscr, TRUE);

        clear();
        refresh();

        return true;
    }

    virtual bool Output_Close() {
        endwin();
        return true;
    }

    virtual bool Output_Clear() {
        clear();
        return true;
    }

    virtual void Output_NewLine() {
        printw("\n");
    }

    virtual void Output_Char(char c) {
        printw("%c", c);
    }

    virtual void Output_Str(string s) {
        printw("%s", s.c_str());
    }

    virtual void Output_Return() {
        printw("\r");
    }

};

#endif /* CLI_OUTPUT_NCURSES_H */
