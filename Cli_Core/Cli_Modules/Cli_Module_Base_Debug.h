/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_Module_Base_Debug.h
 * Author: mike
 *
 * Created on July 20, 2020, 4:18 PM
 */

#ifndef CLI_MODULE_BASE_DEBUG_H
#define CLI_MODULE_BASE_DEBUG_H

#include <sstream>

using namespace std;

#include "Cli_Module.h"

#include "Cli_Output_Abstract.h"

#include "Cli_CMD_Processor_Abstract.h"

class Cli_Module_Base_Debug : public Cli_Module {
protected:

    Cli_Cmd_Privilege_ID User_Privilege;
    Cli_Modules &Modules;

    vector<Level_Description> &Levels;

    Cli_CMD_Processor_Abstract &CMD_Processor;

    Cli_Output_Abstract &Cli_Output;

public:

    enum Local_CmdID {
        CMD_ID_NO,

        CMD_ID_debug_cli,
        CMD_ID_debug_cli_counts,
        CMD_ID_debug_cli_verbose,
        CMD_ID_debug_cli_verbose_failed,

        CMD_ID_LAST
    };

    virtual int Cmd_ID_Count_Get() {
        return CMD_ID_LAST - CMD_ID_NO - 1;
    }

    Cli_Module_Base_Debug(Cli_Cmd_Privilege_ID user_privilege, Cli_Modules &modules,
            vector<Level_Description> &levels, Cli_CMD_Processor_Abstract &cmd_processor,
            Cli_Output_Abstract &cli_output) : Cli_Module("Base Debug"),
    User_Privilege(user_privilege), Modules(modules),
    Levels(levels), CMD_Processor(cmd_processor),
    Cli_Output(cli_output) {
        {
            // debug cli
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_debug_cli);
            cmd->Text_Set("debug cli");
            cmd->Help_Set("debug cli");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("debug", "debug"));
            cmd->Item_Add(new Cmd_Item_Word("cli", "debug cli"));
            Cmd_Add(cmd);
        }
        {
            // debug cli
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_debug_cli_counts);
            cmd->Text_Set("debug cli counts");
            cmd->Help_Set("debug cli counts");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("debug", "debug"));
            cmd->Item_Add(new Cmd_Item_Word("cli", "debug cli"));
            cmd->Item_Add(new Cmd_Item_Word("counts", "debug cli counts"));
            Cmd_Add(cmd);
        }
        {
            // debug cli verbose
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_debug_cli_verbose);
            cmd->Text_Set("debug cli verbose");
            cmd->Help_Set("debug cli verbose");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("debug", "debug"));
            cmd->Item_Add(new Cmd_Item_Word("cli", "debug cli"));
            cmd->Item_Add(new Cmd_Item_Word("verbose", "show all information"));
            Cmd_Add(cmd);
        }
        {
            // debug cli verbose failed
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_debug_cli_verbose_failed);
            cmd->Text_Set("debug cli verbose failed");
            cmd->Help_Set("debug cli verbose failed");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("debug", "debug"));
            cmd->Item_Add(new Cmd_Item_Word("cli", "debug cli"));
            cmd->Item_Add(new Cmd_Item_Word("verbose", "show all information"));
            cmd->Item_Add(new Cmd_Item_Word("failed", "show all information (failed only)"));
            Cmd_Add(cmd);
        }
    }

    virtual ~Cli_Module_Base_Debug() {
    }

    string Str_Trim(string s) {
        int pos_beg = 0;
        int pos_end = s.size() - 1;
        while (pos_beg < s.size() && (s[pos_beg] == ' ' || s[pos_beg] == '\t' || s[pos_beg] == '\r' || s[pos_beg] == '\n')) pos_beg++;
        while (pos_end - 1 > pos_beg && (s[pos_end] == ' ' || s[pos_end] == '\t' || s[pos_end] == '\r' || s[pos_end] == '\n')) pos_end--;
        string s_trim = s.substr(pos_beg, pos_end - pos_beg + 1);
        return s_trim;
    }

    void Debug_Cli_Modules(bool is_counts, bool is_verbose, bool is_failed_only,
            int &total_count_cmd_id,
            int &total_count,
            int &total_count_checked,
            int &total_count_passed,
            int &total_count_failed) {
        bool is_debug = true;
        bool debug_res = false;
        for (int module = 0; module < Modules.Get_Size(); module++) {
            Cli_Module *module_ptr = Modules.Get(module);
            total_count_cmd_id += module_ptr->Cmd_ID_Count_Get();
            if (is_counts) {
                stringstream s_str;
                s_str << "Module: " << module_ptr->Name_Get() << " id_cnt=" << module_ptr->Cmd_ID_Count_Get();
                Cli_Output.Output_Str(s_str.str());
                Cli_Output.Output_NewLine();
            }
            total_count += module_ptr->Cmd_Count_Get();
            if (is_counts) {
                stringstream s_str;
                s_str << "Module: " << module_ptr->Name_Get() << " cmd_cnt=" << module_ptr->Cmd_Count_Get();
                Cli_Output.Output_Str(s_str.str());
                Cli_Output.Output_NewLine();
            }
            for (int cmd = 0; cmd < module_ptr->Module_Cmd_List.size(); cmd++) {
                Cli_Cmd *cmd_ptr = module_ptr->Module_Cmd_List[cmd];
                string s;
                for (int item = 0; item < cmd_ptr->Items.size(); item++) {
                    Cmd_Item_Base *item_ptr = cmd_ptr->Items[item];
                    if (item == 0)
                        s = item_ptr->Debug_Value_Get();
                    else
                        s += " " + item_ptr->Debug_Value_Get();
                }
                string level = cmd_ptr->Level_Get();
                Levels.clear();
                string s_trim = Str_Trim(s);
                Cli_Input_Item input_item(CLI_INPUT_ITEM_TYPE_STR, s_trim);
                if (level.size() == 0) {
                    debug_res = false;
                    CMD_Processor.Process_Input_Item(input_item, is_debug, debug_res);
                    if (is_verbose) {
                        if (!is_failed_only || (is_failed_only && !debug_res)) {
                            Cli_Output.Output_Str(s + " - " + (debug_res ? "Ok" : "Failed"));
                            Cli_Output.Output_NewLine();
                        }
                    }
                } else {
                    Levels.push_back(Level_Description(level));
                    debug_res = false;
                    CMD_Processor.Process_Input_Item(input_item, is_debug, debug_res);
                    if (is_verbose) {
                        if (!is_failed_only || (is_failed_only && !debug_res)) {
                            Cli_Output.Output_Str("[" + cmd_ptr->Level_Get() + "] " + s + " - " + (debug_res ? "Ok" : "Failed"));
                            Cli_Output.Output_NewLine();
                        }
                    }
                }
                total_count_checked++;
                if (debug_res)
                    total_count_passed++;

                else
                    total_count_failed++;
            }
        }
    }

    bool debug_cli(bool is_counts, bool is_verbose, bool is_failed_only) {
        int total_count_cmd_id = 0;
        int total_count = 0;
        int total_count_checked = 0;
        int total_count_passed = 0;
        int total_count_failed = 0;
        Cli_Output.Output_NewLine();
        Debug_Cli_Modules(is_counts, is_verbose, is_failed_only,
                total_count_cmd_id,
                total_count,
                total_count_checked,
                total_count_passed,
                total_count_failed);
        stringstream s_str;
        s_str << "Debug Cli Result:"
                << " id_cnt:" << total_count_cmd_id
                << " total:" << total_count
                << " checked:" << total_count_checked
                << " passed:" << total_count_passed
                << " failed:" << total_count_failed;
        Cli_Output.Output_Str(s_str.str());
        Cli_Output.Output_NewLine();
        Levels.clear();

        return true;
    }

    virtual bool Execute(Cli_Cmd_ID cmd_id, Cli_Cmd *cmd, vector<Level_Description> &Levels, bool is_debug) {
        switch (cmd_id) {
            case CMD_ID_debug_cli:
                if (is_debug) return true;
            {
                bool is_counts = false;
                bool is_verbose = false;
                bool is_failed_only = false;
                return debug_cli(is_counts, is_verbose, is_failed_only);
            }
                break;
            case CMD_ID_debug_cli_counts:
                if (is_debug) return true;
            {
                bool is_counts = true;
                bool is_verbose = false;
                bool is_failed_only = false;
                return debug_cli(is_counts, is_verbose, is_failed_only);
            }
                break;
            case CMD_ID_debug_cli_verbose:
                if (is_debug) return true;
            {
                bool is_counts = false;
                bool is_verbose = true;
                bool is_failed_only = false;
                return debug_cli(is_counts, is_verbose, is_failed_only);
            }
                break;
            case CMD_ID_debug_cli_verbose_failed:
                if (is_debug) return true;
            {
                bool is_counts = false;
                bool is_verbose = true;
                bool is_failed_only = true;

                return debug_cli(is_counts, is_verbose, is_failed_only);
            }
                break;
        }
        return false; // Not Implemented
    }

    virtual void To_Map(map<string, string> &values_map) {
        // Nothing
    }

};

#endif /* CLI_MODULE_BASE_DEBUG_H */
