/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_Module_Test_Tab.h
 * Author: mike
 *
 * Created on July 21, 2020, 3:30 PM
 */

#ifndef CLI_MODULE_TEST_TAB_H
#define CLI_MODULE_TEST_TAB_H

#include "Cli_Module.h"

#include "Cmd_Item_Int_Range.h"
#include "Cmd_Item_Int_List.h"
#include "Cmd_Item_Word.h"
#include "Cmd_Item_Word_List.h"
#include "Cmd_Item_Str.h"

#include "Cmd_Item_Date.h"
#include "Cmd_Item_DateTime.h"
#include "Cmd_Item_Time.h"

class Cli_Module_Test_Tab : public Cli_Module {
public:

    enum Local_Cmd_ID {
        CMD_ID_NO,
        CMD_ID_rem,
        CMD_ID_exit,
        CMD_ID_quit,
        CMD_ID_help,
        CMD_ID_help_full,
        CMD_ID_help_full_verbose,
        CMD_ID_help_command,
        CMD_ID_help_command_verbose,
        CMD_ID_help_command_all_verbose,
        CMD_ID_debug_cli,
        CMD_ID_debug_cli_counts,
        CMD_ID_debug_cli_verbose,
        CMD_ID_debug_cli_verbose_failed,
        CMD_ID_clear_log,
        CMD_ID_clear_history,
        CMD_ID_wait,
        CMD_ID_log_wait_enable,
        CMD_ID_log_wait_disable,
        CMD_ID_do_script,
        CMD_ID_do_script_no_history,
        CMD_ID_do_script_stop,
        CMD_ID_save_history_as_script,
        CMD_ID_history_show,

        CMD_ID_test_set_loopback,
        CMD_ID_test_set_loopback_disable,
        CMD_ID_test_terminal,
        CMD_ID_test_set_range,
        CMD_ID_test_set_list,
        CMD_ID_test_set_str,
        CMD_ID_project_close_project_name,
        CMD_ID_object_close_object_name,
        CMD_ID_projects,
        CMD_ID_projects_save,
        CMD_ID_project_save,

        CMD_ID_set_date,
        CMD_ID_set_datetime,

        CMD_ID_set_sys,
        CMD_ID_set_sysdate,
        CMD_ID_set_sysdatetime,
        CMD_ID_set_systime,
        CMD_ID_set_sysmtime,

        CMD_ID_set_zsys,
        CMD_ID_set_zsys2,
        CMD_ID_set_zsysdate,
        CMD_ID_set_zsysdatetime,
        CMD_ID_set_zsystime,
        CMD_ID_set_zsysmtime,
        CMD_ID_set_zsysntime,

        CMD_ID_set_xsys,
        CMD_ID_set_xsys2,
        CMD_ID_set_xsysdate,

        CMD_ID_set_ysys,
        CMD_ID_set_ysys1,
        CMD_ID_set_ysys2,
        CMD_ID_set_ysysdate,
        CMD_ID_set_ysystime,

        CMD_ID_set_wsys,
        CMD_ID_set_wsys1,
        CMD_ID_set_wsysdate,
        CMD_ID_set_wsystime,
        
        CMD_ID_set_asys,
        CMD_ID_set_asys_A,
        CMD_ID_set_asys_B,

        CMD_ID_LAST
    };

    virtual int Cmd_ID_Count_Get() {
        return CMD_ID_LAST - CMD_ID_NO - 1;
    }

