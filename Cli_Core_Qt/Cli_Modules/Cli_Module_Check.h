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

#include "Cmd_Item_Point_Var_Name.h"

class Cli_Module_Check : public Cli_Module {
protected:

    Cli_Modules &Modules;

    map<string, string> &Values_Map;

    Str_Filter_Abstract &Str_Filter;

    Cli_Output_Abstract &Cli_Output;

    bool &Cmd_Script_Stop;

    int Count_Total;
    int Count_Passed;
    int Count_Failed;

public:

    enum Local_Cmd_ID {
        CMD_ID_NO,

        CMD_ID_check_modules_by_filter_to_map,

        CMD_ID_check_label_str,
        CMD_ID_check_goto_label,

        CMD_ID_check_if_var_compare_var2_print_var3,
        CMD_ID_check_if_var_compare_var2_print_str,

        CMD_ID_check_if_var_compare_var2_print_var3_else_print_var4,
        CMD_ID_check_if_var_compare_var2_print_var3_else_print_str,
        CMD_ID_check_if_var_compare_var2_print_str_else_print_var3,
        CMD_ID_check_if_var_compare_var2_print_str_else_print_str,

        CMD_ID_check_if_var_compare_var2_inc_var3,
        CMD_ID_check_if_var_compare_var2_inc_var3_else_inc_var4,

        CMD_ID_check_if_var_compare_var2_do_script_stop,
        CMD_ID_check_if_var_compare_var2_do_script_filename,
        CMD_ID_check_if_var_compare_var2_do_script_filename_no_history,

        CMD_ID_check_if_var_compare_var2_goto_str,
        CMD_ID_check_if_var_compare_var2_goto_str_else_goto_str,

        CMD_ID_check_if_var_compare_str_print_var2,
        CMD_ID_check_if_var_compare_str_print_str,

        CMD_ID_check_if_var_compare_str_print_var2_else_print_var3,
        CMD_ID_check_if_var_compare_str_print_var2_else_print_str,
        CMD_ID_check_if_var_compare_str_print_str_else_print_var2,
        CMD_ID_check_if_var_compare_str_print_str_else_print_str,

        CMD_ID_check_if_var_compare_str_inc_var2,
        CMD_ID_check_if_var_compare_str_inc_var2_else_inc_var3,

        CMD_ID_check_if_var_compare_str_do_script_stop,
        CMD_ID_check_if_var_compare_str_do_script_filename,
        CMD_ID_check_if_var_compare_str_do_script_filename_no_history,

        CMD_ID_check_if_var_compare_str_goto_str,
        CMD_ID_check_if_var_compare_str_goto_str_else_goto_str,

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
            bool &cmd_script_stop) : Cli_Module("Check"),
    Modules(modules), Values_Map(values_map),
    Str_Filter(str_filter), Cli_Output(cli_output),
    Cmd_Script_Stop(cmd_script_stop) {

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

        // <editor-fold defaultstate="collapsed" desc="Values_Map: modules to map">

        {
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
        } // check modules <module_name> to map

        // </editor-fold>

        // <editor-fold defaultstate="collapsed" desc="Label: label/goto label">

        {
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_check_label_str);
            cmd->Text_Set("check label <lbl>");
            cmd->Help_Set("create label <lbl> (for scripts only)");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("check", "check"));
            cmd->Item_Add(new Cmd_Item_Word("label", "create label"));
            cmd->Item_Add(new Cmd_Item_Str("<lbl>", "label name"));

