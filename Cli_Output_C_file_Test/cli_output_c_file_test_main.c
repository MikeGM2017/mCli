/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   cli_output_c_file_test_main.c
 * Author: mike
 *
 * Created on December 14, 2021, 1:05 PM
 */

#include <stdio.h>

#include "Cli_Output_C_file.h"

int main(int argc, char** argv) {

    char Cli_Output_Log[] = "Cli_Output_Log.log";

    struct Cli_Output_C_file Cli_Output_file = Cli_Output_C_file(Cli_Output_Log);
    struct Cli_Output_C Cli_Output = Cli_Output_file.Cli_Output_Base;

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
