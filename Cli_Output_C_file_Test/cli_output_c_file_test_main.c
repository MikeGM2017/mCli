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

    struct Cli_Output_C Cli_Output = Cli_Output_C_file(Cli_Output_Log);

    Cli_Output.Output_Init();

    Cli_Output.Output_Char('X');
    Cli_Output.Output_NewLine();
    Cli_Output.Output_Str(" - Ok");
    Cli_Output.Output_NewLine();
    Cli_Output.Output_Str("End");
    Cli_Output.Output_Return();

    getchar();

    int res_clear = Cli_Output.Output_Clear();
    Cli_Output.Output_NewLine();
    if (res_clear)
        Cli_Output.Output_Str("Cleared");
    else
        Cli_Output.Output_Str("Not Cleared");

    getchar();

    Cli_Output.Output_Close();

    return 0;
}
