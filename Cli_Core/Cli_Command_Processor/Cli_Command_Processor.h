/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_Command_Processor.h
 * Author: mike
 *
 * Created on July 16, 2020, 11:56 AM
 */

#ifndef CLI_COMMAND_PROCESSOR_H
#define CLI_COMMAND_PROCESSOR_H

#include "Cli_Command_Processor_Abstract.h"

class Cli_Command_Processor : public Cli_Command_Processor_Abstract {
public:

    Cli_Command_Processor() {
    }

    virtual ~Cli_Command_Processor() {
    }

    virtual bool Do(string s_trim, bool is_debug, bool &debug_res) {
        return false;
    }

};

#endif /* CLI_COMMAND_PROCESSOR_H */
