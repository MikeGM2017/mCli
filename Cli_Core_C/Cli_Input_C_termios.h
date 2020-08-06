/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_Input_C_termios.h
 * Author: mike
 *
 * Created on July 2, 2020, 1:36 PM
 */

#ifndef CLI_INPUT_C_TERMIOS_H
#define CLI_INPUT_C_TERMIOS_H

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <termios.h> // @Attention: termios specific
#include <fcntl.h>

#ifdef _WIN32
#include <conio.h>
#include <Windows.h>
#else
#include <unistd.h>
#include <fcntl.h>
#endif

#include "Cli_Input_C.h"

#ifdef __cplusplus
extern "C" {
#endif

    struct Cli_Input_C_Termios {
        struct Cli_Input_C Cli_Input_Base;

        struct termios terminal_state_prev; // @Attention: termios specific
        struct termios terminal_state_new; // @Attention: termios specific

        int Input_State; // @Attention: termios specific
    };

    struct Cli_Input_C_Termios Cli_Input_C_termios(struct Cli_Output_C *cli_output);

#ifdef __cplusplus
}
#endif

#endif /* CLI_INPUT_C_TERMIOS_H */