    Cli_Module_Test_Tab() : Cli_Module("Test Module") {
        {
            // quit
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_quit);
            cmd->Text_Set("quit");
            cmd->Help_Set("quit");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("quit", "quit"));
            Cmd_Add(cmd);
        }

        {
            // help
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_help);
            cmd->Text_Set("help|H");
            cmd->Help_Set("show help");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("help", "show help"));
            Cmd_Add(cmd);
        }
        {
            // help full
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_help_full);
            cmd->Text_Set("help full");
            cmd->Help_Set("show all available commands with arguments");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("help", "show all available commands"));
            cmd->Item_Add(new Cmd_Item_Word("full", "show with arguments"));
            Cmd_Add(cmd);
        }
        {
            // help full verbose
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_help_full_verbose);
            cmd->Text_Set("help full verbose");
            cmd->Help_Set("show all available commands with arguments information");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("help", "show all available commands"));
            cmd->Item_Add(new Cmd_Item_Word("full", "show with arguments"));
            cmd->Item_Add(new Cmd_Item_Word("verbose", "show all arguments information"));
            Cmd_Add(cmd);
        }

        {
            // help "<command>"
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_help_command);
            cmd->Text_Set("help \"<command>\"");
            cmd->Help_Set("show selected commands");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("help", "show selected commands"));
            cmd->Item_Add(new Cmd_Item_Str("\"<command>\"", "command about which need to obtain information"));
            Cmd_Add(cmd);
        }
        {
            // help "<command>" verbose
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_help_command_verbose);
            cmd->Text_Set("help \"<command>\" verbose");
            cmd->Help_Set("show selected commands with arguments information");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("help", "show selected commands with arguments information"));
            cmd->Item_Add(new Cmd_Item_Str("\"<command>\"", "command about which need to obtain information"));
            cmd->Item_Add(new Cmd_Item_Word("verbose", "show all arguments information"));
            Cmd_Add(cmd);
        }
        {
            // help "*" verbose
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_help_command_all_verbose);
            cmd->Text_Set("help \"*\" verbose");
            cmd->Help_Set("show all commands with arguments information");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Word("help", "show all commands with arguments information"));
            cmd->Item_Add(new Cmd_Item_Str("\"*\"", "all commands"));
            cmd->Item_Add(new Cmd_Item_Word("verbose", "show all arguments information"));
            Cmd_Add(cmd);
        }

        {
            // test set loopback [raw,e1,net,local,remote]
            vector<string> words;
            words.push_back("raw");
            words.push_back("e1");
            words.push_back("net");
            words.push_back("local");
            words.push_back("remote");
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_test_set_loopback);
            cmd->Text_Set("set loopback [raw,e1,net,local,remote]");
            cmd->Help_Set("test: set loopback [raw,e1,net,local,remote]");
            cmd->Is_Global_Set(false);
            cmd->Level_Set("test terminal");
            cmd->Item_Add(new Cmd_Item_Word("set", "test: set"));
            cmd->Item_Add(new Cmd_Item_Word("loopback", "test: set loopback"));
            cmd->Item_Add(new Cmd_Item_Word_List("raw e1 net local remote", "test: set loopback [raw,e1,net,local,remote]", words));
            Cmd_Add(cmd);
        }
        {
            // test set loopback disable
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_test_set_loopback_disable);
            cmd->Text_Set("set loopback disable");
            cmd->Help_Set("test: set loopback disable");
            cmd->Is_Global_Set(false);
            cmd->Level_Set("test terminal");
            cmd->Item_Add(new Cmd_Item_Word("set", "test: set"));
            cmd->Item_Add(new Cmd_Item_Word("loopback", "test: set loopback"));
            cmd->Item_Add(new Cmd_Item_Word("disable", "test: set loopback disable"));
            Cmd_Add(cmd);
        }
        {
            // test terminal
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_test_terminal);
            cmd->Text_Set("test terminal");
            cmd->Help_Set("switch to level: test terminal");
            cmd->Is_Global_Set(false);
            cmd->Level_Set("");
            cmd->Item_Add(new Cmd_Item_Word("test", "switch to level: test terminal"));
            cmd->Item_Add(new Cmd_Item_Word("terminal", "switch to level: test terminal"));
            Cmd_Add(cmd);
        }
        {
            // test set range
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_test_set_range);
            cmd->Text_Set("set range <1..4095>");
            cmd->Help_Set("test: set range");
            cmd->Is_Global_Set(false);
            cmd->Level_Set("test terminal");
            cmd->Item_Add(new Cmd_Item_Word("set", "test: set"));
            cmd->Item_Add(new Cmd_Item_Word("range", "test: set range"));
            cmd->Item_Add(new Cmd_Item_Int_Range(1, 4095, "<1..4095>", "test: set range <1..4095>"));
            Cmd_Add(cmd);
        }
        {
            // test set list
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_test_set_list);
            cmd->Text_Set("set list <1-4095>");
            cmd->Help_Set("test: set list");
            cmd->Is_Global_Set(false);
            cmd->Level_Set("test terminal");
            cmd->Item_Add(new Cmd_Item_Word("set", "test: set"));
            cmd->Item_Add(new Cmd_Item_Word("list", "test: set list"));
            cmd->Item_Add(new Cmd_Item_Int_List(1, 4095, "<1-4095>", "test: set list <1-4095>"));
            Cmd_Add(cmd);
        }
        {
            // test set str
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_test_set_str);
            cmd->Text_Set("set str <str>");
            cmd->Help_Set("test: set str");
            cmd->Is_Global_Set(false);
            cmd->Level_Set("test terminal");
            cmd->Item_Add(new Cmd_Item_Word("set", "test: set"));
            cmd->Item_Add(new Cmd_Item_Word("str", "test: set str"));
            cmd->Item_Add(new Cmd_Item_Str("<str>", "test: set str <str>"));
            Cmd_Add(cmd);
        }
        {
            // project close <project_name>
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_project_close_project_name);
            cmd->Text_Set("project close <project_name>");
            cmd->Help_Set("test: project close <project_name>");
            cmd->Is_Global_Set(true);
            cmd->Level_Set("");
            cmd->Item_Add(new Cmd_Item_Word("project", "test: project"));
            cmd->Item_Add(new Cmd_Item_Word("close", "test: project close"));
            //cmd->Item_Add(new Cmd_Item_Str("<project_name>", "test: project close <project_name>"));
            cmd->Item_Add(new Cmd_Item_Str("<project_name>", "test: project close <project_name>"));
            Cmd_Add(cmd);
        }
        {
            // object close <object_name>
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_object_close_object_name);
            cmd->Text_Set("object close <object_name>");
            cmd->Help_Set("test: object close <object_name>");
            cmd->Is_Global_Set(true);
            cmd->Level_Set("");
            cmd->Item_Add(new Cmd_Item_Word("object", "test: object"));
            cmd->Item_Add(new Cmd_Item_Word("close", "test: object close"));
            cmd->Item_Add(new Cmd_Item_Str("<object_name>", "test: object close <object_name>"));
            Cmd_Add(cmd);
        }
        {
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_projects);
            cmd->Text_Set("projects");
            cmd->Help_Set("project list show (all)");
            cmd->Is_Global_Set(true);
            cmd->Level_Set("");
            cmd->Item_Add(new Cmd_Item_Word("projects", "project list show (all)"));
            Cmd_Add(cmd); //Cmd_Add(cmd);
        }
        {
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_projects_save);
            cmd->Text_Set("projects save");
            cmd->Help_Set("projects save (all)");
            cmd->Is_Global_Set(true);
            cmd->Level_Set("");
            cmd->Item_Add(new Cmd_Item_Word("projects", "projects"));
            cmd->Item_Add(new Cmd_Item_Word("save", "projects save (all)"));
            Cmd_Add(cmd); //Cmd_Add(cmd);
        }
        {
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_project_save);
            cmd->Text_Set("project save (current project)");
            cmd->Help_Set("project save (current project)");
            cmd->Is_Global_Set(true);
            cmd->Level_Set("");
            cmd->Item_Add(new Cmd_Item_Word("project", "project"));
            cmd->Item_Add(new Cmd_Item_Word("save", "project save (current project)"));
            Cmd_Add(cmd); //Cmd_Add(cmd);
        }

        {
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_set_date);
            cmd->Text_Set("set date \"<date>\"");
            cmd->Help_Set("set date \"<date>\"");
            cmd->Is_Global_Set(false);
            cmd->Level_Set("test terminal");
            cmd->Item_Add(new Cmd_Item_Word("set", "set"));
            cmd->Item_Add(new Cmd_Item_Word("date", "set date"));
            cmd->Item_Add(new Cmd_Item_Date("\"<date>\"", "set date \"<date>\""));
            Cmd_Add(cmd); //Cmd_Add(cmd);
        }
        {
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_set_datetime);
            cmd->Text_Set("set datetime \"<date: YY-MM-DD> <time: hh-mm-ss>\"");
            cmd->Help_Set("set datetime \"<date: YY-MM-DD> <time: hh-mm-ss>\"");
            cmd->Is_Global_Set(false);
            cmd->Level_Set("test terminal");
            cmd->Item_Add(new Cmd_Item_Word("set", "set"));
            cmd->Item_Add(new Cmd_Item_Word("datetime", "set datetime"));
            cmd->Item_Add(new Cmd_Item_Date("\"<date: YY-MM-DD> <time: hh-mm-ss>\"", "set datetime \"<date: YY-MM-DD> <time: hh-mm-ss>\""));
            Cmd_Add(cmd); //Cmd_Add(cmd);
        }

        {
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_set_sys);
            cmd->Text_Set("set sys \"<sysdate>\"");
            cmd->Help_Set("set sys \"<sysdate>\"");
            cmd->Is_Global_Set(false);
            cmd->Level_Set("test terminal");
            cmd->Item_Add(new Cmd_Item_Word("set", "set"));
            cmd->Item_Add(new Cmd_Item_Word("sys", "set sys"));
            cmd->Item_Add(new Cmd_Item_Date("\"<sysdate>\"", "set sys \"<sysdate>\""));
            Cmd_Add(cmd); //Cmd_Add(cmd);
        }
        {
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_set_sysdate);
            cmd->Text_Set("set sysdate \"<sysdate>\"");
            cmd->Help_Set("set sysdate \"<sysdate>\"");
            cmd->Is_Global_Set(false);
            cmd->Level_Set("test terminal");
            cmd->Item_Add(new Cmd_Item_Word("set", "set"));
            cmd->Item_Add(new Cmd_Item_Word("sysdate", "set sysdate"));
            cmd->Item_Add(new Cmd_Item_Date("\"<sysdate>\"", "set sysdate \"<sysdate>\""));
            Cmd_Add(cmd); //Cmd_Add(cmd);
        }
        {
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_set_sysdatetime);
            cmd->Text_Set("set sysdatetime \"<sysdate: YY-MM-DD> <systime: hh-mm-ss>\"");
            cmd->Help_Set("set sysdatetime \"<sysdate: YY-MM-DD> <systime: hh-mm-ss>\"");
            cmd->Is_Global_Set(false);
            cmd->Level_Set("test terminal");
            cmd->Item_Add(new Cmd_Item_Word("set", "set"));
            cmd->Item_Add(new Cmd_Item_Word("sysdatetime", "set sysdatetime"));
            cmd->Item_Add(new Cmd_Item_Date("\"<sysdate: YY-MM-DD> <systime: hh-mm-ss>\"", "set sysdatetime \"<sysdate: YY-MM-DD> <systime: hh-mm-ss>\""));
            Cmd_Add(cmd); //Cmd_Add(cmd);
        }
        {
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_set_systime);
            cmd->Text_Set("set systime \"<systime: hh-mm-ss>\"");
            cmd->Help_Set("set systime \"<systime: hh-mm-ss>\"");
            cmd->Is_Global_Set(false);
            cmd->Level_Set("test terminal");
            cmd->Item_Add(new Cmd_Item_Word("set", "set"));
            cmd->Item_Add(new Cmd_Item_Word("systime", "set systime"));
            cmd->Item_Add(new Cmd_Item_Time("\"<systime: hh-mm-ss>\"", "set systime \"<systime: hh-mm-ss>\""));
            Cmd_Add(cmd); //Cmd_Add(cmd);
        }
        {
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_set_sysmtime);
            cmd->Text_Set("set sysmtime \"<sysmtime: hh-mm-ss>\"");
            cmd->Help_Set("set sysmtime \"<sysmtime: hh-mm-ss>\"");
            cmd->Is_Global_Set(false);
            cmd->Level_Set("test terminal");
            cmd->Item_Add(new Cmd_Item_Word("set", "set"));
            cmd->Item_Add(new Cmd_Item_Word("sysmtime", "set sysmtime"));
            cmd->Item_Add(new Cmd_Item_Time("\"<sysmtime: hh-mm-ss>\"", "set sysmtime \"<sysmtime: hh-mm-ss>\""));
            Cmd_Add(cmd); //Cmd_Add(cmd);
        }

        {
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_set_zsys);
            cmd->Text_Set("set zsys \"<zsysdate>\"");
            cmd->Help_Set("set zsys \"<zsysdate>\"");
            cmd->Is_Global_Set(false);
            cmd->Level_Set("test terminal");
            cmd->Item_Add(new Cmd_Item_Word("set", "set"));
            cmd->Item_Add(new Cmd_Item_Word("zsys", "set zsys"));
            cmd->Item_Add(new Cmd_Item_Date("\"<zsysdate>\"", "set zsys \"<zsysdate>\""));
            Cmd_Add(cmd); //Cmd_Add(cmd);
        }
        {
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_set_zsys2);
            cmd->Text_Set("set zsys \"<zsysdate2>\"");
            cmd->Help_Set("set zsys \"<zsysdate2>\"");
            cmd->Is_Global_Set(false);
            cmd->Level_Set("test terminal");
            cmd->Item_Add(new Cmd_Item_Word("set", "set"));
            cmd->Item_Add(new Cmd_Item_Word("zsys", "set zsys"));
            cmd->Item_Add(new Cmd_Item_Date("\"<zsysdate2>\"", "set zsys \"<zsysdate2>\""));
            Cmd_Add(cmd); //Cmd_Add(cmd);
        }
        {
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_set_zsysdate);
            cmd->Text_Set("set zsysdate \"<zsysdate>\"");
            cmd->Help_Set("set zsysdate \"<zsysdate>\"");
            cmd->Is_Global_Set(false);
            cmd->Level_Set("test terminal");
            cmd->Item_Add(new Cmd_Item_Word("set", "set"));
            cmd->Item_Add(new Cmd_Item_Word("zsysdate", "set zsysdate"));
            cmd->Item_Add(new Cmd_Item_Date("\"<zsysdate>\"", "set zsysdate \"<zsysdate>\""));
            Cmd_Add(cmd); //Cmd_Add(cmd);
        }
        {
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_set_zsysdatetime);
            cmd->Text_Set("set zsysdatetime \"<zsysdate: YY-MM-DD> <zsystime: hh-mm-ss>\"");
            cmd->Help_Set("set zsysdatetime \"<zsysdate: YY-MM-DD> <zsystime: hh-mm-ss>\"");
            cmd->Is_Global_Set(false);
            cmd->Level_Set("test terminal");
            cmd->Item_Add(new Cmd_Item_Word("set", "set"));
            cmd->Item_Add(new Cmd_Item_Word("zsysdatetime", "set zsysdatetime"));
            cmd->Item_Add(new Cmd_Item_Date("\"<zsysdate: YY-MM-DD> <zsystime: hh-mm-ss>\"", "set zsysdatetime \"<zsysdate: YY-MM-DD> <zsystime: hh-mm-ss>\""));
            Cmd_Add(cmd); //Cmd_Add(cmd);
        }
        {
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_set_zsystime);
            cmd->Text_Set("set zsystime \"<zsystime: hh-mm-ss>\"");
            cmd->Help_Set("set zsystime \"<zsystime: hh-mm-ss>\"");
            cmd->Is_Global_Set(false);
            cmd->Level_Set("test terminal");
            cmd->Item_Add(new Cmd_Item_Word("set", "set"));
            cmd->Item_Add(new Cmd_Item_Word("zsystime", "set zsystime"));
            cmd->Item_Add(new Cmd_Item_Time("\"<zsystime: hh-mm-ss>\"", "set zsystime \"<zsystime: hh-mm-ss>\""));
            Cmd_Add(cmd); //Cmd_Add(cmd);
        }
        {
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_set_zsysmtime);
            cmd->Text_Set("set zsysmtime \"<zsystime: hh-mm-ss>\"");
            cmd->Help_Set("set zsysmtime \"<zsystime: hh-mm-ss>\"");
            cmd->Is_Global_Set(false);
            cmd->Level_Set("test terminal");
            cmd->Item_Add(new Cmd_Item_Word("set", "set"));
            cmd->Item_Add(new Cmd_Item_Word("zsysmtime", "set zsysmtime"));
            cmd->Item_Add(new Cmd_Item_Time("\"<zsystime: hh-mm-ss>\"", "set zsysmtime \"<zsystime: hh-mm-ss>\""));
            Cmd_Add(cmd); //Cmd_Add(cmd);
        }
        {
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_set_zsysntime);
            cmd->Text_Set("set zsysntime \"<zsystime: hh-mm-ss>\"");
            cmd->Help_Set("set zsysntime \"<zsystime: hh-mm-ss>\"");
            cmd->Is_Global_Set(false);
            cmd->Level_Set("test terminal");
            cmd->Item_Add(new Cmd_Item_Word("set", "set"));
            cmd->Item_Add(new Cmd_Item_Word("zsysntime", "set zsysntime"));
            cmd->Item_Add(new Cmd_Item_Time("\"<zsystime: hh-mm-ss>\"", "set zsysntime \"<zsystime: hh-mm-ss>\""));
            Cmd_Add(cmd); //Cmd_Add(cmd);
        }

        {
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_set_xsys);
            cmd->Text_Set("set xsys \"<xsysdate>\"");
            cmd->Help_Set("set xsys \"<xsysdate>\"");
            cmd->Is_Global_Set(false);
            cmd->Level_Set("test terminal");
            cmd->Item_Add(new Cmd_Item_Word("set", "set"));
            cmd->Item_Add(new Cmd_Item_Word("xsys", "set xsys"));
            cmd->Item_Add(new Cmd_Item_Date("\"<xsysdate>\"", "set xsys \"<xsysdate>\""));
            Cmd_Add(cmd); //Cmd_Add(cmd);
        }
        {
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_set_xsys2);
            cmd->Text_Set("set xsys \"<xsysdate2>\"");
            cmd->Help_Set("set xsys \"<xsysdate2>\"");
            cmd->Is_Global_Set(false);
            cmd->Level_Set("test terminal");
            cmd->Item_Add(new Cmd_Item_Word("set", "set"));
            cmd->Item_Add(new Cmd_Item_Word("xsys", "set xsys"));
            cmd->Item_Add(new Cmd_Item_Date("\"<xsysdate2>\"", "set xsys \"<xsysdate2>\""));
            Cmd_Add(cmd); //Cmd_Add(cmd);
        }
        {
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_set_xsysdate);
            cmd->Text_Set("set xsysdate \"<xsysdate>\"");
            cmd->Help_Set("set xsysdate \"<xsysdate>\"");
            cmd->Is_Global_Set(false);
            cmd->Level_Set("test terminal");
            cmd->Item_Add(new Cmd_Item_Word("set", "set"));
            cmd->Item_Add(new Cmd_Item_Word("xsysdate", "set xsysdate"));
            cmd->Item_Add(new Cmd_Item_Date("\"<xsysdate>\"", "set xsysdate \"<xsysdate>\""));
            Cmd_Add(cmd); //Cmd_Add(cmd);
        }

        {
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_set_ysys);
            cmd->Text_Set("set ysys");
            cmd->Help_Set("set ysys");
            cmd->Is_Global_Set(false);
            cmd->Level_Set("test terminal");
            cmd->Item_Add(new Cmd_Item_Word("set", "set"));
            cmd->Item_Add(new Cmd_Item_Word("ysys", "set ysys"));
            Cmd_Add(cmd); //Cmd_Add(cmd);
        }
        {
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_set_ysys1);
            cmd->Text_Set("set ysys \"<ysysdate1>\"");
            cmd->Help_Set("set ysys \"<ysysdate1>\"");
            cmd->Is_Global_Set(false);
            cmd->Level_Set("test terminal");
            cmd->Item_Add(new Cmd_Item_Word("set", "set"));
            cmd->Item_Add(new Cmd_Item_Word("ysys", "set ysys"));
            cmd->Item_Add(new Cmd_Item_Date("\"<ysysdate1>\"", "set ysys \"<ysysdate1>\""));
            Cmd_Add(cmd); //Cmd_Add(cmd);
        }
        {
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_set_ysys2);
            cmd->Text_Set("set ysys \"<ysysdate2>\"");
            cmd->Help_Set("set ysys \"<ysysdate2>\"");
            cmd->Is_Global_Set(false);
            cmd->Level_Set("test terminal");
            cmd->Item_Add(new Cmd_Item_Word("set", "set"));
            cmd->Item_Add(new Cmd_Item_Word("ysys", "set ysys"));
            cmd->Item_Add(new Cmd_Item_Date("\"<ysysdate2>\"", "set ysys \"<ysysdate2>\""));
            Cmd_Add(cmd); //Cmd_Add(cmd);
        }
        {
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_set_ysysdate);
            cmd->Text_Set("set ysysdate \"<ysysdate>\"");
            cmd->Help_Set("set ysysdate \"<ysysdate>\"");
            cmd->Is_Global_Set(false);
            cmd->Level_Set("test terminal");
            cmd->Item_Add(new Cmd_Item_Word("set", "set"));
            cmd->Item_Add(new Cmd_Item_Word("ysysdate", "set ysysdate"));
            cmd->Item_Add(new Cmd_Item_Date("\"<ysysdate>\"", "set ysysdate \"<ysysdate>\""));
            Cmd_Add(cmd); //Cmd_Add(cmd);
        }
        {
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_set_ysystime);
            cmd->Text_Set("set ysystime \"<ysystime: hh-mm-ss>\"");
            cmd->Help_Set("set ysystime \"<ysystime: hh-mm-ss>\"");
            cmd->Is_Global_Set(false);
            cmd->Level_Set("test terminal");
            cmd->Item_Add(new Cmd_Item_Word("set", "set"));
            cmd->Item_Add(new Cmd_Item_Word("ysystime", "set ysystime"));
            cmd->Item_Add(new Cmd_Item_Time("\"<ysystime: hh-mm-ss>\"", "set ysystime \"<ysystime: hh-mm-ss>\""));
            Cmd_Add(cmd); //Cmd_Add(cmd);
        }

        {
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_set_wsys);
            cmd->Text_Set("set wsys");
            cmd->Help_Set("set wsys");
            cmd->Is_Global_Set(false);
            cmd->Level_Set("test terminal");
            cmd->Item_Add(new Cmd_Item_Word("set", "set"));
            cmd->Item_Add(new Cmd_Item_Word("wsys", "set wsys"));
            Cmd_Add(cmd); //Cmd_Add(cmd);
        }
        {
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_set_wsys1);
            cmd->Text_Set("set wsys \"<wsysdate1>\"");
            cmd->Help_Set("set wsys \"<wsysdate1>\"");
            cmd->Is_Global_Set(false);
            cmd->Level_Set("test terminal");
            cmd->Item_Add(new Cmd_Item_Word("set", "set"));
            cmd->Item_Add(new Cmd_Item_Word("wsys", "set wsys"));
            cmd->Item_Add(new Cmd_Item_Date("\"<wsysdate1>\"", "set wsys \"<wsysdate1>\""));
            Cmd_Add(cmd); //Cmd_Add(cmd);
        }
        {
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_set_wsysdate);
            cmd->Text_Set("set wsysdate \"<wsysdate>\"");
            cmd->Help_Set("set wsysdate \"<wsysdate>\"");
            cmd->Is_Global_Set(false);
            cmd->Level_Set("test terminal");
            cmd->Item_Add(new Cmd_Item_Word("set", "set"));
            cmd->Item_Add(new Cmd_Item_Word("wsysdate", "set wsysdate"));
            cmd->Item_Add(new Cmd_Item_Date("\"<wsysdate>\"", "set wsysdate \"<wsysdate>\""));
            Cmd_Add(cmd); //Cmd_Add(cmd);
        }
        {
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_set_wsystime);
            cmd->Text_Set("set wsystime \"<wsystime: hh-mm-ss>\"");
            cmd->Help_Set("set wsystime \"<wsystime: hh-mm-ss>\"");
            cmd->Is_Global_Set(false);
            cmd->Level_Set("test terminal");
            cmd->Item_Add(new Cmd_Item_Word("set", "set"));
            cmd->Item_Add(new Cmd_Item_Word("wsystime", "set wsystime"));
            cmd->Item_Add(new Cmd_Item_Time("\"<wsystime: hh-mm-ss>\"", "set wsystime \"<wsystime: hh-mm-ss>\""));
            Cmd_Add(cmd); //Cmd_Add(cmd);
        }
        
        {
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_set_asys);
            cmd->Text_Set("set asys");
            cmd->Help_Set("set asys");
            cmd->Is_Global_Set(false);
            cmd->Level_Set("test terminal");
            cmd->Item_Add(new Cmd_Item_Word("set", "set"));
            cmd->Item_Add(new Cmd_Item_Word("asys", "set asys"));
            Cmd_Add(cmd); //Cmd_Add(cmd);
        }
        {
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_set_asys_A);
            cmd->Text_Set("set asys A");
            cmd->Help_Set("set asys A");
            cmd->Is_Global_Set(false);
            cmd->Level_Set("test terminal");
            cmd->Item_Add(new Cmd_Item_Word("set", "set"));
            cmd->Item_Add(new Cmd_Item_Word("asys", "set asys"));
            cmd->Item_Add(new Cmd_Item_Word("A", "set asys A"));
            Cmd_Add(cmd); //Cmd_Add(cmd);
        }
        {
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_set_asys_B);
            cmd->Text_Set("set asys B");
            cmd->Help_Set("set asys B");
            cmd->Is_Global_Set(false);
            cmd->Level_Set("test terminal");
            cmd->Item_Add(new Cmd_Item_Word("set", "set"));
            cmd->Item_Add(new Cmd_Item_Word("asys", "set asys"));
            cmd->Item_Add(new Cmd_Item_Word("B", "set asys B"));
            Cmd_Add(cmd); //Cmd_Add(cmd);
        }

    }

    ~Cli_Module_Test_Tab() {
    }

    virtual bool Execute(Cli_Cmd_ID cmd_id, Cli_Cmd *cmd, vector<Level_Description> &Levels, bool is_debug) {
        return false; // Not Implemented
    }

    virtual void To_Map(map<string, string> &values_map) {
    }

};

#endif /* CLI_MODULE_TEST_TAB_H */
