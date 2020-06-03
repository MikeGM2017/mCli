/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_Output_printf.h
 * Author: mike
 *
 * Created on June 3, 2020, 12:11 PM
 */

#ifndef CLI_OUTPUT_PRINTF_H
#define CLI_OUTPUT_PRINTF_H

#include <stdio.h>

#include "Cli_Output_Abstract.h"

class Cli_Output_printf : public Cli_Output_Abstract {
public:

    virtual bool Output_Init() {
        return true;
    }

    virtual bool Output_Close() {
        return true;
    }

    virtual void Output_NewLine() {
        printf("\n");
    }

    virtual void Output_Char(char c) {
        printf("%c", c);
        fflush(stdout);
    }

    virtual void Output_Str(string s) {
        printf("%s", s.c_str());
        fflush(stdout);
    }

};

#endif /* CLI_OUTPUT_PRINTF_H */
