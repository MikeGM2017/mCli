/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_Input_conio.h
 * Author: mike
 *
 * Created on June 3, 2020, 11:10 AM
 */

#ifndef CLI_INPUT_CONIO_H
#define CLI_INPUT_CONIO_H

#include <conio.h>
#include <signal.h>

#include "Cli_Input_Abstract.h"

class Cli_Input_conio : public Cli_Input_Abstract {
protected:

    static Cli_Input_Abstract *Cli_Input_Object; // Attention: for using in SIGINT_Handler
    static Cli_Output_Abstract *Cli_Output_Object; // Attention: for using in SIGINT_Handler

    static void SIGINT_Handler(int sig); // Ctrl+C

    int Input_State;

public:

    Cli_Input_conio(Cli_Output_Abstract &cli_output) : Cli_Input_Abstract(cli_output),
    Input_State(0) {
    }

    virtual bool Input_Init();

    virtual bool Input_Restore();

    virtual Cli_Input_Item Input_Item_Get();

};

#endif /* CLI_INPUT_CONIO_H */
