/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_Input_pdcurses.h
 * Author: mike
 *
 * Created on June 3, 2020, 9:28 AM
 */

#ifndef CLI_INPUT_PDCURSES_H
#define CLI_INPUT_PDCURSES_H

#include <curses.h>

#include "Cli_Input_Abstract.h"

class Cli_Input_pdcurses : public Cli_Input_Abstract {
public:

    virtual bool Input_Init();

    virtual bool Input_Restore();

    virtual Cli_Input_Item Input_Item_Get();

};

#endif /* CLI_INPUT_PDCURSES_H */
