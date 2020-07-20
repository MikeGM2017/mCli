/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_Module_Base_Modules.h
 * Author: mike
 *
 * Created on September 17, 2019, 11:16 AM
 */

#ifndef CLI_MODULE_BASE_MODULES_H
#define CLI_MODULE_BASE_MODULES_H

#include "Cli_Module.h"

#include "Cmd_Item_Word.h"
#include "Cmd_Item_Str.h"

#include "Cli_Cmd_Privilege_ID.h"
#include "Cli_Modules.h"

#include "Str_Filter_Abstract.h"

class Cli_Module_Base_Modules : public Cli_Module {
protected:

    Cli_Cmd_Privilege_ID User_Privilege;
    Cli_Modules &Modules;
    
    Str_Filter_Abstract &Str_Filter;

    Cli_Output_Abstract &Cli_Output;

public:

    enum Local_CmdID {
        CMD_ID_NO,

        CMD_ID_modules,
        CMD_ID_modules_by_filter,
        CMD_ID_modules_by_filter_print,

        CMD_ID_LAST
    };

    virtual int Cmd_ID_Count_Get() {
        return CMD_ID_LAST - CMD_ID_NO - 1;
    }

    Cli_Module_Base_Modules(Cli_Cmd_Privilege_ID user_privilege, Cli_Modules &modules,
            Str_Filter_Abstract &str_filter, Cli_Output_Abstract &cli_output) : Cli_Module("Base Modules"),
    User_Privilege(user_privilege), Modules(modules),
    Str_Filter(str_filter), Cli_Output(cli_output) {
        {
            // modules
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_modules);
            cmd->Text_Set("modules");
            cmd->Help_Set("modules print (all)");
            cmd->Is_Global_Set(true);
            cmd->Level_Set("");
            cmd->Item_Add(new Cmd_Item_Word("modules", "modules print (all)"));
            Cmd_Add(cmd);
        }
        {
            // modules <module_name>
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_modules_by_filter);
            cmd->Text_Set("modules <module_name>");
            cmd->Help_Set("modules print (by filter)");
            cmd->Is_Global_Set(true);
            cmd->Level_Set("");
            cmd->Item_Add(new Cmd_Item_Word("modules", "modules"));
            cmd->Item_Add(new Cmd_Item_Str("<module_name>", "modules print (by filter)"));
            Cmd_Add(cmd);
        }
        {
            // modules <module_name> print
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_modules_by_filter_print);
            cmd->Text_Set("modules <module_name> print");
            cmd->Help_Set("modules print (by filter)");
            cmd->Is_Global_Set(true);
            cmd->Level_Set("");
            cmd->Item_Add(new Cmd_Item_Word("modules", "modules"));
            cmd->Item_Add(new Cmd_Item_Str("<module_name>", "modules (by filter)"));
            cmd->Item_Add(new Cmd_Item_Word("print", "modules print (by filter)"));
            Cmd_Add(cmd);
        }
    }

    virtual ~Cli_Module_Base_Modules() {
    }

    bool modules_by_filter_print(string module_filter, Str_Filter_Abstract &str_filter) {
        Cli_Output.Output_NewLine();
        bool found = false;
        for (int module = 0; module < Modules.Get_Size(); module++) {
            Cli_Module *module_ptr = Modules.Get(module);
            if (module_ptr) {
                string module_name = module_ptr->Name_Get();
                if (str_filter.Is_Match(module_filter, module_name)) {
                    Cli_Output.Output_Str(module_name);
                    Cli_Output.Output_NewLine();
                    found = true;
                }
            }
        }
        if (!found) {
            Cli_Output.Output_Str(module_filter);
            Cli_Output.Output_Str(" - Not Found");
            Cli_Output.Output_NewLine();
        }
        return true;
    }

    virtual bool Execute(Cli_Cmd_ID cmd_id, Cli_Cmd *cmd, vector<Level_Description> &Levels, bool is_debug) {
        switch (cmd_id) {
            case CMD_ID_modules:
                if (is_debug) return true;
            {
                string module_filter = "*";
                return modules_by_filter_print(module_filter, Str_Filter);
            }
            case CMD_ID_modules_by_filter:
                if (is_debug) return true;
            {
                string module_filter = cmd->Items[1]->Value_Str;
                return modules_by_filter_print(module_filter, Str_Filter);
            }
            case CMD_ID_modules_by_filter_print:
                if (is_debug) return true;
            {
                string module_filter = cmd->Items[1]->Value_Str;
                return modules_by_filter_print(module_filter, Str_Filter);
            }
        }
        return false; // Not Implemented
    }

    virtual void To_Map(map<string, string> &values_map) {
    }

};

#endif /* CLI_MODULE_BASE_MODULES_H */
