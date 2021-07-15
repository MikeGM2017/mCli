/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_Module_Base_Help.h
 * Author: mike
 *
 * Created on June 28, 2019, 7:30 PM
 */

#ifndef CLI_MODULE_BASE_HELP_H
#define CLI_MODULE_BASE_HELP_H

#include <sstream>

using namespace std;

#include "Cli_Module.h"

#include "Cmd_Item_Word.h"
#include "Cmd_Item_Str.h"

#include "Cli_Cmd_Privilege_ID.h"
#include "Cli_Modules.h"

#include "Str_Filter_Abstract.h"

class Cli_Module_Base_Help : public Cli_Module {
protected:

    Cli_Cmd_Privilege_ID User_Privilege;
    Cli_Modules &Modules;

    Str_Filter_Abstract &Help_Str_Filter;

    Cli_Output_Abstract &Cli_Output;

public:

    enum Local_Cmd_ID {
        CMD_ID_NO,

        CMD_ID_help_H,
        CMD_ID_help,
        CMD_ID_help_full,
        CMD_ID_help_full_verbose,
        CMD_ID_help_command,
        CMD_ID_help_command_verbose,

        CMD_ID_help_module_module_name,
        CMD_ID_help_module_module_name_verbose,

        CMD_ID_LAST
    };

    virtual int Cmd_ID_Count_Get() {
        return CMD_ID_LAST - CMD_ID_NO - 1;
    }

