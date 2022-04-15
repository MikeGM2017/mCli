/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   cli_output_c_printf_test_main.c
 * Author: mike
 *
 * Created on July 2, 2020, 11:05 AM
 */

#include <stdio.h>

#include "Cli_Output_C_printf.h"

int main(int argc, char** argv) {

    struct Cli_Output_C Cli_Output = Cli_Output_C_printf();

    Cli_Output.Output_Init(&Cli_Output);

    Cli_Output.Output_Char(&Cli_Output, 'X');
    Cli_Output.Output_NewLine(&Cli_Output);
    Cli_Output.Output_Str(&Cli_Output, " - Ok");
    Cli_Output.Output_NewLine(&Cli_Output);
    Cli_Output.Output_Str(&Cli_Output, "End");
    Cli_Output.Output_Return(&Cli_Output);

    getchar();

    int res_clear = Cli_Output.Output_Clear(&Cli_Output);
    Cli_Output.Output_NewLine(&Cli_Output);
    if (res_clear)
        Cli_Output.Output_Str(&Cli_Output, "Cleared");
    else
        Cli_Output.Output_Str(&Cli_Output, "Not Cleared");

    getchar();

    Cli_Output.Output_Close(&Cli_Output);

    return 0;
}
