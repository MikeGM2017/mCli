/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_Input_termios.h
 * Author: mike
 *
 * Created on June 2, 2020, 9:34 AM
 */

#ifndef CLI_INPUT_TERMIOS_H
#define CLI_INPUT_TERMIOS_H

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <termios.h>
#include <fcntl.h>

#ifdef _WIN32
#include <conio.h>
#include <Windows.h>
#else
#include <unistd.h>
#include <fcntl.h>
#endif

#include "Cli_Input_Abstract.h"

class Cli_Input_termios : public Cli_Input_Abstract {
protected:

    struct termios terminal_state_prev;
    struct termios terminal_state_new;

    static Cli_Input_Abstract *Cli_Input_Object; // Attention: for using in SIGINT_Handler / SIGTSTP_Handler only
    static Cli_Output_Abstract *Cli_Output_Object; // Attention: for using in SIGINT_Handler / SIGTSTP_Handler only

    static void SIGINT_Handler(int sig); // Ctrl+C
    static void SIGTSTP_Handler(int sig); // Ctrl+Z

    int Input_State;

public:

    Cli_Input_termios(Cli_Output_Abstract &cli_output) : Cli_Input_Abstract(cli_output),
    Input_State(0) {
    }

    virtual bool Input_Init();

    virtual bool Input_Restore();

    virtual bool Input_Clear();

    virtual Cli_Input_Item Input_Item_Get();

    virtual bool Input_sleep(int sleep_sec);

    virtual bool Input_kbhit();

};

#endif /* CLI_INPUT_TERMIOS_H */
