/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_Module.h
 * Author: mike
 *
 * Created on July 17, 2018, 11:10 AM
 */

#ifndef CLI_MODULE_H
#define CLI_MODULE_H

#include <string>
#include <vector>
#include <map>

using namespace std;

#include "Cli_Cmd.h"
#include "Level_Description.h"

class Cli_Module {
protected:

    string Name;
    string Version;

public:

    vector<Cli_Cmd *> Module_Cmd_List;

    Cli_Module(string name) : Name(name) {
        Version = "0.01"; //@Warning: Dummy value - Version is not set
    }

    virtual ~Cli_Module() {
        for (int i = 0; i < Module_Cmd_List.size(); i++) {
            delete Module_Cmd_List[i];
        }
    }

    string Name_Get() const {
        return Name;
    }

    void Cmd_Add(Cli_Cmd *cmd) {
        Module_Cmd_List.push_back(cmd);
    }

    virtual bool end(vector<Level_Description> &Levels) {
        if (Levels.size()) Levels.pop_back();
        return true;
    }

    virtual bool Execute(Cli_Cmd *cmd, vector<Level_Description> &Levels, bool is_debug) = 0;

    // @Example: virtual bool Execute(...) {...}
    //virtual bool Execute(CliCmd_ID cmd_id, CliCmd *cmd, vector<LevelDescription> &Levels, bool is_debug) {
    //    return false; // Not Implemented
    //}

    virtual int Cmd_ID_Count_Get() = 0;
    //    virtual int Cmd_ID_Count_Get() {
    //        return 0;
    //    }

    int Cmd_Count_Get() {
        return Module_Cmd_List.size();
    }

    Cli_Cmd *Cmd_Get(int cmd_index) {
        if (cmd_index >= 0 && cmd_index < Module_Cmd_List.size()) {
            return Module_Cmd_List[cmd_index];
        }
        return NULL;
    }

    string Version_Get() {
        return Version;
    }

    virtual void To_Map(map<string, string> &values_map) = 0;

};

#endif /* CLI_MODULE_H */
