/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_CMD_Processor_Abstract.h
 * Author: mike
 *
 * Created on July 16, 2020, 11:53 AM
 */

#ifndef CLI_CMD_PROCESSOR_ABSTRACT_H
#define CLI_CMD_PROCESSOR_ABSTRACT_H

#include <string>

using namespace std;

#include "Cli_Input_Item.h"

class Cli_CMD_Processor_Abstract {
public:

    Cli_CMD_Processor_Abstract() {
    }

    virtual ~Cli_CMD_Processor_Abstract() {
    }

    virtual bool Process_Input_Item(Cli_Input_Item &input_item, bool is_debug, bool &debug_res) = 0;

};

#endif /* CLI_CMD_PROCESSOR_ABSTRACT_H */
