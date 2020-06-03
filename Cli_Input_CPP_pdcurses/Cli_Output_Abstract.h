/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_Output_Abstract.h
 * Author: mike
 *
 * Created on June 3, 2020, 12:12 PM
 */

#ifndef CLI_OUTPUT_ABSTRACT_H
#define CLI_OUTPUT_ABSTRACT_H

#include <string>

using namespace std;

class Cli_Output_Abstract {
public:
    
    virtual bool Output_Init() = 0;
    virtual bool Output_Close() = 0;
    
    virtual void Output_NewLine() = 0;
    virtual void Output_Char(char c) = 0;
    virtual void Output_Str(string s) = 0;
    
    virtual void Output_Return() = 0;
    
};

#endif /* CLI_OUTPUT_ABSTRACT_H */
