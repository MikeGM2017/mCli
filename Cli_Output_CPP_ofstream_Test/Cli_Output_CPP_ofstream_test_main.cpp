/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_Output_CPP_ofstream_test_main.cpp
 * Author: mike
 *
 * Created on December 14, 2021, 13:21 PM
 */

#include <limits>

using namespace std;

#include "Cli_Output_ofstream.h"

int main(int argc, char** argv) {

    string Cli_Output_Log = "Cli_Output_Log.log";

    Cli_Output_ofstream Cli_Output(Cli_Output_Log);

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
