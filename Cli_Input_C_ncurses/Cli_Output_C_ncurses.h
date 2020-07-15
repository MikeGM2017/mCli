/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_Output_C_ncurses.h
 * Author: mike
 *
 * Created on July 2, 2020, 12:12 PM
 */

#ifndef CLI_OUTPUT_C_NCURSES_H
#define CLI_OUTPUT_C_NCURSES_H

#include <curses.h>

#include "Cli_Output_C.h"

#ifdef __cplusplus
extern "C" {
#endif

    struct Cli_Output_C Cli_Output_C_ncurses(void);

#ifdef __cplusplus
}
#endif

#endif /* CLI_OUTPUT_C_NCURSES_H */
