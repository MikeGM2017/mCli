/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   cli_output_pdcurses_test_main.cpp
 * Author: mike
 *
 * Created on June 3, 2020, 12:47 PM
 */

#include "Cli_Output_pdcurses.h"

int main(int argc, char** argv) {

    Cli_Output_pdcurses Cli_Output;

    Cli_Output.Output_Init();

    Cli_Output.Output_Char('X');
    Cli_Output.Output_NewLine();
    Cli_Output.Output_Str(" - Ok");
    Cli_Output.Output_NewLine();
    Cli_Output.Output_Str("End");
    Cli_Output.Output_Return();

    getch();

    Cli_Output.Output_Close();

    return 0;
}
