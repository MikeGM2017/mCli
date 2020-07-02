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

#include "Cli_Module.h"

#include "Cmd_Item_Word.h"
#include "Cmd_Item_Str.h"

#include "Cli_Modules.h"

#include "Str_Filter_Abstract.h"

class Cli_Module_Base_Help : public Cli_Module {
protected:

    int User_Privilege;

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
        CMD_ID_help_command_all,
        CMD_ID_help_command_verbose,
        CMD_ID_help_command_all_verbose,

        CMD_ID_help_module_module_name,
        CMD_ID_help_module_module_name_verbose,

        CMD_ID_LAST
    };

    virtual int Cmd_ID_Count_Get() {
        return CMD_ID_LAST - CMD_ID_NO - 1;
    }

    Cli_Module_Base_Help(int user_privilege,
            Cli_Modules &cli_modules,
            Str_Filter_Abstract &help_str_filter,
            Cli_Output_Abstract &cli_output) : Cli_Module("Base Help"),
    User_Privilege(user_privilege),
    Modules(cli_modules),
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

    static int Help_Cli_Modules_Get_Len(int user_privilege, Cli_Modules &Cli_Modules,
            string Level, bool is_verbose, string module_filter, string command_filter, Str_Filter_Abstract &str_filter) {
        int len_max = 0;

        for (int module = 0; module < Cli_Modules.Get_Size(); module++) {
            Cli_Module *climodule_ptr = Cli_Modules.Get(module);
            if (str_filter.Is_Match(module_filter, climodule_ptr->Name_Get())) {
                for (int cmd = 0; cmd < climodule_ptr->Module_Cmd_List.size(); cmd++) {
                    Cli_Cmd *cmd_ptr = climodule_ptr->Module_Cmd_List[cmd];
                    if (
                            (cmd_ptr->Is_Global_Get() || (cmd_ptr->Level_Get() == Level))
                            && (user_privilege <= cmd_ptr->Privilege_Get())
                            && str_filter.Is_Match(command_filter, cmd_ptr->Items[0]->Text_Get())
                            ) {
                        int len = 0;
                        if (Level.size() == 0) {
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

    static void Help_Cli_Modules_Print(int user_privilege, Cli_Modules &CliModules,
            string Level, bool is_verbose, string module_filter, string command_filter, Str_Filter_Abstract &str_filter,
            int len_max, int &modules_count, int &commands_count,
            Cli_Output_Abstract &Cli_Output) {

        Cli_Output.Output_NewLine();

        for (int module = 0; module < CliModules.Get_Size(); module++) {
            Cli_Module *climodule_ptr = CliModules.Get(module);
            if (str_filter.Is_Match(module_filter, climodule_ptr->Name_Get())) {
                modules_count++;
                for (int cmd = 0; cmd < climodule_ptr->Module_Cmd_List.size(); cmd++) {
                    Cli_Cmd *cmd_ptr = climodule_ptr->Module_Cmd_List[cmd];
                    string s;
                    stringstream s_str1;
                    stringstream s_str2;
                    if (Level.size() == 0) {
                        string s_level = cmd_ptr->Level_Get();
                        if (s_level.size() > 0) {
                            s += "[" + s_level + "] ";
                            s_str1 << "[" << s_level << "] ";
                        }
                    }
                    s += cmd_ptr->Text_Get();
                    s_str1 << cmd_ptr->Text_Get();
                    if (
                            (cmd_ptr->Is_Global_Get() || (cmd_ptr->Level_Get() == Level))
                            && (user_privilege <= cmd_ptr->Privilege_Get())
                            && str_filter.Is_Match(command_filter, cmd_ptr->Items[0]->Text_Get())
                            ) {
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

    void help(string Level, bool is_verbose, string module_filter, string command_filter, Cli_Output_Abstract &Cli_Output) {
        int modules_count = 0;
        int commands_count = 0;
        int len_max = 0;
        int len;

        len = Help_Cli_Modules_Get_Len(User_Privilege, Modules, Level, is_verbose, module_filter, command_filter, Help_Str_Filter);
        if (len_max < len)
            len_max = len;

        Help_Cli_Modules_Print(User_Privilege, Modules, Level,
                is_verbose, module_filter, command_filter, Help_Str_Filter,
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

    virtual bool Execute(Cli_Cmd_ID cmd_id, Cli_Cmd *cmd, vector<Level_Description> &Levels, bool is_debug) {
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
                bool is_verbose = false;
                string module_filter = "*";
                string command_filter = "*";
                help(level.Level, is_verbose, module_filter, command_filter, Cli_Output);
            }
                return true;
            case CMD_ID_help_command:
                if (is_debug) return true;
            {
                bool is_verbose = false;
                string module_filter = "*";
                string command_filter = cmd->Items[1]->Value_Str;
                help(level.Level, is_verbose, module_filter, command_filter, Cli_Output);
            }
                return true;
            case CMD_ID_help_command_verbose:
                if (is_debug) return true;
            {
                bool is_verbose = true;
                string module_filter = "*";
                string command_filter = cmd->Items[1]->Value_Str;
                help(level.Level, is_verbose, module_filter, command_filter, Cli_Output);
            }
                return true;

            case CMD_ID_help_module_module_name:
                if (is_debug) return true;
            {
                bool is_verbose = false;
                string module_filter = cmd->Items[2]->Value_Str;
                string command_filter = "*";
                help(level.Level, is_verbose, module_filter, command_filter, Cli_Output);
            }
                return true;
            case CMD_ID_help_module_module_name_verbose:
                if (is_debug) return true;
            {
                bool is_verbose = true;
                string module_filter = cmd->Items[2]->Value_Str;
                string command_filter = "*";
                help(level.Level, is_verbose, module_filter, command_filter, Cli_Output);
            }
                return true;

        }
        return false; // Not Implemented
    }

    virtual void To_Map(map<string, string> &values_map) {
        // Nothing
    }

};

#endif /* CLIMODULE_BASE_HELP_H */
