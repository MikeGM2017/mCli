/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_Module_Check.h
 * Author: mike
 *
 * Created on December 2, 2020, 11:17 AM
 */

#ifndef CLI_MODULE_CHECK_H
#define CLI_MODULE_CHECK_H

#include <map>

using namespace std;

#include "Cli_Module.h"
#include "Cli_Output_Abstract.h"
#include "Cmd_Item_Str.h"
#include "Cmd_Item_Word.h"
#include "Cmd_Item_Int.h"
#include "Cmd_Item_EQU_Range.h"
#include "Cli_Modules.h"
#include "Str_Filter_Abstract.h"
#include "Str_Filter.h"

class Cli_Module_Check : public Cli_Module {
protected:

    Cli_Modules &Modules;

    map<string, string> &Values_Map;

    Str_Filter_Abstract &Str_Filter;

    Cli_Output_Abstract &Cli_Output;

    bool &Cmd_Script_Stop;

    string &Script_Command_Str;
    string &Script_Label_Str;

    int Count_Total;
    int Count_Passed;
    int Count_Failed;

public:

    enum Local_Cmd_ID {
        CMD_ID_NO,

        CMD_ID_check_map,
        CMD_ID_check_map_print,
        CMD_ID_check_map_print_by_filter,
        CMD_ID_check_map_clear,

        CMD_ID_check_modules_by_filter_to_map,
        //CMD_ID_check_modules_by_filter_from_map,

        CMD_ID_check_var_str_set_str_as_value,
        CMD_ID_check_var_str_set_str_as_value_force,
        CMD_ID_check_var_str_set_str_as_var,
        CMD_ID_check_var_str_set_str_as_var_force,
        CMD_ID_check_var_str_set_str_as_expr,
        CMD_ID_check_var_str_set_str_as_expr_force,

        CMD_ID_check_var_str_inc,

        CMD_ID_check_if_str_compare_int_print_str,
        CMD_ID_check_if_str_compare_int_print_str_else_print_str,
        CMD_ID_check_if_str_compare_int_inc_str,
        CMD_ID_check_if_str_compare_int_inc_str_else_inc_str,
        CMD_ID_check_if_str_compare_int_do_script_stop,
        CMD_ID_check_if_str_compare_int_do_script_filename,
        CMD_ID_check_if_str_compare_int_do_script_filename_no_history,

        CMD_ID_check_if_str_compare_str_as_value_print_str,
        CMD_ID_check_if_str_compare_str_as_value_print_str_else_print_str,
        CMD_ID_check_if_str_compare_str_as_value_inc_str,
        CMD_ID_check_if_str_compare_str_as_value_inc_str_else_inc_str,
        CMD_ID_check_if_str_compare_str_as_value_do_script_stop,
        CMD_ID_check_if_str_compare_str_as_value_do_script_filename,
        CMD_ID_check_if_str_compare_str_as_value_do_script_filename_no_history,

        CMD_ID_check_if_str_compare_str_as_var_print_str,
        CMD_ID_check_if_str_compare_str_as_var_print_str_else_print_str,
        CMD_ID_check_if_str_compare_str_as_var_inc_str,
        CMD_ID_check_if_str_compare_str_as_var_inc_str_else_inc_str,
        CMD_ID_check_if_str_compare_str_as_var_do_script_stop,
        CMD_ID_check_if_str_compare_str_as_var_do_script_filename,
        CMD_ID_check_if_str_compare_str_as_var_do_script_filename_no_history,

        CMD_ID_check_if_str_compare_int_do_command_str,
        CMD_ID_check_if_str_compare_int_do_command_str_else_do_command_str,
        CMD_ID_check_if_str_compare_str_as_value_do_command_str,
        CMD_ID_check_if_str_compare_str_as_value_do_command_str_else_do_command_str,
        CMD_ID_check_if_str_compare_str_as_var_do_command_str,
        CMD_ID_check_if_str_compare_str_as_var_do_command_str_else_do_command_str,

        CMD_ID_check_label_str,
        CMD_ID_check_goto_label,

        CMD_ID_check_if_str_compare_int_goto_str,
        CMD_ID_check_if_str_compare_int_goto_str_else_goto_str,
        CMD_ID_check_if_str_compare_str_as_value_goto_str,
        CMD_ID_check_if_str_compare_str_as_value_goto_str_else_goto_str,
        CMD_ID_check_if_str_compare_str_as_var_goto_str,
        CMD_ID_check_if_str_compare_str_as_var_goto_str_else_goto_str,

        CMD_ID_LAST
    };

    virtual int Cmd_ID_Count_Get() {
        return CMD_ID_LAST - CMD_ID_NO - 1;
    }

    enum Local_Compare_Result {
        CMP_FALSE,
        CMP_TRUE,
        CMP_ERROR
    };

    Cli_Module_Check(Cli_Modules &modules, map<string, string> &values_map,
            Str_Filter_Abstract &str_filter, Cli_Output_Abstract &cli_output,
            bool &cmd_script_stop,
            string &script_command_str, string &script_label_str) : Cli_Module("Check"),
    Modules(modules), Values_Map(values_map),
    Str_Filter(str_filter), Cli_Output(cli_output),
    Cmd_Script_Stop(cmd_script_stop),
    Script_Command_Str(script_command_str), Script_Label_Str(script_label_str) {

        // <editor-fold defaultstate="collapsed" desc="Decl: cmp_int_str/words, cmp_str_str/words">
        string cmp_int_str = "== != < > <= >= & | && ||";
        vector<string> cmp_int_words;
        cmp_int_words.push_back("==");
        cmp_int_words.push_back("!=");
        cmp_int_words.push_back("<");
        cmp_int_words.push_back(">");
        cmp_int_words.push_back("<=");
        cmp_int_words.push_back(">=");
        cmp_int_words.push_back("&");
        cmp_int_words.push_back("|");
        cmp_int_words.push_back("&&");
        cmp_int_words.push_back("||");

        string cmp_str_str = "== != < > <= >=";
        vector<string> cmp_str_words;
        cmp_str_words.push_back("==");
        cmp_str_words.push_back("!=");
        cmp_str_words.push_back("<");
        cmp_str_words.push_back(">");
        cmp_str_words.push_back("<=");
        cmp_str_words.push_back(">=");
        cmp_str_words.push_back("&");
        cmp_str_words.push_back("|");
        cmp_str_words.push_back("&&");
        cmp_str_words.push_back("||");
        // </editor-fold>

        // <editor-fold defaultstate="collapsed" desc="Values_Map: print, clear">
        {
            // check map
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_check_map);
            cmd->Text_Set("check map");
            cmd->Help_Set("print values from map (all values)");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("check", "check"));
            cmd->Item_Add(new Cmd_Item_Word("map", "check map"));

