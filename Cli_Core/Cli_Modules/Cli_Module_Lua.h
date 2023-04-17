/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_Module_Lua.h
 * Author: mike
 *
 * Created on April 10, 2023, 9:10 AM
 */

#ifndef CLI_MODULE_LUA_H
#define CLI_MODULE_LUA_H

#include "Cli_Module.h"

#include "Cmd_Item_Word.h"
#include "Cmd_Item_Str.h"

#include "Str_Filter_Abstract.h"
#include "Cli_Modules/Str_Filter.h"
#include "Cli_Output/Cli_Output_Abstract.h"

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

class Cli_Module_Lua : public Cli_Module {
protected:

    map<string, string> &Values_Map;

    Str_Filter_Abstract &Str_Filter;

    Cli_Input_Abstract &Cli_Input;
    Cli_Output_Abstract &Cli_Output;

    string Parent_Level;
    string New_Level;

    lua_State *L;
    set<string> Lua_System_Objects;

public:

    enum Local_Cmd_ID {
        CMD_ID_NO,

        CMD_ID_lua,
        CMD_ID_end,

        CMD_ID_lua_vars,
        CMD_ID_lua_vars_print,
        CMD_ID_lua_vars_print_strfilter,
        CMD_ID_lua_vars_to_map,
        CMD_ID_lua_vars_to_map_strfilter,
        CMD_ID_lua_vars_from_map,
        CMD_ID_lua_vars_from_map_strfilter,
        CMD_ID_lua_do_command_strcmd,
        CMD_ID_lua_do_script_strfile,

        CMD_ID_lua_tables_print_strtables,
        CMD_ID_lua_tables_print_strtables_verbose,
        CMD_ID_lua_tables_print_strtables_with_system,
        CMD_ID_lua_tables_print_strtables_with_system_verbose,
        CMD_ID_lua_tables_print_strtables_system_only,
        CMD_ID_lua_tables_print_strtables_system_only_verbose,
        CMD_ID_lua_tables_print_strtables_system_internal,

        CMD_ID_lua_strcmd, //@Warning: After all but before CMD_ID_strcmd
        CMD_ID_strcmd, //@Warning: Last

        CMD_ID_LAST
    };

    virtual int Cmd_ID_Count_Get() {
        return CMD_ID_LAST - CMD_ID_NO - 1;
    }

    bool lua(vector<Level_Description> &Levels) {
        Parent_Level = Cli_Input.Level_Get();
        Levels.push_back(Level_Description(New_Level));
        Cli_Input.Level_Set(New_Level);
        return true;
    }

    virtual bool end(vector<Level_Description> &Levels) {
        if (Levels.size()) Levels.pop_back();
        Cli_Input.Level_Set(Parent_Level);
        return true;
    }