            Cmd_Add(cmd);
        } // check label str

        {
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_check_goto_label);
            cmd->Text_Set("check goto <lbl>");
            cmd->Help_Set("goto <lbl> (for scripts only)");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("check", "check"));
            cmd->Item_Add(new Cmd_Item_Word("goto", "goto"));
            cmd->Item_Add(new Cmd_Item_Str("<lbl>", "label name"));

            Cmd_Add(cmd);
        } // check goto label

        // </editor-fold>

        // <editor-fold defaultstate="collapsed" desc="Check if: var compare var2/str print/inc/do script/do command">

        {
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_check_if_var_compare_var2_print_var3);
            cmd->Text_Set("check if .<v> [compare: " + cmp_str_str + "] .<v2> print .<v3>");
            cmd->Help_Set("check .var by .var2 and print .var3");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("check", "check"));
            cmd->Item_Add(new Cmd_Item_Word("if", "check if"));
            cmd->Item_Add(new Cmd_Item_Point_Var_Name(".<v>", ".var name"));
            cmd->Item_Add(new Cmd_Item_EQU_Range("[compare: " + cmp_str_str + "]", "compare function", cmp_str_words));
            cmd->Item_Add(new Cmd_Item_Point_Var_Name(".<v2>", ".var2 name"));
            cmd->Item_Add(new Cmd_Item_Word("print", "check and print"));
            cmd->Item_Add(new Cmd_Item_Point_Var_Name(".<v3>", ".var3 to print"));

            Cmd_Add(cmd);
        } // check if .v compare .v2 print .v3
        {

            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_check_if_var_compare_var2_print_str);
            cmd->Text_Set("check if .<v> [compare: " + cmp_str_str + "] .<v2> print <msg>");
            cmd->Help_Set("check .var by .var2 and print <msg>");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("check", "check"));
            cmd->Item_Add(new Cmd_Item_Word("if", "check if"));
            cmd->Item_Add(new Cmd_Item_Point_Var_Name(".<v>", ".var name"));
            cmd->Item_Add(new Cmd_Item_EQU_Range("[compare: " + cmp_str_str + "]", "compare function", cmp_str_words));
            cmd->Item_Add(new Cmd_Item_Point_Var_Name(".<v2>", ".var2 name"));
            cmd->Item_Add(new Cmd_Item_Word("print", "check and print"));
            cmd->Item_Add(new Cmd_Item_Str("<msg>", "msg to print"));

            Cmd_Add(cmd);
        } // check if .v compare .v2 print str

        {
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_check_if_var_compare_var2_print_var3_else_print_var4);
            cmd->Text_Set("check if .<v> [compare: " + cmp_str_str + "] .<v2> print .<v3> else print .<v4>");
            cmd->Help_Set("check .var by .var2 and print .var3 else print .var4");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("check", "check"));
            cmd->Item_Add(new Cmd_Item_Word("if", "check if"));
            cmd->Item_Add(new Cmd_Item_Point_Var_Name(".<v>", ".var name"));
            cmd->Item_Add(new Cmd_Item_EQU_Range("[compare: " + cmp_str_str + "]", "compare function", cmp_str_words));
            cmd->Item_Add(new Cmd_Item_Point_Var_Name(".<v2>", ".var2 name"));
            cmd->Item_Add(new Cmd_Item_Word("print", "check and print"));
            cmd->Item_Add(new Cmd_Item_Point_Var_Name(".<v3>", ".var3 to print"));
            cmd->Item_Add(new Cmd_Item_Word("else", "else"));
            cmd->Item_Add(new Cmd_Item_Word("print", "check and print"));
            cmd->Item_Add(new Cmd_Item_Point_Var_Name(".<v4>", ".var4 to print"));

            Cmd_Add(cmd);
        } // check if .v compare .v2 print .v3 else print .v4
        {
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_check_if_var_compare_var2_print_var3_else_print_str);
            cmd->Text_Set("check if .<v> [compare: " + cmp_str_str + "] .<v2> print .<v3> else print <msg>");
            cmd->Help_Set("check .var by .var2 and print .var3 else print <msg>");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("check", "check"));
            cmd->Item_Add(new Cmd_Item_Word("if", "check if"));
            cmd->Item_Add(new Cmd_Item_Point_Var_Name(".<v>", "var name"));
            cmd->Item_Add(new Cmd_Item_EQU_Range("[compare: " + cmp_str_str + "]", "compare function", cmp_str_words));
            cmd->Item_Add(new Cmd_Item_Point_Var_Name(".<v2>", ".var2 name"));
            cmd->Item_Add(new Cmd_Item_Word("print", "check and print"));
            cmd->Item_Add(new Cmd_Item_Point_Var_Name(".<v3>", ".var3 to print"));
            cmd->Item_Add(new Cmd_Item_Word("else", "else"));
            cmd->Item_Add(new Cmd_Item_Word("print", "check and print"));
            cmd->Item_Add(new Cmd_Item_Str("<msg>", "msg to print"));

            Cmd_Add(cmd);
        } // check if .v compare .v2 print .v3 else print str
        {

            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_check_if_var_compare_var2_print_str_else_print_var3);
            cmd->Text_Set("check if .<v> [compare: " + cmp_str_str + "] .<v2> print <msg> else print .<v3>");
            cmd->Help_Set("check .var by .var2 and print <msg> else print .var3");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("check", "check"));
            cmd->Item_Add(new Cmd_Item_Word("if", "check if"));
            cmd->Item_Add(new Cmd_Item_Point_Var_Name(".<v>", ".var name"));
            cmd->Item_Add(new Cmd_Item_EQU_Range("[compare: " + cmp_str_str + "]", "compare function", cmp_str_words));
            cmd->Item_Add(new Cmd_Item_Point_Var_Name(".<v2>", ".var2 name"));
            cmd->Item_Add(new Cmd_Item_Word("print", "check and print"));
            cmd->Item_Add(new Cmd_Item_Str("<msg>", "msg to print"));
            cmd->Item_Add(new Cmd_Item_Word("else", "else"));
            cmd->Item_Add(new Cmd_Item_Word("print", "check and print"));
            cmd->Item_Add(new Cmd_Item_Point_Var_Name(".<v3>", ".var3 to print"));

            Cmd_Add(cmd);
        } // check if .v compare .v2 print str else print .v3
        {
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_check_if_var_compare_var2_print_str_else_print_str);
            cmd->Text_Set("check if .<v> [compare: " + cmp_str_str + "] .<v2> print <msg> else print <msg2>");
            cmd->Help_Set("check .var by .var2 and print <msg> else print <msg2>");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("check", "check"));
            cmd->Item_Add(new Cmd_Item_Word("if", "check if"));
            cmd->Item_Add(new Cmd_Item_Point_Var_Name(".<v>", "var name"));
            cmd->Item_Add(new Cmd_Item_EQU_Range("[compare: " + cmp_str_str + "]", "compare function", cmp_str_words));
            cmd->Item_Add(new Cmd_Item_Point_Var_Name(".<v2>", "var2 name"));
            cmd->Item_Add(new Cmd_Item_Word("print", "check and print"));
            cmd->Item_Add(new Cmd_Item_Str("<msg>", "msg to print"));
            cmd->Item_Add(new Cmd_Item_Word("else", "else"));
            cmd->Item_Add(new Cmd_Item_Word("print", "print"));
            cmd->Item_Add(new Cmd_Item_Str("<msg2>", "msg2 to print"));

            Cmd_Add(cmd);
        } // check if .v compare .v2 print str else print str2

        {
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_check_if_var_compare_var2_inc_var3);
            cmd->Text_Set("check if .<v> [compare: " + cmp_str_str + "] .<v2> inc .<v3>");
            cmd->Help_Set("check .var by .var2 and increment .var3");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("check", "check"));
            cmd->Item_Add(new Cmd_Item_Word("if", "check if"));
            cmd->Item_Add(new Cmd_Item_Point_Var_Name(".<v>", "var name"));
            cmd->Item_Add(new Cmd_Item_EQU_Range("[compare: " + cmp_str_str + "]", "compare function", cmp_str_words));
            cmd->Item_Add(new Cmd_Item_Point_Var_Name(".<v2>", "var2 name"));
            cmd->Item_Add(new Cmd_Item_Word("inc", "check and increment"));
            cmd->Item_Add(new Cmd_Item_Point_Var_Name(".<v3>", ".var3 to increment"));

            Cmd_Add(cmd);
        } // check if .v compare .v2 inc .v3
        {
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_check_if_var_compare_var2_inc_var3_else_inc_var4);
            cmd->Text_Set("check if .<v> [compare: " + cmp_str_str + "] .<v2> inc .<v3> else inc .<v4>");
            cmd->Help_Set("check .var by .var2 and increment .var3 else increment .var4");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("check", "check"));
            cmd->Item_Add(new Cmd_Item_Word("if", "check if"));
            cmd->Item_Add(new Cmd_Item_Point_Var_Name(".<v>", "var name"));
            cmd->Item_Add(new Cmd_Item_EQU_Range("[compare: " + cmp_str_str + "]", "compare function", cmp_str_words));
            cmd->Item_Add(new Cmd_Item_Point_Var_Name(".<v2>", "var2 name"));
            cmd->Item_Add(new Cmd_Item_Word("inc", "check and increment"));
            cmd->Item_Add(new Cmd_Item_Point_Var_Name(".<v3>", ".var3 to increment"));
            cmd->Item_Add(new Cmd_Item_Word("else", "else"));
            cmd->Item_Add(new Cmd_Item_Word("inc", "check and increment"));
            cmd->Item_Add(new Cmd_Item_Point_Var_Name(".<v4>", ".var4 to increment"));

            Cmd_Add(cmd);
        } // check if .v compare .v2 inc .v3 else inc .v4

        {
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_check_if_var_compare_var2_do_script_stop);
            cmd->Text_Set("check if .<v> [compare: " + cmp_str_str + "] .<v2> do script stop");
            cmd->Help_Set("check .var by .var2 and stop script");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("check", "check"));
            cmd->Item_Add(new Cmd_Item_Word("if", "check if"));
            cmd->Item_Add(new Cmd_Item_Point_Var_Name(".<v>", "var name"));
            cmd->Item_Add(new Cmd_Item_EQU_Range("[compare: " + cmp_str_str + "]", "compare function", cmp_int_words));
            cmd->Item_Add(new Cmd_Item_Point_Var_Name(".<v2>", "var2 name"));
            cmd->Item_Add(new Cmd_Item_Word("do", "do"));
            cmd->Item_Add(new Cmd_Item_Word("script", "do script"));
            cmd->Item_Add(new Cmd_Item_Word("stop", "do script stop"));

            Cmd_Add(cmd);
        } // check if .v compare .v2 do script stop

        {
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_check_if_var_compare_var2_do_script_filename);
            cmd->Text_Set("check if .<v> [compare: " + cmp_str_str + "] .<v2> do script <filename>");
            cmd->Help_Set("check .var by .var2 and do script from file");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("check", "check"));
            cmd->Item_Add(new Cmd_Item_Word("if", "check if"));
            cmd->Item_Add(new Cmd_Item_Point_Var_Name(".<v>", "var name"));
            cmd->Item_Add(new Cmd_Item_EQU_Range("[compare: " + cmp_str_str + "]", "compare function", cmp_str_words));
            cmd->Item_Add(new Cmd_Item_Point_Var_Name(".<v2>", "var2 name"));
            cmd->Item_Add(new Cmd_Item_Word("do", "do"));
            cmd->Item_Add(new Cmd_Item_Word("script", "do script"));
            cmd->Item_Add(new Cmd_Item_Str("<filename>", "script file name"));

            Cmd_Add(cmd);
        } // check if .v compare .v2 do script str
        {
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_check_if_var_compare_var2_do_script_filename_no_history);
            cmd->Text_Set("check if .<v> [compare: " + cmp_str_str + "] .<v2> do script <filename> no history");
            cmd->Help_Set("check .var by .var2 and do script from file, not save to history");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("check", "check"));
            cmd->Item_Add(new Cmd_Item_Word("if", "check if"));
            cmd->Item_Add(new Cmd_Item_Point_Var_Name(".<v>", "var name"));
            cmd->Item_Add(new Cmd_Item_EQU_Range("[compare: " + cmp_str_str + "]", "compare function", cmp_str_words));
            cmd->Item_Add(new Cmd_Item_Point_Var_Name(".<v2>", "var2 name"));
            cmd->Item_Add(new Cmd_Item_Word("do", "do"));
            cmd->Item_Add(new Cmd_Item_Word("script", "do script"));
            cmd->Item_Add(new Cmd_Item_Str("<filename>", "script file name"));
            cmd->Item_Add(new Cmd_Item_Word("no", "not save"));
            cmd->Item_Add(new Cmd_Item_Word("history", "not save to history"));

            Cmd_Add(cmd);
        } // check if .v compare .v2 do script str no history

        {
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_check_if_var_compare_var2_goto_str);
            cmd->Text_Set("check if .<v> [compare: " + cmp_str_str + "] .<v2> goto <lbl>");
            cmd->Help_Set("check .var by .var2 and goto <lbl> (for scripts only)");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("check", "check"));
            cmd->Item_Add(new Cmd_Item_Word("if", "check if"));
            cmd->Item_Add(new Cmd_Item_Point_Var_Name(".<v>", "var name"));
            cmd->Item_Add(new Cmd_Item_EQU_Range("[compare: " + cmp_str_str + "]", "compare function", cmp_str_words));
            cmd->Item_Add(new Cmd_Item_Point_Var_Name(".<v2>", "var2 name"));
            cmd->Item_Add(new Cmd_Item_Word("goto", "goto"));
            cmd->Item_Add(new Cmd_Item_Str("<lbl>", "label name"));

            Cmd_Add(cmd);
        } // check if .v compare .v2 goto str
        {
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_check_if_var_compare_var2_goto_str_else_goto_str);
            cmd->Text_Set("check if .<v> [compare: " + cmp_str_str + "] .<v2> goto <lbl> else goto <lbl2>");
            cmd->Help_Set("check .var by .var2 and goto <lbl> or <lbl2> (for scripts only)");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("check", "check"));
            cmd->Item_Add(new Cmd_Item_Word("if", "check if"));
            cmd->Item_Add(new Cmd_Item_Point_Var_Name(".<v>", "var name"));
            cmd->Item_Add(new Cmd_Item_EQU_Range("[compare: " + cmp_str_str + "]", "compare function", cmp_str_words));
            cmd->Item_Add(new Cmd_Item_Point_Var_Name(".<v2>", "var2 name"));
            cmd->Item_Add(new Cmd_Item_Word("goto", "goto"));
            cmd->Item_Add(new Cmd_Item_Str("<lbl>", "label name"));
            cmd->Item_Add(new Cmd_Item_Word("else", "else"));
            cmd->Item_Add(new Cmd_Item_Word("goto", "goto"));
            cmd->Item_Add(new Cmd_Item_Str("<lbl2>", "label2 name"));

            Cmd_Add(cmd);
        } // check if .v compare .v2 goto str else goto str

        // </editor-fold>

        // <editor-fold defaultstate="collapsed" desc="Check if: var compare var2/str print/inc/do script/do command">

        {
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_check_if_var_compare_str_print_var2);
            cmd->Text_Set("check if .<v> [compare: " + cmp_str_str + "] <str> print .<v2>");
            cmd->Help_Set("check .var by str and print .var2");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("check", "check"));
            cmd->Item_Add(new Cmd_Item_Word("if", "check if"));
            cmd->Item_Add(new Cmd_Item_Point_Var_Name(".<v>", ".var name"));
            cmd->Item_Add(new Cmd_Item_EQU_Range("[compare: " + cmp_str_str + "]", "compare function", cmp_str_words));
            cmd->Item_Add(new Cmd_Item_Str("<str>", "str to compare"));
            cmd->Item_Add(new Cmd_Item_Word("print", "check and print"));
            cmd->Item_Add(new Cmd_Item_Point_Var_Name(".<v2>", ".var2 to print"));

            Cmd_Add(cmd);
        } // check if .v compare str print .v2
        {
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_check_if_var_compare_str_print_str);
            cmd->Text_Set("check if .<v> [compare: " + cmp_str_str + "] <str> print <msg>");
            cmd->Help_Set("check .var by str and print <msg>");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("check", "check"));
            cmd->Item_Add(new Cmd_Item_Word("if", "check if"));
            cmd->Item_Add(new Cmd_Item_Point_Var_Name(".<v>", ".var name"));
            cmd->Item_Add(new Cmd_Item_EQU_Range("[compare: " + cmp_str_str + "]", "compare function", cmp_str_words));
            cmd->Item_Add(new Cmd_Item_Str("<str>", "str to compare"));
            cmd->Item_Add(new Cmd_Item_Word("print", "check and print"));
            cmd->Item_Add(new Cmd_Item_Str("<msg>", "msg to print"));

            Cmd_Add(cmd);
        } // check if .v compare str print str

        {
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_check_if_var_compare_str_print_var2_else_print_var3);
            cmd->Text_Set("check if .<v> [compare: " + cmp_str_str + "] <str> print .<v2> else print .<v3>");
            cmd->Help_Set("check .var by str and print .var2 else print .var3");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("check", "check"));
            cmd->Item_Add(new Cmd_Item_Word("if", "check if"));
            cmd->Item_Add(new Cmd_Item_Point_Var_Name(".<v>", ".var name"));
            cmd->Item_Add(new Cmd_Item_EQU_Range("[compare: " + cmp_str_str + "]", "compare function", cmp_str_words));
            cmd->Item_Add(new Cmd_Item_Str("<str>", "str to compare"));
            cmd->Item_Add(new Cmd_Item_Word("print", "check and print"));
            cmd->Item_Add(new Cmd_Item_Point_Var_Name(".<v2>", ".var2 to print"));
            cmd->Item_Add(new Cmd_Item_Word("else", "else"));
            cmd->Item_Add(new Cmd_Item_Word("print", "check and print"));
            cmd->Item_Add(new Cmd_Item_Point_Var_Name(".<v3>", ".var3 to print"));

            Cmd_Add(cmd);
        } // check if .v compare str print .v2 else print .v3
        {
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_check_if_var_compare_str_print_var2_else_print_str);
            cmd->Text_Set("check if .<v> [compare: " + cmp_str_str + "] <str> print .<v3> else print <msg>");
            cmd->Help_Set("check .var by str and print .var2 else print <msg>");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("check", "check"));
            cmd->Item_Add(new Cmd_Item_Word("if", "check if"));
            cmd->Item_Add(new Cmd_Item_Point_Var_Name(".<v>", "var name"));
            cmd->Item_Add(new Cmd_Item_EQU_Range("[compare: " + cmp_str_str + "]", "compare function", cmp_str_words));
            cmd->Item_Add(new Cmd_Item_Str("<str>", "str to compare"));
            cmd->Item_Add(new Cmd_Item_Word("print", "check and print"));
            cmd->Item_Add(new Cmd_Item_Point_Var_Name(".<v2>", ".var2 to print"));
            cmd->Item_Add(new Cmd_Item_Word("else", "else"));
            cmd->Item_Add(new Cmd_Item_Word("print", "check and print"));
            cmd->Item_Add(new Cmd_Item_Str("<msg>", "msg to print"));

            Cmd_Add(cmd);
        } // check if .v compare str print .v2 else print str
        {
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_check_if_var_compare_str_print_str_else_print_var2);
            cmd->Text_Set("check if .<v> [compare: " + cmp_str_str + "] <str> print <msg> else print .<v2>");
            cmd->Help_Set("check .var by str and print <msg> else print .var2");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("check", "check"));
            cmd->Item_Add(new Cmd_Item_Word("if", "check if"));
            cmd->Item_Add(new Cmd_Item_Point_Var_Name(".<v>", ".var name"));
            cmd->Item_Add(new Cmd_Item_EQU_Range("[compare: " + cmp_str_str + "]", "compare function", cmp_str_words));
            cmd->Item_Add(new Cmd_Item_Str("<str>", "str to compare"));
            cmd->Item_Add(new Cmd_Item_Word("print", "check and print"));
            cmd->Item_Add(new Cmd_Item_Str("<msg>", "msg to print"));
            cmd->Item_Add(new Cmd_Item_Word("else", "else"));
            cmd->Item_Add(new Cmd_Item_Word("print", "check and print"));
            cmd->Item_Add(new Cmd_Item_Point_Var_Name(".<v2>", ".var2 to print"));

            Cmd_Add(cmd);
        } // check if .v compare str print str else print .v2
        {
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_check_if_var_compare_str_print_str_else_print_str);
            cmd->Text_Set("check if .<v> [compare: " + cmp_str_str + "] <str> print <msg> else print <msg2>");
            cmd->Help_Set("check .var by str and print <msg> else print <msg2>");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("check", "check"));
            cmd->Item_Add(new Cmd_Item_Word("if", "check if"));
            cmd->Item_Add(new Cmd_Item_Point_Var_Name(".<v>", "var name"));
            cmd->Item_Add(new Cmd_Item_EQU_Range("[compare: " + cmp_str_str + "]", "compare function", cmp_str_words));
            cmd->Item_Add(new Cmd_Item_Str("<str>", "str to compare"));
            cmd->Item_Add(new Cmd_Item_Word("print", "check and print"));
            cmd->Item_Add(new Cmd_Item_Str("<msg>", "msg to print"));
            cmd->Item_Add(new Cmd_Item_Word("else", "else"));
            cmd->Item_Add(new Cmd_Item_Word("print", "print"));
            cmd->Item_Add(new Cmd_Item_Str("<msg2>", "msg2 to print"));

            Cmd_Add(cmd);
        } // check if .v compare str print str else print str2

        {
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_check_if_var_compare_str_inc_var2);
            cmd->Text_Set("check if .<v> [compare: " + cmp_str_str + "] <str> inc .<v2>");
            cmd->Help_Set("check .var by str and increment .var2");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("check", "check"));
            cmd->Item_Add(new Cmd_Item_Word("if", "check if"));
            cmd->Item_Add(new Cmd_Item_Point_Var_Name(".<v>", "var name"));
            cmd->Item_Add(new Cmd_Item_EQU_Range("[compare: " + cmp_str_str + "]", "compare function", cmp_str_words));
            cmd->Item_Add(new Cmd_Item_Str("<str>", "str to compare"));
            cmd->Item_Add(new Cmd_Item_Word("inc", "check and increment"));
            cmd->Item_Add(new Cmd_Item_Point_Var_Name(".<v2>", ".var2 to increment"));

            Cmd_Add(cmd);
        } // check if .v compare str inc .v2
        {
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_check_if_var_compare_str_inc_var2_else_inc_var3);
            cmd->Text_Set("check if .<v> [compare: " + cmp_str_str + "] <str> inc .<v2> else inc .<v3>");
            cmd->Help_Set("check .var by str and increment .var2 else increment .var3");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("check", "check"));
            cmd->Item_Add(new Cmd_Item_Word("if", "check if"));
            cmd->Item_Add(new Cmd_Item_Point_Var_Name(".<v>", "var name"));
            cmd->Item_Add(new Cmd_Item_EQU_Range("[compare: " + cmp_str_str + "]", "compare function", cmp_str_words));
            cmd->Item_Add(new Cmd_Item_Str("<str>", "str to compare"));
            cmd->Item_Add(new Cmd_Item_Word("inc", "check and increment"));
            cmd->Item_Add(new Cmd_Item_Point_Var_Name(".<v2>", ".var2 to increment"));
            cmd->Item_Add(new Cmd_Item_Word("else", "else"));
            cmd->Item_Add(new Cmd_Item_Word("inc", "check and increment"));
            cmd->Item_Add(new Cmd_Item_Point_Var_Name(".<v3>", ".var3 to increment"));

            Cmd_Add(cmd);
        } // check if .v compare str inc .v2 else inc .v3

        {
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_check_if_var_compare_str_do_script_stop);
            cmd->Text_Set("check if .<v> [compare: " + cmp_str_str + "] <str> do script stop");
            cmd->Help_Set("check .var by str and stop script");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("check", "check"));
            cmd->Item_Add(new Cmd_Item_Word("if", "check if"));
            cmd->Item_Add(new Cmd_Item_Point_Var_Name(".<v>", "var name"));
            cmd->Item_Add(new Cmd_Item_EQU_Range("[compare: " + cmp_str_str + "]", "compare function", cmp_int_words));
            cmd->Item_Add(new Cmd_Item_Str("<str>", "str to compare"));
            cmd->Item_Add(new Cmd_Item_Word("do", "do"));
            cmd->Item_Add(new Cmd_Item_Word("script", "do script"));
            cmd->Item_Add(new Cmd_Item_Word("stop", "do script stop"));

            Cmd_Add(cmd);
        } // check if .v compare str do script stop

        {
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_check_if_var_compare_str_do_script_filename);
            cmd->Text_Set("check if .<v> [compare: " + cmp_str_str + "] <str> do script <filename>");
            cmd->Help_Set("check .var by str and do script from file");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("check", "check"));
            cmd->Item_Add(new Cmd_Item_Word("if", "check if"));
            cmd->Item_Add(new Cmd_Item_Point_Var_Name(".<v>", "var name"));
            cmd->Item_Add(new Cmd_Item_EQU_Range("[compare: " + cmp_str_str + "]", "compare function", cmp_str_words));
            cmd->Item_Add(new Cmd_Item_Str("<str>", "str to compare"));
            cmd->Item_Add(new Cmd_Item_Word("do", "do"));
            cmd->Item_Add(new Cmd_Item_Word("script", "do script"));
            cmd->Item_Add(new Cmd_Item_Str("<filename>", "script file name"));

            Cmd_Add(cmd);
        } // check if .v compare str do script str
        {
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_check_if_var_compare_str_do_script_filename_no_history);
            cmd->Text_Set("check if .<v> [compare: " + cmp_str_str + "] <str> do script <filename> no history");
            cmd->Help_Set("check .var by str and do script from file, not save to history");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("check", "check"));
            cmd->Item_Add(new Cmd_Item_Word("if", "check if"));
            cmd->Item_Add(new Cmd_Item_Point_Var_Name(".<v>", "var name"));
            cmd->Item_Add(new Cmd_Item_EQU_Range("[compare: " + cmp_str_str + "]", "compare function", cmp_str_words));
            cmd->Item_Add(new Cmd_Item_Str("<str>", "str to compare"));
            cmd->Item_Add(new Cmd_Item_Word("do", "do"));
            cmd->Item_Add(new Cmd_Item_Word("script", "do script"));
            cmd->Item_Add(new Cmd_Item_Str("<filename>", "script file name"));
            cmd->Item_Add(new Cmd_Item_Word("no", "not save"));
            cmd->Item_Add(new Cmd_Item_Word("history", "not save to history"));

            Cmd_Add(cmd);
        } // check if .v compare str do script str no history

        {
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_check_if_var_compare_str_goto_str);
            cmd->Text_Set("check if .<v> [compare: " + cmp_str_str + "] <str> goto <lbl>");
            cmd->Help_Set("check .var by str and goto <lbl> (for scripts only)");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("check", "check"));
            cmd->Item_Add(new Cmd_Item_Word("if", "check if"));
            cmd->Item_Add(new Cmd_Item_Point_Var_Name(".<v>", "var name"));
            cmd->Item_Add(new Cmd_Item_EQU_Range("[compare: " + cmp_str_str + "]", "compare function", cmp_str_words));
            cmd->Item_Add(new Cmd_Item_Str("<str>", "str to compare"));
            cmd->Item_Add(new Cmd_Item_Word("goto", "goto"));
            cmd->Item_Add(new Cmd_Item_Str("<lbl>", "label name"));

            Cmd_Add(cmd);
        } // check if .v compare str goto str
        {
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_check_if_var_compare_str_goto_str_else_goto_str);
            cmd->Text_Set("check if .<v> [compare: " + cmp_str_str + "] <str> goto <lbl> else goto <lbl2>");
            cmd->Help_Set("check .var by str and goto <lbl> or <lbl2> (for scripts only)");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("check", "check"));
            cmd->Item_Add(new Cmd_Item_Word("if", "check if"));
            cmd->Item_Add(new Cmd_Item_Point_Var_Name(".<v>", "var name"));
            cmd->Item_Add(new Cmd_Item_EQU_Range("[compare: " + cmp_str_str + "]", "compare function", cmp_str_words));
            cmd->Item_Add(new Cmd_Item_Str("<str>", "str to compare"));
            cmd->Item_Add(new Cmd_Item_Word("goto", "goto"));
            cmd->Item_Add(new Cmd_Item_Str("<lbl>", "label name"));
            cmd->Item_Add(new Cmd_Item_Word("else", "else"));
            cmd->Item_Add(new Cmd_Item_Word("goto", "goto"));
            cmd->Item_Add(new Cmd_Item_Str("<lbl2>", "label2 name"));

            Cmd_Add(cmd);
        } // check if .v compare str goto str else goto str

        // </editor-fold>

    }

    virtual ~Cli_Module_Check() {
    }

    // @Double Code: Str_Get_Without_Commas(...) - from Cli_Module_Vars.h

    string Str_Get_Without_Commas(string value_str) {
        string s = value_str;
        if (value_str.size() >= 2) {
            if (
                    (value_str[0] == '\"' && value_str[value_str.size() - 1] == '\"')
                    || (value_str[0] == '\'' && value_str[value_str.size() - 1] == '\'')
                    ) {
                s = value_str.substr(1, value_str.size() - 2);
            }
        }
        return s;
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
                if (str_filter.Is_Match(module_filter, module_name)) {
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

    bool check_AS_INT_var_by_var_print_msg1_or_msg2(string var_left, string s_compare, string var_right,
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

    bool check_AS_STR_var_by_var_print_msg1_or_msg2(string var_left, string s_compare, string var_right,
            string s_msg1, bool is_msg2, string s_msg2) {
        map<string, string>::iterator var_left_iter = Values_Map.find(var_left);
        map<string, string>::iterator var_right_iter = Values_Map.find(var_right);

        Cli_Output.Output_NewLine();

        if (var_left_iter != Values_Map.end() && var_right_iter != Values_Map.end()) {
            string var_left_value = var_left_iter->second;
            string var_right_value = var_right_iter->second;
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
                Values_Map[var1_inc] = s_str.str();
            } else if (cmp_res == CMP_FALSE) {
                if (is_var2_inc) {
                    var2_value++;
                    stringstream s_str;
                    s_str << var2_value;
                    Values_Map[var2_inc] = s_str.str();
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
                Values_Map[var1_inc] = s_str.str();
            } else if (cmp_res == CMP_FALSE) {
                if (is_var2_inc) {
                    var2_value++;
                    stringstream s_str;
                    s_str << var2_value;
                    Values_Map[var2_inc] = s_str.str();
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
        Cli_Output.Output_Str("Do_Script_From_File: " + filename + (is_no_history ? " no history" : " history") + " - Not Realized");
        Cli_Output.Output_NewLine();
        return false;
    }

    bool Do_Command(string command) {
        Cli_Output.Output_Str("Do_Command: " + command + " - Not Realized");
        Cli_Output.Output_NewLine();
        return false;
    }

    bool Do_Label(string label) {
        Cli_Output.Output_Str("Do_Label: " + label + " - Not Realized");
        Cli_Output.Output_NewLine();
        return false;
    }

    bool Do_Goto_Label(string label) {
        Cli_Output.Output_Str("Do_Goto_Label: " + label + " - Not Realized");
        Cli_Output.Output_NewLine();
        return false;
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

                // <editor-fold defaultstate="collapsed" desc="Values_Map: modules to map">

            case CMD_ID_check_modules_by_filter_to_map:
                if (is_debug) return true;
            {
                string module_filter = cmd->Items[2]->Value_Str;
                return check_modules_to_map(module_filter, Str_Filter);
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

                // <editor-fold defaultstate="collapsed" desc="Check if: .v compare .v2 print/inc/do/goto">

            case CMD_ID_check_if_var_compare_var2_print_var3:
                if (is_debug) return true;
            {
                string var_left = cmd->Items[2]->Value_Str.substr(1);
                string s_compare = cmd->Items[3]->Value_Str;
                string var_right = cmd->Items[4]->Value_Str.substr(1);
                string var_to_print = cmd->Items[6]->Value_Str.substr(1);
                string s_msg1;
                bool is_msg2;
                string s_msg2;
                {
                    map<string, string>::iterator iter_to_print = Values_Map.find(var_to_print);
                    if (iter_to_print != Values_Map.end()) {
                        s_msg1 = iter_to_print->second;
                        return check_AS_STR_var_by_var_print_msg1_or_msg2(var_left, s_compare, var_right, s_msg1, is_msg2 = false, s_msg2);
                    } else {
                        Cli_Output.Output_NewLine();
                        Cli_Output.Output_Str("ERROR: var " + var_to_print + " not found");
                        Cli_Output.Output_NewLine();
                    }
                }
                return true;
            }
                break;
            case CMD_ID_check_if_var_compare_var2_print_str:
                if (is_debug) return true;
            {
                string var_left = cmd->Items[2]->Value_Str.substr(1);
                string s_compare = cmd->Items[3]->Value_Str;
                string var_right = cmd->Items[4]->Value_Str.substr(1);
                string s_msg1 = cmd->Items[6]->Value_Str;
                bool is_msg2;
                string s_msg2;
                return check_AS_STR_var_by_var_print_msg1_or_msg2(var_left, s_compare, var_right, s_msg1, is_msg2 = false, s_msg2);
            }
                break;

            case CMD_ID_check_if_var_compare_var2_print_var3_else_print_var4:
                if (is_debug) return true;
            {
                string var_left = cmd->Items[2]->Value_Str.substr(1);
                string s_compare = cmd->Items[3]->Value_Str;
                string var_right = cmd->Items[4]->Value_Str.substr(1);
                string var_to_print = cmd->Items[6]->Value_Str.substr(1);
                string var_to_print2 = cmd->Items[9]->Value_Str.substr(1);
                string s_msg1;
                bool is_msg2;
                string s_msg2;
                {
                    map<string, string>::iterator iter_to_print = Values_Map.find(var_to_print);
                    map<string, string>::iterator iter_to_print2 = Values_Map.find(var_to_print2);
                    if (iter_to_print != Values_Map.end() && iter_to_print2 != Values_Map.end()) {
                        s_msg1 = iter_to_print->second;
                        s_msg2 = iter_to_print2->second;
                        return check_AS_STR_var_by_var_print_msg1_or_msg2(var_left, s_compare, var_right, s_msg1, is_msg2 = true, s_msg2);
                    } else {
                        Cli_Output.Output_NewLine();
                        if (iter_to_print == Values_Map.end()) {
                            Cli_Output.Output_Str("ERROR: var " + var_to_print + " not found");
                            Cli_Output.Output_NewLine();
                        }
                        if (iter_to_print2 == Values_Map.end()) {
                            Cli_Output.Output_Str("ERROR: var " + var_to_print2 + " not found");
                            Cli_Output.Output_NewLine();
                        }
                    }
                }
                return true;
            }
                break;
            case CMD_ID_check_if_var_compare_var2_print_var3_else_print_str:
                if (is_debug) return true;
            {
                string var_left = cmd->Items[2]->Value_Str.substr(1);
                string s_compare = cmd->Items[3]->Value_Str;
                string var_right = cmd->Items[4]->Value_Str.substr(1);
                string var_to_print = cmd->Items[6]->Value_Str.substr(1);
                string s_msg1;
                bool is_msg2;
                string s_msg2 = cmd->Items[9]->Value_Str;
                {
                    map<string, string>::iterator iter_to_print = Values_Map.find(var_to_print);
                    if (iter_to_print != Values_Map.end()) {
                        s_msg1 = iter_to_print->second;
                        return check_AS_STR_var_by_var_print_msg1_or_msg2(var_left, s_compare, var_right, s_msg1, is_msg2 = true, s_msg2);
                    } else {
                        Cli_Output.Output_NewLine();
                        if (iter_to_print == Values_Map.end()) {
                            Cli_Output.Output_Str("ERROR: var " + var_to_print + " not found");
                            Cli_Output.Output_NewLine();
                        }
                    }
                }
                return true;
            }
                break;
            case CMD_ID_check_if_var_compare_var2_print_str_else_print_var3:
                if (is_debug) return true;
            {
                string var_left = cmd->Items[2]->Value_Str.substr(1);
                string s_compare = cmd->Items[3]->Value_Str;
                string var_right = cmd->Items[4]->Value_Str.substr(1);
                string var_to_print = cmd->Items[9]->Value_Str.substr(1);
                string s_msg1;
                bool is_msg2;
                string s_msg2 = cmd->Items[6]->Value_Str;
                {
                    map<string, string>::iterator iter_to_print = Values_Map.find(var_to_print);
                    if (iter_to_print != Values_Map.end()) {
                        s_msg1 = iter_to_print->second;
                        return check_AS_STR_var_by_var_print_msg1_or_msg2(var_left, s_compare, var_right, s_msg1, is_msg2 = true, s_msg2);
                    } else {
                        Cli_Output.Output_NewLine();
                        if (iter_to_print == Values_Map.end()) {
                            Cli_Output.Output_Str("ERROR: var " + var_to_print + " not found");
                            Cli_Output.Output_NewLine();
                        }
                    }
                }
                return true;
            }
                break;
            case CMD_ID_check_if_var_compare_var2_print_str_else_print_str:
                if (is_debug) return true;
            {
                string var_left = cmd->Items[2]->Value_Str.substr(1);
                string s_compare = cmd->Items[3]->Value_Str;
                string var_right = cmd->Items[4]->Value_Str.substr(1);
                string s_msg1 = cmd->Items[6]->Value_Str;
                bool is_msg2;
                string s_msg2 = cmd->Items[9]->Value_Str;
                return check_AS_STR_var_by_var_print_msg1_or_msg2(var_left, s_compare, var_right, s_msg1, is_msg2 = true, s_msg2);
            }
                break;

            case CMD_ID_check_if_var_compare_var2_inc_var3:
                if (is_debug) return true;
            {
                string var_left = cmd->Items[2]->Value_Str.substr(1);
                string s_compare = cmd->Items[3]->Value_Str;
                string var_right = cmd->Items[4]->Value_Str.substr(1);
                string var1_to_inc = cmd->Items[6]->Value_Str.substr(1);
                bool is_var2_inc;
                string var2_to_inc;
                return check_var_by_var_inc_var1_or_var2(var_left, s_compare, var_right, var1_to_inc, is_var2_inc = false, var2_to_inc);
            }
                break;
            case CMD_ID_check_if_var_compare_var2_inc_var3_else_inc_var4:
                if (is_debug) return true;
            {
                string var_left = cmd->Items[2]->Value_Str.substr(1);
                string s_compare = cmd->Items[3]->Value_Str;
                string var_right = cmd->Items[4]->Value_Str.substr(1);
                string var1_to_inc = cmd->Items[6]->Value_Str.substr(1);
                bool is_var2_inc;
                string var2_to_inc = cmd->Items[9]->Value_Str.substr(1);
                return check_var_by_var_inc_var1_or_var2(var_left, s_compare, var_right, var1_to_inc, is_var2_inc = true, var2_to_inc);
            }
                break;

            case CMD_ID_check_if_var_compare_var2_do_script_stop:
                if (is_debug) return true;
            {
                string var_left = cmd->Items[2]->Value_Str.substr(1);
                string s_compare = cmd->Items[3]->Value_Str;
                string var_right = cmd->Items[4]->Value_Str.substr(1);
                return check_var_by_var_do_script_stop(var_left, s_compare, var_right);
            }

            case CMD_ID_check_if_var_compare_var2_do_script_filename:
                if (is_debug) return true;
            {
                string var_left = cmd->Items[2]->Value_Str.substr(1);
                string s_compare = cmd->Items[3]->Value_Str;
                string var_right = cmd->Items[4]->Value_Str.substr(1);
                string filename = cmd->Items[7]->Value_Str;
                bool is_no_history;
                return check_var_by_var_do_script_from_file(var_left, s_compare, var_right, filename, is_no_history = false);
            }
            case CMD_ID_check_if_var_compare_var2_do_script_filename_no_history:
                if (is_debug) return true;
            {
                string var_left = cmd->Items[2]->Value_Str.substr(1);
                string s_compare = cmd->Items[3]->Value_Str;
                string var_right = cmd->Items[4]->Value_Str.substr(1);
                string filename = cmd->Items[7]->Value_Str;
                bool is_no_history;
                return check_var_by_var_do_script_from_file(var_left, s_compare, var_right, filename, is_no_history = true);
            }

            case CMD_ID_check_if_var_compare_var2_goto_str:
                if (is_debug) return true;
            {
                string var_left = cmd->Items[2]->Value_Str.substr(1);
                string s_compare = cmd->Items[3]->Value_Str;
                string var_right = cmd->Items[4]->Value_Str.substr(1);
                string label1 = cmd->Items[6]->Value_Str;
                bool is_label2;
                string label2;
                return check_var_by_var_goto_label(var_left, s_compare, var_right, label1, is_label2 = false, label2);
            }
            case CMD_ID_check_if_var_compare_var2_goto_str_else_goto_str:
                if (is_debug) return true;
            {
                string var_left = cmd->Items[2]->Value_Str.substr(1);
                string s_compare = cmd->Items[3]->Value_Str;
                string var_right = cmd->Items[4]->Value_Str.substr(1);
                string label1 = cmd->Items[6]->Value_Str;
                bool is_label2;
                string label2 = cmd->Items[9]->Value_Str;
                return check_var_by_var_goto_label(var_left, s_compare, var_right, label1, is_label2 = true, label2);
            }

                // </editor-fold>

                // <editor-fold defaultstate="collapsed" desc="Check if: .v compare str print/inc/do/goto">

            case CMD_ID_check_if_var_compare_str_print_var2:
                if (is_debug) return true;
            {
                string var_left = cmd->Items[2]->Value_Str.substr(1);
                string s_compare = cmd->Items[3]->Value_Str;
                string value_right = Str_Get_Without_Commas(cmd->Items[4]->Value_Str); //.substr(1);
                string var_to_print = cmd->Items[6]->Value_Str.substr(1);
                string s_msg1;
                bool is_msg2;
                string s_msg2;
                {
                    map<string, string>::iterator iter_to_print = Values_Map.find(var_to_print);
                    if (iter_to_print != Values_Map.end()) {
                        s_msg1 = iter_to_print->second;
                        //return check_point_var_by_point_var_print_msg1_or_msg2(var_left, s_compare, var_right, s_msg1, is_msg2 = false, s_msg2);
                        return check_var_by_str_print_msg1_or_msg2(var_left, s_compare, value_right, s_msg1, is_msg2 = false, s_msg2);
                    } else {
                        Cli_Output.Output_NewLine();
                        Cli_Output.Output_Str("ERROR: var " + var_to_print + " not found");
                        Cli_Output.Output_NewLine();
                    }
                }
                return true;
            }
                break;
            case CMD_ID_check_if_var_compare_str_print_str:
                if (is_debug) return true;
            {
                string var_left = cmd->Items[2]->Value_Str.substr(1);
                string s_compare = cmd->Items[3]->Value_Str;
                string value_right = Str_Get_Without_Commas(cmd->Items[4]->Value_Str); //.substr(1);
                string s_msg1 = Str_Get_Without_Commas(cmd->Items[6]->Value_Str);
                bool is_msg2;
                string s_msg2;
                //return check_point_var_by_point_var_print_msg1_or_msg2(var_left, s_compare, var_right, s_msg1, is_msg2 = false, s_msg2);
                return check_var_by_str_print_msg1_or_msg2(var_left, s_compare, value_right, s_msg1, is_msg2 = false, s_msg2);
            }
                break;

            case CMD_ID_check_if_var_compare_str_print_var2_else_print_var3:
                if (is_debug) return true;
            {
                string var_left = cmd->Items[2]->Value_Str.substr(1);
                string s_compare = cmd->Items[3]->Value_Str;
                string value_right = Str_Get_Without_Commas(cmd->Items[4]->Value_Str); //.substr(1);
                string var_to_print = cmd->Items[6]->Value_Str.substr(1);
                string var_to_print2 = cmd->Items[9]->Value_Str.substr(1);
                string s_msg1;
                bool is_msg2;
                string s_msg2;
                {
                    map<string, string>::iterator iter_to_print = Values_Map.find(var_to_print);
                    map<string, string>::iterator iter_to_print2 = Values_Map.find(var_to_print2);
                    if (iter_to_print != Values_Map.end() && iter_to_print2 != Values_Map.end()) {
                        s_msg1 = iter_to_print->second;
                        s_msg2 = iter_to_print2->second;
                        //return check_point_var_by_point_var_print_msg1_or_msg2(var_left, s_compare, var_right, s_msg1, is_msg2 = true, s_msg2);
                        return check_var_by_str_print_msg1_or_msg2(var_left, s_compare, value_right, s_msg1, is_msg2 = true, s_msg2);
                    } else {
                        Cli_Output.Output_NewLine();
                        if (iter_to_print == Values_Map.end()) {
                            Cli_Output.Output_Str("ERROR: var " + var_to_print + " not found");
                            Cli_Output.Output_NewLine();
                        }
                        if (iter_to_print2 == Values_Map.end()) {
                            Cli_Output.Output_Str("ERROR: var " + var_to_print2 + " not found");
                            Cli_Output.Output_NewLine();
                        }
                    }
                }
                return true;
            }
                break;
            case CMD_ID_check_if_var_compare_str_print_var2_else_print_str:
                if (is_debug) return true;
            {
                string var_left = cmd->Items[2]->Value_Str.substr(1);
                string s_compare = cmd->Items[3]->Value_Str;
                string value_right = Str_Get_Without_Commas(cmd->Items[4]->Value_Str); //.substr(1);
                string var_to_print = cmd->Items[6]->Value_Str.substr(1);
                string s_msg1;
                bool is_msg2;
                string s_msg2 = Str_Get_Without_Commas(cmd->Items[9]->Value_Str);
                {
                    map<string, string>::iterator iter_to_print = Values_Map.find(var_to_print);
                    if (iter_to_print != Values_Map.end()) {
                        s_msg1 = iter_to_print->second;
                        //return check_point_var_by_point_var_print_msg1_or_msg2(var_left, s_compare, var_right, s_msg1, is_msg2 = true, s_msg2);
                        return check_var_by_str_print_msg1_or_msg2(var_left, s_compare, value_right, s_msg1, is_msg2 = true, s_msg2);
                    } else {
                        Cli_Output.Output_NewLine();
                        if (iter_to_print == Values_Map.end()) {
                            Cli_Output.Output_Str("ERROR: var " + var_to_print + " not found");
                            Cli_Output.Output_NewLine();
                        }
                    }
                }
                return true;
            }
                break;
            case CMD_ID_check_if_var_compare_str_print_str_else_print_var2:
                if (is_debug) return true;
            {
                string var_left = cmd->Items[2]->Value_Str.substr(1);
                string s_compare = cmd->Items[3]->Value_Str;
                string value_right = Str_Get_Without_Commas(cmd->Items[4]->Value_Str); //.substr(1);
                string var_to_print = cmd->Items[9]->Value_Str.substr(1);
                string s_msg1;
                bool is_msg2;
                string s_msg2 = Str_Get_Without_Commas(cmd->Items[6]->Value_Str);
                {
                    map<string, string>::iterator iter_to_print = Values_Map.find(var_to_print);
                    if (iter_to_print != Values_Map.end()) {
                        s_msg1 = iter_to_print->second;
                        //return check_point_var_by_point_var_print_msg1_or_msg2(var_left, s_compare, var_right, s_msg1, is_msg2 = true, s_msg2);
                        return check_var_by_str_print_msg1_or_msg2(var_left, s_compare, value_right, s_msg1, is_msg2 = true, s_msg2);
                    } else {
                        Cli_Output.Output_NewLine();
                        if (iter_to_print == Values_Map.end()) {
                            Cli_Output.Output_Str("ERROR: var " + var_to_print + " not found");
                            Cli_Output.Output_NewLine();
                        }
                    }
                }
                return true;
            }
                break;
            case CMD_ID_check_if_var_compare_str_print_str_else_print_str:
                if (is_debug) return true;
            {
                string var_left = cmd->Items[2]->Value_Str.substr(1);
                string s_compare = cmd->Items[3]->Value_Str;
                string value_right = Str_Get_Without_Commas(cmd->Items[4]->Value_Str); //.substr(1);
                string s_msg1 = cmd->Items[6]->Value_Str;
                bool is_msg2;
                string s_msg2 = cmd->Items[9]->Value_Str;
                //return check_point_var_by_point_var_print_msg1_or_msg2(var_left, s_compare, var_right, s_msg1, is_msg2 = true, s_msg2);
                return check_var_by_str_print_msg1_or_msg2(var_left, s_compare, value_right, s_msg1, is_msg2 = true, s_msg2);
            }
                break;

            case CMD_ID_check_if_var_compare_str_inc_var2:
                if (is_debug) return true;
            {
                string var_left = cmd->Items[2]->Value_Str.substr(1);
                string s_compare = cmd->Items[3]->Value_Str;
                string value_right = Str_Get_Without_Commas(cmd->Items[4]->Value_Str); //.substr(1);
                string var1_to_inc = cmd->Items[6]->Value_Str.substr(1);
                bool is_var2_inc;
                string var2_to_inc;
                return check_var_by_str_inc_var1_or_var2(var_left, s_compare, value_right, var1_to_inc, is_var2_inc = false, var2_to_inc);
            }
                break;
            case CMD_ID_check_if_var_compare_str_inc_var2_else_inc_var3:
                if (is_debug) return true;
            {
                string var_left = cmd->Items[2]->Value_Str.substr(1);
                string s_compare = cmd->Items[3]->Value_Str;
                string value_right = Str_Get_Without_Commas(cmd->Items[4]->Value_Str); //.substr(1);
                string var1_to_inc = cmd->Items[6]->Value_Str.substr(1);
                bool is_var2_inc;
                string var2_to_inc = cmd->Items[9]->Value_Str.substr(1);
                return check_var_by_str_inc_var1_or_var2(var_left, s_compare, value_right, var1_to_inc, is_var2_inc = true, var2_to_inc);
            }
                break;

            case CMD_ID_check_if_var_compare_str_do_script_stop:
                if (is_debug) return true;
            {
                string var_left = cmd->Items[2]->Value_Str.substr(1);
                string s_compare = cmd->Items[3]->Value_Str;
                string value_right = Str_Get_Without_Commas(cmd->Items[4]->Value_Str); //.substr(1);
                return check_var_by_str_do_script_stop(var_left, s_compare, value_right);
            }

            case CMD_ID_check_if_var_compare_str_do_script_filename:
                if (is_debug) return true;
            {
                string var_left = cmd->Items[2]->Value_Str.substr(1);
                string s_compare = cmd->Items[3]->Value_Str;
                string value_right = Str_Get_Without_Commas(cmd->Items[4]->Value_Str); //.substr(1);
                string filename = cmd->Items[7]->Value_Str;
                bool is_no_history;
                return check_var_by_str_do_script_from_file(var_left, s_compare, value_right, filename, is_no_history = false);
            }
            case CMD_ID_check_if_var_compare_str_do_script_filename_no_history:
                if (is_debug) return true;
            {
                string var_left = cmd->Items[2]->Value_Str.substr(1);
                string s_compare = cmd->Items[3]->Value_Str;
                string value_right = Str_Get_Without_Commas(cmd->Items[4]->Value_Str); //.substr(1);
                string filename = cmd->Items[7]->Value_Str;
                bool is_no_history;
                return check_var_by_str_do_script_from_file(var_left, s_compare, value_right, filename, is_no_history = true);
            }

            case CMD_ID_check_if_var_compare_str_goto_str:
                if (is_debug) return true;
            {
                string var_left = cmd->Items[2]->Value_Str.substr(1);
                string s_compare = cmd->Items[3]->Value_Str;
                string value_right = Str_Get_Without_Commas(cmd->Items[4]->Value_Str);
                string label1 = cmd->Items[6]->Value_Str;
                bool is_label2;
                string label2;
                return check_var_by_str_goto_label(var_left, s_compare, value_right, label1, is_label2 = false, label2);
            }
            case CMD_ID_check_if_var_compare_str_goto_str_else_goto_str:
                if (is_debug) return true;
            {
                string var_left = cmd->Items[2]->Value_Str.substr(1);
                string s_compare = cmd->Items[3]->Value_Str;
                string value_right = Str_Get_Without_Commas(cmd->Items[4]->Value_Str);
                string label1 = cmd->Items[6]->Value_Str;
                bool is_label2;
                string label2 = cmd->Items[9]->Value_Str;
                return check_var_by_str_goto_label(var_left, s_compare, value_right, label1, is_label2 = true, label2);
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