            Cmd_Add(cmd);
        }
        {
            // check map print
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_check_map_print);
            cmd->Text_Set("check map print");
            cmd->Help_Set("print values from map (all values)");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("check", "check"));
            cmd->Item_Add(new Cmd_Item_Word("map", "check map"));
            cmd->Item_Add(new Cmd_Item_Word("print", "check map print"));

            Cmd_Add(cmd);
        }
        {
            // check map print <var_name>
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_check_map_print_by_filter);
            cmd->Text_Set("check map print <var_name>");
            cmd->Help_Set("print values from map (by filter)");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("check", "check"));
            cmd->Item_Add(new Cmd_Item_Word("map", "check map"));
            cmd->Item_Add(new Cmd_Item_Word("print", "check map print"));
            cmd->Item_Add(new Cmd_Item_Str("<var_name>", "var name (by filter)"));

            Cmd_Add(cmd);
        }
        {
            // check map clear
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_check_map_clear);
            cmd->Text_Set("check map clear");
            cmd->Help_Set("clear map");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("check", "check"));
            cmd->Item_Add(new Cmd_Item_Word("map", "check map"));
            cmd->Item_Add(new Cmd_Item_Word("clear", "clear map print"));

            Cmd_Add(cmd);
        }
        // </editor-fold>

        // <editor-fold defaultstate="collapsed" desc="Values_Map: modules to map">
        {
            // check modules <module_name> to map
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_check_modules_by_filter_to_map);
            cmd->Text_Set("check modules <module_name> to map");
            cmd->Help_Set("vars from modules (modules by filter) to map");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("check", "check"));
            cmd->Item_Add(new Cmd_Item_Word("modules", "modules"));
            cmd->Item_Add(new Cmd_Item_Str("<module_name>", "modules (by filter)"));
            cmd->Item_Add(new Cmd_Item_Word("to", "modules to"));
            cmd->Item_Add(new Cmd_Item_Word("map", "modules to map"));

            Cmd_Add(cmd);
        }
        // </editor-fold>

        // <editor-fold defaultstate="collapsed" desc="Var: set as value, as var, as expression, force">
        {
            // check var str set str as value
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_check_var_str_set_str_as_value);
            cmd->Text_Set("check var <var_name> set <value> as value");
            cmd->Help_Set("set var to value");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("check", "check"));
            cmd->Item_Add(new Cmd_Item_Word("var", "check var"));
            cmd->Item_Add(new Cmd_Item_Str("<var_name>", "var name"));
            cmd->Item_Add(new Cmd_Item_Word("set", "var set"));
            cmd->Item_Add(new Cmd_Item_Str("<value>", "var new value"));
            cmd->Item_Add(new Cmd_Item_Word("as", "new value as"));
            cmd->Item_Add(new Cmd_Item_Word("value", "new value as value"));

            Cmd_Add(cmd);
        }
        {
            // check var str set str as value force
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_check_var_str_set_str_as_value_force);
            cmd->Text_Set("check var <var_name> set <value> as value force");
            cmd->Help_Set("set var to value (or create new var)");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("check", "check"));
            cmd->Item_Add(new Cmd_Item_Word("var", "check var"));
            cmd->Item_Add(new Cmd_Item_Str("<var_name>", "var name"));
            cmd->Item_Add(new Cmd_Item_Word("set", "var set"));
            cmd->Item_Add(new Cmd_Item_Str("<value>", "var new value"));
            cmd->Item_Add(new Cmd_Item_Word("as", "new value as"));
            cmd->Item_Add(new Cmd_Item_Word("value", "new value as value"));
            cmd->Item_Add(new Cmd_Item_Word("force", "create new var if needed"));

            Cmd_Add(cmd);
        }

        {
            // check var str set str as var
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_check_var_str_set_str_as_var);
            cmd->Text_Set("check var <var1_name> set <var2_name> as var");
            cmd->Help_Set("set var1 to value of var2");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("check", "check"));
            cmd->Item_Add(new Cmd_Item_Word("var", "check var"));
            cmd->Item_Add(new Cmd_Item_Str("<var1_name>", "var1 name"));
            cmd->Item_Add(new Cmd_Item_Word("set", "var set"));
            cmd->Item_Add(new Cmd_Item_Str("<var2_name>", "var2 name"));
            cmd->Item_Add(new Cmd_Item_Word("as", "as"));
            cmd->Item_Add(new Cmd_Item_Word("var", "new value as var2 value"));

            Cmd_Add(cmd);
        }
        {
            // check var str set str as var force
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_check_var_str_set_str_as_var_force);
            cmd->Text_Set("check var <var1_name> set <var2_name> as var force");
            cmd->Help_Set("set var1 to value of var2 (or create new var)");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("check", "check"));
            cmd->Item_Add(new Cmd_Item_Word("var", "check var"));
            cmd->Item_Add(new Cmd_Item_Str("<var1_name>", "var1 name"));
            cmd->Item_Add(new Cmd_Item_Word("set", "var set"));
            cmd->Item_Add(new Cmd_Item_Str("<var2_name>", "var2 name"));
            cmd->Item_Add(new Cmd_Item_Word("as", "as"));
            cmd->Item_Add(new Cmd_Item_Word("var", "new value as var2 value"));
            cmd->Item_Add(new Cmd_Item_Word("force", "create new var if needed"));

            Cmd_Add(cmd);
        }

        {
            // check var str set str as expr
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_check_var_str_set_str_as_expr);
            cmd->Text_Set("check var <var_name> set <str> as expr");
            cmd->Help_Set("set var to value of expr (or create new var)");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("check", "check"));
            cmd->Item_Add(new Cmd_Item_Word("var", "check var"));
            cmd->Item_Add(new Cmd_Item_Str("<var_name>", "var name"));
            cmd->Item_Add(new Cmd_Item_Word("set", "var set"));
            cmd->Item_Add(new Cmd_Item_Str("<str>", "expr"));
            cmd->Item_Add(new Cmd_Item_Word("as", "as"));
            cmd->Item_Add(new Cmd_Item_Word("expr", "new value as expression value"));

            Cmd_Add(cmd);
        }
        {
            // check var str set str as expr force
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_check_var_str_set_str_as_expr_force);
            cmd->Text_Set("check var <var_name> set <str> as expr force");
            cmd->Help_Set("set var to value of expr (or create new var)");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("check", "check"));
            cmd->Item_Add(new Cmd_Item_Word("var", "check var"));
            cmd->Item_Add(new Cmd_Item_Str("<var_name>", "var name"));
            cmd->Item_Add(new Cmd_Item_Word("set", "var set"));
            cmd->Item_Add(new Cmd_Item_Str("<str>", "expr"));
            cmd->Item_Add(new Cmd_Item_Word("as", "as"));
            cmd->Item_Add(new Cmd_Item_Word("expr", "new value as expression value"));
            cmd->Item_Add(new Cmd_Item_Word("force", "create new var if needed"));

            Cmd_Add(cmd);
        }
        // </editor-fold>

        // <editor-fold defaultstate="collapsed" desc="Var: inc">
        {
            // check var str inc
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_check_var_str_inc);
            cmd->Text_Set("check var <var_name> inc");
            cmd->Help_Set("increment var value");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("check", "check"));
            cmd->Item_Add(new Cmd_Item_Word("var", "check var"));
            cmd->Item_Add(new Cmd_Item_Str("<var_name>", "var name"));
            cmd->Item_Add(new Cmd_Item_Word("inc", "increment var value"));

            Cmd_Add(cmd);
        }
        // </editor-fold>

        // <editor-fold defaultstate="collapsed" desc="Check if: int print/inc/do script/do command">
        {
            // check if str compare INT print str // @Attention: Must be before check if str compare STR print str
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_check_if_str_compare_int_print_str);
            cmd->Text_Set("check if <var_name>  <compare: " + cmp_int_str + "> <int_value> print <msg>");
            cmd->Help_Set("check var by int and print msg");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("check", "check"));
            cmd->Item_Add(new Cmd_Item_Word("if", "check if"));
            cmd->Item_Add(new Cmd_Item_Str("<var_name>", "var name"));
            cmd->Item_Add(new Cmd_Item_EQU_Range("<compare: " + cmp_int_str + ">", "compare function", cmp_int_words));
            cmd->Item_Add(new Cmd_Item_Int("<int_value>", "value to compare"));
            cmd->Item_Add(new Cmd_Item_Word("print", "check and print"));
            cmd->Item_Add(new Cmd_Item_Str("<msg>", "msg to print"));

            Cmd_Add(cmd);
        }
        {
            // check if str compare INT print str else print str // @Attention: Must be before check if str compare STR print str
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_check_if_str_compare_int_print_str_else_print_str);
            cmd->Text_Set("check if <var_name>  <compare: " + cmp_int_str + "> <int_value> print <msg1> else print <msg2>");
            cmd->Help_Set("check var by int and print msg1 or msg2");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("check", "check"));
            cmd->Item_Add(new Cmd_Item_Word("if", "check if"));
            cmd->Item_Add(new Cmd_Item_Str("<var_name>", "var name"));
            cmd->Item_Add(new Cmd_Item_EQU_Range("<compare: " + cmp_int_str + ">", "compare function", cmp_int_words));
            cmd->Item_Add(new Cmd_Item_Int("<int_value>", "value to compare"));
            cmd->Item_Add(new Cmd_Item_Word("print", "check and print"));
            cmd->Item_Add(new Cmd_Item_Str("<msg1>", "msg to print (if compare result = true)"));
            cmd->Item_Add(new Cmd_Item_Word("else", "else"));
            cmd->Item_Add(new Cmd_Item_Word("print", "else print"));
            cmd->Item_Add(new Cmd_Item_Str("<msg2>", "msg to print (if compare result = false)"));

            Cmd_Add(cmd);
        }

        {
            // check if str compare INT inc str // @Attention: Must be before check if str compare STR inc str
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_check_if_str_compare_int_inc_str);
            cmd->Text_Set("check if <var1_name> <compare: " + cmp_int_str + "> <int_value> inc <var2_name>");
            cmd->Help_Set("check var1 by int and increment var2");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("check", "check"));
            cmd->Item_Add(new Cmd_Item_Word("if", "check if"));
            cmd->Item_Add(new Cmd_Item_Str("<var1_name>", "var1 name"));
            cmd->Item_Add(new Cmd_Item_EQU_Range("<compare: " + cmp_int_str + ">", "compare function", cmp_int_words));
            cmd->Item_Add(new Cmd_Item_Int("<int_value>", "value to compare"));
            cmd->Item_Add(new Cmd_Item_Word("inc", "check and increment"));
            cmd->Item_Add(new Cmd_Item_Str("<var2_name>", "var2 name to increment"));

            Cmd_Add(cmd);
        }
        {
            // check if str compare INT inc str else inc str // @Attention: Must be before check if str compare STR inc str
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_check_if_str_compare_int_inc_str_else_inc_str);
            cmd->Text_Set("check if <var1_name> <compare: " + cmp_int_str + "> <int_value> inc <var2_name> else inc <var3_name>");
            cmd->Help_Set("check var1 by int and increment var2 or var3");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("check", "check"));
            cmd->Item_Add(new Cmd_Item_Word("if", "check if"));
            cmd->Item_Add(new Cmd_Item_Str("<var1_name>", "var1 name"));
            cmd->Item_Add(new Cmd_Item_EQU_Range("<compare: " + cmp_int_str + ">", "compare function", cmp_int_words));
            cmd->Item_Add(new Cmd_Item_Int("<int_value>", "value to compare"));
            cmd->Item_Add(new Cmd_Item_Word("inc", "check and increment"));
            cmd->Item_Add(new Cmd_Item_Str("<var2_name>", "var2 name to increment (if compare result = true)"));
            cmd->Item_Add(new Cmd_Item_Word("else", "else"));
            cmd->Item_Add(new Cmd_Item_Word("inc", "check and increment"));
            cmd->Item_Add(new Cmd_Item_Str("<var3_name>", "var3 name to increment (if compare result = false)"));

            Cmd_Add(cmd);
        }

        {
            // check if str compare INT do script stop // @Attention: Must be before check if str compare STR do script stop
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_check_if_str_compare_int_do_script_stop);
            cmd->Text_Set("check if <var_name>  <compare: " + cmp_int_str + "> <int_value> do script stop");
            cmd->Help_Set("check var by int and stop script");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("check", "check"));
            cmd->Item_Add(new Cmd_Item_Word("if", "check if"));
            cmd->Item_Add(new Cmd_Item_Str("<var_name>", "var name"));
            cmd->Item_Add(new Cmd_Item_EQU_Range("<compare: " + cmp_int_str + ">", "compare function", cmp_int_words));
            cmd->Item_Add(new Cmd_Item_Int("<int_value>", "value to compare"));
            cmd->Item_Add(new Cmd_Item_Word("do", "do"));
            cmd->Item_Add(new Cmd_Item_Word("script", "do script"));
            cmd->Item_Add(new Cmd_Item_Word("stop", "do script stop"));

            Cmd_Add(cmd);
        }

        {
            // check if str compare INT do script str // @Attention: Must be before check if str compare STR do script str
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_check_if_str_compare_int_do_script_filename);
            cmd->Text_Set("check if <var_name>  <compare: " + cmp_int_str + "> <int_value> do script <filename>");
            cmd->Help_Set("check var by int and do script from file");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("check", "check"));
            cmd->Item_Add(new Cmd_Item_Word("if", "check if"));
            cmd->Item_Add(new Cmd_Item_Str("<var_name>", "var name"));
            cmd->Item_Add(new Cmd_Item_EQU_Range("<compare: " + cmp_int_str + ">", "compare function", cmp_int_words));
            cmd->Item_Add(new Cmd_Item_Int("<int_value>", "value to compare"));
            cmd->Item_Add(new Cmd_Item_Word("do", "do"));
            cmd->Item_Add(new Cmd_Item_Word("script", "do script"));
            cmd->Item_Add(new Cmd_Item_Str("<filename>", "script file name"));

            Cmd_Add(cmd);
        }
        {
            // check if str compare INT do script str no history // @Attention: Must be before check if str compare STR do script str
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_check_if_str_compare_int_do_script_filename_no_history);
            cmd->Text_Set("check if <var_name>  <compare: " + cmp_int_str + "> <int_value> do script <filename> no history");
            cmd->Help_Set("check var by int and do script from file, not save to history");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("check", "check"));
            cmd->Item_Add(new Cmd_Item_Word("if", "check if"));
            cmd->Item_Add(new Cmd_Item_Str("<var_name>", "var name"));
            cmd->Item_Add(new Cmd_Item_EQU_Range("<compare: " + cmp_int_str + ">", "compare function", cmp_int_words));
            cmd->Item_Add(new Cmd_Item_Int("<int_value>", "value to compare"));
            cmd->Item_Add(new Cmd_Item_Word("do", "do"));
            cmd->Item_Add(new Cmd_Item_Word("script", "do script"));
            cmd->Item_Add(new Cmd_Item_Str("<filename>", "script file name"));
            cmd->Item_Add(new Cmd_Item_Word("no", "not save"));
            cmd->Item_Add(new Cmd_Item_Word("history", "not save to history"));

            Cmd_Add(cmd);
        }
        // </editor-fold>

        // <editor-fold defaultstate="collapsed" desc="Check if: str as value print/inc/do script/do command">
        {
            // check if str compare STR as value print str // @Attention: Must be after check if str compare INT print str
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_check_if_str_compare_str_as_value_print_str);
            cmd->Text_Set("check if <var_name>  <compare: " + cmp_str_str + " > <str> as value print <msg>");
            cmd->Help_Set("check var by str and print msg");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("check", "check"));
            cmd->Item_Add(new Cmd_Item_Word("if", "check if"));
            cmd->Item_Add(new Cmd_Item_Str("<var_name>", "var name"));
            cmd->Item_Add(new Cmd_Item_EQU_Range("<compare: " + cmp_str_str + " >", "compare function", cmp_str_words));
            cmd->Item_Add(new Cmd_Item_Str("<str>", "str to compare"));
            cmd->Item_Add(new Cmd_Item_Word("as", "as"));
            cmd->Item_Add(new Cmd_Item_Word("value", "as value"));
            cmd->Item_Add(new Cmd_Item_Word("print", "check and print"));
            cmd->Item_Add(new Cmd_Item_Str("<msg>", "msg to print"));

            Cmd_Add(cmd);
        }
        {
            // check if str compare STR as value print str else print str // @Attention: Must be after check if str compare INT print str
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_check_if_str_compare_str_as_value_print_str_else_print_str);
            cmd->Text_Set("check if <var_name>  <compare: " + cmp_str_str + " > <str> as value print <msg1> else print <msg2>");
            cmd->Help_Set("check var by str and print msg1 or msg2");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("check", "check"));
            cmd->Item_Add(new Cmd_Item_Word("if", "check if"));
            cmd->Item_Add(new Cmd_Item_Str("<var_name>", "var name"));
            cmd->Item_Add(new Cmd_Item_EQU_Range("<compare: " + cmp_str_str + " >", "compare function", cmp_str_words));
            cmd->Item_Add(new Cmd_Item_Str("<str>", "str to compare"));
            cmd->Item_Add(new Cmd_Item_Word("as", "as"));
            cmd->Item_Add(new Cmd_Item_Word("value", "as value"));
            cmd->Item_Add(new Cmd_Item_Word("print", "check and print"));
            cmd->Item_Add(new Cmd_Item_Str("<msg1>", "msg to print (if compare result = true)"));
            cmd->Item_Add(new Cmd_Item_Word("else", "else"));
            cmd->Item_Add(new Cmd_Item_Word("print", "else print"));
            cmd->Item_Add(new Cmd_Item_Str("<msg2>", "msg to print (if compare result = false)"));

            Cmd_Add(cmd);
        }

        {
            // check if str compare STR as value inc str // @Attention: Must be after check if str compare INT inc str
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_check_if_str_compare_str_as_value_inc_str);
            cmd->Text_Set("check if <var1_name> <compare: " + cmp_str_str + "> <str> inc <var2_name>");
            cmd->Help_Set("check var1 by str and increment var2 or var3");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("check", "check"));
            cmd->Item_Add(new Cmd_Item_Word("if", "check if"));
            cmd->Item_Add(new Cmd_Item_Str("<var1_name>", "var1 name"));
            cmd->Item_Add(new Cmd_Item_EQU_Range("<compare: " + cmp_str_str + ">", "compare function", cmp_str_words));
            cmd->Item_Add(new Cmd_Item_Int("<str>", "value to compare"));
            cmd->Item_Add(new Cmd_Item_Word("as", "as"));
            cmd->Item_Add(new Cmd_Item_Word("value", "as value"));
            cmd->Item_Add(new Cmd_Item_Word("inc", "check and increment"));
            cmd->Item_Add(new Cmd_Item_Str("<var2_name>", "var2 name to increment (if compare result = true)"));

            Cmd_Add(cmd);
        }
        {
            // check if str compare STR as value inc str else inc str // @Attention: Must be after check if str compare INT inc str
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_check_if_str_compare_str_as_value_inc_str_else_inc_str);
            cmd->Text_Set("check if <var1_name> <compare: " + cmp_str_str + "> <str> inc <var2_name> else inc <var3_name>");
            cmd->Help_Set("check var1 by str and increment var2 or var3");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("check", "check"));
            cmd->Item_Add(new Cmd_Item_Word("if", "check if"));
            cmd->Item_Add(new Cmd_Item_Str("<var1_name>", "var1 name"));
            cmd->Item_Add(new Cmd_Item_EQU_Range("<compare: " + cmp_str_str + ">", "compare function", cmp_str_words));
            cmd->Item_Add(new Cmd_Item_Int("<str>", "value to compare"));
            cmd->Item_Add(new Cmd_Item_Word("as", "as"));
            cmd->Item_Add(new Cmd_Item_Word("value", "as value"));
            cmd->Item_Add(new Cmd_Item_Word("inc", "check and increment"));
            cmd->Item_Add(new Cmd_Item_Str("<var2_name>", "var2 name to increment (if compare result = true)"));
            cmd->Item_Add(new Cmd_Item_Word("else", "else"));
            cmd->Item_Add(new Cmd_Item_Word("inc", "check and increment"));
            cmd->Item_Add(new Cmd_Item_Str("<var3_name>", "var3 name to increment (if compare result = false)"));

            Cmd_Add(cmd);
        }

        {
            // check if str compare STR as value do script stop // @Attention: Must be after check if str compare INT do script stop
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_check_if_str_compare_str_as_value_do_script_stop);
            cmd->Text_Set("check if <var_name>  <compare: " + cmp_int_str + "> <str> as value do script stop");
            cmd->Help_Set("check var by str and stop script");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("check", "check"));
            cmd->Item_Add(new Cmd_Item_Word("if", "check if"));
            cmd->Item_Add(new Cmd_Item_Str("<var_name>", "var name"));
            cmd->Item_Add(new Cmd_Item_EQU_Range("<compare: " + cmp_int_str + ">", "compare function", cmp_int_words));
            cmd->Item_Add(new Cmd_Item_Str("<str>", "value to compare"));
            cmd->Item_Add(new Cmd_Item_Word("as", "as"));
            cmd->Item_Add(new Cmd_Item_Word("value", "str as value"));
            cmd->Item_Add(new Cmd_Item_Word("do", "do"));
            cmd->Item_Add(new Cmd_Item_Word("script", "do script"));
            cmd->Item_Add(new Cmd_Item_Word("stop", "do script stop"));

            Cmd_Add(cmd);
        }

        {
            // check if str compare STR as value do script filename // @Attention: Must be after check if str compare INT do script filename
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_check_if_str_compare_str_as_value_do_script_filename);
            cmd->Text_Set("check if <var_name>  <compare: " + cmp_str_str + "> <str> as value do script <filename>");
            cmd->Help_Set("check var by str and execute script from file");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("check", "check"));
            cmd->Item_Add(new Cmd_Item_Word("if", "check if"));
            cmd->Item_Add(new Cmd_Item_Str("<var_name>", "var name"));
            cmd->Item_Add(new Cmd_Item_EQU_Range("<compare: " + cmp_str_str + ">", "compare function", cmp_str_words));
            cmd->Item_Add(new Cmd_Item_Str("<str>", "value to compare"));
            cmd->Item_Add(new Cmd_Item_Word("as", "as"));
            cmd->Item_Add(new Cmd_Item_Word("value", "str as value"));
            cmd->Item_Add(new Cmd_Item_Word("do", "do"));
            cmd->Item_Add(new Cmd_Item_Word("script", "do script"));
            cmd->Item_Add(new Cmd_Item_Str("<filename>", "script file name"));

            Cmd_Add(cmd);
        }
        {
            // check if str compare STR as value do script str no history // @Attention: Must be after check if str compare INT do script str
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_check_if_str_compare_str_as_value_do_script_filename_no_history);
            cmd->Text_Set("check if <var_name>  <compare: " + cmp_str_str + "> <str> as value do script <filename> no history");
            cmd->Help_Set("check var by str as value and do script from file, not save to history");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("check", "check"));
            cmd->Item_Add(new Cmd_Item_Word("if", "check if"));
            cmd->Item_Add(new Cmd_Item_Str("<var_name>", "var name"));
            cmd->Item_Add(new Cmd_Item_EQU_Range("<compare: " + cmp_str_str + ">", "compare function", cmp_str_words));
            cmd->Item_Add(new Cmd_Item_Str("<str>", "value to compare"));
            cmd->Item_Add(new Cmd_Item_Word("as", "as"));
            cmd->Item_Add(new Cmd_Item_Word("value", "str as value"));
            cmd->Item_Add(new Cmd_Item_Word("do", "do"));
            cmd->Item_Add(new Cmd_Item_Word("script", "do script"));
            cmd->Item_Add(new Cmd_Item_Str("<filename>", "script file name"));
            cmd->Item_Add(new Cmd_Item_Word("no", "not save"));
            cmd->Item_Add(new Cmd_Item_Str("history", "not save to history"));

            Cmd_Add(cmd);
        }
        // </editor-fold>

        // <editor-fold defaultstate="collapsed" desc="Check if: str as var print/inc/do script/do command">
        {
            // check if str compare STR as var print str // @Attention: Must be after check if str compare INT print str
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_check_if_str_compare_str_as_var_print_str);
            cmd->Text_Set("check if <var1_name> <compare: " + cmp_str_str + "> <var2_name> as var print <msg>");
            cmd->Help_Set("check var1 by var2 and print msg");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("check", "check"));
            cmd->Item_Add(new Cmd_Item_Word("if", "check if"));
            cmd->Item_Add(new Cmd_Item_Str("<var1_name>", "var1 name"));
            cmd->Item_Add(new Cmd_Item_EQU_Range("<compare: " + cmp_str_str + ">", "compare function", cmp_str_words));
            cmd->Item_Add(new Cmd_Item_Str("<var2_name>", "var2 name"));
            cmd->Item_Add(new Cmd_Item_Word("as", "as"));
            cmd->Item_Add(new Cmd_Item_Word("var", "as var"));
            cmd->Item_Add(new Cmd_Item_Word("print", "check and print"));
            cmd->Item_Add(new Cmd_Item_Str("<msg>", "msg to print"));

            Cmd_Add(cmd);
        }
        {
            // check if str compare STR as var print str else print str // @Attention: Must be after check if str compare INT print str
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_check_if_str_compare_str_as_var_print_str_else_print_str);
            cmd->Text_Set("check if <var1_name> <compare: " + cmp_str_str + "> <var2_name> as var print <msg1> else print <msg2>");
            cmd->Help_Set("check var1 by var2 and print msg1 or msg2");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("check", "check"));
            cmd->Item_Add(new Cmd_Item_Word("if", "check if"));
            cmd->Item_Add(new Cmd_Item_Str("<var1_name>", "var1 name"));
            cmd->Item_Add(new Cmd_Item_EQU_Range("<compare: " + cmp_str_str + ">", "compare function", cmp_str_words));
            cmd->Item_Add(new Cmd_Item_Str("<var2_name>", "var2 name"));
            cmd->Item_Add(new Cmd_Item_Word("as", "as"));
            cmd->Item_Add(new Cmd_Item_Word("var", "as var"));
            cmd->Item_Add(new Cmd_Item_Word("print", "check and print"));
            cmd->Item_Add(new Cmd_Item_Str("<msg1>", "msg to print (if compare result = true)"));
            cmd->Item_Add(new Cmd_Item_Word("else", "else"));
            cmd->Item_Add(new Cmd_Item_Word("print", "else print"));
            cmd->Item_Add(new Cmd_Item_Str("<msg2>", "msg to print (if compare result = false)"));

            Cmd_Add(cmd);
        }

        {
            // check if str compare STR as var inc str // @Attention: Must be after check if str compare INT inc str
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_check_if_str_compare_str_as_var_inc_str);
            cmd->Text_Set("check if <var1_name> <compare: " + cmp_str_str + "> <var2_name> as var inc <var3_name>");
            cmd->Help_Set("check var1 by var2 and increment var3");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("check", "check"));
            cmd->Item_Add(new Cmd_Item_Word("if", "check if"));
            cmd->Item_Add(new Cmd_Item_Str("<var1_name>", "var1 name"));
            cmd->Item_Add(new Cmd_Item_EQU_Range("<compare: " + cmp_str_str + ">", "compare function", cmp_str_words));
            cmd->Item_Add(new Cmd_Item_Int("<var2_name>", "var2 name"));
            cmd->Item_Add(new Cmd_Item_Word("as", "as"));
            cmd->Item_Add(new Cmd_Item_Word("var", "as var"));
            cmd->Item_Add(new Cmd_Item_Word("inc", "check and increment"));
            cmd->Item_Add(new Cmd_Item_Str("<var3_name>", "var3 name to increment (if compare result = true)"));

            Cmd_Add(cmd);
        }
        {
            // check if str compare STR as var inc str else inc str // @Attention: Must be after check if str compare INT inc str
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_check_if_str_compare_str_as_var_inc_str_else_inc_str);
            cmd->Text_Set("check if <var1_name> <compare: " + cmp_str_str + "> <var2_name> as var inc <var3_name> else inc <var4_name>");
            cmd->Help_Set("check var1 by var2 and increment var3 or var4");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("check", "check"));
            cmd->Item_Add(new Cmd_Item_Word("if", "check if"));
            cmd->Item_Add(new Cmd_Item_Str("<var1_name>", "var1 name"));
            cmd->Item_Add(new Cmd_Item_EQU_Range("<compare: " + cmp_str_str + ">", "compare function", cmp_str_words));
            cmd->Item_Add(new Cmd_Item_Int("<var2_name>", "var2 name"));
            cmd->Item_Add(new Cmd_Item_Word("as", "as"));
            cmd->Item_Add(new Cmd_Item_Word("var", "as var"));
            cmd->Item_Add(new Cmd_Item_Word("inc", "check and increment"));
            cmd->Item_Add(new Cmd_Item_Str("<var3_name>", "var3 name to increment (if compare result = true)"));
            cmd->Item_Add(new Cmd_Item_Word("else", "else"));
            cmd->Item_Add(new Cmd_Item_Word("inc", "check and increment"));
            cmd->Item_Add(new Cmd_Item_Str("<var4_name>", "var4 name to increment (if compare result = false)"));

            Cmd_Add(cmd);
        }

        {
            // check if str compare STR as var do script stop // @Attention: Must be after check if str compare INT do script stop
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_check_if_str_compare_str_as_var_do_script_stop);
            cmd->Text_Set("check if <var1_name>  <compare: " + cmp_str_str + "> <var2_name> as var do script stop");
            cmd->Help_Set("check var1 by var2 and stop script");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("check", "check"));
            cmd->Item_Add(new Cmd_Item_Word("if", "check if"));
            cmd->Item_Add(new Cmd_Item_Str("<var1_name>", "var1 name"));
            cmd->Item_Add(new Cmd_Item_EQU_Range("<compare: " + cmp_str_str + ">", "compare function", cmp_str_words));
            cmd->Item_Add(new Cmd_Item_Int("<var2_name>", "var2 name"));
            cmd->Item_Add(new Cmd_Item_Word("as", "as"));
            cmd->Item_Add(new Cmd_Item_Word("var", "as var"));
            cmd->Item_Add(new Cmd_Item_Word("do", "do"));
            cmd->Item_Add(new Cmd_Item_Word("script", "do script"));
            cmd->Item_Add(new Cmd_Item_Word("stop", "do script stop"));

            Cmd_Add(cmd);
        }

        {
            // check if str compare STR as var do script str // @Attention: Must be after check if str compare INT do script str
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_check_if_str_compare_str_as_var_do_script_filename);
            cmd->Text_Set("check if <var1_name>  <compare: " + cmp_str_str + "> <var2_name> as var do script <filename>");
            cmd->Help_Set("check var1 by var2 and do script from file");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("check", "check"));
            cmd->Item_Add(new Cmd_Item_Word("if", "check if"));
            cmd->Item_Add(new Cmd_Item_Str("<var1_name>", "var1 name"));
            cmd->Item_Add(new Cmd_Item_EQU_Range("<compare: " + cmp_str_str + ">", "compare function", cmp_str_words));
            cmd->Item_Add(new Cmd_Item_Str("<var2_name>", "var2 name"));
            cmd->Item_Add(new Cmd_Item_Word("as", "as"));
            cmd->Item_Add(new Cmd_Item_Word("var", "as var"));
            cmd->Item_Add(new Cmd_Item_Word("do", "do"));
            cmd->Item_Add(new Cmd_Item_Word("script", "do script"));
            cmd->Item_Add(new Cmd_Item_Str("<filename>", "script file name"));

            Cmd_Add(cmd);
        }
        {
            // check if str compare STR as var do script str no history // @Attention: Must be after check if str compare INT do script str
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_check_if_str_compare_str_as_var_do_script_filename_no_history);
            cmd->Text_Set("check if <var1_name>  <compare: " + cmp_str_str + "> <var2_name> as var do script <filename> no history");
            cmd->Help_Set("check var1 by var2 and do script from file, not save to history");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("check", "check"));
            cmd->Item_Add(new Cmd_Item_Word("if", "check if"));
            cmd->Item_Add(new Cmd_Item_Str("<var1_name>", "var1 name"));
            cmd->Item_Add(new Cmd_Item_EQU_Range("<compare: " + cmp_str_str + ">", "compare function", cmp_str_words));
            cmd->Item_Add(new Cmd_Item_Str("<var2_name>", "var2 name"));
            cmd->Item_Add(new Cmd_Item_Word("as", "as"));
            cmd->Item_Add(new Cmd_Item_Word("var", "as var"));
            cmd->Item_Add(new Cmd_Item_Word("do", "do"));
            cmd->Item_Add(new Cmd_Item_Word("script", "do script"));
            cmd->Item_Add(new Cmd_Item_Str("<filename>", "script file name"));
            cmd->Item_Add(new Cmd_Item_Word("no", "not save"));
            cmd->Item_Add(new Cmd_Item_Str("history", "not save to history"));

            Cmd_Add(cmd);
        }
        // </editor-fold>

        // <editor-fold defaultstate="collapsed" desc="Check if: int/str as value/str as var do command">
        {
            // check if str compare INT do command str // @Attention: Must be before check if str compare INT do command str
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_check_if_str_compare_int_do_command_str);
            cmd->Text_Set("check if <var_name>  <compare: " + cmp_str_str + "> <int_value> do command <command_str>");
            cmd->Help_Set("check var by int and do command");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("check", "check"));
            cmd->Item_Add(new Cmd_Item_Word("if", "check if"));
            cmd->Item_Add(new Cmd_Item_Str("<var_name>", "var name"));
            cmd->Item_Add(new Cmd_Item_EQU_Range("<compare: " + cmp_str_str + ">", "compare function", cmp_str_words));
            cmd->Item_Add(new Cmd_Item_Str("<int_value>", "value to compare"));
            cmd->Item_Add(new Cmd_Item_Word("do", "do"));
            cmd->Item_Add(new Cmd_Item_Word("command", "do command"));
            cmd->Item_Add(new Cmd_Item_Str("<command_str>", "command"));

            Cmd_Add(cmd);
        }
        {
            // check if str compare INT do command str else do command str // @Attention: Must be before check if str compare INT do command str
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_check_if_str_compare_int_do_command_str_else_do_command_str);
            cmd->Text_Set("check if <var_name>  <compare: " + cmp_str_str + "> <int_value> do command <command1_str> else do command <command2_str>");
            cmd->Help_Set("check var by int and do command1 or do command2");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("check", "check"));
            cmd->Item_Add(new Cmd_Item_Word("if", "check if"));
            cmd->Item_Add(new Cmd_Item_Str("<var_name>", "var name"));
            cmd->Item_Add(new Cmd_Item_EQU_Range("<compare: " + cmp_str_str + ">", "compare function", cmp_str_words));
            cmd->Item_Add(new Cmd_Item_Str("<int_value>", "value to compare"));
            cmd->Item_Add(new Cmd_Item_Word("do", "do"));
            cmd->Item_Add(new Cmd_Item_Word("command", "do command"));
            cmd->Item_Add(new Cmd_Item_Str("<command1_str>", "command1"));
            cmd->Item_Add(new Cmd_Item_Word("else", "else"));
            cmd->Item_Add(new Cmd_Item_Word("do", "do"));
            cmd->Item_Add(new Cmd_Item_Word("command", "do command"));
            cmd->Item_Add(new Cmd_Item_Str("<command2_str>", "command2"));

            Cmd_Add(cmd);
        }

        {
            // check if str compare STR as value do command str // @Attention: Must be after check if str compare INT do command str
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_check_if_str_compare_str_as_value_do_command_str);
            cmd->Text_Set("check if <var_name>  <compare: " + cmp_str_str + "> <str> as value do command <command_str>");
            cmd->Help_Set("check var by str and do command");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("check", "check"));
            cmd->Item_Add(new Cmd_Item_Word("if", "check if"));
            cmd->Item_Add(new Cmd_Item_Str("<var_name>", "var name"));
            cmd->Item_Add(new Cmd_Item_EQU_Range("<compare: " + cmp_str_str + ">", "compare function", cmp_str_words));
            cmd->Item_Add(new Cmd_Item_Str("<str>", "str to compare"));
            cmd->Item_Add(new Cmd_Item_Word("as", "as"));
            cmd->Item_Add(new Cmd_Item_Word("value", "as value"));
            cmd->Item_Add(new Cmd_Item_Word("do", "do"));
            cmd->Item_Add(new Cmd_Item_Word("command", "do command"));
            cmd->Item_Add(new Cmd_Item_Str("<command_str>", "command"));

            Cmd_Add(cmd);
        }
        {
            // check if str compare STR as value do command str else do command str // @Attention: Must be after check if str compare INT do command str
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_check_if_str_compare_str_as_value_do_command_str_else_do_command_str);
            cmd->Text_Set("check if <var_name>  <compare: " + cmp_str_str + "> <str> as value do command <command1_str> else do command <command2_str>");
            cmd->Help_Set("check var by str and do command1 or do command2");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("check", "check"));
            cmd->Item_Add(new Cmd_Item_Word("if", "check if"));
            cmd->Item_Add(new Cmd_Item_Str("<var_name>", "var name"));
            cmd->Item_Add(new Cmd_Item_EQU_Range("<compare: " + cmp_str_str + ">", "compare function", cmp_str_words));
            cmd->Item_Add(new Cmd_Item_Str("<str>", "str to compare"));
            cmd->Item_Add(new Cmd_Item_Word("as", "as"));
            cmd->Item_Add(new Cmd_Item_Word("value", "as value"));
            cmd->Item_Add(new Cmd_Item_Word("do", "do"));
            cmd->Item_Add(new Cmd_Item_Word("command", "do command"));
            cmd->Item_Add(new Cmd_Item_Str("<command1_str>", "command1"));
            cmd->Item_Add(new Cmd_Item_Word("else", "else"));
            cmd->Item_Add(new Cmd_Item_Word("do", "do"));
            cmd->Item_Add(new Cmd_Item_Word("command", "do command"));
            cmd->Item_Add(new Cmd_Item_Str("<command2_str>", "command2"));

            Cmd_Add(cmd);
        }

        {
            // check if str compare STR as var do command str // @Attention: Must be after check if str compare INT do command str
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_check_if_str_compare_str_as_var_do_command_str);
            cmd->Text_Set("check if <var1_name>  <compare: " + cmp_str_str + "> <var2_name> as var do command <command_str>");
            cmd->Help_Set("check var1 by var2 and do command");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("check", "check"));
            cmd->Item_Add(new Cmd_Item_Word("if", "check if"));
            cmd->Item_Add(new Cmd_Item_Str("<var1_name>", "var1 name"));
            cmd->Item_Add(new Cmd_Item_EQU_Range("<compare: " + cmp_str_str + ">", "compare function", cmp_str_words));
            cmd->Item_Add(new Cmd_Item_Str("<var2_name>", "var2 name"));
            cmd->Item_Add(new Cmd_Item_Word("as", "as"));
            cmd->Item_Add(new Cmd_Item_Word("var", "as var"));
            cmd->Item_Add(new Cmd_Item_Word("do", "do"));
            cmd->Item_Add(new Cmd_Item_Word("command", "do command"));
            cmd->Item_Add(new Cmd_Item_Str("<command_str>", "command"));

            Cmd_Add(cmd);
        }
        {
            // check if str compare STR as var do command str else do command str // @Attention: Must be after check if str compare INT do command str
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_check_if_str_compare_str_as_var_do_command_str_else_do_command_str);
            cmd->Text_Set("check if <var1_name>  <compare: " + cmp_str_str + "> <var2_name> as var do command <command1_str> else do command <command2_str>");
            cmd->Help_Set("check var1 by var2 and do command1 or do command2");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("check", "check"));
            cmd->Item_Add(new Cmd_Item_Word("if", "check if"));
            cmd->Item_Add(new Cmd_Item_Str("<var1_name>", "var1 name"));
            cmd->Item_Add(new Cmd_Item_EQU_Range("<compare: " + cmp_str_str + ">", "compare function", cmp_str_words));
            cmd->Item_Add(new Cmd_Item_Str("<var2_name>", "var2 name"));
            cmd->Item_Add(new Cmd_Item_Word("as", "as"));
            cmd->Item_Add(new Cmd_Item_Word("var", "as var"));
            cmd->Item_Add(new Cmd_Item_Word("do", "do"));
            cmd->Item_Add(new Cmd_Item_Word("command", "do command"));
            cmd->Item_Add(new Cmd_Item_Str("<command1_str>", "command1"));
            cmd->Item_Add(new Cmd_Item_Word("else", "else"));
            cmd->Item_Add(new Cmd_Item_Word("do", "do"));
            cmd->Item_Add(new Cmd_Item_Word("command", "do command"));
            cmd->Item_Add(new Cmd_Item_Str("<command2_str>", "command2"));

            Cmd_Add(cmd);
        }
        // </editor-fold>

        // <editor-fold defaultstate="collapsed" desc="Label: label/goto label">
        {
            // check label str
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_check_label_str);
            cmd->Text_Set("check label <label_name>");
            cmd->Help_Set("create label <label_name> (for scripts only)");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("check", "check"));
            cmd->Item_Add(new Cmd_Item_Word("label", "create label"));
            cmd->Item_Add(new Cmd_Item_Str("<label_name>", "label name"));

            Cmd_Add(cmd);
        }

        {
            // check goto label
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_check_goto_label);
            cmd->Text_Set("check goto <label_name>");
            cmd->Help_Set("goto <label_name> (for scripts only)");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("check", "check"));
            cmd->Item_Add(new Cmd_Item_Word("goto", "goto"));
            cmd->Item_Add(new Cmd_Item_Str("<label_name>", "label name"));

            Cmd_Add(cmd);
        }
        // </editor-fold>

        // <editor-fold defaultstate="collapsed" desc="Check if: int/str as value/str as var goto label">
        {
            // check if str compare INT goto str
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_check_if_str_compare_int_goto_str);
            cmd->Text_Set("check if <var_name>  <compare: " + cmp_int_str + "> <int_value> goto <label_name>");
            cmd->Help_Set("check var by int and goto <label_name>(for scripts only)");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("check", "check"));
            cmd->Item_Add(new Cmd_Item_Word("if", "check if"));
            cmd->Item_Add(new Cmd_Item_Str("<var_name>", "var name"));
            cmd->Item_Add(new Cmd_Item_EQU_Range("<compare: " + cmp_str_str + ">", "compare function", cmp_str_words));
            cmd->Item_Add(new Cmd_Item_Int("<int_value>", "value to compare"));
            cmd->Item_Add(new Cmd_Item_Word("goto", "goto"));
            cmd->Item_Add(new Cmd_Item_Str("<label_name>", "label name"));

            Cmd_Add(cmd);
        }
        {
            // check if str compare INT goto str else goto str
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_check_if_str_compare_int_goto_str_else_goto_str);
            cmd->Text_Set("check if <var_name>  <compare: " + cmp_int_str + "> <int_value> goto <label1_name> else goto <label2_name>");
            cmd->Help_Set("check var by int and goto <label1_name> or <label2_name> (for scripts only)");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("check", "check"));
            cmd->Item_Add(new Cmd_Item_Word("if", "check if"));
            cmd->Item_Add(new Cmd_Item_Str("<var_name>", "var name"));
            cmd->Item_Add(new Cmd_Item_EQU_Range("<compare: " + cmp_str_str + ">", "compare function", cmp_str_words));
            cmd->Item_Add(new Cmd_Item_Int("<int_value>", "value to compare"));
            cmd->Item_Add(new Cmd_Item_Word("goto", "goto"));
            cmd->Item_Add(new Cmd_Item_Str("<label1_name>", "label1 name"));
            cmd->Item_Add(new Cmd_Item_Word("else", "else"));
            cmd->Item_Add(new Cmd_Item_Word("goto", "goto"));
            cmd->Item_Add(new Cmd_Item_Str("<label2_name>", "label2 name"));

            Cmd_Add(cmd);
        }

        {
            // check if str compare str as value goto str
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_check_if_str_compare_str_as_value_goto_str);
            cmd->Text_Set("check if <var_name>  <compare: " + cmp_int_str + "> <str> as value goto <label1_name> else goto <label2_name>");
            cmd->Help_Set("check var by str and goto <label1_name> or <label2_name> (for scripts only)");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("check", "check"));
            cmd->Item_Add(new Cmd_Item_Word("if", "check if"));
            cmd->Item_Add(new Cmd_Item_Str("<var_name>", "var name"));
            cmd->Item_Add(new Cmd_Item_EQU_Range("<compare: " + cmp_str_str + ">", "compare function", cmp_str_words));
            cmd->Item_Add(new Cmd_Item_Str("<str>", "str to compare"));
            cmd->Item_Add(new Cmd_Item_Word("as", "as"));
            cmd->Item_Add(new Cmd_Item_Word("value", "as value"));
            cmd->Item_Add(new Cmd_Item_Word("goto", "goto"));
            cmd->Item_Add(new Cmd_Item_Str("<label1_name>", "label1 name"));
            cmd->Item_Add(new Cmd_Item_Word("else", "else"));
            cmd->Item_Add(new Cmd_Item_Word("goto", "goto"));
            cmd->Item_Add(new Cmd_Item_Str("<label2_name>", "label2 name"));

            Cmd_Add(cmd);
        }
        {
            // check if str compare str as value goto str else goto str
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_check_if_str_compare_str_as_value_goto_str_else_goto_str);
            cmd->Text_Set("check if <var_name>  <compare: " + cmp_int_str + "> <str> as value goto <label1_name> else goto <label2_name>");
            cmd->Help_Set("check var by str and goto <label1_name> or <label2_name> (for scripts only)");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("check", "check"));
            cmd->Item_Add(new Cmd_Item_Word("if", "check if"));
            cmd->Item_Add(new Cmd_Item_Str("<var_name>", "var name"));
            cmd->Item_Add(new Cmd_Item_EQU_Range("<compare: " + cmp_str_str + ">", "compare function", cmp_str_words));
            cmd->Item_Add(new Cmd_Item_Str("<str>", "str to compare"));
            cmd->Item_Add(new Cmd_Item_Word("as", "as"));
            cmd->Item_Add(new Cmd_Item_Word("value", "as value"));
            cmd->Item_Add(new Cmd_Item_Word("goto", "goto"));
            cmd->Item_Add(new Cmd_Item_Str("<label1_name>", "label1 name"));
            cmd->Item_Add(new Cmd_Item_Word("else", "else"));
            cmd->Item_Add(new Cmd_Item_Word("goto", "goto"));
            cmd->Item_Add(new Cmd_Item_Str("<label2_name>", "label2 name"));

            Cmd_Add(cmd);
        }

        {
            // check if str compare str as var goto str
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_check_if_str_compare_str_as_var_goto_str);
            cmd->Text_Set("check if <var1_name>  <compare: " + cmp_int_str + "> <var2_name> as var goto <label_name>");
            cmd->Help_Set("check var1 by var2 and goto <label_name> (for scripts only)");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("check", "check"));
            cmd->Item_Add(new Cmd_Item_Word("if", "check if"));
            cmd->Item_Add(new Cmd_Item_Str("<var1_name>", "var1 name"));
            cmd->Item_Add(new Cmd_Item_EQU_Range("<compare: " + cmp_str_str + ">", "compare function", cmp_str_words));
            cmd->Item_Add(new Cmd_Item_Str("<var2_name>", "var2 name"));
            cmd->Item_Add(new Cmd_Item_Word("as", "as"));
            cmd->Item_Add(new Cmd_Item_Word("var", "as var"));
            cmd->Item_Add(new Cmd_Item_Word("goto", "goto"));
            cmd->Item_Add(new Cmd_Item_Str("<label_name>", "label name"));

            Cmd_Add(cmd);
        }
        {
            // check if str compare str as var goto str else goto str
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_check_if_str_compare_str_as_var_goto_str_else_goto_str);
            cmd->Text_Set("check if <var1_name>  <compare: " + cmp_int_str + "> <var2_name> as var goto <label1_name> else goto <label2_name>");
            cmd->Help_Set("check var1 by var2 and goto <label1_name> or <label2_name> (for scripts only)");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("check", "check"));
            cmd->Item_Add(new Cmd_Item_Word("if", "check if"));
            cmd->Item_Add(new Cmd_Item_Str("<var1_name>", "var1 name"));
            cmd->Item_Add(new Cmd_Item_EQU_Range("<compare: " + cmp_str_str + ">", "compare function", cmp_str_words));
            cmd->Item_Add(new Cmd_Item_Str("<var2_name>", "var2 name"));
            cmd->Item_Add(new Cmd_Item_Word("as", "as"));
            cmd->Item_Add(new Cmd_Item_Word("var", "as var"));
            cmd->Item_Add(new Cmd_Item_Word("goto", "goto"));
            cmd->Item_Add(new Cmd_Item_Str("<label1_name>", "label1 name"));
            cmd->Item_Add(new Cmd_Item_Word("else", "else"));
            cmd->Item_Add(new Cmd_Item_Word("goto", "goto"));
            cmd->Item_Add(new Cmd_Item_Str("<label2_name>", "label2 name"));

            Cmd_Add(cmd);
        }
        // </editor-fold>

    }

    virtual ~Cli_Module_Check() {
    }

    // <editor-fold defaultstate="collapsed" desc="Values_Map: print, clear">

    bool check_map_print(string var_filter, Str_Filter_Abstract &str_filter) {

        Cli_Output.Output_NewLine();

        if (!Values_Map.empty()) {
            Cli_Output.Output_Str("Values Map:");
            Cli_Output.Output_NewLine();
            bool found = false;
            for (map<string, string>::iterator iter = Values_Map.begin();
                    iter != Values_Map.end(); iter++) {
                if (str_filter.Is_Match(var_filter, iter->first)) {
                    Cli_Output.Output_Str(iter->first + " = " + iter->second);
                    Cli_Output.Output_NewLine();
                    found = true;
                }
            }
            if (!found) {
                Cli_Output.Output_Str(var_filter);
                Cli_Output.Output_Str(" - Not Found");
                Cli_Output.Output_NewLine();
            }
        } else {
            Cli_Output.Output_Str("Values Map is empty");
            Cli_Output.Output_NewLine();
        }

        return true;
    }

    bool check_map_clear() {

        Cli_Output.Output_NewLine();

        if (!Values_Map.empty()) {
            Values_Map.clear();
            Cli_Output.Output_Str("Values Map cleared");
            Cli_Output.Output_NewLine();
        } else {
            Cli_Output.Output_Str("Values Map is empty");
            Cli_Output.Output_NewLine();
        }

        return true;
    }

    // </editor-fold>

    // <editor-fold defaultstate="collapsed" desc="Values_Map: modules to map">

    bool check_modules_to_map(string module_filter, Str_Filter_Abstract &str_filter) {
        Cli_Output.Output_NewLine();
        bool found = false;
        for (int module = 0; module < Modules.Get_Size(); module++) {
            Cli_Module *module_ptr = Modules.Get(module);
            if (module_ptr) {
                string module_name = module_ptr->Name_Get();
                string module_name_with_commas = "\"" + module_ptr->Name_Get() + "\"";
                if (str_filter.Is_Match(module_filter, module_name)
                        || str_filter.Is_Match(module_filter, module_name_with_commas)) {
                    module_ptr->To_Map(Values_Map);
                    Cli_Output.Output_Str(module_name + " -> Values Map");
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

    // </editor-fold>

    // <editor-fold defaultstate="collapsed" desc="Var: set as value, as var, as expression, force">

    bool check_var_set_str_as_value(string var_left, string value, bool is_force) {
        map<string, string>::iterator var_left_iter = Values_Map.find(var_left);
        if (var_left_iter != Values_Map.end() || is_force) {
            Values_Map[var_left] = value;
            if (var_left_iter == Values_Map.end()) {
                Cli_Output.Output_NewLine();
                Cli_Output.Output_Str("Var Created: " + var_left + " = " + value);
                Cli_Output.Output_NewLine();
            }
        } else {
            Cli_Output.Output_NewLine();
            Cli_Output.Output_Str("ERROR: var " + var_left + " not found");
            Cli_Output.Output_NewLine();
        }

        return true;
    }

    bool check_var_set_str_as_var(string var_left, string var_right, bool is_force) {
        map<string, string>::iterator var_left_iter = Values_Map.find(var_left);
        map<string, string>::iterator var_right_iter = Values_Map.find(var_right);
        if ((var_left_iter != Values_Map.end() && var_right_iter != Values_Map.end()) || is_force) {
            string value = var_right_iter->second;
            Values_Map[var_left] = value;
            if (var_left_iter == Values_Map.end()) {
                Cli_Output.Output_NewLine();
                Cli_Output.Output_Str("Var Created: " + var_left + " = " + value);
                Cli_Output.Output_NewLine();
            }
        } else {
            Cli_Output.Output_NewLine();

            if (var_left_iter == Values_Map.end()) {
                Cli_Output.Output_Str("ERROR: var " + var_left + " not found");
            }
            if (var_right_iter == Values_Map.end()) {
                Cli_Output.Output_Str("ERROR: var " + var_right + " not found");
            }

            Cli_Output.Output_NewLine();
        }

        return true;
    }

    string Expr_Calc(map<string, string> &values_map, string expr) {
        return "<Expr_Calc(" + expr + ")>";
    }

    bool check_var_set_str_as_expr(string var_left, string expr, bool is_force) {
        map<string, string>::iterator var_left_iter = Values_Map.find(var_left);
        if (var_left_iter != Values_Map.end() || is_force) {
            string value = Expr_Calc(Values_Map, expr);
            Values_Map[var_left] = value;
            if (var_left_iter == Values_Map.end()) {
                Cli_Output.Output_NewLine();
                Cli_Output.Output_Str("Var Created: " + var_left + " = " + value);
                Cli_Output.Output_NewLine();
            }
        } else {
            Cli_Output.Output_NewLine();
            Cli_Output.Output_Str("ERROR: var " + var_left + " not found");
            Cli_Output.Output_NewLine();
        }

        return true;
    }

    // </editor-fold>

    // <editor-fold defaultstate="collapsed" desc="Var: inc">

    bool check_var_inc_value(string var_left) {
        map<string, string>::iterator var_left_iter = Values_Map.find(var_left);
        if (var_left_iter != Values_Map.end()) {
            int value = atoi(var_left_iter->second.c_str());
            value++;
            stringstream s_str;
            s_str << value;
            Values_Map[var_left] = s_str.str();
        } else {
            Cli_Output.Output_NewLine();
            Cli_Output.Output_Str("ERROR: var " + var_left + " not found");
            Cli_Output.Output_NewLine();
        }

        return true;
    }

    // </editor-fold>

    // <editor-fold defaultstate="collapsed" desc="Compare_Values: int/str">

    Local_Compare_Result Compare_Values_Int(int var_left_value, string s_compare, int var_right_value) {
        Local_Compare_Result cmp_res = CMP_FALSE;
        if (s_compare == "==") {
            if (var_left_value == var_right_value) cmp_res = CMP_TRUE;
        } else if (s_compare == "!=") {
            if (var_left_value != var_right_value) cmp_res = CMP_TRUE;
        } else if (s_compare == "<") {
            if (var_left_value < var_right_value) cmp_res = CMP_TRUE;
        } else if (s_compare == ">") {
            if (var_left_value > var_right_value) cmp_res = CMP_TRUE;
        } else if (s_compare == "<=") {
            if (var_left_value <= var_right_value) cmp_res = CMP_TRUE;
        } else if (s_compare == ">=") {
            if (var_left_value >= var_right_value) cmp_res = CMP_TRUE;
        } else if (s_compare == "&") {
            if (var_left_value & var_right_value) cmp_res = CMP_TRUE;
        } else if (s_compare == "|") {
            if (var_left_value | var_right_value) cmp_res = CMP_TRUE;
        } else if (s_compare == "&&") {
            if (var_left_value && var_right_value) cmp_res = CMP_TRUE;
        } else if (s_compare == "||") {
            if (var_left_value || var_right_value) cmp_res = CMP_TRUE;
        } else {
            cmp_res = CMP_ERROR;
        }
        return cmp_res;
    }

    Local_Compare_Result Compare_Values_Str(string var_left_value, string s_compare, string var_right_value) {
        Local_Compare_Result cmp_res = CMP_FALSE;
        if (s_compare == "==") {
            if (var_left_value == var_right_value) cmp_res = CMP_TRUE;
        } else if (s_compare == "!=") {
            if (var_left_value != var_right_value) cmp_res = CMP_TRUE;
        } else if (s_compare == "<") {
            if (var_left_value < var_right_value) cmp_res = CMP_TRUE;
        } else if (s_compare == ">") {
            if (var_left_value > var_right_value) cmp_res = CMP_TRUE;
        } else if (s_compare == "<=") {
            if (var_left_value <= var_right_value) cmp_res = CMP_TRUE;
        } else if (s_compare == ">=") {
            if (var_left_value >= var_right_value) cmp_res = CMP_TRUE;
        } else {
            cmp_res = CMP_ERROR;
        }
        return cmp_res;
    }

    // </editor-fold>

    // <editor-fold defaultstate="collapsed" desc="Check if: int/str as value/as var print/inc">

    bool check_var_by_int_print_msg1_or_msg2(string var_left, string s_compare, int var_right_value,
            string s_msg1, bool is_msg2, string s_msg2) {
        map<string, string>::iterator var_left_iter = Values_Map.find(var_left);
        if (var_left_iter != Values_Map.end()) {
            int var_left_value = atoi(var_left_iter->second.c_str());
            Local_Compare_Result cmp_res = Compare_Values_Int(var_left_value, s_compare, var_right_value);
            if (cmp_res == CMP_TRUE) {
                Cli_Output.Output_Str(s_msg1);
                Cli_Output.Output_NewLine();
            } else if (cmp_res == CMP_FALSE) {
                if (is_msg2) {
                    Cli_Output.Output_Str(s_msg2);
                    Cli_Output.Output_NewLine();
                }
            } else if (cmp_res == CMP_ERROR) {
                Cli_Output.Output_Str("ERROR: compare operation " + s_compare + " not found");
                Cli_Output.Output_NewLine();
            }

        } else {
            Cli_Output.Output_Str("ERROR: var " + var_left + " not found");
            Cli_Output.Output_NewLine();
        }

        return true;
    }

    bool check_var_by_str_print_msg1_or_msg2(string var_left, string s_compare, string var_right_value,
            string s_msg1, bool is_msg2, string s_msg2) {
        map<string, string>::iterator var_left_iter = Values_Map.find(var_left);

        Cli_Output.Output_NewLine();

        if (var_left_iter != Values_Map.end()) {
            string var_left_value = var_left_iter->second;
            Local_Compare_Result cmp_res = Compare_Values_Str(var_left_value, s_compare, var_right_value);
            if (cmp_res == CMP_TRUE) {
                Cli_Output.Output_Str(s_msg1);
                Cli_Output.Output_NewLine();
            } else if (cmp_res == CMP_FALSE) {
                if (is_msg2) {
                    Cli_Output.Output_Str(s_msg2);
                    Cli_Output.Output_NewLine();
                }
            } else if (cmp_res == CMP_ERROR) {
                Cli_Output.Output_Str("ERROR: compare operation " + s_compare + " not found");
                Cli_Output.Output_NewLine();
            }
        } else {
            Cli_Output.Output_Str("ERROR: var " + var_left + " not found");
            Cli_Output.Output_NewLine();
        }

        return true;
    }

    bool check_var_by_var_print_msg1_or_msg2(string var_left, string s_compare, string var_right,
            string s_msg1, bool is_msg2, string s_msg2) {
        map<string, string>::iterator var_left_iter = Values_Map.find(var_left);
        map<string, string>::iterator var_right_iter = Values_Map.find(var_right);

        Cli_Output.Output_NewLine();

        if (var_left_iter != Values_Map.end() && var_right_iter != Values_Map.end()) {
            int var_right_value = atoi(var_right_iter->second.c_str());
            return check_var_by_int_print_msg1_or_msg2(var_left, s_compare, var_right_value, s_msg1, is_msg2, s_msg2);
        } else {
            if (var_left_iter == Values_Map.end()) {
                Cli_Output.Output_Str("ERROR: var " + var_left + " not found");
                Cli_Output.Output_NewLine();
            }
            if (var_right_iter == Values_Map.end()) {
                Cli_Output.Output_Str("ERROR: var " + var_right + " not found");
                Cli_Output.Output_NewLine();
            }
        }

        return true;
    }

    bool check_var_by_int_inc_var1_or_var2(string var_left, string s_compare, int var_right_value,
            string var1_inc, bool is_var2_inc, string var2_inc) {
        map<string, string>::iterator var_left_iter = Values_Map.find(var_left);
        map<string, string>::iterator var1_inc_iter = Values_Map.find(var1_inc);
        map<string, string>::iterator var2_inc_iter = Values_Map.find(var2_inc);

        Cli_Output.Output_NewLine();

        if (var_left_iter != Values_Map.end() && var1_inc_iter != Values_Map.end()
                && ((is_var2_inc && var1_inc_iter != Values_Map.end()) || !is_var2_inc)) {
            int var_left_value = atoi(var_left_iter->second.c_str());
            int var1_value = atoi(var1_inc_iter->second.c_str());
            int var2_value = atoi(var2_inc_iter->second.c_str());

            Local_Compare_Result cmp_res = Compare_Values_Int(var_left_value, s_compare, var_right_value);
            if (cmp_res == CMP_TRUE) {
                var1_value++;
                stringstream s_str;
                s_str << var1_value;
                Values_Map[var_left] = s_str.str();
            } else if (cmp_res == CMP_FALSE) {
                if (is_var2_inc) {
                    var2_value++;
                    stringstream s_str;
                    s_str << var2_value;
                    Values_Map[var_left] = s_str.str();
                }
            } else if (cmp_res == CMP_ERROR) {
                Cli_Output.Output_Str("ERROR: compare operation " + s_compare + " not found");
                Cli_Output.Output_NewLine();
            }

        } else {
            if (var_left_iter == Values_Map.end()) {
                Cli_Output.Output_Str("ERROR: var " + var_left + " not found");
                Cli_Output.Output_NewLine();
            }
            if (var1_inc_iter == Values_Map.end()) {
                Cli_Output.Output_Str("ERROR: var " + var1_inc + " not found");
                Cli_Output.Output_NewLine();
            }
            if (is_var2_inc && var2_inc_iter == Values_Map.end()) {
                Cli_Output.Output_Str("ERROR: var " + var2_inc + " not found");
                Cli_Output.Output_NewLine();
            }
        }

        return true;
    }

    bool check_var_by_str_inc_var1_or_var2(string var_left, string s_compare, string var_right_value,
            string var1_inc, bool is_var2_inc, string var2_inc) {
        map<string, string>::iterator var_left_iter = Values_Map.find(var_left);
        map<string, string>::iterator var1_inc_iter = Values_Map.find(var1_inc);
        map<string, string>::iterator var2_inc_iter = Values_Map.find(var2_inc);

        Cli_Output.Output_NewLine();

        if (var_left_iter != Values_Map.end() && var1_inc_iter != Values_Map.end()
                && ((is_var2_inc && var1_inc_iter != Values_Map.end()) || !is_var2_inc)) {
            int var1_value = atoi(var1_inc_iter->second.c_str());
            int var2_value = atoi(var2_inc_iter->second.c_str());

            string var_left_value = var_left_iter->second;
            Local_Compare_Result cmp_res = Compare_Values_Str(var_left_value, s_compare, var_right_value);
            if (cmp_res == CMP_TRUE) {
                var1_value++;
                stringstream s_str;
                s_str << var1_value;
                Values_Map[var_left] = s_str.str();
            } else if (cmp_res == CMP_FALSE) {
                if (is_var2_inc) {
                    var2_value++;
                    stringstream s_str;
                    s_str << var2_value;
                    Values_Map[var_left] = s_str.str();
                }
            } else if (cmp_res == CMP_ERROR) {
                Cli_Output.Output_Str("ERROR: compare operation " + s_compare + " not found");
                Cli_Output.Output_NewLine();
            }

        } else {
            if (var_left_iter == Values_Map.end()) {
                Cli_Output.Output_Str("ERROR: var " + var_left + " not found");
                Cli_Output.Output_NewLine();
            }
            if (var1_inc_iter == Values_Map.end()) {
                Cli_Output.Output_Str("ERROR: var " + var1_inc + " not found");
                Cli_Output.Output_NewLine();
            }
            if (is_var2_inc && var2_inc_iter == Values_Map.end()) {
                Cli_Output.Output_Str("ERROR: var " + var2_inc + " not found");
                Cli_Output.Output_NewLine();
            }
        }

        return true;
    }

    bool check_var_by_var_inc_var1_or_var2(string var_left, string s_compare, string var_right,
            string var1_inc, bool is_var2_inc, string var2_inc) {
        map<string, string>::iterator var_left_iter = Values_Map.find(var_left);
        map<string, string>::iterator var_right_iter = Values_Map.find(var_right);
        map<string, string>::iterator var1_inc_iter = Values_Map.find(var1_inc);
        map<string, string>::iterator var2_inc_iter = Values_Map.find(var2_inc);

        Cli_Output.Output_NewLine();

        if (var_left_iter != Values_Map.end()
                && var_right_iter != Values_Map.end()
                && var1_inc_iter != Values_Map.end()
                && ((is_var2_inc && var1_inc_iter != Values_Map.end()) || !is_var2_inc)) {
            int var1_value = atoi(var1_inc_iter->second.c_str());
            int var2_value = atoi(var2_inc_iter->second.c_str());

            string var_left_value = var_left_iter->second;
            string var_right_value = var_right_iter->second;
            Local_Compare_Result cmp_res = Compare_Values_Str(var_left_value, s_compare, var_right_value);
            if (cmp_res == CMP_TRUE) {
                var1_value++;
                stringstream s_str;
                s_str << var1_value;
                Values_Map[var_left] = s_str.str();
            } else if (cmp_res == CMP_FALSE) {
                if (is_var2_inc) {
                    var2_value++;
                    stringstream s_str;
                    s_str << var2_value;
                    Values_Map[var_left] = s_str.str();
                }
            } else if (cmp_res == CMP_ERROR) {
                Cli_Output.Output_Str("ERROR: compare operation " + s_compare + " not found");
                Cli_Output.Output_NewLine();
            }

        } else {
            if (var_left_iter == Values_Map.end()) {
                Cli_Output.Output_Str("ERROR: var " + var_left + " not found");
                Cli_Output.Output_NewLine();
            }
            if (var_right_iter == Values_Map.end()) {
                Cli_Output.Output_Str("ERROR: var " + var_right + " not found");
                Cli_Output.Output_NewLine();
            }
            if (var1_inc_iter == Values_Map.end()) {
                Cli_Output.Output_Str("ERROR: var " + var1_inc + " not found");
                Cli_Output.Output_NewLine();
            }
            if (is_var2_inc && var2_inc_iter == Values_Map.end()) {
                Cli_Output.Output_Str("ERROR: var " + var2_inc + " not found");
                Cli_Output.Output_NewLine();
            }
        }

        return true;
    }

    // </editor-fold>

    bool Do_Script_From_File(string filename, bool is_no_history) {
        bool is_filename_spaces = false;
        if (filename.find(' ') != std::string::npos) is_filename_spaces = true;
        if (filename.find('\t') != std::string::npos) is_filename_spaces = true;
        if (is_filename_spaces) {
            Script_Command_Str = "do script \"" + filename + "\"";
        } else {
            Script_Command_Str = "do script " + filename;
        }
        if (is_no_history) {
            Script_Command_Str += " no history";
        }
        return true;
    }

    bool Do_Command(string command) {
        Script_Command_Str = command;
        return true;
    }

    bool Do_Label(string label) {
        //@Warning: Command "check goto <label>" - special case: is moves file position
        // no action
        return true;
    }

    bool Do_Goto_Label(string label) {
        //Script_Command_Str = "check goto " + label;
        Script_Label_Str = label;
        return true;
    }

    // <editor-fold defaultstate="collapsed" desc="Check if: int/str as value/as var do">

    bool check_var_by_int_do_script_stop(string var_left, string s_compare, int var_right_value) {
        map<string, string>::iterator var_left_iter = Values_Map.find(var_left);
        if (var_left_iter != Values_Map.end()) {
            int var_left_value = atoi(var_left_iter->second.c_str());
            Local_Compare_Result cmp_res = Compare_Values_Int(var_left_value, s_compare, var_right_value);
            if (cmp_res == CMP_TRUE) {
                Cmd_Script_Stop = true;
            } else if (cmp_res == CMP_FALSE) {
                // Nothing
            } else if (cmp_res == CMP_ERROR) {
                Cli_Output.Output_Str("ERROR: compare operation " + s_compare + " not found");
                Cli_Output.Output_NewLine();
            }

        } else {
            Cli_Output.Output_Str("ERROR: var " + var_left + " not found");
            Cli_Output.Output_NewLine();
        }

        return true;
    }

    bool check_var_by_int_do_script_from_file(string var_left, string s_compare, int var_right_value, string filename, bool is_no_history) {
        map<string, string>::iterator var_left_iter = Values_Map.find(var_left);
        if (var_left_iter != Values_Map.end()) {
            int var_left_value = atoi(var_left_iter->second.c_str());
            Local_Compare_Result cmp_res = Compare_Values_Int(var_left_value, s_compare, var_right_value);
            if (cmp_res == CMP_TRUE) {
                Do_Script_From_File(filename, is_no_history);
            } else if (cmp_res == CMP_FALSE) {
                // Nothing
            } else if (cmp_res == CMP_ERROR) {
                Cli_Output.Output_Str("ERROR: compare operation " + s_compare + " not found");
                Cli_Output.Output_NewLine();
            }

        } else {
            Cli_Output.Output_Str("ERROR: var " + var_left + " not found");
            Cli_Output.Output_NewLine();
        }

        return true;
    }

    bool check_var_by_str_do_script_stop(string var_left, string s_compare, string var_right_value) {
        map<string, string>::iterator var_left_iter = Values_Map.find(var_left);
        if (var_left_iter != Values_Map.end()) {
            string var_left_value = var_left_iter->second;
            Local_Compare_Result cmp_res = Compare_Values_Str(var_left_value, s_compare, var_right_value);
            if (cmp_res == CMP_TRUE) {
                Cmd_Script_Stop = true;
            } else if (cmp_res == CMP_FALSE) {
                // Nothing
            } else if (cmp_res == CMP_ERROR) {
                Cli_Output.Output_Str("ERROR: compare operation " + s_compare + " not found");
                Cli_Output.Output_NewLine();
            }

        } else {
            Cli_Output.Output_Str("ERROR: var " + var_left + " not found");
            Cli_Output.Output_NewLine();
        }

        return true;
    }

    bool check_var_by_str_do_script_from_file(string var_left, string s_compare, string var_right_value, string filename, bool is_no_history) {
        map<string, string>::iterator var_left_iter = Values_Map.find(var_left);
        if (var_left_iter != Values_Map.end()) {
            //int var_left_value = atoi(var_left_iter->second.c_str());
            string var_left_value = var_left_iter->second;
            Local_Compare_Result cmp_res = Compare_Values_Str(var_left_value, s_compare, var_right_value);
            if (cmp_res == CMP_TRUE) {
                Do_Script_From_File(filename, is_no_history);
            } else if (cmp_res == CMP_FALSE) {
                // Nothing
            } else if (cmp_res == CMP_ERROR) {
                Cli_Output.Output_Str("ERROR: compare operation " + s_compare + " not found");
                Cli_Output.Output_NewLine();
            }

        } else {
            Cli_Output.Output_Str("ERROR: var " + var_left + " not found");
            Cli_Output.Output_NewLine();
        }

        return true;
    }

    bool check_var_by_var_do_script_stop(string var_left, string s_compare, string var_right) {
        map<string, string>::iterator var_left_iter = Values_Map.find(var_left);
        map<string, string>::iterator var_right_iter = Values_Map.find(var_right);
        if (var_left_iter != Values_Map.end() && var_right_iter != Values_Map.end()) {
            string var_left_value = var_left_iter->second;
            string var_right_value = var_right_iter->second;
            Local_Compare_Result cmp_res = Compare_Values_Str(var_left_value, s_compare, var_right_value);
            if (cmp_res == CMP_TRUE) {
                Cmd_Script_Stop = true;
            } else if (cmp_res == CMP_FALSE) {
                // Nothing
            } else if (cmp_res == CMP_ERROR) {
                Cli_Output.Output_Str("ERROR: compare operation " + s_compare + " not found");
                Cli_Output.Output_NewLine();
            }

        } else {
            if (var_left_iter == Values_Map.end()) {
                Cli_Output.Output_Str("ERROR: var " + var_left + " not found");
                Cli_Output.Output_NewLine();
            }
            if (var_right_iter == Values_Map.end()) {
                Cli_Output.Output_Str("ERROR: var " + var_right + " not found");
                Cli_Output.Output_NewLine();
            }
        }

        return true;
    }

    bool check_var_by_var_do_script_from_file(string var_left, string s_compare, string var_right, string filename, bool is_no_history) {
        map<string, string>::iterator var_left_iter = Values_Map.find(var_left);
        map<string, string>::iterator var_right_iter = Values_Map.find(var_right);
        if (var_left_iter != Values_Map.end() && var_right_iter != Values_Map.end()) {
            //int var_left_value = atoi(var_left_iter->second.c_str());
            string var_left_value = var_left_iter->second;
            string var_right_value = var_right_iter->second;
            Local_Compare_Result cmp_res = Compare_Values_Str(var_left_value, s_compare, var_right_value);
            if (cmp_res == CMP_TRUE) {
                Do_Script_From_File(filename, is_no_history);
            } else if (cmp_res == CMP_FALSE) {
                // Nothing
            } else if (cmp_res == CMP_ERROR) {
                Cli_Output.Output_Str("ERROR: compare operation " + s_compare + " not found");
                Cli_Output.Output_NewLine();
            }

        } else {
            if (var_left_iter != Values_Map.end()) {
                Cli_Output.Output_Str("ERROR: var " + var_left + " not found");
                Cli_Output.Output_NewLine();
            }
            if (var_right_iter != Values_Map.end()) {
                Cli_Output.Output_Str("ERROR: var " + var_right + " not found");
                Cli_Output.Output_NewLine();
            }
        }

        return true;
    }

    bool check_var_by_int_do_command(string var_left, string s_compare, int var_right_value, string command1, bool is_command2, string command2) {
        map<string, string>::iterator var_left_iter = Values_Map.find(var_left);
        //map<string, string>::iterator var_right_iter = Values_Map.find(var_right);
        if (var_left_iter != Values_Map.end()
                //&& var_right_iter != Values_Map.end()
                ) {
            //int var_left_value = atoi(var_left_iter->second.c_str());
            int var_left_value = atoi(var_left_iter->second.c_str());
            //string var_left_value = var_left_iter->second;
            //string var_right_value = var_right_iter->second;
            Local_Compare_Result cmp_res = Compare_Values_Int(var_left_value, s_compare, var_right_value);
            if (cmp_res == CMP_TRUE) {
                Do_Command(command1);
            } else if (cmp_res == CMP_FALSE && is_command2) {
                Do_Command(command2);
            } else if (cmp_res == CMP_ERROR) {
                Cli_Output.Output_Str("ERROR: compare operation " + s_compare + " not found");
                Cli_Output.Output_NewLine();
            }

        } else {
            //if (var_left_iter != Values_Map.end()) {
            Cli_Output.Output_Str("ERROR: var " + var_left + " not found");
            Cli_Output.Output_NewLine();
            //}
            //if (var_right_iter != Values_Map.end()) {
            //    Cli_Output.Output_Str("ERROR: var " + var_right + " not found");
            //    Cli_Output.Output_NewLine();
            //}
        }
        return true;
    }

    bool check_var_by_str_do_command(string var_left, string s_compare, string var_right_value, string command1, bool is_command2, string command2) {
        map<string, string>::iterator var_left_iter = Values_Map.find(var_left);
        //map<string, string>::iterator var_right_iter = Values_Map.find(var_right);
        if (var_left_iter != Values_Map.end()
                //&& var_right_iter != Values_Map.end()
                ) {
            //int var_left_value = atoi(var_left_iter->second.c_str());
            string var_left_value = var_left_iter->second;
            //string var_right_value = var_right_iter->second;
            Local_Compare_Result cmp_res = Compare_Values_Str(var_left_value, s_compare, var_right_value);
            if (cmp_res == CMP_TRUE) {
                Do_Command(command1);
            } else if (cmp_res == CMP_FALSE && is_command2) {
                Do_Command(command2);
            } else if (cmp_res == CMP_ERROR) {
                Cli_Output.Output_Str("ERROR: compare operation " + s_compare + " not found");
                Cli_Output.Output_NewLine();
            }

        } else {
            //if (var_left_iter != Values_Map.end()) {
            Cli_Output.Output_Str("ERROR: var " + var_left + " not found");
            Cli_Output.Output_NewLine();
            //}
            //if (var_right_iter != Values_Map.end()) {
            //    Cli_Output.Output_Str("ERROR: var " + var_right + " not found");
            //    Cli_Output.Output_NewLine();
            //}
        }
        return true;
    }

    bool check_var_by_var_do_command(string var_left, string s_compare, string var_right, string command1, bool is_command2, string command2) {
        map<string, string>::iterator var_left_iter = Values_Map.find(var_left);
        map<string, string>::iterator var_right_iter = Values_Map.find(var_right);
        if (var_left_iter != Values_Map.end() && var_right_iter != Values_Map.end()) {
            //int var_left_value = atoi(var_left_iter->second.c_str());
            string var_left_value = var_left_iter->second;
            string var_right_value = var_right_iter->second;
            Local_Compare_Result cmp_res = Compare_Values_Str(var_left_value, s_compare, var_right_value);
            if (cmp_res == CMP_TRUE) {
                Do_Command(command1);
            } else if (cmp_res == CMP_FALSE && is_command2) {
                Do_Command(command2);
            } else if (cmp_res == CMP_ERROR) {
                Cli_Output.Output_Str("ERROR: compare operation " + s_compare + " not found");
                Cli_Output.Output_NewLine();
            }

        } else {
            if (var_left_iter != Values_Map.end()) {
                Cli_Output.Output_Str("ERROR: var " + var_left + " not found");
                Cli_Output.Output_NewLine();
            }
            if (var_right_iter != Values_Map.end()) {
                Cli_Output.Output_Str("ERROR: var " + var_right + " not found");
                Cli_Output.Output_NewLine();
            }
        }
        return true;
    }

    // </editor-fold>

    // <editor-fold defaultstate="collapsed" desc="Label: label/goto label">

    bool check_label(string label) {
        return Do_Label(label);
    }

    bool check_goto_label(string label) {
        return Do_Goto_Label(label);
    }

    // </editor-fold>

    // <editor-fold defaultstate="collapsed" desc="Check if: int/str as value/str as var goto label">

    bool check_var_by_int_goto_label(string var_left, string s_compare, int var_right_value, string label1, bool is_label2, string label2) {
        map<string, string>::iterator var_left_iter = Values_Map.find(var_left);
        //map<string, string>::iterator var_right_iter = Values_Map.find(var_right);
        if (var_left_iter != Values_Map.end()
                //&& var_right_iter != Values_Map.end()
                ) {
            //int var_left_value = atoi(var_left_iter->second.c_str());
            int var_left_value = atoi(var_left_iter->second.c_str());
            //string var_right_value = var_right_iter->second;
            Local_Compare_Result cmp_res = Compare_Values_Int(var_left_value, s_compare, var_right_value);
            if (cmp_res == CMP_TRUE) {
                check_goto_label(label1);
            } else if (cmp_res == CMP_FALSE && is_label2) {
                check_goto_label(label2);
            } else if (cmp_res == CMP_ERROR) {
                Cli_Output.Output_Str("ERROR: compare operation " + s_compare + " not found");
                Cli_Output.Output_NewLine();
            }

        } else {
            //if (var_left_iter != Values_Map.end()) {
            Cli_Output.Output_Str("ERROR: var " + var_left + " not found");
            Cli_Output.Output_NewLine();
            //}
            //if (var_right_iter != Values_Map.end()) {
            //    Cli_Output.Output_Str("ERROR: var " + var_right + " not found");
            //    Cli_Output.Output_NewLine();
            //}
        }
        return true;
    }

    bool check_var_by_str_goto_label(string var_left, string s_compare, string var_right_value, string label1, bool is_label2, string label2) {
        map<string, string>::iterator var_left_iter = Values_Map.find(var_left);
        //map<string, string>::iterator var_right_iter = Values_Map.find(var_right);
        if (var_left_iter != Values_Map.end()
                //&& var_right_iter != Values_Map.end()
                ) {
            //int var_left_value = atoi(var_left_iter->second.c_str());
            string var_left_value = var_left_iter->second;
            //string var_right_value = var_right_iter->second;
            Local_Compare_Result cmp_res = Compare_Values_Str(var_left_value, s_compare, var_right_value);
            if (cmp_res == CMP_TRUE) {
                check_goto_label(label1);
            } else if (cmp_res == CMP_FALSE && is_label2) {
                check_goto_label(label2);
            } else if (cmp_res == CMP_ERROR) {
                Cli_Output.Output_Str("ERROR: compare operation " + s_compare + " not found");
                Cli_Output.Output_NewLine();
            }

        } else {
            //if (var_left_iter != Values_Map.end()) {
            Cli_Output.Output_Str("ERROR: var " + var_left + " not found");
            Cli_Output.Output_NewLine();
            //}
            //if (var_right_iter != Values_Map.end()) {
            //    Cli_Output.Output_Str("ERROR: var " + var_right + " not found");
            //    Cli_Output.Output_NewLine();
            //}
        }
        return true;
    }

    bool check_var_by_var_goto_label(string var_left, string s_compare, string var_right, string label1, bool is_label2, string label2) {
        map<string, string>::iterator var_left_iter = Values_Map.find(var_left);
        map<string, string>::iterator var_right_iter = Values_Map.find(var_right);
        if (var_left_iter != Values_Map.end() && var_right_iter != Values_Map.end()) {
            //int var_left_value = atoi(var_left_iter->second.c_str());
            string var_left_value = var_left_iter->second;
            string var_right_value = var_right_iter->second;
            Local_Compare_Result cmp_res = Compare_Values_Str(var_left_value, s_compare, var_right_value);
            if (cmp_res == CMP_TRUE) {
                check_goto_label(label1);
            } else if (cmp_res == CMP_FALSE && is_label2) {
                check_goto_label(label2);
            } else if (cmp_res == CMP_ERROR) {
                Cli_Output.Output_Str("ERROR: compare operation " + s_compare + " not found");
                Cli_Output.Output_NewLine();
            }

        } else {
            if (var_left_iter != Values_Map.end()) {
                Cli_Output.Output_Str("ERROR: var " + var_left + " not found");
                Cli_Output.Output_NewLine();
            }
            if (var_right_iter != Values_Map.end()) {
                Cli_Output.Output_Str("ERROR: var " + var_right + " not found");
                Cli_Output.Output_NewLine();
            }
        }
        return true;
    }

    // </editor-fold>

    virtual bool Execute(Cli_Cmd *cmd, vector<Level_Description> &Levels, bool is_debug) {
        enum Local_Cmd_ID cmd_id = (enum Local_Cmd_ID)cmd->ID_Get();
        switch (cmd_id) {

                // <editor-fold defaultstate="collapsed" desc="Values_Map: print, clear">

            case CMD_ID_check_map:
            case CMD_ID_check_map_print:
                if (is_debug) return true;
            {
                string var_filter = "*";
                return check_map_print(var_filter, Str_Filter);
            }
            case CMD_ID_check_map_print_by_filter:
                if (is_debug) return true;
            {
                string var_filter = cmd->Items[3]->Value_Str;
                return check_map_print(var_filter, Str_Filter);
            }
            case CMD_ID_check_map_clear:
                if (is_debug) return true;
                return check_map_clear();

                // </editor-fold>

                // <editor-fold defaultstate="collapsed" desc="Values_Map: modules to map">

            case CMD_ID_check_modules_by_filter_to_map:
                if (is_debug) return true;
            {
                string module_filter = cmd->Items[2]->Value_Str;
                return check_modules_to_map(module_filter, Str_Filter);
            }

                // </editor-fold>

                // <editor-fold defaultstate="collapsed" desc="Var: set as value, as var, as expression, force">

            case CMD_ID_check_var_str_set_str_as_value:
                if (is_debug) return true;
            {
                string var_left = cmd->Items[2]->Value_Str;
                string value = cmd->Items[4]->Value_Str;
                bool if_force;
                return check_var_set_str_as_value(var_left, value, if_force = false);
            }
            case CMD_ID_check_var_str_set_str_as_value_force:
                if (is_debug) return true;
            {
                string var_left = cmd->Items[2]->Value_Str;
                string value = cmd->Items[4]->Value_Str;
                bool if_force;
                return check_var_set_str_as_value(var_left, value, if_force = true);
            }

            case CMD_ID_check_var_str_set_str_as_var:
                if (is_debug) return true;
            {
                string var_left = cmd->Items[2]->Value_Str;
                string value = cmd->Items[4]->Value_Str;
                bool if_force;
                return check_var_set_str_as_var(var_left, value, if_force = false);
            }
            case CMD_ID_check_var_str_set_str_as_var_force:
                if (is_debug) return true;
            {
                string var_left = cmd->Items[2]->Value_Str;
                string value = cmd->Items[4]->Value_Str;
                bool if_force;
                return check_var_set_str_as_var(var_left, value, if_force = true);
            }

            case CMD_ID_check_var_str_set_str_as_expr:
                if (is_debug) return true;
            {
                string var_left = cmd->Items[2]->Value_Str;
                string expr = cmd->Items[4]->Value_Str;
                bool if_force;
                return check_var_set_str_as_expr(var_left, expr, if_force = false);
            }
            case CMD_ID_check_var_str_set_str_as_expr_force:
                if (is_debug) return true;
            {
                string var_left = cmd->Items[2]->Value_Str;
                string expr = cmd->Items[4]->Value_Str;
                bool if_force;
                return check_var_set_str_as_expr(var_left, expr, if_force = true);
            }

                // </editor-fold>

                // <editor-fold defaultstate="collapsed" desc="Var: inc">

            case CMD_ID_check_var_str_inc:
                if (is_debug) return true;
            {
                string var_left = cmd->Items[2]->Value_Str;
                return check_var_inc_value(var_left);
            }

                // </editor-fold>

                // <editor-fold defaultstate="collapsed" desc="Check if: int print/inc/do">

            case CMD_ID_check_if_str_compare_int_print_str:
                if (is_debug) return true;
            {
                string var_left = cmd->Items[2]->Value_Str;
                string s_compare = cmd->Items[3]->Value_Str;
                int var_right_value = atoi(cmd->Items[4]->Value_Str.c_str());
                string s_msg1 = cmd->Items[6]->Value_Str;
                bool is_msg2;
                string s_msg2;
                return check_var_by_int_print_msg1_or_msg2(var_left, s_compare, var_right_value, s_msg1, is_msg2 = false, s_msg2);
            }
            case CMD_ID_check_if_str_compare_int_print_str_else_print_str:
                if (is_debug) return true;
            {
                string var_left = cmd->Items[2]->Value_Str;
                string s_compare = cmd->Items[3]->Value_Str;
                int var_right_value = atoi(cmd->Items[4]->Value_Str.c_str());
                string s_msg1 = cmd->Items[6]->Value_Str;
                bool is_msg2;
                string s_msg2 = cmd->Items[9]->Value_Str;
                return check_var_by_int_print_msg1_or_msg2(var_left, s_compare, var_right_value, s_msg1, is_msg2 = true, s_msg2);
            }

            case CMD_ID_check_if_str_compare_int_inc_str:
                if (is_debug) return true;
            {
                string var_left = cmd->Items[2]->Value_Str;
                string s_compare = cmd->Items[3]->Value_Str;
                int var_right_value = atoi(cmd->Items[4]->Value_Str.c_str());
                string var1_inc = cmd->Items[6]->Value_Str;
                bool is_var2_inc;
                string var2_inc;
                return check_var_by_int_inc_var1_or_var2(var_left, s_compare, var_right_value, var1_inc, is_var2_inc = false, var2_inc);
            }
            case CMD_ID_check_if_str_compare_int_inc_str_else_inc_str:
                if (is_debug) return true;
            {
                string var_left = cmd->Items[2]->Value_Str;
                string s_compare = cmd->Items[3]->Value_Str;
                int var_right_value = atoi(cmd->Items[4]->Value_Str.c_str());
                string var1_inc = cmd->Items[6]->Value_Str;
                bool is_var2_inc;
                string var2_inc = cmd->Items[9]->Value_Str;
                return check_var_by_int_inc_var1_or_var2(var_left, s_compare, var_right_value, var1_inc, is_var2_inc = true, var2_inc);
            }

            case CMD_ID_check_if_str_compare_int_do_script_stop:
                if (is_debug) return true;
            {
                string var_left = cmd->Items[2]->Value_Str;
                string s_compare = cmd->Items[3]->Value_Str;
                int var_right_value = atoi(cmd->Items[4]->Value_Str.c_str());
                return check_var_by_int_do_script_stop(var_left, s_compare, var_right_value);
            }

            case CMD_ID_check_if_str_compare_int_do_script_filename:
                if (is_debug) return true;
            {
                string var_left = cmd->Items[2]->Value_Str;
                string s_compare = cmd->Items[3]->Value_Str;
                int var_right_value = atoi(cmd->Items[4]->Value_Str.c_str());
                string filename = cmd->Items[7]->Value_Str;
                bool is_no_history;
                return check_var_by_int_do_script_from_file(var_left, s_compare, var_right_value, filename, is_no_history = false);
            }
            case CMD_ID_check_if_str_compare_int_do_script_filename_no_history:
                if (is_debug) return true;
            {
                string var_left = cmd->Items[2]->Value_Str;
                string s_compare = cmd->Items[3]->Value_Str;
                int var_right_value = atoi(cmd->Items[4]->Value_Str.c_str());
                string filename = cmd->Items[7]->Value_Str;
                bool is_no_history;
                return check_var_by_int_do_script_from_file(var_left, s_compare, var_right_value, filename, is_no_history = true);
            }

                // </editor-fold>

                // <editor-fold defaultstate="collapsed" desc="Check if: str as value print/inc/do">

            case CMD_ID_check_if_str_compare_str_as_value_print_str:
                if (is_debug) return true;
            {
                string var_left = cmd->Items[2]->Value_Str;
                string s_compare = cmd->Items[3]->Value_Str;
                string value = cmd->Items[4]->Value_Str;
                string s_msg1 = cmd->Items[8]->Value_Str;
                bool is_msg2;
                string s_msg2;
                return check_var_by_str_print_msg1_or_msg2(var_left, s_compare, value, s_msg1, is_msg2 = false, s_msg2);
            }
            case CMD_ID_check_if_str_compare_str_as_value_print_str_else_print_str:
                if (is_debug) return true;
            {
                string var_left = cmd->Items[2]->Value_Str;
                string s_compare = cmd->Items[3]->Value_Str;
                string value = cmd->Items[4]->Value_Str;
                string s_msg1 = cmd->Items[8]->Value_Str;
                bool is_msg2;
                string s_msg2 = cmd->Items[11]->Value_Str;
                return check_var_by_str_print_msg1_or_msg2(var_left, s_compare, value, s_msg1, is_msg2 = true, s_msg2);
            }

            case CMD_ID_check_if_str_compare_str_as_value_inc_str:
                if (is_debug) return true;
            {
                string var_left = cmd->Items[2]->Value_Str;
                string s_compare = cmd->Items[3]->Value_Str;
                string value = cmd->Items[4]->Value_Str;
                string var1_inc = cmd->Items[8]->Value_Str;
                bool is_var2_inc;
                string var2_inc;
                return check_var_by_str_inc_var1_or_var2(var_left, s_compare, value, var1_inc, is_var2_inc = false, var2_inc);
            }
            case CMD_ID_check_if_str_compare_str_as_value_inc_str_else_inc_str:
                if (is_debug) return true;
            {
                string var_left = cmd->Items[2]->Value_Str;
                string s_compare = cmd->Items[3]->Value_Str;
                string value = cmd->Items[4]->Value_Str;
                string var1_inc = cmd->Items[8]->Value_Str;
                bool is_var2_inc;
                string var2_inc = cmd->Items[11]->Value_Str;
                return check_var_by_str_inc_var1_or_var2(var_left, s_compare, value, var1_inc, is_var2_inc = true, var2_inc);
            }

            case CMD_ID_check_if_str_compare_str_as_value_do_script_stop:
                if (is_debug) return true;
            {
                string var_left = cmd->Items[2]->Value_Str;
                string s_compare = cmd->Items[3]->Value_Str;
                string var_right_value = cmd->Items[4]->Value_Str;
                return check_var_by_str_do_script_stop(var_left, s_compare, var_right_value);
            }

            case CMD_ID_check_if_str_compare_str_as_value_do_script_filename:
                if (is_debug) return true;
            {
                string var_left = cmd->Items[2]->Value_Str;
                string s_compare = cmd->Items[3]->Value_Str;
                string var_right_value = cmd->Items[4]->Value_Str.c_str();
                string filename = cmd->Items[7]->Value_Str;
                bool is_no_history;
                return check_var_by_str_do_script_from_file(var_left, s_compare, var_right_value, filename, is_no_history = false);
            }
            case CMD_ID_check_if_str_compare_str_as_value_do_script_filename_no_history:
                if (is_debug) return true;
            {
                string var_left = cmd->Items[2]->Value_Str;
                string s_compare = cmd->Items[3]->Value_Str;
                string var_right_value = cmd->Items[4]->Value_Str.c_str();
                string filename = cmd->Items[7]->Value_Str;
                bool is_no_history;
                return check_var_by_str_do_script_from_file(var_left, s_compare, var_right_value, filename, is_no_history = true);
            }

                // </editor-fold>

                // <editor-fold defaultstate="collapsed" desc="Check if: str as var print/inc/do">

            case CMD_ID_check_if_str_compare_str_as_var_print_str:
                if (is_debug) return true;
            {
                string var_left = cmd->Items[2]->Value_Str;
                string s_compare = cmd->Items[3]->Value_Str;
                string var_right = cmd->Items[4]->Value_Str;
                string s_msg1 = cmd->Items[8]->Value_Str;
                bool is_msg2;
                string s_msg2;
                return check_var_by_var_print_msg1_or_msg2(var_left, s_compare, var_right, s_msg1, is_msg2 = false, s_msg2);
            }
            case CMD_ID_check_if_str_compare_str_as_var_print_str_else_print_str:
                if (is_debug) return true;
            {
                string var_left = cmd->Items[2]->Value_Str;
                string s_compare = cmd->Items[3]->Value_Str;
                string var_right = cmd->Items[4]->Value_Str;
                string s_msg1 = cmd->Items[8]->Value_Str;
                bool is_msg2;
                string s_msg2 = cmd->Items[11]->Value_Str;
                return check_var_by_var_print_msg1_or_msg2(var_left, s_compare, var_right, s_msg1, is_msg2 = true, s_msg2);
            }

            case CMD_ID_check_if_str_compare_str_as_var_inc_str:
                if (is_debug) return true;
            {
                string var_left = cmd->Items[2]->Value_Str;
                string s_compare = cmd->Items[3]->Value_Str;
                string var_right = cmd->Items[4]->Value_Str;
                string var1_inc = cmd->Items[8]->Value_Str;
                bool is_var2_inc;
                string var2_inc;
                return check_var_by_var_inc_var1_or_var2(var_left, s_compare, var_right, var1_inc, is_var2_inc = false, var2_inc);
            }
            case CMD_ID_check_if_str_compare_str_as_var_inc_str_else_inc_str:
                if (is_debug) return true;
            {
                string var_left = cmd->Items[2]->Value_Str;
                string s_compare = cmd->Items[3]->Value_Str;
                string var_right = cmd->Items[4]->Value_Str;
                string var1_inc = cmd->Items[8]->Value_Str;
                bool is_var2_inc;
                string var2_inc = cmd->Items[11]->Value_Str;
                return check_var_by_var_inc_var1_or_var2(var_left, s_compare, var_right, var1_inc, is_var2_inc = true, var2_inc);
            }

            case CMD_ID_check_if_str_compare_str_as_var_do_script_stop:
                if (is_debug) return true;
            {
                string var_left = cmd->Items[2]->Value_Str;
                string s_compare = cmd->Items[3]->Value_Str;
                string var_right = cmd->Items[4]->Value_Str;
                return check_var_by_var_do_script_stop(var_left, s_compare, var_right);
            }

            case CMD_ID_check_if_str_compare_str_as_var_do_script_filename:
                if (is_debug) return true;
            {
                string var_left = cmd->Items[2]->Value_Str;
                string s_compare = cmd->Items[3]->Value_Str;
                string var_right = cmd->Items[4]->Value_Str.c_str();
                string filename = cmd->Items[7]->Value_Str;
                bool is_no_history;
                return check_var_by_var_do_script_from_file(var_left, s_compare, var_right, filename, is_no_history = false);
            }
            case CMD_ID_check_if_str_compare_str_as_var_do_script_filename_no_history:
                if (is_debug) return true;
            {
                string var_left = cmd->Items[2]->Value_Str;
                string s_compare = cmd->Items[3]->Value_Str;
                string var_right = cmd->Items[4]->Value_Str.c_str();
                string filename = cmd->Items[7]->Value_Str;
                bool is_no_history;
                return check_var_by_var_do_script_from_file(var_left, s_compare, var_right, filename, is_no_history = true);
            }

                // </editor-fold>

                // <editor-fold defaultstate="collapsed" desc="Check if: int/str as value/str as var do command">
            case CMD_ID_check_if_str_compare_int_do_command_str:
                if (is_debug) return true;
            {
                string var_left = cmd->Items[2]->Value_Str;
                string s_compare = cmd->Items[3]->Value_Str;
                int var_right_value = atoi(cmd->Items[4]->Value_Str.c_str());
                string command1 = cmd->Items[7]->Value_Str;
                bool is_command2;
                string command2;
                return check_var_by_int_do_command(var_left, s_compare, var_right_value, command1, is_command2 = false, command2);
            }
            case CMD_ID_check_if_str_compare_int_do_command_str_else_do_command_str:
                if (is_debug) return true;
            {
                string var_left = cmd->Items[2]->Value_Str;
                string s_compare = cmd->Items[3]->Value_Str;
                int var_right_value = atoi(cmd->Items[4]->Value_Str.c_str());
                string command1 = cmd->Items[7]->Value_Str;
                bool is_command2;
                string command2 = cmd->Items[10]->Value_Str;
                return check_var_by_int_do_command(var_left, s_compare, var_right_value, command1, is_command2 = true, command2);
            }

            case CMD_ID_check_if_str_compare_str_as_value_do_command_str:
                if (is_debug) return true;
            {
                string var_left = cmd->Items[2]->Value_Str;
                string s_compare = cmd->Items[3]->Value_Str;
                string var_right_value = cmd->Items[4]->Value_Str.c_str();
                string command1 = cmd->Items[9]->Value_Str;
                bool is_command2;
                string command2;
                return check_var_by_str_do_command(var_left, s_compare, var_right_value, command1, is_command2 = false, command2);
            }
            case CMD_ID_check_if_str_compare_str_as_value_do_command_str_else_do_command_str:
                if (is_debug) return true;
            {
                string var_left = cmd->Items[2]->Value_Str;
                string s_compare = cmd->Items[3]->Value_Str;
                string var_right_value = cmd->Items[4]->Value_Str.c_str();
                string command1 = cmd->Items[9]->Value_Str;
                bool is_command2;
                string command2 = cmd->Items[13]->Value_Str;
                return check_var_by_str_do_command(var_left, s_compare, var_right_value, command1, is_command2 = true, command2);
            }

            case CMD_ID_check_if_str_compare_str_as_var_do_command_str:
                if (is_debug) return true;
            {
                string var_left = cmd->Items[2]->Value_Str;
                string s_compare = cmd->Items[3]->Value_Str;
                string var_right = cmd->Items[4]->Value_Str.c_str();
                string command1 = cmd->Items[9]->Value_Str;
                bool is_command2;
                string command2;
                return check_var_by_var_do_command(var_left, s_compare, var_right, command1, is_command2 = false, command2);
            }
            case CMD_ID_check_if_str_compare_str_as_var_do_command_str_else_do_command_str:
                if (is_debug) return true;
            {
                string var_left = cmd->Items[2]->Value_Str;
                string s_compare = cmd->Items[3]->Value_Str;
                string var_right = cmd->Items[4]->Value_Str.c_str();
                string command1 = cmd->Items[9]->Value_Str;
                bool is_command2;
                string command2 = cmd->Items[13]->Value_Str;
                return check_var_by_var_do_command(var_left, s_compare, var_right, command1, is_command2 = true, command2);
            }
                // </editor-fold>

                // <editor-fold defaultstate="collapsed" desc="Label: label/goto label">
            case CMD_ID_check_label_str:
                if (is_debug) return true;
            {
                string label = cmd->Items[2]->Value_Str;
                return check_label(label);
            }
            case CMD_ID_check_goto_label:
                if (is_debug) return true;
            {
                string label = cmd->Items[2]->Value_Str;
                return check_goto_label(label);
            }
                // </editor-fold>

                // <editor-fold defaultstate="collapsed" desc="Check if: int/str as value/str as var goto label">
            case CMD_ID_check_if_str_compare_int_goto_str:
                if (is_debug) return true;
            {
                string var_left = cmd->Items[2]->Value_Str;
                string s_compare = cmd->Items[3]->Value_Str;
                int var_right_value = atoi(cmd->Items[4]->Value_Str.c_str());
                string label1 = cmd->Items[6]->Value_Str;
                bool is_label2;
                string label2;
                return check_var_by_int_goto_label(var_left, s_compare, var_right_value, label1, is_label2 = false, label2);
            }
            case CMD_ID_check_if_str_compare_int_goto_str_else_goto_str:
                if (is_debug) return true;
            {
                string var_left = cmd->Items[2]->Value_Str;
                string s_compare = cmd->Items[3]->Value_Str;
                int var_right_value = atoi(cmd->Items[4]->Value_Str.c_str());
                string label1 = cmd->Items[6]->Value_Str;
                bool is_label2;
                string label2 = cmd->Items[9]->Value_Str;
                return check_var_by_int_goto_label(var_left, s_compare, var_right_value, label1, is_label2 = true, label2);
            }

            case CMD_ID_check_if_str_compare_str_as_value_goto_str:
                if (is_debug) return true;
            {
                string var_left = cmd->Items[2]->Value_Str;
                string s_compare = cmd->Items[3]->Value_Str;
                string var_right_value = cmd->Items[4]->Value_Str.c_str();
                string label1 = cmd->Items[8]->Value_Str;
                bool is_label2;
                string label2;
                return check_var_by_str_goto_label(var_left, s_compare, var_right_value, label1, is_label2 = false, label2);
            }
            case CMD_ID_check_if_str_compare_str_as_value_goto_str_else_goto_str:
                if (is_debug) return true;
            {
                string var_left = cmd->Items[2]->Value_Str;
                string s_compare = cmd->Items[3]->Value_Str;
                string var_right_value = cmd->Items[4]->Value_Str.c_str();
                string label1 = cmd->Items[8]->Value_Str;
                bool is_label2;
                string label2 = cmd->Items[11]->Value_Str;
                return check_var_by_str_goto_label(var_left, s_compare, var_right_value, label1, is_label2 = true, label2);
            }

            case CMD_ID_check_if_str_compare_str_as_var_goto_str:
                if (is_debug) return true;
            {
                string var_left = cmd->Items[2]->Value_Str;
                string s_compare = cmd->Items[3]->Value_Str;
                string var_right = cmd->Items[4]->Value_Str.c_str();
                string label1 = cmd->Items[8]->Value_Str;
                bool is_label2;
                string label2;
                return check_var_by_var_goto_label(var_left, s_compare, var_right, label1, is_label2 = false, label2);
            }
            case CMD_ID_check_if_str_compare_str_as_var_goto_str_else_goto_str:
                if (is_debug) return true;
            {
                string var_left = cmd->Items[2]->Value_Str;
                string s_compare = cmd->Items[3]->Value_Str;
                string var_right = cmd->Items[4]->Value_Str.c_str();
                string label1 = cmd->Items[8]->Value_Str;
                bool is_label2;
                string label2 = cmd->Items[11]->Value_Str;
                return check_var_by_var_goto_label(var_left, s_compare, var_right, label1, is_label2 = true, label2);
            }
                // </editor-fold>

            default:
                return false; // Not Implemented

        }
        return false; // Not Implemented
    }

    virtual void To_Map(map<string, string> &values_map) {
        string Prefix = "Check";
        {
            stringstream s_str;
            s_str << Count_Total;
            values_map[Prefix + ".Count_Total"] = s_str.str();
        }
        {
            stringstream s_str;
            s_str << Count_Passed;
            values_map[Prefix + ".Count_Passed"] = s_str.str();
        }
        {
            stringstream s_str;
            s_str << Count_Failed;
            values_map[Prefix + ".Count_Failed"] = s_str.str();
        }
    }

};

#endif /* CLI_MODULE_CHECK_H */
