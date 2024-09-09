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

#include <sstream>

using namespace std;

#include "Cli_Module.h"

#include "Cmd_Item_Base.h"
#include "Cmd_Item_Date.h"
#include "Cmd_Item_DateTime.h"
#include "Cmd_Item_Time.h"
#include "Cmd_Item_EQU.h"
#include "Cmd_Item_EQU_Range.h"
#include "Cmd_Item_IP4.h"
#include "Cmd_Item_IP6.h"
#include "Cmd_Item_Int.h"
#include "Cmd_Item_Int_List.h"
#include "Cmd_Item_Int_Range.h"
#include "Cmd_Item_MAC.h"
#include "Cmd_Item_Point_Var_Name.h"
#include "Cmd_Item_Rem.h"
#include "Cmd_Item_Str.h"
#include "Cmd_Item_Str_Esc.h"
#include "Cmd_Item_Word.h"
#include "Cmd_Item_Word_List.h"
#include "Cmd_Item_Word_Range.h"
#include "Cmd_Item_Assignment_Mark.h"

#include "Cli_Cmd_Privilege_ID.h"
#include "Cli_Modules.h"

#include "Str_Filter_Abstract.h"

#include "Cli_CMD_Processor.h"
#include "Cli_TAB_Processor.h"

class Cli_Module_Base_Modules : public Cli_Module {
protected:

    Cli_Modules &Modules;

    Str_Filter_Abstract &Str_Filter;

    Cli_Input_Abstract &Cli_Input;

    Cli_Output_Abstract &Cli_Output;

public:

    enum Local_Cmd_ID {
        CMD_ID_NO,

        CMD_ID_modules,
        CMD_ID_modules_by_filter,
        CMD_ID_modules_by_filter_print,
        CMD_ID_modules_by_filter_print_verbose,

        CMD_ID_LAST
    };

    virtual int Cmd_ID_Count_Get() {
        return CMD_ID_LAST - CMD_ID_NO - 1;
    }

