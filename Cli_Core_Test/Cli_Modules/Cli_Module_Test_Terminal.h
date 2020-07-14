/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_Module_Test_Terminal.h
 * Author: mike
 *
 * Created on July 2, 2020, 9:52 AM
 */

#ifndef CLI_MODULE_TEST_TERMINAL_H
#define CLI_MODULE_TEST_TERMINAL_H

#include "Cli_Module.h"

#include "Cmd_Item_Word.h"
#include "Cmd_Item_Word_Range.h"
#include "Cmd_Item_Word_List.h"
#include "Cmd_Item_Str.h"
#include "Cmd_Item_Date.h"
#include "Cmd_Item_Time.h"
#include "Cmd_Item_DateTime.h"
#include "Cmd_Item_IP4.h"
#include "Cmd_Item_IP6.h"
#include "Cmd_Item_MAC.h"

class Cli_Module_Test_Terminal : public Cli_Module {
protected:

    Cli_Input_Abstract &Cli_Input;
    Cli_Output_Abstract &Cli_Output;

    string Parent_Level;
    string New_Level;

    string Value_Str;
    string Value_Date;
    string Value_Time;
    string Value_DateTime;
    string Value_IP4;
    string Value_Mask;
    string Value_IP6;
    string Value_MAC;
    string Value_Enable;
    string Value_Loopback;
    string Value_Loopback_Repeating;

public:

    enum Local_CmdID {
        CMD_ID_NO,
        CMD_ID_test_terminal,
        CMD_ID_end,
        CMD_ID_test,
        CMD_ID_test_get,
        CMD_ID_test_get_all,
        CMD_ID_test_set_range,
        CMD_ID_test_set_list,
        CMD_ID_test_set_ip4,
        CMD_ID_test_set_mask,
        CMD_ID_test_set_ip6,
        CMD_ID_test_set_mac,
        CMD_ID_test_set_str,
        CMD_ID_test_set_date,
        CMD_ID_test_set_time,
        CMD_ID_test_set_datetime,
        CMD_ID_test_set_enable,
        CMD_ID_test_set_loopback,
        CMD_ID_test_set_loopback_repeating,
        CMD_ID_test_set_loopback_disable,
        CMD_ID_LAST
    };

    virtual int Cmd_ID_Count_Get() {
        return CMD_ID_LAST - CMD_ID_NO - 1;
    }

