/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_Modules.h
 * Author: mike
 *
 * Created on June 5, 2020, 4:56 PM
 */

#ifndef CLI_MODULES_H
#define CLI_MODULES_H

#include <vector>

using namespace std;

#include "Cli_Module.h"

class Cli_Modules {
protected:

    vector<Cli_Module *> Modules;

public:

    Cli_Modules() {
    }

    virtual ~Cli_Modules() {
    }
    
    virtual int Get_Size() {
        return Modules.size();
    }

    virtual Cli_Module* Get(int index) {
        if (index >= 0 && index < Modules.size())
            return Modules[index];
        return NULL;
    }

    virtual void Add(Cli_Module *cli_module) {
        Modules.push_back(cli_module);
    }

};

#endif /* CLI_MODULES_H */
