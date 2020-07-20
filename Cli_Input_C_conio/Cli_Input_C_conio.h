/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_Input_C_conio.h
 * Author: mike
 *
 * Created on July 2, 2020, 5:59 PM
 */

#ifndef CLI_INPUT_C_CONIO_H
#define CLI_INPUT_C_CONIO_H

#include <conio.h>
#include <signal.h>
#include <stdlib.h>

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

    struct Cli_Input_C_Conio {
        struct Cli_Input_C Cli_Input_Base;

        int Input_State; // @Attention: conio specific
    };

    struct Cli_Input_C_Conio Cli_Input_C_conio(void);

#ifdef __cplusplus
}
#endif

#endif /* CLI_INPUT_C_CONIO_H */
