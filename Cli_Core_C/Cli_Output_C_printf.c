/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Cli_Output_C_printf.h"

static int Cli_Output_Init_printf(void) {
    return 1; // Ok
}

static int Cli_Output_Close_printf(void) {
    return 1; // Ok
}

static int Cli_Output_Clear_printf(void) {
    return 0; // Failed: can not clear
}

static void Cli_Output_NewLine_printf(void) {
    printf("\n");
}

static void Cli_Output_Char_printf(char c) {
    printf("%c", c);
    fflush(stdout);
}

static void Cli_Output_Str_printf(char *s) {
    printf("%s", s);
    fflush(stdout);
}

static void Cli_Output_Return_printf(void) {
    printf("\r");
}

struct Cli_Output_C Cli_Output_C_printf(void) {
    struct Cli_Output_C Cli_Output = {
        .Output_Init = Cli_Output_Init_printf,
        .Output_Close = Cli_Output_Close_printf,
        .Output_Clear = Cli_Output_Clear_printf,
        .Output_NewLine = Cli_Output_NewLine_printf,
        .Output_Char = Cli_Output_Char_printf,
        .Output_Str = Cli_Output_Str_printf,
        .Output_Return = Cli_Output_Return_printf,
    };
    return Cli_Output;
}
