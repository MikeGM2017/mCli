/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   cli_output_c_ncurses_test_main.c
 * Author: mike
 *
 * Created on July 2, 2020, 11:58 AM
 */

#include "Cli_Output_C_ncurses.h"

int main(int argc, char** argv) {

    struct Cli_Output_C Cli_Output = Cli_Output_C_ncurses();

    Cli_Output.Output_Init(&Cli_Output);

    Cli_Output.Output_Char(&Cli_Output, 'X');
    Cli_Output.Output_NewLine(&Cli_Output);
    Cli_Output.Output_Str(&Cli_Output, " - Ok");
    Cli_Output.Output_NewLine(&Cli_Output);
    Cli_Output.Output_Str(&Cli_Output, "End");
    Cli_Output.Output_Return(&Cli_Output);

    getch();

    int res_clear = Cli_Output.Output_Clear(&Cli_Output);
    Cli_Output.Output_NewLine(&Cli_Output);
    if (res_clear)
        Cli_Output.Output_Str(&Cli_Output, "Cleared");
    else
        Cli_Output.Output_Str(&Cli_Output, "Not Cleared");

    getch();

    Cli_Output.Output_Close(&Cli_Output);

    return 0;
}