    Cli_Module_Base_Modules(Cli_Modules &modules,
            Str_Filter_Abstract &str_filter,
            Cli_Input_Abstract &cli_input, Cli_Output_Abstract &cli_output) : Cli_Module("Base Modules"),
    Modules(modules),
    Str_Filter(str_filter), Cli_Input(cli_input), Cli_Output(cli_output) {
        Version = "0.03";
        {
            // modules
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_modules, CMD_PRIVILEGE_USER_DEF);
            cmd->Text_Set("modules");
            cmd->Help_Set("modules print (all)");
            cmd->Is_Global_Set(true);
            cmd->Level_Set("");
            cmd->Item_Add(new Cmd_Item_Word("modules", "modules print (all)"));
            Cmd_Add(cmd);
        }
        {
            // modules <module_name>
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_modules_by_filter, CMD_PRIVILEGE_USER_DEF);
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
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_modules_by_filter_print, CMD_PRIVILEGE_USER_DEF);
            cmd->Text_Set("modules <module_name> print");
            cmd->Help_Set("modules print (by filter)");
            cmd->Is_Global_Set(true);
            cmd->Level_Set("");
            cmd->Item_Add(new Cmd_Item_Word("modules", "modules"));
            cmd->Item_Add(new Cmd_Item_Str("<module_name>", "modules (by filter)"));
            cmd->Item_Add(new Cmd_Item_Word("print", "modules print (by filter)"));
            Cmd_Add(cmd);
        }
        {
            // modules <module_name> print verbose
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_modules_by_filter_print_verbose, CMD_PRIVILEGE_USER_DEF);
            cmd->Text_Set("modules <module_name> print verbose");
            cmd->Help_Set("modules print (by filter) verbose");
            cmd->Is_Global_Set(true);
            cmd->Level_Set("");
            cmd->Item_Add(new Cmd_Item_Word("modules", "modules"));
            cmd->Item_Add(new Cmd_Item_Str("<module_name>", "modules (by filter)"));
            cmd->Item_Add(new Cmd_Item_Word("print", "modules print (by filter)"));
            cmd->Item_Add(new Cmd_Item_Word("verbose", "modules print (by filter) verbose"));
            Cmd_Add(cmd);
        }
    }

    virtual ~Cli_Module_Base_Modules() {
    }

    void processors_print() {
        Cli_Cmd_Privilege_ID user_privilege = CMD_PRIVILEGE_ROOT_DEF;
        Cli_Modules modules;
        vector<Level_Description> levels;
        Cmd_Token_Parser parser;
        string str_rem = "$";
        Cli_CMD_Processor CMD_Processor(user_privilege, modules, levels, parser, Cli_Input, Cli_Output, str_rem);
        bool log_is_active = false;
        Cli_TAB_Processor TAB_Processor(user_privilege, modules, levels, parser, Cli_Input, Cli_Output, str_rem, log_is_active);
        stringstream s_str;
        s_str << "Processors[" << 2 << "]:";
        Cli_Output.Output_Str(s_str.str());
        Cli_Output.Output_NewLine();
        Cli_Output.Output_NewLine();

        {
            string type = CMD_Processor.Type_Get();
            string version = CMD_Processor.Version_Get();
            Cli_Output.Output_Str(type);
            Cli_Output.Output_Str(" V");
            Cli_Output.Output_Str(version);
            Cli_Output.Output_NewLine();
        }

        {
            string type = TAB_Processor.Type_Get();
            string version = TAB_Processor.Version_Get();
            Cli_Output.Output_Str(type);
            Cli_Output.Output_Str(" V");
            Cli_Output.Output_Str(version);
            Cli_Output.Output_NewLine();
        }

        Cli_Output.Output_NewLine();
    }

    void filters_print() {
        string type = Str_Filter.Type_Get();
        string version = Str_Filter.Version_Get();
        Cli_Output.Output_Str(type);
        Cli_Output.Output_Str(" V");
        Cli_Output.Output_Str(version);
        Cli_Output.Output_NewLine();
        Cli_Output.Output_NewLine();
    }

    void cmd_items_print(string module_filter, Str_Filter_Abstract &str_filter) {
        vector<Cmd_Item_Base *> items;
        vector<string> words;
        items.push_back(new Cmd_Item_Base("", ""));
        items.push_back(new Cmd_Item_Date("", ""));
        items.push_back(new Cmd_Item_DateTime("", ""));
        items.push_back(new Cmd_Item_Time("", ""));
        items.push_back(new Cmd_Item_EQU("", ""));
        items.push_back(new Cmd_Item_EQU_Range("", "", words));
        items.push_back(new Cmd_Item_IP4("", ""));
        items.push_back(new Cmd_Item_IP6("", ""));
        items.push_back(new Cmd_Item_Int("", ""));
        items.push_back(new Cmd_Item_Int_List(1, 8, "", ""));
        items.push_back(new Cmd_Item_Int_Range(1, 8, "", ""));
        items.push_back(new Cmd_Item_MAC("", ""));
        items.push_back(new Cmd_Item_Point_Var_Name("", ""));
        items.push_back(new Cmd_Item_Rem("", ""));
        items.push_back(new Cmd_Item_Str("", ""));
        items.push_back(new Cmd_Item_Str_Esc("", ""));
        items.push_back(new Cmd_Item_Word("", ""));
        items.push_back(new Cmd_Item_Word_List("", "", words));
        items.push_back(new Cmd_Item_Word_Range("", "", words));
        items.push_back(new Cmd_Item_Assignment_Mark("", ""));

        bool found = false;
        for (int i = 0; i < items.size(); i++) {
            Cmd_Item_Base *item = items[i];
            string type = item->Type_Get();
            if (str_filter.Is_Match(module_filter, type)) {
                found = true;
                break;
            }
        }

        if (found) {
            stringstream s_str;
            s_str << "Cmd Items[" << items.size() << "]:";
            Cli_Output.Output_Str(s_str.str());
            Cli_Output.Output_NewLine();
            Cli_Output.Output_NewLine();
            for (int i = 0; i < items.size(); i++) {
                Cmd_Item_Base *item = items[i];
                string type = item->Type_Get();
                if (str_filter.Is_Match(module_filter, type)) {
                    string version = item->Version_Get();
                    Cli_Output.Output_Str(type);
                    Cli_Output.Output_Str(" V");
                    Cli_Output.Output_Str(version);
                    Cli_Output.Output_NewLine();
                }
            }
        }
    }

    bool modules_by_filter_print(string module_filter, Str_Filter_Abstract &str_filter, bool is_verbose) {
        Cli_Output.Output_NewLine();
        bool found = false;
        if (is_verbose) {
            stringstream s_str;
            s_str << "Modules[" << Modules.Get_Size() << "]:";
            Cli_Output.Output_Str(s_str.str());
            Cli_Output.Output_NewLine();
            Cli_Output.Output_NewLine();
        }
        for (int module = 0; module < Modules.Get_Size(); module++) {
            Cli_Module *module_ptr = Modules.Get(module);
            if (module_ptr) {
                string module_name = module_ptr->Name_Get();
                string module_name_with_commas = "\"" + module_ptr->Name_Get() + "\"";
                if (str_filter.Is_Match(module_filter, module_name)
                        || str_filter.Is_Match(module_filter, module_name_with_commas)) {
                    if (!is_verbose) {
                        Cli_Output.Output_Str(module_name);
                    } else {
                        Cli_Output.Output_Str(module_name + " V" + module_ptr->Version_Get());
                    }
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

    virtual bool Execute(Cli_Cmd *cmd, vector<Level_Description> &Levels, bool is_debug) {
        enum Local_Cmd_ID cmd_id = (enum Local_Cmd_ID)cmd->ID_Get();
        switch (cmd_id) {
            case CMD_ID_modules:
                if (is_debug) return true;
            {
                string module_filter = "*";
                bool is_verbose;
                return modules_by_filter_print(module_filter, Str_Filter, is_verbose = false);
            }
            case CMD_ID_modules_by_filter:
                if (is_debug) return true;
            {
                string module_filter = cmd->Items[1]->Value_Str;
                bool is_verbose;
                return modules_by_filter_print(module_filter, Str_Filter, is_verbose = false);
            }
            case CMD_ID_modules_by_filter_print:
                if (is_debug) return true;
            {
                string module_filter = cmd->Items[1]->Value_Str;
                bool is_verbose;
                return modules_by_filter_print(module_filter, Str_Filter, is_verbose = false);
            }
            case CMD_ID_modules_by_filter_print_verbose:
                if (is_debug) return true;
            {
                string module_filter = cmd->Items[1]->Value_Str;
                bool is_verbose;
                Cli_Output.Output_NewLine();
                processors_print();
                filters_print();
                cmd_items_print(module_filter, Str_Filter);
                return modules_by_filter_print(module_filter, Str_Filter, is_verbose = true);
            }

            default:
                return false; // Not Implemented

        }
        return false; // Not Implemented
    }

    virtual void To_Map(map<string, string> &values_map) {
    }

};

#endif /* CLI_MODULE_BASE_MODULES_H */
