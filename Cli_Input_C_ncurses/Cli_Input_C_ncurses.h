/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_Input_C_ncurses.h
 * Author: mike
 *
 * Created on July 2, 2020, 4:52 PM
 */

#ifndef CLI_INPUT_C_NCURSES_H
#define CLI_INPUT_C_NCURSES_H

#include <curses.h>

#include "Cli_Input_C.h"

#ifdef __cplusplus
extern "C" {
#endif

    struct Cli_Input_C_NCurses {
        struct Cli_Input_C Cli_Input_Base;
    };

    struct Cli_Input_C_NCurses Cli_Input_C_ncurses(void);

#ifdef __cplusplus
}
#endif

#endif /* CLI_INPUT_C_NCURSES_H */
