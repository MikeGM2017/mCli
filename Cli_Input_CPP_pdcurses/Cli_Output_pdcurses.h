/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_Output_pdcurses.h
 * Author: mike
 *
 * Created on June 3, 2020, 12:49 PM
 */

#ifndef CLI_OUTPUT_PDCURSES_H
#define CLI_OUTPUT_PDCURSES_H

#include <curses.h>

#include "Cli_Output_Abstract.h"

class Cli_Output_pdcurses : public Cli_Output_Abstract {
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

    virtual void Output_NewLine() {
        printw("\n");
    }

    virtual void Output_Char(char c) {
        printw("%c", c);
    }

    virtual void Output_Str(string s) {
        printw("%s", s.c_str());
    }

};

#endif /* CLI_OUTPUT_PDCURSES_H */
