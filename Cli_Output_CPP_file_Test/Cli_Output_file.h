/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_Output_file.h
 * Author: mike
 *
 * Created on December 14, 2021, 11:13 AM
 */

#ifndef CLI_OUTPUT_FILE_H
#define CLI_OUTPUT_FILE_H

#include <stdio.h>

#include "Cli_Output_Abstract.h"

class Cli_Output_file : public Cli_Output_Abstract {
protected:

    string File_Name;

    FILE *File_Out;

public:

    Cli_Output_file(string filename) : File_Name(filename), File_Out(NULL) {
    }

    virtual bool Output_Init() {
        if (!File_Out) {
            File_Out = fopen(File_Name.c_str(), "wt");
            if (File_Out) {
                return true; // Ok
            }
        }
        return false; // Failed
    }

    virtual bool Output_Close() {
        if (File_Out) {
            fclose(File_Out);
            File_Out = NULL;
            return true; // Ok
        }
        return false; // Failed
    }

    virtual bool Output_Clear() {
        return false; // Can not clear
    }

    virtual void Output_NewLine() {
        if (File_Out) {
            fprintf(File_Out, "\n");
        }
    }

    virtual void Output_Char(char c) {
        if (File_Out) {
            fprintf(File_Out, "%c", c);
            fflush(File_Out);
        }
    }

    virtual void Output_Str(string s) {
        if (File_Out) {
            fprintf(File_Out, "%s", s.c_str());
            fflush(File_Out);
        }
    }

    virtual void Output_Return() {
        if (File_Out) {
            fprintf(File_Out, "\r");
        }
    }

};

#endif /* CLI_OUTPUT_FILE_H */
