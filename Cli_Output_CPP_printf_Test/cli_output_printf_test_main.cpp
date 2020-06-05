/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   cli_output_printf_test_main.cpp
 * Author: mike
 *
 * Created on June 3, 2020, 12:10 PM
 */

#include <stdio.h>

#include "Cli_Output_printf.h"

int main(int argc, char** argv) {
    
    Cli_Output_printf Cli_Output;
    
    Cli_Output.Output_Char('X');
    Cli_Output.Output_NewLine();
    Cli_Output.Output_Str(" - Ok");
    Cli_Output.Output_NewLine();
    Cli_Output.Output_Str("End");
    Cli_Output.Output_Return();
    
    getchar();

    return 0;
}
