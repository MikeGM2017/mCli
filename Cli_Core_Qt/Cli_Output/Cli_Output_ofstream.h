/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_Output_ofstream.h
 * Author: mike
 *
 * Created on December 14, 2021, 13:24 PM
 */

#ifndef CLI_OUTPUT_OFSTREAM_H
#define CLI_OUTPUT_OFSTREAM_H

#include <iostream>
#include <fstream>

using namespace std;

#include "Cli_Output_Abstract.h"

class Cli_Output_ofstream : public Cli_Output_Abstract {
protected:

    string File_Name;

    ofstream File_Out;

public:

    Cli_Output_ofstream(string filename) : File_Name(filename) {
    }

    virtual bool Output_Init() {
        if (!File_Out.is_open()) {
            File_Out.open(File_Name.c_str(), ios_base::out);
            if (File_Out.is_open()) {
                return true; // Ok
            }
        }
        return false; // Failed
    }

    virtual bool Output_Close() {
        if (File_Out.is_open()) {
            File_Out.close();
            return true; // Ok
        }
        return false; // Failed
    }

    virtual bool Output_Clear() {
        return false; // Can not clear
    }

    virtual void Output_NewLine() {
        if (File_Out.is_open()) {
            File_Out << endl;
        }
    }

    virtual void Output_Char(char c) {
        if (File_Out.is_open()) {
            File_Out << c;
            File_Out.flush();
        }
    }

    virtual void Output_Str(string s) {
        if (File_Out.is_open()) {
            File_Out << s;
            File_Out.flush();
        }
    }

    virtual void Output_Return() {
        if (File_Out.is_open()) {
            File_Out << '\r';
            File_Out.flush();
        }
    }
    
    virtual void Caret_Pos_Set(int input_str_len, int input_str_pos) {
        // no action
    }

};

#endif /* CLI_OUTPUT_OFSTREAM_H */
