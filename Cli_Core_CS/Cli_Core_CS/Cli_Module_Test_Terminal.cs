﻿using System;
using System.Collections.Generic;
using System.Text;

namespace Cli_Core_CS
{
    class Cli_Module_Test_Terminal : Cli_Module
    {
        Cli_Input_CS Cli_Input;
        Cli_Output_CS Cli_Output;

        string Parent_Level = "";
        string New_Level = "";

        int Value_Int = 0;
        int Value_Int_Range = 0;
        List<Cmd_Item_Int_List_Item> Values_Int_List_Items = new List<Cmd_Item_Int_List_Item>();
        string Value_Str = "";
        string Value_Date = "";
        string Value_Time = "";
        string Value_DateTime = "";
        string Value_IP4 = "";
        string Value_Mask = "";
        string Value_IP6 = "";
        string Value_MAC = "";
        string Value_Enable = "";
        string Value_Loopback = "";
        string Value_Loopback_Repeating = "";

        enum Local_Cmd_ID
        {
            CMD_ID_NO,

            CMD_ID_test_terminal,
            CMD_ID_end,
            CMD_ID_test,
            CMD_ID_test_get,
            CMD_ID_test_get_all,
            CMD_ID_test_get_list,
            CMD_ID_test_set_int,
            CMD_ID_test_set_range,
            CMD_ID_test_set_list,
            CMD_ID_test_set_ip4,
            CMD_ID_test_set_mask,
            CMD_ID_test_set_ip6,
            CMD_ID_test_set_mac,
            CMD_ID_test_set_str,
            CMD_ID_test_set_str_verbose,
            CMD_ID_test_set_esc_str,
            CMD_ID_test_set_esc_str_verbose,
            CMD_ID_test_set_date,
            CMD_ID_test_set_time,
            CMD_ID_test_set_datetime,
            CMD_ID_test_set_enable,
            CMD_ID_test_set_loopback_local_remote_enable_disable,
            CMD_ID_test_set_loopback_disable,
            CMD_ID_test_set_loopback_repeating,
            CMD_ID_test_set_loopback_repeating_disable,

            CMD_ID_phy_phynum_set_speed_speedvalue_duplex_duplexvalue,

            CMD_ID_LAST
        };

        public override int Cmd_ID_Count_Get()
        {
            return Local_Cmd_ID.CMD_ID_LAST - Local_Cmd_ID.CMD_ID_NO - 1;
        }

        bool test_terminal(List<Level_Description> Levels)
        {
            Parent_Level = Cli_Input.Level_Get();
            Levels.Add(new Level_Description(New_Level));
            Cli_Input.Level_Set(New_Level);
            return true;
        }

        override public bool end(List<Level_Description> Levels)
        {
            if (Levels.Count > 0) Levels.RemoveAt(Levels.Count - 1);
            Cli_Input.Level_Set(Parent_Level);
            return true;
        }

        public Cli_Module_Test_Terminal(Cli_Input_CS cli_input, Cli_Output_CS cli_output)
        : base("Test Terminal")
        {
            Version = "0.02";
            Cli_Input = cli_input;
            Cli_Output = cli_output;
            New_Level = "test terminal";
            {
                // test terminal
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_test_terminal);
                cmd.Text_Set(New_Level);
                cmd.Help_Set("switch to level: " + New_Level);
                cmd.Is_Global_Set(false);
                cmd.Level_Set("");
                cmd.Item_Add(new Cmd_Item_Word("test", "switch to level: " + New_Level));
                cmd.Item_Add(new Cmd_Item_Word("terminal", "switch to level: " + New_Level));
                Cmd_Add(cmd);
            }
            {
                // end
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_end);
                cmd.Text_Set("end");
                cmd.Help_Set("level up");
                cmd.Is_Global_Set(false);
                cmd.Level_Set(New_Level);
                cmd.Item_Add(new Cmd_Item_Word("end", "level up"));
                Cmd_Add(cmd);
            }

