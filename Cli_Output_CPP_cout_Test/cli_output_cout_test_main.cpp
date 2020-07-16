/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   cli_output_cout_test_main.cpp
 * Author: mike
 *
 * Created on June 3, 2020, 12:18 PM
 */

#include <limits>

using namespace std;

#include "Cli_Output_cout.h"

int main(int argc, char** argv) {

    Cli_Output_cout Cli_Output;

    Cli_Output.Output_Init();

    Cli_Output.Output_Char('X');
    Cli_Output.Output_NewLine();
    Cli_Output.Output_Str(" - Ok");
    Cli_Output.Output_NewLine();
    Cli_Output.Output_Str("End");
    Cli_Output.Output_Return();

    char c;
    cin.peek() >> c;

    bool res_clear = Cli_Output.Output_Clear();
    Cli_Output.Output_NewLine();
    if (res_clear)
        Cli_Output.Output_Str("Cleared");
    else
        Cli_Output.Output_Str("Not Cleared");

    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cin.peek() >> c;

    Cli_Output.Output_Close();

    return 0;
}