    Cli_Module_Lua(map<string, string> &values_map, Str_Filter_Abstract &str_filter,
            Cli_Input_Abstract &cli_input, Cli_Output_Abstract &cli_output)
    : Cli_Module("Lua"), Values_Map(values_map), Str_Filter(str_filter),
    Cli_Input(cli_input), Cli_Output(cli_output), New_Level("lua"), L(0) {

        L = luaL_newstate(); // open Lua
        luaL_openlibs(L); // open std Lua libs

        Lua_System_Objects_Fill(Lua_System_Objects);

        {
            // lua
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_lua);
            cmd->Text_Set(New_Level);
            cmd->Help_Set("switch to level: " + New_Level);
            cmd->Is_Global_Set(false);
            cmd->Level_Set("");
            cmd->Item_Add(new Cmd_Item_Word("lua", "switch to level: " + New_Level));
            Cmd_Add(cmd);
        }
        {
            // end
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_end);
            cmd->Text_Set("end");
            cmd->Help_Set("level up");
            cmd->Is_Global_Set(false);
            cmd->Level_Set(New_Level);
            cmd->Item_Add(new Cmd_Item_Word("end", "level up"));
            Cmd_Add(cmd);
        }

        {
            // lua vars
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_lua_vars);
            cmd->Text_Set("lua vars");
            cmd->Help_Set("show lua vars (all)");
            cmd->Is_Global_Set(false);
            cmd->Level_Set(New_Level);
            cmd->Item_Add(new Cmd_Item_Word("lua", "lua"));
            cmd->Item_Add(new Cmd_Item_Word("vars", "show lua vars (all)"));
            Cmd_Add(cmd);
        }
        {
            // lua vars print
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_lua_vars_print);
            cmd->Text_Set("lua vars print");
            cmd->Help_Set("show lua vars (all)");
            cmd->Is_Global_Set(false);
            cmd->Level_Set(New_Level);
            cmd->Item_Add(new Cmd_Item_Word("lua", "lua"));
            cmd->Item_Add(new Cmd_Item_Word("vars", "lua vars"));
            cmd->Item_Add(new Cmd_Item_Word("print", "show lua vars (all)"));
            Cmd_Add(cmd);
        }
        {
            // lua vars print "<vars>"
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_lua_vars_print_strfilter);
            cmd->Text_Set("lua vars print \"<vars>\"");
            cmd->Help_Set("show lua vars (by filter)");
            cmd->Is_Global_Set(false);
            cmd->Level_Set(New_Level);
            cmd->Item_Add(new Cmd_Item_Word("lua", "lua"));
            cmd->Item_Add(new Cmd_Item_Word("vars", "lua vars"));
            cmd->Item_Add(new Cmd_Item_Word("print", "show lua vars"));
            cmd->Item_Add(new Cmd_Item_Str("\"<vars>\"", "show lua vars (by filter)"));
            Cmd_Add(cmd);
        }

        {
            // lua vars to map
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_lua_vars_to_map);
            cmd->Text_Set("lua vars to map");
            cmd->Help_Set("lua vars to map (all)");
            cmd->Is_Global_Set(false);
            cmd->Level_Set(New_Level);
            cmd->Item_Add(new Cmd_Item_Word("lua", "lua"));
            cmd->Item_Add(new Cmd_Item_Word("vars", "lua vars"));
            cmd->Item_Add(new Cmd_Item_Word("to", "lua vars to"));
            cmd->Item_Add(new Cmd_Item_Word("map", "lua vars to map (all)"));
            Cmd_Add(cmd);
        }
        {
            // lua vars to map "<vars>"
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_lua_vars_to_map_strfilter);
            cmd->Text_Set("lua vars to map \"<vars>\"");
            cmd->Help_Set("lua vars to map (by filter)");
            cmd->Is_Global_Set(false);
            cmd->Level_Set(New_Level);
            cmd->Item_Add(new Cmd_Item_Word("lua", "lua"));
            cmd->Item_Add(new Cmd_Item_Word("vars", "lua vars"));
            cmd->Item_Add(new Cmd_Item_Word("to", "lua vars to"));
            cmd->Item_Add(new Cmd_Item_Word("map", "lua vars to map"));
            cmd->Item_Add(new Cmd_Item_Str("\"<vars>\"", "lua vars to map (by filter)"));
            Cmd_Add(cmd);
        }

        {
            // lua vars from map
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_lua_vars_from_map);
            cmd->Text_Set("lua vars from map");
            cmd->Help_Set("lua vars from map (all)");
            cmd->Is_Global_Set(false);
            cmd->Level_Set(New_Level);
            cmd->Item_Add(new Cmd_Item_Word("lua", "lua"));
            cmd->Item_Add(new Cmd_Item_Word("vars", "lua vars"));
            cmd->Item_Add(new Cmd_Item_Word("from", "lua vars from"));
            cmd->Item_Add(new Cmd_Item_Word("map", "lua vars from map (all)"));
            Cmd_Add(cmd);
        }
        {
            // lua vars from map "<vars>"
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_lua_vars_from_map_strfilter);
            cmd->Text_Set("lua vars from map \"<vars>\"");
            cmd->Help_Set("lua vars from map (by filter)");
            cmd->Is_Global_Set(false);
            cmd->Level_Set(New_Level);
            cmd->Item_Add(new Cmd_Item_Word("lua", "lua"));
            cmd->Item_Add(new Cmd_Item_Word("vars", "lua vars"));
            cmd->Item_Add(new Cmd_Item_Word("from", "lua vars from"));
            cmd->Item_Add(new Cmd_Item_Word("map", "lua vars from map"));
            cmd->Item_Add(new Cmd_Item_Str("\"<vars>\"", "lua vars from map (by filter)"));
            Cmd_Add(cmd);
        }

        {
            // lua do command "<strcmd>"
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_lua_do_command_strcmd);
            cmd->Text_Set("lua do command \"<strcmd>\"");
            cmd->Help_Set("execute lua command \"<strcmd>\"");
            cmd->Is_Global_Set(false);
            cmd->Level_Set(New_Level);
            cmd->Item_Add(new Cmd_Item_Word("lua", "lua"));
            cmd->Item_Add(new Cmd_Item_Word("do", "lua do"));
            cmd->Item_Add(new Cmd_Item_Word("command", "lua do command"));
            cmd->Item_Add(new Cmd_Item_Str("\"<strcmd>\"", "lua do command \"<strcmd>\""));
            Cmd_Add(cmd);
        }
        {
            // lua do script "<file.lua>"
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_lua_do_script_strfile);
            cmd->Text_Set("lua do script \"<file.lua>\"");
            cmd->Help_Set("execute lua script");
            cmd->Is_Global_Set(false);
            cmd->Level_Set(New_Level);
            cmd->Item_Add(new Cmd_Item_Word("lua", "lua"));
            cmd->Item_Add(new Cmd_Item_Word("do", "lua do"));
            cmd->Item_Add(new Cmd_Item_Word("script", "lua do script"));
            cmd->Item_Add(new Cmd_Item_Str("\"<file.lua>\"", "lua do script \"<file.lua>\""));
            Cmd_Add(cmd);
        }

        {
            // lua tables print "<tables>"
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_lua_tables_print_strtables);
            cmd->Text_Set("lua tables print \"<tables>\"");
            cmd->Help_Set("show lua tables (by filter)");
            cmd->Is_Global_Set(false);
            cmd->Level_Set(New_Level);
            cmd->Item_Add(new Cmd_Item_Word("lua", "lua"));
            cmd->Item_Add(new Cmd_Item_Word("tables", "lua tables"));
            cmd->Item_Add(new Cmd_Item_Word("print", "show lua tables"));
            cmd->Item_Add(new Cmd_Item_Str("\"<tables>\"", "show lua tables (by filter)"));
            Cmd_Add(cmd);
        }
        {
            // lua tables print "<tables>" verbose
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_lua_tables_print_strtables_verbose);
            cmd->Text_Set("lua tables print \"<tables>\"");
            cmd->Help_Set("show lua tables (by filter)");
            cmd->Is_Global_Set(false);
            cmd->Level_Set(New_Level);
            cmd->Item_Add(new Cmd_Item_Word("lua", "lua"));
            cmd->Item_Add(new Cmd_Item_Word("tables", "lua tables"));
            cmd->Item_Add(new Cmd_Item_Word("print", "show lua tables"));
            cmd->Item_Add(new Cmd_Item_Str("\"<tables>\"", "show lua tables (by filter)"));
            cmd->Item_Add(new Cmd_Item_Word("verbose", "show lua tables (by filter) with items"));
            Cmd_Add(cmd);
        }
        {
            // lua tables print "<tables>" with system
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_lua_tables_print_strtables_with_system);
            cmd->Text_Set("lua tables print \"<tables>\" with system");
            cmd->Help_Set("show lua tables (by filter) with system");
            cmd->Is_Global_Set(false);
            cmd->Level_Set(New_Level);
            cmd->Item_Add(new Cmd_Item_Word("lua", "lua"));
            cmd->Item_Add(new Cmd_Item_Word("tables", "lua tables"));
            cmd->Item_Add(new Cmd_Item_Word("print", "show lua tables"));
            cmd->Item_Add(new Cmd_Item_Str("\"<tables>\"", "show lua tables (by filter)"));
            cmd->Item_Add(new Cmd_Item_Word("with", "show lua tables (by filter) with"));
            cmd->Item_Add(new Cmd_Item_Word("system", "show lua tables (by filter) with system"));
            Cmd_Add(cmd);
        }
        {
            // lua tables print "<tables>" with system verbose
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_lua_tables_print_strtables_with_system_verbose);
            cmd->Text_Set("lua tables print \"<tables>\" with system verbose");
            cmd->Help_Set("show lua tables (by filter) with system with items");
            cmd->Is_Global_Set(false);
            cmd->Level_Set(New_Level);
            cmd->Item_Add(new Cmd_Item_Word("lua", "lua"));
            cmd->Item_Add(new Cmd_Item_Word("tables", "lua tables"));
            cmd->Item_Add(new Cmd_Item_Word("print", "show lua tables"));
            cmd->Item_Add(new Cmd_Item_Str("\"<tables>\"", "show lua tables (by filter)"));
            cmd->Item_Add(new Cmd_Item_Word("with", "show lua tables (by filter) with"));
            cmd->Item_Add(new Cmd_Item_Word("system", "show lua tables (by filter) with system"));
            cmd->Item_Add(new Cmd_Item_Word("verbose", "show lua tables (by filter) with items"));
            Cmd_Add(cmd);
        }
        {
            // lua tables print "<tables>" system only
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_lua_tables_print_strtables_system_only);
            cmd->Text_Set("lua tables print \"<tables>\" system only");
            cmd->Help_Set("show lua tables (by filter) system only");
            cmd->Is_Global_Set(false);
            cmd->Level_Set(New_Level);
            cmd->Item_Add(new Cmd_Item_Word("lua", "lua"));
            cmd->Item_Add(new Cmd_Item_Word("tables", "lua tables"));
            cmd->Item_Add(new Cmd_Item_Word("print", "show lua tables"));
            cmd->Item_Add(new Cmd_Item_Str("\"<tables>\"", "show lua tables (by filter)"));
            cmd->Item_Add(new Cmd_Item_Word("system", "show lua tables (by filter) system"));
            cmd->Item_Add(new Cmd_Item_Word("only", "show lua tables (by filter) system only"));
            Cmd_Add(cmd);
        }
        {
            // lua tables print "<tables>" system only verbose
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_lua_tables_print_strtables_system_only_verbose);
            cmd->Text_Set("lua tables print \"<tables>\" system only verbose");
            cmd->Help_Set("show lua tables (by filter) system only with items");
            cmd->Is_Global_Set(false);
            cmd->Level_Set(New_Level);
            cmd->Item_Add(new Cmd_Item_Word("lua", "lua"));
            cmd->Item_Add(new Cmd_Item_Word("tables", "lua tables"));
            cmd->Item_Add(new Cmd_Item_Word("print", "show lua tables"));
            cmd->Item_Add(new Cmd_Item_Str("\"<tables>\"", "show lua tables (by filter)"));
            cmd->Item_Add(new Cmd_Item_Word("system", "show lua tables (by filter) system"));
            cmd->Item_Add(new Cmd_Item_Word("only", "show lua tables (by filter) system only"));
            cmd->Item_Add(new Cmd_Item_Word("verbose", "show lua tables (by filter) with items"));
            Cmd_Add(cmd);
        }

        {
            // lua tables print "<tables>" system internal
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_lua_tables_print_strtables_system_internal);
            cmd->Text_Set("lua tables print \"<tables>\" system internal");
            cmd->Help_Set("show lua tables (by filter) system internal");
            cmd->Is_Global_Set(false);
            cmd->Level_Set(New_Level);
            cmd->Item_Add(new Cmd_Item_Word("lua", "lua"));
            cmd->Item_Add(new Cmd_Item_Word("tables", "lua tables"));
            cmd->Item_Add(new Cmd_Item_Word("print", "show lua tables"));
            cmd->Item_Add(new Cmd_Item_Str("\"<tables>\"", "show lua tables (by filter)"));
            cmd->Item_Add(new Cmd_Item_Word("system", "show lua tables (by filter) system"));
            cmd->Item_Add(new Cmd_Item_Word("internal", "show lua tables (by filter) system internal"));
            Cmd_Add(cmd);
        }

        {
            // lua "<strcmd>" //@Warning: After all but before CMD_ID_strcmd
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_lua_strcmd);
            cmd->Text_Set("lua \"<strcmd>\"");
            cmd->Help_Set("execute lua command \"<strcmd>\"");
            cmd->Is_Global_Set(false);
            cmd->Level_Set(New_Level);
            cmd->Item_Add(new Cmd_Item_Word("lua", "lua"));
            cmd->Item_Add(new Cmd_Item_Str("\"<strcmd>\"", "lua \"<strcmd>\""));
            Cmd_Add(cmd);
        }
        {
            // "<strcmd>" //@Warning: Last
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_strcmd);
            cmd->Text_Set("\"<strcmd>\"");
            cmd->Help_Set("execute lua command \"<strcmd>\"");
            cmd->Is_Global_Set(false);
            cmd->Level_Set(New_Level);
            cmd->Item_Add(new Cmd_Item_Str("\"<strcmd>\"", "lua do command \"<strcmd>\""));
            Cmd_Add(cmd);
        }

    }

    ~Cli_Module_Lua() {
        if (L) lua_close(L);
    }

    void Lua_System_Objects_Fill(set<string> &system_objects) {
        lua_getglobal(L, "_G");
        if (lua_istable(L, -1)) {
            lua_pushnil(L); /* first key */
            while (lua_next(L, -2) != 0) {
                string table_name = lua_tostring(L, -2);
                system_objects.insert(table_name);
                lua_pop(L, 1);
            }
        }
    }

    bool lua_do_command_str(string lua_command_str, bool is_log = true) {

        if (is_log) {
            Cli_Output.Output_NewLine();
            Cli_Output.Output_Str("Lua Command: " + lua_command_str);
            Cli_Output.Output_NewLine();
        }

        // LUA command execution:
        // Commas need if command has spaces ("<cmd with spaces>" / '<cmd with spaces>')
        string s = lua_command_str;
        string s1;
        if (s.size() >= 2 && s[0] == '\"' && s[s.size() - 1] == '\"')
            s1 = s.substr(1, s.size() - 2);
        else if (s.size() >= 2 && s[0] == '\'' && s[s.size() - 1] == '\'')
            s1 = s.substr(1, s.size() - 2);
        else
            s1 = s;
        int error = luaL_dostring(L, s1.c_str());
        if (error) {
            string err = lua_tostring(L, -1);
            lua_pop(L, 1); // pop error message
            Cli_Output.Output_NewLine();
            Cli_Output.Output_Str("ERROR: " + err);
            Cli_Output.Output_NewLine();
        }

        return true;
    }

    bool lua_do_script_str(string lua_script_str) {
        Cli_Output.Output_NewLine();
        Cli_Output.Output_Str("Lua script: " + lua_script_str);
        Cli_Output.Output_NewLine();

        string cmd = "dofile('" + lua_script_str + "')";

        bool is_log;
        lua_do_command_str(cmd, is_log = false);

        return true;
    }

    bool lua_vars_iterate_byfilter(string vars_filter, bool is_print, bool is_to_map) {
        bool found = false;

        for (map<string, string>::iterator iter = Values_Map.begin(); iter != Values_Map.end(); iter++) {
            string key = iter->first;
            string value = iter->second;

            if (Str_Filter.Is_Match(vars_filter, key)) {
                std::size_t found_index = key.find('.');
                if (found_index == std::string::npos) {
                    string var_name = key;

                    int res = lua_getglobal(L, var_name.c_str());
                    if (res == LUA_TNUMBER || res == LUA_TSTRING) {
                        string var_value = lua_tostring(L, -1);
                        lua_pop(L, 1);

                        stringstream s_str;
                        s_str << key << " = \"" << var_value << "\"";

                        if (is_print) {
                            Cli_Output.Output_Str(s_str.str());
                            Cli_Output.Output_NewLine();
                        }

                        if (is_to_map) {
                            Values_Map.at(key) = var_value;
                        }

                        found = true;
                    }
                } else {
                    string table_name = key.substr(0, found_index);
                    string var_name = key.substr(found_index + 1);

                    lua_getglobal(L, table_name.c_str());
                    if (lua_istable(L, -1)) {
                        int res = lua_getfield(L, -1, var_name.c_str());
                        if (res == LUA_TNUMBER || res == LUA_TSTRING) {
                            string var_value = lua_tostring(L, -1);
                            lua_pop(L, 1);

                            stringstream s_str;
                            s_str << key << " = \"" << var_value << "\"";

                            if (is_print) {
                                Cli_Output.Output_Str(s_str.str());
                                Cli_Output.Output_NewLine();
                            }

                            if (is_to_map) {
                                Values_Map.at(key) = var_value;
                            }

                            found = true;
                        }
                    }
                }
            }

        }

        return found;
    }

    bool lua_vars_print_byfilter(string vars_filter) {
        Cli_Output.Output_NewLine();
        Cli_Output.Output_Str("Lua vars \"" + vars_filter + "\":");
        Cli_Output.Output_NewLine();

        bool is_print;
        bool is_to_map;
        bool found = lua_vars_iterate_byfilter(vars_filter, is_print = true, is_to_map = false);

        if (!found) {
            Cli_Output.Output_Str("\"" + vars_filter + "\" - not found");
        }
        Cli_Output.Output_NewLine();

        return true;
    }

    bool lua_tables_print_byfilter(string tables_filter, bool is_with_system, bool is_system_only, bool is_verbose) {
        Cli_Output.Output_NewLine();
        Cli_Output.Output_Str("Lua tables \"" + tables_filter + "\":");
        Cli_Output.Output_NewLine();

        bool found = false;

        lua_getglobal(L, "_G");
        if (lua_istable(L, -1)) {

            lua_pushnil(L); /* first key */
            while (lua_next(L, -2) != 0) {
                if (lua_istable(L, -1)) {
                    string table_name = lua_tostring(L, -2);
                    bool is_match = Str_Filter.Is_Match(tables_filter, table_name);
                    if (!is_with_system) {
                        if (Lua_System_Objects.find(table_name) != Lua_System_Objects.end()) {
                            is_match = false;
                        }
                    }
                    if (is_system_only) {
                        is_match = false;
                        if (Lua_System_Objects.find(table_name) != Lua_System_Objects.end()) {
                            is_match = true;
                        }
                    }
                    if (is_match) {
                        if (is_verbose) {
                            Cli_Output.Output_Str(table_name + ":");
                            Cli_Output.Output_NewLine();
                            lua_pushnil(L); /* first key */
                            while (lua_next(L, -2) != 0) {
                                stringstream s_str;
                                s_str << "    "
                                        << lua_typename(L, lua_type(L, -2))
                                        << ":" << lua_tostring(L, -2)
                                        << " - " << lua_typename(L, lua_type(L, -1))
                                        << ":" << lua_tostring(L, -1);
                                Cli_Output.Output_Str(s_str.str());
                                Cli_Output.Output_NewLine();

                                lua_pop(L, 1);
                            }
                        } else {
                            Cli_Output.Output_Str(table_name);
                            Cli_Output.Output_NewLine();
                        }
                        found = true;
                    }
                }
                lua_pop(L, 1);
            }

        }

        if (!found) {
            Cli_Output.Output_Str("\"" + tables_filter + "\" - not found");
        }
        Cli_Output.Output_NewLine();

        return true;
    }

    bool lua_tables_print_byfilter_internal(string tables_filter) {
        Cli_Output.Output_NewLine();
        Cli_Output.Output_Str("Lua system objects (internal):");
        Cli_Output.Output_NewLine();
        for (set<string>::iterator iter = Lua_System_Objects.begin();
                iter != Lua_System_Objects.end(); iter++) {
            Cli_Output.Output_Str(*iter);
            Cli_Output.Output_NewLine();
        }
        return true;
    }

    bool lua_vars_to_map_byfilter(string vars_filter) {
        Cli_Output.Output_NewLine();
        Cli_Output.Output_Str("Lua vars to map \"" + vars_filter + "\":");
        Cli_Output.Output_NewLine();

        bool is_print;
        bool is_to_map;
        bool found = lua_vars_iterate_byfilter(vars_filter, is_print = true, is_to_map = true);

        if (!found) {
            Cli_Output.Output_Str("\"" + vars_filter + "\" - not found");
        }
        Cli_Output.Output_NewLine();

        return true;
    }

    bool lua_vars_from_map_byfilter_V01(string vars_filter) {
        Cli_Output.Output_NewLine();
        Cli_Output.Output_Str("Lua vars from map \"" + vars_filter + "\":");
        Cli_Output.Output_NewLine();

        bool found = false;
        set<string> tables;
        bool is_log;
        for (map<string, string>::iterator iter = Values_Map.begin(); iter != Values_Map.end(); iter++) {
            string key = iter->first;
            string value = iter->second;
            if (Str_Filter.Is_Match(vars_filter, key)) {
                std::size_t found_index = key.find('.');
                if (found_index == std::string::npos) {
                    string s = key + " = \"" + value + "\"";
                    Cli_Output.Output_Str(s);
                    Cli_Output.Output_NewLine();
                    lua_do_command_str(s, is_log = false);
                    found = true;
                } else {
                    string s1 = key.substr(0, found_index);
                    string s2 = key.substr(found_index + 1);
                    if (tables.find(s1) == tables.end()) {
                        lua_do_command_str(s1 + "={}", is_log = false);
                        tables.insert(s1);
                    }
                    string s = key + " = \"" + value + "\"";
                    Cli_Output.Output_Str(s);
                    Cli_Output.Output_NewLine();
                    lua_do_command_str(s, is_log = false);
                    found = true;
                }
            }
        }

        if (!found) {
            Cli_Output.Output_Str("\"" + vars_filter + "\" - not found");
        }
        Cli_Output.Output_NewLine();

        return true;
    }

    bool lua_vars_from_map_byfilter(string vars_filter) {
        Cli_Output.Output_NewLine();
        Cli_Output.Output_Str("Lua vars from map \"" + vars_filter + "\":");
        Cli_Output.Output_NewLine();

        bool found = false;
        set<string> tables;
        bool is_log;
        for (map<string, string>::iterator iter = Values_Map.begin(); iter != Values_Map.end(); iter++) {
            string key = iter->first;
            string value = iter->second;
            if (Str_Filter.Is_Match(vars_filter, key)) {
                std::size_t found_index = key.find('.');
                if (found_index == std::string::npos) {
                    if (Lua_System_Objects.find(key) == Lua_System_Objects.end()) {
                        string s = key + " = \"" + value + "\"";
                        Cli_Output.Output_Str(s);
                        Cli_Output.Output_NewLine();
                        lua_do_command_str(s, is_log = false);
                    } else {
                        Cli_Output.Output_Str("ERROR: " + key + " - is system object");
                        Cli_Output.Output_NewLine();
                    }
                    found = true;
                } else {
                    string s1 = key.substr(0, found_index);
                    string s2 = key.substr(found_index + 1);
                    if (Lua_System_Objects.find(s1) == Lua_System_Objects.end()) {
                        if (tables.find(s1) == tables.end()) {
                            lua_do_command_str(s1 + "={}", is_log = false);
                            tables.insert(s1);
                        }
                        string s = key + " = \"" + value + "\"";
                        Cli_Output.Output_Str(s);
                        Cli_Output.Output_NewLine();
                        lua_do_command_str(s, is_log = false);
                    } else {
                        Cli_Output.Output_Str("ERROR: " + s1 + " - is system object");
                        Cli_Output.Output_NewLine();
                    }
                    found = true;
                }
            }
        }

        if (!found) {
            Cli_Output.Output_Str("\"" + vars_filter + "\" - not found");
        }
        Cli_Output.Output_NewLine();

        return true;
    }

    virtual bool Execute(Cli_Cmd *cmd, vector<Level_Description> &Levels, bool is_debug) {
        enum Local_Cmd_ID cmd_id = (enum Local_Cmd_ID)cmd->ID_Get();
        switch (cmd_id) {
            case CMD_ID_lua:
                if (is_debug) return true;
                return lua(Levels);
            case CMD_ID_end:
                if (is_debug) return true;
                return end(Levels);

            case CMD_ID_lua_vars:
            case CMD_ID_lua_vars_print:
                if (is_debug) return true;
            {
                string vars_filter = "*";
                return lua_vars_print_byfilter(vars_filter);
            }
            case CMD_ID_lua_vars_print_strfilter:
                if (is_debug) return true;
            {
                string vars_filter = cmd->Items[3]->Value_Str;
                return lua_vars_print_byfilter(vars_filter);
            }

            case CMD_ID_lua_vars_to_map:
                if (is_debug) return true;
            {
                string vars_filter = "*";
                return lua_vars_to_map_byfilter(vars_filter);
            }
            case CMD_ID_lua_vars_to_map_strfilter:
                if (is_debug) return true;
            {
                string vars_filter = cmd->Items[4]->Value_Str;
                return lua_vars_to_map_byfilter(vars_filter);
            }

            case CMD_ID_lua_vars_from_map:
                if (is_debug) return true;
            {
                string vars_filter = "*";
                return lua_vars_from_map_byfilter(vars_filter);
            }
            case CMD_ID_lua_vars_from_map_strfilter:
                if (is_debug) return true;
            {
                string vars_filter = cmd->Items[4]->Value_Str;
                return lua_vars_from_map_byfilter(vars_filter);
            }

            case CMD_ID_lua_do_command_strcmd:
                if (is_debug) return true;
            {
                string lua_command_str = cmd->Items[3]->Value_Str;
                return lua_do_command_str(lua_command_str);
            }

            case CMD_ID_lua_do_script_strfile:
                if (is_debug) return true;
            {
                string lua_script_str = cmd->Items[3]->Value_Str;
                return lua_do_script_str(lua_script_str);
            }

            case CMD_ID_lua_tables_print_strtables:
                if (is_debug) return true;
            {
                string table_filter = cmd->Items[3]->Value_Str;
                bool is_with_system = false;
                bool is_system_only = false;
                bool is_verbose = false;
                return lua_tables_print_byfilter(table_filter, is_with_system, is_system_only, is_verbose);
            }
            case CMD_ID_lua_tables_print_strtables_verbose:
                if (is_debug) return true;
            {
                string table_filter = cmd->Items[3]->Value_Str;
                bool is_with_system = false;
                bool is_system_only = false;
                bool is_verbose = true;
                return lua_tables_print_byfilter(table_filter, is_with_system, is_system_only, is_verbose);
            }
            case CMD_ID_lua_tables_print_strtables_with_system:
                if (is_debug) return true;
            {
                string table_filter = cmd->Items[3]->Value_Str;
                bool is_with_system = true;
                bool is_system_only = false;
                bool is_verbose = false;
                return lua_tables_print_byfilter(table_filter, is_with_system, is_system_only, is_verbose);
            }
            case CMD_ID_lua_tables_print_strtables_with_system_verbose:
                if (is_debug) return true;
            {
                string table_filter = cmd->Items[3]->Value_Str;
                bool is_with_system = true;
                bool is_system_only = false;
                bool is_verbose = true;
                return lua_tables_print_byfilter(table_filter, is_with_system, is_system_only, is_verbose);
            }
            case CMD_ID_lua_tables_print_strtables_system_only:
                if (is_debug) return true;
            {
                string table_filter = cmd->Items[3]->Value_Str;
                bool is_with_system = true;
                bool is_system_only = true;
                bool is_verbose = false;
                return lua_tables_print_byfilter(table_filter, is_with_system, is_system_only, is_verbose);
            }
            case CMD_ID_lua_tables_print_strtables_system_only_verbose:
                if (is_debug) return true;
            {
                string table_filter = cmd->Items[3]->Value_Str;
                bool is_with_system = true;
                bool is_system_only = true;
                bool is_verbose = true;
                return lua_tables_print_byfilter(table_filter, is_with_system, is_system_only, is_verbose);
            }

            case CMD_ID_lua_tables_print_strtables_system_internal:
                if (is_debug) return true;
            {
                string table_filter = cmd->Items[3]->Value_Str;
                return lua_tables_print_byfilter_internal(table_filter);
            }

            case CMD_ID_lua_strcmd:
                if (is_debug) return true;
            {
                string lua_command_str = cmd->Items[1]->Value_Str;
                return lua_do_command_str(lua_command_str);
            }
            case CMD_ID_strcmd:
                if (is_debug) return true;
            {
                string lua_command_str = cmd->Items[0]->Value_Str;
                return lua_do_command_str(lua_command_str);
            }

            default:
                return false; // Not Implemented

        }
        return false; // Not Implemented
    }

    virtual void To_Map(map<string, string> &values_map) {

        string Prefix = "lua";

        string Test_Value_Str = "test_value_str";

        values_map[Prefix + ".test_value_str"] = Test_Value_Str;
    }
};

#endif /* CLI_MODULE_LUA_H */
