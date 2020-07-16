/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_Command_Processor_Abstract.h
 * Author: mike
 *
 * Created on July 16, 2020, 11:53 AM
 */

#ifndef CLI_COMMAND_PROCESSOR_ABSTRACT_H
#define CLI_COMMAND_PROCESSOR_ABSTRACT_H

#include <string>

using namespace std;

class Cli_Command_Processor_Abstract {
public:

    Cli_Command_Processor_Abstract() {
    }

    virtual ~Cli_Command_Processor_Abstract() {
    }

    virtual bool Do(string s_trim, bool is_debug, bool &debug_res) = 0;

};

#endif /* CLI_COMMAND_PROCESSOR_ABSTRACT_H */