            {
                // test
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_test);
                cmd.Text_Set("test");
                cmd.Help_Set("test: set all values");
                cmd.Is_Global_Set(false);
                cmd.Level_Set(New_Level);
                cmd.Item_Add(new Cmd_Item_Word("test", "test: set all values"));
                Cmd_Add(cmd);
            }

            {
                // test get
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_test_get);
                cmd.Text_Set("get");
                cmd.Help_Set("test: get all");
                cmd.Is_Global_Set(false);
                cmd.Level_Set(New_Level);
                cmd.Item_Add(new Cmd_Item_Word("get", "test: get all"));
                Cmd_Add(cmd);
            }
            {
                // test get all
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_test_get_all);
                cmd.Text_Set("get all");
                cmd.Help_Set("test: get all");
                cmd.Is_Global_Set(false);
                cmd.Level_Set(New_Level);
                cmd.Item_Add(new Cmd_Item_Word("get", "test: get"));
                cmd.Item_Add(new Cmd_Item_Word("all", "test: get all"));
                Cmd_Add(cmd);
            }

            {
                // test get list
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_test_get_list);
                cmd.Text_Set("get list");
                cmd.Help_Set("test: get list");
                cmd.Is_Global_Set(false);
                cmd.Level_Set(New_Level);
                cmd.Item_Add(new Cmd_Item_Word("get", "test: get"));
                cmd.Item_Add(new Cmd_Item_Word("list", "test: get list"));
                Cmd_Add(cmd);
            }

            {
                // test set int
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_test_set_int);
                cmd.Text_Set("set int <int_value>");
                cmd.Help_Set("test: set int");
                cmd.Is_Global_Set(false);
                cmd.Level_Set("test terminal");
                cmd.Item_Add(new Cmd_Item_Word("set", "test: set"));
                cmd.Item_Add(new Cmd_Item_Word("int", "test: set int"));
                cmd.Item_Add(new Cmd_Item_Int("<int_value>", "test: set int <int_value>"));
                Cmd_Add(cmd);
            }
            {
                // test set range
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_test_set_range);
                cmd.Text_Set("set range <1..4095>");
                cmd.Help_Set("test: set range");
                cmd.Is_Global_Set(false);
                cmd.Level_Set("test terminal");
                cmd.Item_Add(new Cmd_Item_Word("set", "test: set"));
                cmd.Item_Add(new Cmd_Item_Word("range", "test: set range"));
                cmd.Item_Add(new Cmd_Item_Int_Range(1, 4095, "<1..4095>", "test: set range <1..4095>"));
                Cmd_Add(cmd);
            }
            {
                // test set list
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_test_set_list);
                cmd.Text_Set("set list <1-4095>");
                cmd.Help_Set("test: set list");
                cmd.Is_Global_Set(false);
                cmd.Level_Set("test terminal");
                cmd.Item_Add(new Cmd_Item_Word("set", "test: set"));
                cmd.Item_Add(new Cmd_Item_Word("list", "test: set list"));
                cmd.Item_Add(new Cmd_Item_Int_List(1, 4095, "<1-4095>", "test: set list <1-4095>"));
                Cmd_Add(cmd);
            }

            {
                // test set str
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_test_set_str);
                cmd.Text_Set("set str <str>");
                cmd.Help_Set("test: set str");
                cmd.Is_Global_Set(false);
                cmd.Level_Set("test terminal");
                cmd.Item_Add(new Cmd_Item_Word("set", "test: set"));
                cmd.Item_Add(new Cmd_Item_Word("str", "test: set str"));
                cmd.Item_Add(new Cmd_Item_Str("<str>", "test: set str <str>"));
                Cmd_Add(cmd);
            }
            {
                // test set str verbose
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_test_set_str_verbose);
                cmd.Text_Set("set str <str> verbose");
                cmd.Help_Set("test: set str verbose");
                cmd.Is_Global_Set(false);
                cmd.Level_Set("test terminal");
                cmd.Item_Add(new Cmd_Item_Word("set", "test: set"));
                cmd.Item_Add(new Cmd_Item_Word("str", "test: set str"));
                cmd.Item_Add(new Cmd_Item_Str("<str>", "test: set str <str>"));
                cmd.Item_Add(new Cmd_Item_Word("verbose", "test: set str <str> verbose"));
                Cmd_Add(cmd);
            }

            {
                // test set esc_str
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_test_set_esc_str);
                cmd.Text_Set("set esc_str <esc_str>");
                cmd.Help_Set("test: set esc_str");
                cmd.Is_Global_Set(false);
                cmd.Level_Set("test terminal");
                cmd.Item_Add(new Cmd_Item_Word("set", "test: set"));
                cmd.Item_Add(new Cmd_Item_Word("esc_str", "test: set esc_str"));
                cmd.Item_Add(new Cmd_Item_Str_Esc("<esc_str>", "test: set esc_str <esc_str>"));
                Cmd_Add(cmd);
            }
            {
                // test set esc_str verbose
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_test_set_esc_str_verbose);
                cmd.Text_Set("set esc_str <esc_str>");
                cmd.Help_Set("test: set esc_str");
                cmd.Is_Global_Set(false);
                cmd.Level_Set("test terminal");
                cmd.Item_Add(new Cmd_Item_Word("set", "test: set"));
                cmd.Item_Add(new Cmd_Item_Word("esc_str", "test: set esc_str"));
                cmd.Item_Add(new Cmd_Item_Str_Esc("<esc_str>", "test: set esc_str <esc_str>"));
                cmd.Item_Add(new Cmd_Item_Word("verbose", "test: set esc_str <esc_str> verbose"));
                Cmd_Add(cmd);
            }

            {
                // test set date
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_test_set_date);
                cmd.Text_Set("set date \"yyyy-mm-dd\"");
                cmd.Help_Set("test: set date");
                cmd.Is_Global_Set(false);
                cmd.Level_Set("test terminal");
                cmd.Item_Add(new Cmd_Item_Word("set", "test: set"));
                cmd.Item_Add(new Cmd_Item_Word("date", "test: set date"));
                cmd.Item_Add(new Cmd_Item_Date("\"yyyy-mm-dd\"", "test: set date \"yyyy-mm-dd\""));
                Cmd_Add(cmd);
            }
            {
                // test set time
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_test_set_time);
                cmd.Text_Set("set time \"HH-MM-SS\"");
                cmd.Help_Set("test: set time");
                cmd.Is_Global_Set(false);
                cmd.Level_Set("test terminal");
                cmd.Item_Add(new Cmd_Item_Word("set", "test: set"));
                cmd.Item_Add(new Cmd_Item_Word("time", "test: time"));
                cmd.Item_Add(new Cmd_Item_Time("\"HH-MM-SS\"", "test: set date \"HH-MM-SS\""));
                Cmd_Add(cmd);
            }
            {
                // test set datetime
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_test_set_datetime);
                cmd.Text_Set("set datetime \"yyyy-mm-dd HH-MM-SS\"");
                cmd.Help_Set("test: set datetime");
                cmd.Is_Global_Set(false);
                cmd.Level_Set("test terminal");
                cmd.Item_Add(new Cmd_Item_Word("set", "test: set"));
                cmd.Item_Add(new Cmd_Item_Word("datetime", "test: set datetime"));
                cmd.Item_Add(new Cmd_Item_DateTime("\"yyyy-mm-dd HH-MM-SS\"", "test: set datetime \"yyyy-mm-dd HH-MM-SS\""));
                Cmd_Add(cmd);
            }

            {
                // test set ip4
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_test_set_ip4);
                cmd.Text_Set("set ip4 <ip4-address>");
                cmd.Help_Set("test: set ip4");
                cmd.Is_Global_Set(false);
                cmd.Level_Set("test terminal");
                cmd.Item_Add(new Cmd_Item_Word("set", "test: set"));
                cmd.Item_Add(new Cmd_Item_Word("ip4", "test: set ip4"));
                cmd.Item_Add(new Cmd_Item_IP4("<ip4-address>", "test: set ip4 <ip4-address>"));
                Cmd_Add(cmd);
            }

            {
                // test set mask
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_test_set_mask);
                cmd.Text_Set("set mask <mask>");
                cmd.Help_Set("test: set mask");
                cmd.Is_Global_Set(false);
                cmd.Level_Set("test terminal");
                cmd.Item_Add(new Cmd_Item_Word("set", "test: set"));
                cmd.Item_Add(new Cmd_Item_Word("mask", "test: set mask"));
                cmd.Item_Add(new Cmd_Item_IP4("<mask>", "test: set mask <mask>"));
                Cmd_Add(cmd);
            }

            {
                // test set ip6
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_test_set_ip6);
                cmd.Text_Set("set ip6 <ip6-address>");
                cmd.Help_Set("test: set ip6");
                cmd.Is_Global_Set(false);
                cmd.Level_Set("test terminal");
                cmd.Item_Add(new Cmd_Item_Word("set", "test: set"));
                cmd.Item_Add(new Cmd_Item_Word("ip6", "test: set ip6"));
                cmd.Item_Add(new Cmd_Item_IP6("<ip6-address>", "test: set ip6 <ip6-address>"));
                Cmd_Add(cmd);
            }

            {
                // test set mac
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_test_set_mac);
                cmd.Text_Set("set mac <mac-address>");
                cmd.Help_Set("test: set mac");
                cmd.Is_Global_Set(false);
                cmd.Level_Set("test terminal");
                cmd.Item_Add(new Cmd_Item_Word("set", "test: set"));
                cmd.Item_Add(new Cmd_Item_Word("mac", "test: set mac"));
                cmd.Item_Add(new Cmd_Item_MAC("<mac-address>", "test: set mac <mac-address>"));
                Cmd_Add(cmd);
            }

            {
                // test set enable
                List<string> words = new List<string>();
                words.Add("enable");
                words.Add("disable");
                words.Add("else");
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_test_set_enable);
                cmd.Text_Set("set <enable|disable|else>");
                cmd.Help_Set("test: set <enable|disable|else>");
                cmd.Is_Global_Set(false);
                cmd.Level_Set("test terminal");
                cmd.Item_Add(new Cmd_Item_Word("set", "test: set"));
                cmd.Item_Add(new Cmd_Item_Word_Range("<enable|disable|else>", "test: set <enable|disable|else>", words));
                Cmd_Add(cmd);
            }

            {
                // test set loopback [raw,net,local,remote] <enable|disable>

                List<string> words_loopback = new List<string>();
                words_loopback.Add("raw");
                words_loopback.Add("net");
                words_loopback.Add("local");
                words_loopback.Add("remote");

                List<string> words_enable_disable = new List<string>();
                words_enable_disable.Add("enable");
                words_enable_disable.Add("disable");

                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_test_set_loopback_local_remote_enable_disable);
                cmd.Text_Set("set loopback [raw,net,local,remote] <enable|disable>");
                cmd.Help_Set("test: set loopback [raw,net,local,remote] <enable|disable>");
                cmd.Is_Global_Set(false);
                cmd.Level_Set("test terminal");
                cmd.Item_Add(new Cmd_Item_Word("set", "test: set"));
                cmd.Item_Add(new Cmd_Item_Word("loopback", "test: set loopback"));
                cmd.Item_Add(new Cmd_Item_Word_List("[raw,net,local,remote]", "test: set loopback [raw,net,local,remote]", words_loopback));
                cmd.Item_Add(new Cmd_Item_Word_Range("<enable|disable>", "test: set loopback <enable|disable>", words_enable_disable));
                Cmd_Add(cmd);
            }
            {
                // test set loopback disable
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_test_set_loopback_disable);
                cmd.Text_Set("set loopback disable");
                cmd.Help_Set("test: set loopback disable");
                cmd.Is_Global_Set(false);
                cmd.Level_Set("test terminal");
                cmd.Item_Add(new Cmd_Item_Word("set", "test: set"));
                cmd.Item_Add(new Cmd_Item_Word("loopback", "test: set loopback"));
                cmd.Item_Add(new Cmd_Item_Word("disable", "test: set loopback disable"));
                Cmd_Add(cmd);
            }

            {
                // test set loopback repeating [raw,net,local,remote]
                List<string> words = new List<string>();
                words.Add("raw");
                words.Add("net");
                words.Add("local");
                words.Add("remote");
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_test_set_loopback_repeating);
                cmd.Text_Set("set loopback repeating [raw,net,local,remote]");
                cmd.Help_Set("test: set loopback repeating [raw,net,local,remote]");
                cmd.Is_Global_Set(false);
                cmd.Level_Set("test terminal");
                cmd.Item_Add(new Cmd_Item_Word("set", "test: set"));
                cmd.Item_Add(new Cmd_Item_Word("loopback", "test: set loopback"));
                cmd.Item_Add(new Cmd_Item_Word("repeating", "test: set loopback repeating"));

                bool is_repeating = true;
                cmd.Item_Add(new Cmd_Item_Word_List("[raw,net,local,remote]", "test: set loopback repeating [raw,net,local,remote]", words,
                        is_repeating));

                Cmd_Add(cmd);
            }
            {
                // test set loopback repeating disable
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_test_set_loopback_repeating_disable);
                cmd.Text_Set("set loopback repeating disable");
                cmd.Help_Set("test: set loopback repeating disable");
                cmd.Is_Global_Set(false);
                cmd.Level_Set("test terminal");
                cmd.Item_Add(new Cmd_Item_Word("set", "test: set"));
                cmd.Item_Add(new Cmd_Item_Word("loopback", "test: set loopback"));
                cmd.Item_Add(new Cmd_Item_Word("repeating", "test: set loopback repeating"));
                cmd.Item_Add(new Cmd_Item_Word("disable", "test: set loopback repeating disable"));

                Cmd_Add(cmd);
            }

            {
                // phy <phy_num> set speed <auto|10|100|1000> duplex <full|half>
                Cli_Cmd cmd = new Cli_Cmd((int)Local_Cmd_ID.CMD_ID_phy_phynum_set_speed_speedvalue_duplex_duplexvalue);
                cmd.Text_Set("phy <phy_num> set speed <auto|10|100|1000> duplex <auto|full|half>");
                cmd.Help_Set("sw phy set speed and duplex");
                cmd.Is_Global_Set(false);
                cmd.Level_Set(New_Level);
                cmd.Item_Add(new Cmd_Item_Word("phy", "sw phy"));
                cmd.Item_Add(new Cmd_Item_Int_List(3, 4, "<phy_num:3-4>", "sw phy num"));
                cmd.Item_Add(new Cmd_Item_Word("set", "sw phy set"));
                cmd.Item_Add(new Cmd_Item_Word("speed", "sw phy set speed"));

                List<string> speed_words = new List<string>();
                speed_words.Add("auto");
                speed_words.Add("10");
                speed_words.Add("100");
                speed_words.Add("1000");
                cmd.Item_Add(new Cmd_Item_Word_Range("<auto|10|100|1000>", "speed value", speed_words));

                cmd.Item_Add(new Cmd_Item_Word("duplex", "sw phy set duplex"));

                List<string> duplex_words = new List<string>();
                duplex_words.Add("auto");
                duplex_words.Add("full");
                duplex_words.Add("half");
                cmd.Item_Add(new Cmd_Item_Word_Range("<auto|full|half>", "duplex value", duplex_words));

                Cmd_Add(cmd);
            }

        }

        ~Cli_Module_Test_Terminal()
        {
        }

        bool test()
        {
            List<Cmd_Item_Base> cmd_items = new List<Cmd_Item_Base>();

            cmd_items.Add(new Cmd_Item_Base("TestBase", ""));

            cmd_items.Add(new Cmd_Item_Rem("$", ""));

            cmd_items.Add(new Cmd_Item_Int("7", ""));
            cmd_items.Add(new Cmd_Item_Int_Range(1, 4095, "2000", ""));
            cmd_items.Add(new Cmd_Item_Int_List(1, 4095, "2,7,2000,3000-4000", ""));
            cmd_items.Add(new Cmd_Item_Str("\"TestStr\"", ""));
            cmd_items.Add(new Cmd_Item_Word("TestWord1", ""));

            List<string> words = new List<string>();
            words.Add("TestWord1");
            words.Add("TestWord2");
            words.Add("TestWord3");
            cmd_items.Add(new Cmd_Item_Word_Range("TestWord2", "", words));
            cmd_items.Add(new Cmd_Item_Word_List("TestWord3", "", words));

            cmd_items.Add(new Cmd_Item_IP4("192.168.1.1", ""));
            cmd_items.Add(new Cmd_Item_IP6("::192.168.1.1", ""));
            cmd_items.Add(new Cmd_Item_MAC("AA:BB:CC:DD:EE:FF", ""));

            cmd_items.Add(new Cmd_Item_Date("\"2020-01-01\"", ""));
            cmd_items.Add(new Cmd_Item_DateTime("\"2020-01-01 23:59:59\"", ""));
            cmd_items.Add(new Cmd_Item_Time("\"23:59:59\"", ""));

            int w_type_max = 0;
            int w_text_max = 0;
            for (int i = 0; i < cmd_items.Count; i++)
            {
                Cmd_Item_Base cmd_item = cmd_items[i];
                if (w_type_max < cmd_item.Type_Get().Length) w_type_max = cmd_item.Type_Get().Length;
                if (w_text_max < cmd_item.Text_Get().Length) w_text_max = cmd_item.Text_Get().Length;
            }

            StringBuilder sb_type_format = new StringBuilder();
            sb_type_format.Append("{0,").Append(w_type_max).Append("}");
            string s_type_format = sb_type_format.ToString();

            StringBuilder sb_text_format = new StringBuilder();
            sb_text_format.Append("{0,-").Append(w_text_max).Append("}");
            string s_text_format = sb_text_format.ToString();

            Cli_Output.Output_NewLine();
            for (int i = 0; i < cmd_items.Count; i++)
            {
                StringBuilder sb = new StringBuilder();

                Cmd_Item_Base cmd_item = cmd_items[i];
                sb.AppendFormat(s_type_format, cmd_item.Type_Get())
                        .Append(": ")
                        .AppendFormat(s_text_format, cmd_item.Text_Get());
                Cmd_Item_Valid_Result res_parse = cmd_item.Parse(cmd_item.Text_Get());
                sb.Append(" Parse: ").Append(res_parse.ToString());
                Cli_Output.Output_Str(sb.ToString());
                Cli_Output.Output_NewLine();
            }

            return true;
        }

        bool test_get_all()
        {
            StringBuilder sb = new StringBuilder();

            int w = 20;

            StringBuilder sb_format = new StringBuilder();
            sb_format.Append("{0,").Append(w).Append("}");
            string s_format = sb_format.ToString();

            sb.AppendFormat(s_format, "Int: ").Append(Value_Int).Append("\r\n");
            sb.AppendFormat(s_format, "Int Range: ").Append(Value_Int_Range).Append("\r\n");

            sb.AppendFormat(s_format, "Int List: ");
            for (int i = 0; i < Values_Int_List_Items.Count; i++)
            {
                Cmd_Item_Int_List_Item item = Values_Int_List_Items[i];
                if (i > 0)
                {
                    sb.Append(",");
                }
                if (item.Min == item.Max)
                {
                    sb.Append(item.Min);
                }
                else
                {
                    sb.Append(item.Min).Append("-").Append(item.Max);
                }
            }
            sb.Append("\r\n");

            sb.AppendFormat(s_format, "Str: ").Append(Value_Str).Append("\r\n");
            sb.AppendFormat(s_format, "Date: ").Append(Value_Date).Append("\r\n");
            sb.AppendFormat(s_format, "Time: ").Append(Value_Time).Append("\r\n");
            sb.AppendFormat(s_format, "DateTime: ").Append(Value_DateTime).Append("\r\n");
            sb.AppendFormat(s_format, "IP4: ").Append(Value_IP4).Append("\r\n");
            sb.AppendFormat(s_format, "Mask: ").Append(Value_Mask).Append("\r\n");
            sb.AppendFormat(s_format, "IP6: ").Append(Value_IP6).Append("\r\n");
            sb.AppendFormat(s_format, "MAC: ").Append(Value_MAC).Append("\r\n");
            sb.AppendFormat(s_format, "Enable: ").Append(Value_Enable).Append("\r\n");
            sb.AppendFormat(s_format, "Loopback: ").Append(Value_Loopback).Append("\r\n");
            sb.AppendFormat(s_format, "Loopback Repeating: ").Append(Value_Loopback_Repeating).Append("\r\n");

            Cli_Output.Output_NewLine();
            Cli_Output.Output_Str(sb.ToString());

            return true;
        }

        bool test_get_list()
        {

            if (Values_Int_List_Items.Count > 0)
            {

                Cli_Output.Output_NewLine();
                Cli_Output.Output_Str("Int List:");
                Cli_Output.Output_NewLine();

                for (int i = 0; i < Values_Int_List_Items.Count; i++)
                {
                    Cmd_Item_Int_List_Item item = Values_Int_List_Items[i];
                    for (int j = item.Min; j <= item.Max; j++)
                    {
                        Cli_Output.Output_Str(j.ToString());
                        Cli_Output.Output_NewLine();
                    }
                }

                Cli_Output.Output_NewLine();

            }
            else
            {
                Cli_Output.Output_NewLine();
                Cli_Output.Output_Str("Int List: <empty>");
                Cli_Output.Output_NewLine();
            }

            return true;
        }

        bool test_set_int(string value)
        {
            Value_Int = 0;
            Int32.TryParse(value, out Value_Int);
            Cli_Output.Output_NewLine();
            StringBuilder sb = new StringBuilder();
            sb.Append("Int=").Append(Value_Int);
            Cli_Output.Output_Str(sb.ToString());
            Cli_Output.Output_NewLine();
            return true;
        }

        bool test_set_range(string value)
        {
            Value_Int_Range = 0;
            Int32.TryParse(value, out Value_Int_Range);
            Cli_Output.Output_NewLine();
            StringBuilder sb = new StringBuilder();
            sb.Append("Int Range=").Append(Value_Int_Range);
            Cli_Output.Output_Str(sb.ToString());
            Cli_Output.Output_NewLine();
            return true;
        }

        bool test_set_list(Cli_Cmd cmd)
        {
            Cmd_Item_Int_List int_list = (Cmd_Item_Int_List)cmd.Items[2];
            Values_Int_List_Items.Clear();
            for (int i = 0; i < int_list.Values_Int_List_Items.Count; i++)
            {
                Values_Int_List_Items.Add(int_list.Values_Int_List_Items[i]);
            }
            Cli_Output.Output_NewLine();
            StringBuilder sb = new StringBuilder();
            sb.Append("Int List=");
            for (int i = 0; i < Values_Int_List_Items.Count; i++)
            {
                Cmd_Item_Int_List_Item item = Values_Int_List_Items[i];
                if (i > 0)
                {
                    sb.Append(",");
                }
                if (item.Min == item.Max)
                {
                    sb.Append(item.Min);
                }
                else
                {
                    sb.Append(item.Min).Append("-").Append(item.Max);
                }
            }
            Cli_Output.Output_Str(sb.ToString());
            Cli_Output.Output_NewLine();
            return true;
        }

        bool test_set_str(string value, bool is_verbose)
        {
            Value_Str = value;
            Cli_Output.Output_NewLine();
            if (!is_verbose)
            {
                Cli_Output.Output_Str("Str=\"" + Value_Str + "\"");
            }
            else
            {
                Cli_Output.Output_Str("Str=\"" + Value_Str + "\" verbose");
            }
            Cli_Output.Output_NewLine();
            return true;
        }

        bool test_set_date(string value)
        {
            Value_Date = value;
            Cli_Output.Output_NewLine();
            Cli_Output.Output_Str("Date=" + Value_Date);
            Cli_Output.Output_NewLine();
            return true;
        }

        bool test_set_time(string value)
        {
            Value_Time = value;
            Cli_Output.Output_NewLine();
            Cli_Output.Output_Str("Time=" + Value_Time);
            Cli_Output.Output_NewLine();
            return true;
        }

        bool test_set_datetime(string value)
        {
            Value_DateTime = value;
            Cli_Output.Output_NewLine();
            Cli_Output.Output_Str("DateTime=" + Value_DateTime);
            Cli_Output.Output_NewLine();
            return true;
        }

        bool test_set_ip4(string value)
        {
            Value_IP4 = value;
            Cli_Output.Output_NewLine();
            Cli_Output.Output_Str("IP4=" + Value_IP4);
            Cli_Output.Output_NewLine();
            return true;
        }

        bool test_set_mask(string value)
        {
            Value_Mask = value;
            Cli_Output.Output_NewLine();
            Cli_Output.Output_Str("Mask=" + Value_Mask);
            Cli_Output.Output_NewLine();
            return true;
        }

        bool test_set_ip6(string value)
        {
            Value_IP6 = value;
            Cli_Output.Output_NewLine();
            Cli_Output.Output_Str("IP6=" + Value_IP6);
            Cli_Output.Output_NewLine();
            return true;
        }

        bool test_set_mac(string value)
        {
            Value_MAC = value;
            Cli_Output.Output_NewLine();
            Cli_Output.Output_Str("MAC=" + Value_MAC);
            Cli_Output.Output_NewLine();
            return true;
        }

        bool test_set_enable(string value)
        {
            Value_Enable = value;
            Cli_Output.Output_NewLine();
            Cli_Output.Output_Str("Enable=" + Value_Enable);
            Cli_Output.Output_NewLine();
            return true;
        }

        bool test_set_loopback(Cli_Cmd cmd)
        {

            Cmd_Item_Word_List word_list = (Cmd_Item_Word_List)cmd.Items[2];
            Cmd_Item_Word_Range word_range = (Cmd_Item_Word_Range)cmd.Items[3];

            Value_Loopback = "";
            for (int i = 0; i < word_list.Values_Str.Count; i++)
            {
                if (i == 0)
                    Value_Loopback += word_list.Values_Str[i];
                else
                    Value_Loopback += " " + word_list.Values_Str[i];
            }

            Value_Loopback += " " + word_range.Value_Str;

            Cli_Output.Output_NewLine();
            Cli_Output.Output_Str("Loopback=" + Value_Loopback);
            Cli_Output.Output_NewLine();

            return true;
        }

        bool test_set_loopback_disable()
        {
            Value_Loopback = "disable";
            Cli_Output.Output_NewLine();
            Cli_Output.Output_Str("Loopback=" + Value_Loopback);
            Cli_Output.Output_NewLine();
            return true;
        }

        bool test_set_loopback_repeating(Cli_Cmd cmd)
        {
            Cmd_Item_Word_List word_list = (Cmd_Item_Word_List)cmd.Items[3];
            Value_Loopback_Repeating = "";
            for (int i = 0; i < word_list.Values_Str.Count; i++)
            {
                if (i == 0)
                    Value_Loopback_Repeating += word_list.Values_Str[i];
                else
                    Value_Loopback_Repeating += " " + word_list.Values_Str[i];
            }

            Cli_Output.Output_NewLine();
            Cli_Output.Output_Str("Loopback Repeating=" + Value_Loopback_Repeating);
            Cli_Output.Output_NewLine();

            return true;
        }

        bool test_set_loopback_repeating_disable()
        {
            Value_Loopback_Repeating = "disable";
            Cli_Output.Output_NewLine();
            Cli_Output.Output_Str("Loopback Repeating=" + Value_Loopback_Repeating);
            Cli_Output.Output_NewLine();
            return true;
        }

        override public bool Execute(Cli_Cmd cmd, List<Level_Description> Levels, bool is_debug)
        {
            Local_Cmd_ID cmd_id = (Local_Cmd_ID)cmd.ID_Get();
            switch (cmd_id)
            {
                case Local_Cmd_ID.CMD_ID_test_terminal:
                    if (is_debug) return true;
                    return test_terminal(Levels);
                case Local_Cmd_ID.CMD_ID_end:
                    if (is_debug) return true;
                    return end(Levels);

                case Local_Cmd_ID.CMD_ID_test:
                    if (is_debug) return true;
                    return test();

                case Local_Cmd_ID.CMD_ID_test_get:
                case Local_Cmd_ID.CMD_ID_test_get_all:
                    if (is_debug) return true;
                    return test_get_all();

                case Local_Cmd_ID.CMD_ID_test_get_list:
                    if (is_debug) return true;
                    return test_get_list();

                case Local_Cmd_ID.CMD_ID_test_set_int:
                    if (is_debug) return true;
                    {
                        string value = cmd.Items[2].Value_Str;
                        return test_set_int(value);
                    }
                case Local_Cmd_ID.CMD_ID_test_set_range:
                    if (is_debug) return true;
                    {
                        string value = cmd.Items[2].Value_Str;
                        return test_set_range(value);
                    }
                case Local_Cmd_ID.CMD_ID_test_set_list:
                    if (is_debug) return true;
                    return test_set_list(cmd);

                case Local_Cmd_ID.CMD_ID_test_set_str:
                case Local_Cmd_ID.CMD_ID_test_set_str_verbose:
                case Local_Cmd_ID.CMD_ID_test_set_esc_str:
                case Local_Cmd_ID.CMD_ID_test_set_esc_str_verbose:
                    if (is_debug) return true;
                    {
                        string value = cmd.Items[2].Value_Str;
                        bool is_verbose = ((cmd_id == Local_Cmd_ID.CMD_ID_test_set_str_verbose)
                                || (cmd_id == Local_Cmd_ID.CMD_ID_test_set_esc_str_verbose));
                        return test_set_str(value, is_verbose);
                    }

                case Local_Cmd_ID.CMD_ID_test_set_date:
                    if (is_debug) return true;
                    {
                        string value = cmd.Items[2].Value_Str;
                        return test_set_date(value);
                    }
                case Local_Cmd_ID.CMD_ID_test_set_time:
                    if (is_debug) return true;
                    {
                        string value = cmd.Items[2].Value_Str;
                        return test_set_time(value);
                    }
                case Local_Cmd_ID.CMD_ID_test_set_datetime:
                    if (is_debug) return true;
                    {
                        string value = cmd.Items[2].Value_Str;
                        return test_set_datetime(value);
                    }

                case Local_Cmd_ID.CMD_ID_test_set_ip4:
                    if (is_debug) return true;
                    {
                        string value = cmd.Items[2].Value_Str;
                        return test_set_ip4(value);
                    }

                case Local_Cmd_ID.CMD_ID_test_set_mask:
                    if (is_debug) return true;
                    {
                        string value = cmd.Items[2].Value_Str;
                        return test_set_mask(value);
                    }

                case Local_Cmd_ID.CMD_ID_test_set_ip6:
                    if (is_debug) return true;
                    {
                        string value = cmd.Items[2].Value_Str;
                        return test_set_ip6(value);
                    }

                case Local_Cmd_ID.CMD_ID_test_set_mac:
                    if (is_debug) return true;
                    {
                        string value = cmd.Items[2].Value_Str;
                        return test_set_mac(value);
                    }

                case Local_Cmd_ID.CMD_ID_test_set_enable:
                    if (is_debug) return true;
                    {
                        string value = cmd.Items[1].Value_Str;
                        return test_set_enable(value);
                    }

                case Local_Cmd_ID.CMD_ID_test_set_loopback_local_remote_enable_disable:
                    if (is_debug) return true;
                    return test_set_loopback(cmd);
                case Local_Cmd_ID.CMD_ID_test_set_loopback_disable:
                    if (is_debug) return true;
                    return test_set_loopback_disable();

                case Local_Cmd_ID.CMD_ID_test_set_loopback_repeating:
                    if (is_debug) return true;
                    return test_set_loopback_repeating(cmd);
                case Local_Cmd_ID.CMD_ID_test_set_loopback_repeating_disable:
                    if (is_debug) return true;
                    return test_set_loopback_repeating_disable();
            }
            return false; // Not Implemented
        }

        override public void To_Map(Dictionary<string, string> values_map)
        {

            string Prefix = "Test_Terminal";

            {
                StringBuilder sb = new StringBuilder();
                sb.Append(Value_Int);
                values_map[Prefix + ".Value_Int"] = sb.ToString();
            }
            {
                StringBuilder sb = new StringBuilder();
                sb.Append(Value_Int_Range);
                values_map[Prefix + ".Value_Int_Range"] = sb.ToString();
            }

            values_map[Prefix + ".Value_Str"] = Value_Str;
            values_map[Prefix + ".Value_Date"] = Value_Date;
            values_map[Prefix + ".Value_Time"] = Value_Time;
            values_map[Prefix + ".Value_DateTime"] = Value_DateTime;
            values_map[Prefix + ".Value_IP4"] = Value_IP4;
            values_map[Prefix + ".Value_Mask"] = Value_Mask;
            values_map[Prefix + ".Value_IP6"] = Value_IP6;
            values_map[Prefix + ".Value_MAC"] = Value_MAC;
            values_map[Prefix + ".Value_Enable"] = Value_Enable;
            values_map[Prefix + ".Value_Loopback"] = Value_Loopback;
            values_map[Prefix + ".Value_Loopback_Repeating"] = Value_Loopback_Repeating;

        }
    }

}
