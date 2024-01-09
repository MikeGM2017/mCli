/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_Output_cout.h
 * Author: mike
 *
 * Created on June 3, 2020, 12:18 PM
 */

#ifndef CLI_OUTPUT_COUT_H
#define CLI_OUTPUT_COUT_H

#include <iostream>

using namespace std;

#include "Cli_Output_Abstract.h"

class Cli_Output_cout : public Cli_Output_Abstract {
public:

    virtual bool Output_Init() {
        return true;
    }

    virtual bool Output_Close() {
        return true;
    }

    virtual bool Output_Clear() {
        return false; // can not clear
    }

    virtual void Output_NewLine() {
        cout << endl;
    }

    virtual void Output_Char(char c) {
        cout << c;
        cout.flush();
    }

    virtual void Output_Str(string s) {
        cout << s;
        cout.flush();
    }

    virtual void Output_Return() {
        cout << '\r';
        cout.flush();
    }

};

#endif /* CLI_OUTPUT_COUT_H */
