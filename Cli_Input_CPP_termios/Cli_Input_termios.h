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

#include <iostream>

using namespace std;

#include "Cli_Input_Abstract.h"

class Cli_Input_termios : public Cli_Input_Abstract {
protected:

    struct termios terminal_state_prev;
    struct termios terminal_state_new;

    static Cli_Input_Abstract *CliInput_Object; // Attention: for using in SIGINT_Handler / SIGTSTP_Handler only

    static void SIGINT_Handler(int sig); // Ctrl+C
    static void SIGTSTP_Handler(int sig); // Ctrl+Z

public:

    virtual void InputPos_ToEnd() {
    }

    virtual bool Input_Init();

    virtual bool Input_Restore();

    virtual Cli_Input_Item Input_Item_Get();

};

#endif /* CLI_INPUT_TERMIOS_H */