    bool test_terminal(vector<Level_Description> &Levels) {
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

    Cli_Module_Test_Terminal(Cli_Input_Abstract &cli_input, Cli_Output_Abstract &cli_output)
    : Cli_Module("Test Terminal"), Cli_Input(cli_input), Cli_Output(cli_output), New_Level("test terminal") {
        {
            // test terminal
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_test_terminal);
            cmd->Text_Set(New_Level);
            cmd->Help_Set("switch to level: " + New_Level);
            cmd->Is_Global_Set(false);
            cmd->Level_Set("");
            cmd->Item_Add(new Cmd_Item_Word("test", "switch to level: " + New_Level));
            cmd->Item_Add(new Cmd_Item_Word("terminal", "switch to level: " + New_Level));
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
            // test get
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_test_get);
            cmd->Text_Set("get");
            cmd->Help_Set("test: get all");
            cmd->Is_Global_Set(false);
            cmd->Level_Set(New_Level);
            cmd->Item_Add(new Cmd_Item_Word("get", "test: get all"));
            Cmd_Add(cmd);
        }
        {
            // test get all
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_test_get_all);
            cmd->Text_Set("get all");
            cmd->Help_Set("test: get all");
            cmd->Is_Global_Set(false);
            cmd->Level_Set(New_Level);
            cmd->Item_Add(new Cmd_Item_Word("get", "test: get"));
            cmd->Item_Add(new Cmd_Item_Word("all", "test: get all"));
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
            // test set date
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_test_set_date);
            cmd->Text_Set("set date \"yyyy-mm-dd\"");
            cmd->Help_Set("test: set date");
            cmd->Is_Global_Set(false);
            cmd->Level_Set("test terminal");
            cmd->Item_Add(new Cmd_Item_Word("set", "test: set"));
            cmd->Item_Add(new Cmd_Item_Word("date", "test: set date"));
            cmd->Item_Add(new Cmd_Item_Date("\"yyyy-mm-dd\"", "test: set date \"yyyy-mm-dd\""));
            Cmd_Add(cmd);
        }
        {
            // test set time
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_test_set_time);
            cmd->Text_Set("set time \"HH-MM-SS\"");
            cmd->Help_Set("test: set time");
            cmd->Is_Global_Set(false);
            cmd->Level_Set("test terminal");
            cmd->Item_Add(new Cmd_Item_Word("set", "test: set"));
            cmd->Item_Add(new Cmd_Item_Word("time", "test: time"));
            cmd->Item_Add(new Cmd_Item_Time("\"HH-MM-SS\"", "test: set date \"HH-MM-SS\""));
            Cmd_Add(cmd);
        }
        {
            // test set datetime
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_test_set_datetime);
            cmd->Text_Set("set datetime \"yyyy-mm-dd HH-MM-SS\"");
            cmd->Help_Set("test: set datetime");
            cmd->Is_Global_Set(false);
            cmd->Level_Set("test terminal");
            cmd->Item_Add(new Cmd_Item_Word("set", "test: set"));
            cmd->Item_Add(new Cmd_Item_Word("datetime", "test: set datetime"));
            cmd->Item_Add(new Cmd_Item_DateTime("\"yyyy-mm-dd HH-MM-SS\"", "test: set datetime \"yyyy-mm-dd HH-MM-SS\""));
            Cmd_Add(cmd);
        }

        {
            // test set ip4
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_test_set_ip4);
            cmd->Text_Set("set ip4 <ip4-address>");
            cmd->Help_Set("test: set ip4");
            cmd->Is_Global_Set(false);
            cmd->Level_Set("test terminal");
            cmd->Item_Add(new Cmd_Item_Word("set", "test: set"));
            cmd->Item_Add(new Cmd_Item_Word("ip4", "test: set ip4"));
            cmd->Item_Add(new Cmd_Item_IP4("<ip4-address>", "test: set ip4 <ip4-address>"));
            Cmd_Add(cmd);
        }

        {
            // test set mask
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_test_set_mask);
            cmd->Text_Set("set mask <mask>");
            cmd->Help_Set("test: set mask");
            cmd->Is_Global_Set(false);
            cmd->Level_Set("test terminal");
            cmd->Item_Add(new Cmd_Item_Word("set", "test: set"));
            cmd->Item_Add(new Cmd_Item_Word("mask", "test: set mask"));
            cmd->Item_Add(new Cmd_Item_IP4("<mask>", "test: set mask <mask>"));
            Cmd_Add(cmd);
        }

        {
            // test set ip6
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_test_set_ip6);
            cmd->Text_Set("set ip6 <ip6-address>");
            cmd->Help_Set("test: set ip6");
            cmd->Is_Global_Set(false);
            cmd->Level_Set("test terminal");
            cmd->Item_Add(new Cmd_Item_Word("set", "test: set"));
            cmd->Item_Add(new Cmd_Item_Word("ip6", "test: set ip6"));
            cmd->Item_Add(new Cmd_Item_IP6("<ip6-address>", "test: set ip6 <ip6-address>"));
            Cmd_Add(cmd);
        }

        {
            // test set mac
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_test_set_mac);
            cmd->Text_Set("set mac <mac-address>");
            cmd->Help_Set("test: set mac");
            cmd->Is_Global_Set(false);
            cmd->Level_Set("test terminal");
            cmd->Item_Add(new Cmd_Item_Word("set", "test: set"));
            cmd->Item_Add(new Cmd_Item_Word("mac", "test: set mac"));
            cmd->Item_Add(new Cmd_Item_MAC("<mac-address>", "test: set mac <mac-address>"));
            Cmd_Add(cmd);
        }

        {
            // test set enable
            vector<string> words;
            words.push_back("enable");
            words.push_back("disable");
            words.push_back("else");
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_test_set_enable);
            cmd->Text_Set("set <enable|disable|else>");
            cmd->Help_Set("test: set <enable|disable|else>");
            cmd->Is_Global_Set(false);
            cmd->Level_Set("test terminal");
            cmd->Item_Add(new Cmd_Item_Word("set", "test: set"));
            cmd->Item_Add(new Cmd_Item_Word_Range("<enable|disable|else>", "test: set <enable|disable|else>", words));
            Cmd_Add(cmd);
        }

        {
            // test set loopback [raw,net,local,remote]
            vector<string> words;
            words.push_back("raw");
            words.push_back("net");
            words.push_back("local");
            words.push_back("remote");
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_test_set_loopback);
            cmd->Text_Set("set loopback [raw,net,local,remote]");
            cmd->Help_Set("test: set loopback [raw,net,local,remote]");
            cmd->Is_Global_Set(false);
            cmd->Level_Set("test terminal");
            cmd->Item_Add(new Cmd_Item_Word("set", "test: set"));
            cmd->Item_Add(new Cmd_Item_Word("loopback", "test: set loopback"));
            cmd->Item_Add(new Cmd_Item_Word_List("[raw,net,local,remote]", "test: set loopback [raw,net,local,remote]", words));
            Cmd_Add(cmd);
        }
        {
            // test set loopback repeating [raw,net,local,remote]
            vector<string> words;
            words.push_back("raw");
            words.push_back("net");
            words.push_back("local");
            words.push_back("remote");
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_test_set_loopback_repeating);
            cmd->Text_Set("set loopback repeating [raw,net,local,remote]");
            cmd->Help_Set("test: set loopback repeating [raw,net,local,remote]");
            cmd->Is_Global_Set(false);
            cmd->Level_Set("test terminal");
            cmd->Item_Add(new Cmd_Item_Word("set", "test: set"));
            cmd->Item_Add(new Cmd_Item_Word("loopback", "test: set loopback"));
            cmd->Item_Add(new Cmd_Item_Word("repeating", "test: set loopback repeating"));

            bool is_repeating = true;
            cmd->Item_Add(new Cmd_Item_Word_List("[raw,net,local,remote]", "test: set loopback repeating [raw,net,local,remote]", words,
                    is_repeating));

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

    }

    ~Cli_Module_Test_Terminal() {
    }

    bool test_get_all() {
        stringstream s_str;
        int w = 20;

        s_str << setw(w) << "Str: " << setw(0) << Value_Str << endl;
        s_str << setw(w) << "Date: " << setw(0) << Value_Date << endl;
        s_str << setw(w) << "Time: " << setw(0) << Value_Time << endl;
        s_str << setw(w) << "DateTime: " << setw(0) << Value_DateTime << endl;
        s_str << setw(w) << "IP4: " << setw(0) << Value_IP4 << endl;
        s_str << setw(w) << "Mask: " << setw(0) << Value_Mask << endl;
        s_str << setw(w) << "IP6: " << setw(0) << Value_IP6 << endl;
        s_str << setw(w) << "MAC: " << setw(0) << Value_MAC << endl;
        s_str << setw(w) << "Enable: " << setw(0) << Value_Enable << endl;
        s_str << setw(w) << "Loopback: " << setw(0) << Value_Loopback << endl;
        s_str << setw(w) << "Loopback Repeating: " << setw(0) << Value_Loopback_Repeating << endl;

        Cli_Output.Output_NewLine();
        Cli_Output.Output_Str(s_str.str());

        return true;
    }

    bool test_set_str(string value) {
        Value_Str = value;
        Cli_Output.Output_NewLine();
        Cli_Output.Output_Str("Str=\"" + Value_Str + "\"");
        Cli_Output.Output_NewLine();
        return true;
    }

    bool test_set_date(string value) {
        Value_Date = value;
        Cli_Output.Output_NewLine();
        Cli_Output.Output_Str("Str=" + Value_Date);
        Cli_Output.Output_NewLine();
        return true;
    }

    bool test_set_time(string value) {
        Value_Time = value;
        Cli_Output.Output_NewLine();
        Cli_Output.Output_Str("Str" + Value_Time);
        Cli_Output.Output_NewLine();
        return true;
    }

    bool test_set_datetime(string value) {
        Value_DateTime = value;
        Cli_Output.Output_NewLine();
        Cli_Output.Output_Str("Str" + Value_DateTime);
        Cli_Output.Output_NewLine();
        return true;
    }

    bool test_set_ip4(string value) {
        Value_IP4 = value;
        Cli_Output.Output_NewLine();
        Cli_Output.Output_Str("IP4=" + Value_IP4);
        Cli_Output.Output_NewLine();
        return true;
    }

    bool test_set_mask(string value) {
        Value_Mask = value;
        Cli_Output.Output_NewLine();
        Cli_Output.Output_Str("Mask=" + Value_Mask);
        Cli_Output.Output_NewLine();
        return true;
    }

    bool test_set_ip6(string value) {
        Value_IP6 = value;
        Cli_Output.Output_NewLine();
        Cli_Output.Output_Str("IP6=" + Value_IP6);
        Cli_Output.Output_NewLine();
        return true;
    }

    bool test_set_mac(string value) {
        Value_MAC = value;
        Cli_Output.Output_NewLine();
        Cli_Output.Output_Str("MAC=" + Value_MAC);
        Cli_Output.Output_NewLine();
        return true;
    }

    bool test_set_enable(string value) {
        Value_Enable = value;
        Cli_Output.Output_NewLine();
        Cli_Output.Output_Str("Enable=" + Value_Enable);
        Cli_Output.Output_NewLine();
        return true;
    }

    bool test_set_loopback(Cli_Cmd *cmd) {

        Cmd_Item_Word_List *word_list = (Cmd_Item_Word_List *) cmd->Items[2];
        Value_Loopback = "";
        for (int i = 0; i < word_list->Values_Str.size(); i++) {
            if (i == 0)
                Value_Loopback += word_list->Values_Str[i];
            else
                Value_Loopback += " " + word_list->Values_Str[i];
        }

        Cli_Output.Output_NewLine();
        Cli_Output.Output_Str("Loopback=" + Value_Loopback);
        Cli_Output.Output_NewLine();

        return true;
    }

    bool test_set_loopback_repeating(Cli_Cmd *cmd) {

        Cmd_Item_Word_List *word_list = (Cmd_Item_Word_List *) cmd->Items[3];
        Value_Loopback_Repeating = "";
        for (int i = 0; i < word_list->Values_Str.size(); i++) {
            if (i == 0)
                Value_Loopback_Repeating += word_list->Values_Str[i];
            else
                Value_Loopback_Repeating += " " + word_list->Values_Str[i];
        }

        Cli_Output.Output_NewLine();
        Cli_Output.Output_Str("Loopback Repeating=" + Value_Loopback_Repeating);
        Cli_Output.Output_NewLine();

        return true;
    }
    
    bool test_set_loopback_disable() {
        Value_Loopback = "disable";
        Cli_Output.Output_NewLine();
        Cli_Output.Output_Str("Value_Loopback=" + Value_Loopback);
        Cli_Output.Output_NewLine();
        return true;
    }

    virtual bool Execute(Cli_Cmd_ID cmd_id, Cli_Cmd *cmd, vector<Level_Description> &Levels, bool is_debug) {
        switch (cmd_id) {
            case CMD_ID_test_terminal:
                if (is_debug) return true;
                return test_terminal(Levels);
            case CMD_ID_end:
                if (is_debug) return true;
                return end(Levels);

            case CMD_ID_test_get:
            case CMD_ID_test_get_all:
                if (is_debug) return true;
                return test_get_all();

            case CMD_ID_test_set_str:
                if (is_debug) return true;
            {
                string value = cmd->Items[2]->Value_Str;
                return test_set_str(value);
            }

            case CMD_ID_test_set_date:
                if (is_debug) return true;
            {
                string value = cmd->Items[2]->Value_Str;
                return test_set_date(value);
            }
            case CMD_ID_test_set_time:
                if (is_debug) return true;
            {
                string value = cmd->Items[2]->Value_Str;
                return test_set_time(value);
            }
            case CMD_ID_test_set_datetime:
                if (is_debug) return true;
            {
                string value = cmd->Items[2]->Value_Str;
                return test_set_datetime(value);
            }

            case CMD_ID_test_set_ip4:
                if (is_debug) return true;
            {
                string value = cmd->Items[2]->Value_Str;
                return test_set_ip4(value);
            }

            case CMD_ID_test_set_mask:
                if (is_debug) return true;
            {
                string value = cmd->Items[2]->Value_Str;
                return test_set_mask(value);
            }

            case CMD_ID_test_set_ip6:
                if (is_debug) return true;
            {
                string value = cmd->Items[2]->Value_Str;
                return test_set_ip6(value);
            }

            case CMD_ID_test_set_mac:
                if (is_debug) return true;
            {
                string value = cmd->Items[2]->Value_Str;
                return test_set_mac(value);
            }

            case CMD_ID_test_set_enable:
                if (is_debug) return true;
            {
                string value = cmd->Items[1]->Value_Str;
                return test_set_enable(value);
            }

            case CMD_ID_test_set_loopback:
                if (is_debug) return true;
                return test_set_loopback(cmd);

            case CMD_ID_test_set_loopback_repeating:
                if (is_debug) return true;
                return test_set_loopback_repeating(cmd);

            case CMD_ID_test_set_loopback_disable:
                if (is_debug) return true;
                return test_set_loopback_disable();

        }
        return false; // Not Implemented
    }

    virtual void To_Map(map<string, string> &values_map) {
    }

};

#endif /* CLI_MODULE_TEST_TERMINAL_H */