    Cli_Module_Base_Help(Cli_Cmd_Privilege_ID user_privilege, Cli_Modules &modules,
            Str_Filter_Abstract &help_str_filter,
            Cli_Output_Abstract &cli_output) : Cli_Module("Base Help"),
    User_Privilege(user_privilege), Modules(modules),
    Help_Str_Filter(help_str_filter),
    Cli_Output(cli_output) {
        {
            // H - help
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_help_H);
            cmd->Text_Set("H");
            cmd->Help_Set("show help");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("H", "show help"));
            Cmd_Add(cmd);
        }
        {
            // help
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_help);
            cmd->Text_Set("help");
            cmd->Help_Set("show help");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("help", "show help"));
            Cmd_Add(cmd);
        }

        {
            // help full
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_help_full);
            cmd->Text_Set("help full");
            cmd->Help_Set("show all commands");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("help", "show help"));
            cmd->Item_Add(new Cmd_Item_Word("full", "show all commands"));
            Cmd_Add(cmd);
        }
        {
            // help full verbose
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_help_full_verbose);
            cmd->Text_Set("help full verbose");
            cmd->Help_Set("show all commands with arguments information");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("help", "show help"));
            cmd->Item_Add(new Cmd_Item_Word("full", "show all commands"));
            cmd->Item_Add(new Cmd_Item_Word("verbose", "show all arguments information"));
            Cmd_Add(cmd);
        }

        {
            // help "<command>"
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_help_command);
            cmd->Text_Set("help \"<command>\"");
            cmd->Help_Set("show selected commands (by filter)");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("help", "show help"));
            cmd->Item_Add(new Cmd_Item_Str("\"<command>\"", "command about which need to obtain information (by filter)"));
            Cmd_Add(cmd);
        }
        {
            // help "<command>" verbose
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_help_command_verbose);
            cmd->Text_Set("help \"<command>\" verbose");
            cmd->Help_Set("show selected commands (by filter) with arguments information");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("help", "show help"));
            cmd->Item_Add(new Cmd_Item_Str("\"<command>\"", "command about which need to obtain information (by filter)"));
            cmd->Item_Add(new Cmd_Item_Word("verbose", "show all arguments information"));
            Cmd_Add(cmd);
        }

        {
            // help module "<module_name>"
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_help_module_module_name);
            cmd->Text_Set("help module \"<module_name>\"");
            cmd->Help_Set("show module commands (modules by filter)");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("help", "show help"));
            cmd->Item_Add(new Cmd_Item_Word("module", "show module commands (modules by filter)"));
            cmd->Item_Add(new Cmd_Item_Str("\"<module_name>\"", "modules about which need to obtain information (by filter)"));
            Cmd_Add(cmd);
        }
        {
            // help module "<module_name>" verbose
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_help_module_module_name_verbose);
            cmd->Text_Set("help module \"<module_name>\" verbose");
            cmd->Help_Set("show module commands (modules by filter) with arguments information");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("help", "show help"));
            cmd->Item_Add(new Cmd_Item_Word("module", "show module commands (modules by filter)"));
            cmd->Item_Add(new Cmd_Item_Str("\"<module_name>\"", "modules about which need to obtain information (by filter)"));
            cmd->Item_Add(new Cmd_Item_Word("verbose", "show all arguments information"));
            Cmd_Add(cmd);
        }

    }

    virtual ~Cli_Module_Base_Help() {
    }

    virtual bool HELP_Cmd_Ptr_Check_By_Level(Cli_Cmd *cmd_ptr, Cli_Cmd_Privilege_ID user_privilege, string level,
            bool is_full, bool is_module_full) {
        if (cmd_ptr && user_privilege <= cmd_ptr->Privilege_Get()) {
            if (is_full) return true;
            if (is_module_full) return true;
            if (cmd_ptr->Is_Global_Get()) return true;
            if (cmd_ptr->Level_Get() == level) return true;
        }
        return false;
    }

    virtual int Help_Cli_Modules_Get_Len(int user_privilege, Cli_Modules &modules,
            string level,
            bool is_full, bool is_verbose, bool is_module_full,
            string module_filter, string command_filter, Str_Filter_Abstract &str_filter) {
        int len_max = 0;

        for (int module = 0; module < modules.Get_Size(); module++) {
            Cli_Module *module_ptr = modules.Get(module);
            if (is_full || str_filter.Is_Match(module_filter, module_ptr->Name_Get())) {
                for (int cmd = 0; cmd < module_ptr->Module_Cmd_List.size(); cmd++) {
                    Cli_Cmd *cmd_ptr = module_ptr->Module_Cmd_List[cmd];
                    bool is_cmd_prt_valid = HELP_Cmd_Ptr_Check_By_Level(cmd_ptr, User_Privilege, level, is_full, is_module_full);
                    if (is_cmd_prt_valid && str_filter.Is_Match(command_filter, cmd_ptr->Items[0]->Text_Get())) {
                        int len = 0;
                        if (level.size() == 0) {
                            int len_level = cmd_ptr->Level_Get().size();
                            if (len_level > 0)
                                len += len_level + 3; // "[" + ... + "] " - OnHelp_CliModules(...)
                        }
                        len += cmd_ptr->Text_Get().size();
                        if (len_max < len)
                            len_max = len;
                        if (is_verbose) {
                            for (int i = 0; i < cmd_ptr->Items.size(); i++) {
                                Cmd_Item_Base *item = cmd_ptr->Items[i];
                                len = 1 + item->Text_Get().size(); // " " + ...
                                if (len_max < len)
                                    len_max = len;
                            }
                        }
                    }
                }
            }
        }

        return len_max;
    }

    virtual void Help_Cli_Modules_Print_V01(int user_privilege, Cli_Modules &modules,
            string level,
            bool is_full, bool is_verbose, bool is_module_full,
            string module_filter, string command_filter, Str_Filter_Abstract &str_filter,
            int len_max, int &modules_count, int &commands_count,
            Cli_Output_Abstract &Cli_Output) {

        Cli_Output.Output_NewLine();

        for (int module = 0; module < modules.Get_Size(); module++) {
            Cli_Module *module_ptr = modules.Get(module);
            if (is_full || str_filter.Is_Match(module_filter, module_ptr->Name_Get())) {
                modules_count++;
                for (int cmd = 0; cmd < module_ptr->Module_Cmd_List.size(); cmd++) {
                    Cli_Cmd *cmd_ptr = module_ptr->Module_Cmd_List[cmd];
                    string s;
                    stringstream s_str1;
                    stringstream s_str2;
                    if (level.size() == 0) {
                        string s_level = cmd_ptr->Level_Get();
                        if (s_level.size() > 0) {
                            s += "[" + s_level + "] ";
                            s_str1 << "[" << s_level << "] ";
                        }
                    }
                    s += cmd_ptr->Text_Get();
                    s_str1 << cmd_ptr->Text_Get();
                    bool is_cmd_prt_valid = HELP_Cmd_Ptr_Check_By_Level(cmd_ptr, User_Privilege, level, is_full, is_module_full);
                    if (is_cmd_prt_valid && str_filter.Is_Match(command_filter, cmd_ptr->Items[0]->Text_Get())) {
                        s_str2 << setw(len_max) << left << s_str1.str() << " - " << cmd_ptr->Help_Get();
                        Cli_Output.Output_Str(s_str2.str());
                        Cli_Output.Output_NewLine();
                        commands_count++;
                        if (is_verbose) {
                            for (int i = 0; i < cmd_ptr->Items.size(); i++) {
                                Cmd_Item_Base *item = cmd_ptr->Items[i];
                                stringstream s_str3;
                                stringstream s_str4;
                                s_str3 << " " << item->Text_Get();
                                s_str4 << setw(len_max) << left << s_str3.str() << " - " << item->Help_Get();
                                Cli_Output.Output_Str(s_str4.str());
                                Cli_Output.Output_NewLine();
                            }
                        }
                    }
                }
            }
        }
    }

    virtual void Help_Cli_Modules_Print(int user_privilege, Cli_Modules &modules,
            string level,
            bool is_full, bool is_verbose, bool is_module_full,
            string module_filter, string command_filter, Str_Filter_Abstract &str_filter,
            int len_max, int &modules_count, int &commands_count,
            Cli_Output_Abstract &Cli_Output) {
        
        stringstream s_str;

        //Cli_Output.Output_NewLine();
        s_str << endl;

        for (int module = 0; module < modules.Get_Size(); module++) {
            Cli_Module *module_ptr = modules.Get(module);
            if (is_full || str_filter.Is_Match(module_filter, module_ptr->Name_Get())) {
                modules_count++;
                for (int cmd = 0; cmd < module_ptr->Module_Cmd_List.size(); cmd++) {
                    Cli_Cmd *cmd_ptr = module_ptr->Module_Cmd_List[cmd];
                    string s;
                    stringstream s_str1;
                    stringstream s_str2;
                    if (level.size() == 0) {
                        string s_level = cmd_ptr->Level_Get();
                        if (s_level.size() > 0) {
                            s += "[" + s_level + "] ";
                            s_str1 << "[" << s_level << "] ";
                        }
                    }
                    s += cmd_ptr->Text_Get();
                    s_str1 << cmd_ptr->Text_Get();
                    bool is_cmd_prt_valid = HELP_Cmd_Ptr_Check_By_Level(cmd_ptr, User_Privilege, level, is_full, is_module_full);
                    if (is_cmd_prt_valid && str_filter.Is_Match(command_filter, cmd_ptr->Items[0]->Text_Get())) {
                        s_str2 << setw(len_max) << left << s_str1.str() << " - " << cmd_ptr->Help_Get();
                        //Cli_Output.Output_Str(s_str2.str());
                        //Cli_Output.Output_NewLine();
                        s_str << s_str2.str() << endl;
                        commands_count++;
                        if (is_verbose && cmd_ptr->Items.size() > 1) {
                            for (int i = 1; i < cmd_ptr->Items.size(); i++) {
                                Cmd_Item_Base *item = cmd_ptr->Items[i];
                                stringstream s_str3;
                                stringstream s_str4;
                                s_str3 << " " << item->Text_Get();
                                s_str4 << setw(len_max) << left << s_str3.str() << " - " << item->Help_Get();
                                //Cli_Output.Output_Str(s_str4.str());
                                //Cli_Output.Output_NewLine();
                                s_str << s_str4.str() << endl;
                            }
                        }
                    }
                }
            }
        }
        
        Cli_Output.Output_Str(s_str.str());
        
    }

    void help(string level, bool is_full, bool is_verbose, bool is_module_full,
            string module_filter, string command_filter, Cli_Output_Abstract &Cli_Output) {
        int modules_count = 0;
        int commands_count = 0;
        int len_max = 0;
        int len;

        len = Help_Cli_Modules_Get_Len(User_Privilege, Modules, level,
                is_full, is_verbose, is_module_full,
                module_filter, command_filter, Help_Str_Filter);
        if (len_max < len)
            len_max = len;

        Help_Cli_Modules_Print(User_Privilege, Modules, level,
                is_full, is_verbose, is_module_full,
                module_filter, command_filter, Help_Str_Filter,
                len_max, modules_count, commands_count,
                Cli_Output);

        if (modules_count == 0) {
            Cli_Output.Output_Str("modules \"");
            Cli_Output.Output_Str(module_filter);
            Cli_Output.Output_Str("\" - not found");
            Cli_Output.Output_NewLine();
        } else if (commands_count == 0) {
            Cli_Output.Output_Str("commands \"");
            Cli_Output.Output_Str(command_filter);
            Cli_Output.Output_Str("\" - not found");
            Cli_Output.Output_NewLine();
        }

    }

    virtual bool Execute(Cli_Cmd *cmd, vector<Level_Description> &Levels, bool is_debug) {
        enum Local_Cmd_ID cmd_id = (enum Local_Cmd_ID)cmd->ID_Get();
        Level_Description level;
        string parameter;
        if (Levels.size() > 0) {
            level = Levels.back();
            parameter = level.Parameter;
        }
        switch (cmd_id) {
            case CMD_ID_help_H:
            case CMD_ID_help:
                if (is_debug) return true;
            {
                bool is_full = false;
                bool is_verbose = false;
                bool is_module_full = false;
                string module_filter = "*";
                string command_filter = "*";
                help(level.Level, is_full, is_verbose, is_module_full, module_filter, command_filter, Cli_Output);
            }
                return true;

            case CMD_ID_help_full:
                if (is_debug) return true;
            {
                bool is_full = true;
                bool is_verbose = false;
                bool is_module_full = false;
                string module_filter = "*";
                string command_filter = "*";
                help(level.Level, is_full, is_verbose, is_module_full, module_filter, command_filter, Cli_Output);
            }
                return true;
            case CMD_ID_help_full_verbose:
                if (is_debug) return true;
            {
                bool is_full = true;
                bool is_verbose = true;
                bool is_module_full = false;
                string module_filter = "*";
                string command_filter = "*";
                help(level.Level, is_full, is_verbose, is_module_full, module_filter, command_filter, Cli_Output);
            }
                return true;

            case CMD_ID_help_command:
                if (is_debug) return true;
            {
                bool is_full = false;
                bool is_verbose = false;
                bool is_module_full = false;
                string module_filter = "*";
                string command_filter = cmd->Items[1]->Value_Str;
                help(level.Level, is_full, is_verbose, is_module_full, module_filter, command_filter, Cli_Output);
            }
                return true;
            case CMD_ID_help_command_verbose:
                if (is_debug) return true;
            {
                bool is_full = false;
                bool is_verbose = true;
                bool is_module_full = false;
                string module_filter = "*";
                string command_filter = cmd->Items[1]->Value_Str;
                help(level.Level, is_full, is_verbose, is_module_full, module_filter, command_filter, Cli_Output);
            }
                return true;

            case CMD_ID_help_module_module_name:
                if (is_debug) return true;
            {
                bool is_full = false;
                bool is_verbose = false;
                bool is_module_full = true;
                string module_filter = cmd->Items[2]->Value_Str;
                string command_filter = "*";
                help(level.Level, is_full, is_verbose, is_module_full, module_filter, command_filter, Cli_Output);
            }
                return true;
            case CMD_ID_help_module_module_name_verbose:
                if (is_debug) return true;
            {
                bool is_full = false;
                bool is_verbose = true;
                bool is_module_full = true;
                string module_filter = cmd->Items[2]->Value_Str;
                string command_filter = "*";
                help(level.Level, is_full, is_verbose, is_module_full, module_filter, command_filter, Cli_Output);
            }
                return true;

            default:
                return false; // Not Implemented

        }
        return false; // Not Implemented
    }

    virtual void To_Map(map<string, string> &values_map) {
        // Nothing
    }

};

#endif /* CLIMODULE_BASE_HELP_H */
