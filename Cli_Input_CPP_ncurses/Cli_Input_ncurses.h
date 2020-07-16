/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_Input_ncurses.h
 * Author: mike
 *
 * Created on June 2, 2020, 12:20 PM
 */

#ifndef CLI_INPUT_NCURSES_H
#define CLI_INPUT_NCURSES_H

#include <curses.h>

#include "Cli_Input_Abstract.h"

class Cli_Input_ncurses : public Cli_Input_Abstract {
public:

    Cli_Input_ncurses(Cli_Output_Abstract &cli_output) : Cli_Input_Abstract(cli_output) {
    }

    virtual bool Input_Init();

    virtual bool Input_Restore();

    virtual bool Input_Clear();

    virtual Cli_Input_Item Input_Item_Get();

};

#endif /* CLI_INPUT_NCURSES_H */
