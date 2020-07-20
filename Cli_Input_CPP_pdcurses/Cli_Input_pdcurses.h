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

#ifdef _WIN32
#include <conio.h>
#include <Windows.h>
#else
#include <unistd.h>
#include <fcntl.h>
#endif

#include "Cli_Input_Abstract.h"

class Cli_Input_pdcurses : public Cli_Input_Abstract {
public:

    Cli_Input_pdcurses(Cli_Output_Abstract &cli_output) : Cli_Input_Abstract(cli_output) {
    }

    virtual bool Input_Init();

    virtual bool Input_Restore();

    virtual bool Input_Clear();

    virtual Cli_Input_Item Input_Item_Get();

    bool Input_sleep(int sleep_sec);

    virtual bool Input_kbhit();

};

#endif /* CLI_INPUT_PDCURSES_H */
