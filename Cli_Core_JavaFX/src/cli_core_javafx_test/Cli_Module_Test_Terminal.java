/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cli_core_javafx_test;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;

/**
 *
 * @author mike
 */
public class Cli_Module_Test_Terminal extends Cli_Module {

    protected Cli_Input_JavaFX Cli_Input;
    protected Cli_Output_JavaFX Cli_Output;

    protected String Parent_Level = "";
    protected String New_Level;

    protected int Value_Int = 0;
    protected int Value_Int_Range = 0;
    protected List<Cmd_Item_Int_List_Item> Values_Int_List_Items = new ArrayList<>();
    protected String Value_Str = "";
    protected String Value_Date = "";
    protected String Value_Time = "";
    protected String Value_DateTime = "";
    protected String Value_IP4 = "";
    protected String Value_Mask = "";
    protected String Value_IP6 = "";
    protected String Value_MAC = "";
    protected String Value_Enable = "";
    protected String Value_Loopback = "";
    protected String Value_Loopback_Repeating = "";

    //enum Local_Cmd_ID {
    private final int CMD_ID_NO = 0;

    private final int CMD_ID_test_terminal = 1;
    private final int CMD_ID_end = 2;
    private final int CMD_ID_test = 3;
    private final int CMD_ID_test_get = 4;
    private final int CMD_ID_test_get_all = 5;
    private final int CMD_ID_test_get_list = 6;
    private final int CMD_ID_test_set_int = 7;
    private final int CMD_ID_test_set_range = 8;
    private final int CMD_ID_test_set_list = 9;
    private final int CMD_ID_test_set_ip4 = 10;
    private final int CMD_ID_test_set_mask = 11;
    private final int CMD_ID_test_set_ip6 = 12;
    private final int CMD_ID_test_set_mac = 13;
    private final int CMD_ID_test_set_str = 14;
    private final int CMD_ID_test_set_str_verbose = 15;
    private final int CMD_ID_test_set_esc_str = 16;
    private final int CMD_ID_test_set_esc_str_verbose = 17;
    private final int CMD_ID_test_set_date = 18;
    private final int CMD_ID_test_set_time = 19;
    private final int CMD_ID_test_set_datetime = 20;
    private final int CMD_ID_test_set_enable = 21;
    private final int CMD_ID_test_set_loopback_local_remote_enable_disable = 22;
    private final int CMD_ID_test_set_loopback_disable = 23;
    private final int CMD_ID_test_set_loopback_repeating = 24;
    private final int CMD_ID_test_set_loopback_repeating_disable = 25;

    private final int CMD_ID_phy_phynum_set_speed_speedvalue_duplex_duplexvalue = 26;

    private final int CMD_ID_LAST = 27;
    //};

    @Override
    public int Cmd_ID_Count_Get() {
        return CMD_ID_LAST - CMD_ID_NO - 1;
    }

    boolean test_terminal(List<Level_Description> Levels) {
        Parent_Level = Cli_Input.Level_Get();
        Levels.add(new Level_Description(New_Level));
        Cli_Input.Level_Set(New_Level);
        return true;
    }

    boolean end(List<Level_Description> Levels) {
        if (Levels.size() > 0) {
            Levels.remove(Levels.size() - 1);
        }
        Cli_Input.Level_Set(Parent_Level);
        return true;
    }

    Cli_Module_Test_Terminal(Cli_Input_JavaFX cli_input, Cli_Output_JavaFX cli_output) {
        super("Test Terminal");

        Version = "0.02";

        Cli_Input = cli_input;
        Cli_Output = cli_output;
        New_Level = "test terminal";

        {
            // test terminal
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_test_terminal);
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
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_end);
            cmd.Text_Set("end");
            cmd.Help_Set("level up");
            cmd.Is_Global_Set(false);
            cmd.Level_Set(New_Level);
            cmd.Item_Add(new Cmd_Item_Word("end", "level up"));
            Cmd_Add(cmd);
        }

        {
            // test
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_test);
            cmd.Text_Set("test");
            cmd.Help_Set("test: set all values");
            cmd.Is_Global_Set(false);
            cmd.Level_Set(New_Level);
            cmd.Item_Add(new Cmd_Item_Word("test", "test: set all values"));
            Cmd_Add(cmd);
        }

        {
            // test get
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_test_get);
            cmd.Text_Set("get");
            cmd.Help_Set("test: get all");
            cmd.Is_Global_Set(false);
            cmd.Level_Set(New_Level);
            cmd.Item_Add(new Cmd_Item_Word("get", "test: get all"));
            Cmd_Add(cmd);
        }
        {
            // test get all
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_test_get_all);
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
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_test_get_list);
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
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_test_set_int);
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
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_test_set_range);
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
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_test_set_list);
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
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_test_set_str);
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
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_test_set_str_verbose);
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
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_test_set_esc_str);
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
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_test_set_esc_str_verbose);
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
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_test_set_date);
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
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_test_set_time);
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
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_test_set_datetime);
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
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_test_set_ip4);
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
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_test_set_mask);
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
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_test_set_ip6);
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
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_test_set_mac);
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
            List<String> words = new ArrayList<>();
            words.add("enable");
            words.add("disable");
            words.add("else");
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_test_set_enable);
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
            List<String> words_loopback = new ArrayList<>();
            words_loopback.add("raw");
            words_loopback.add("net");
            words_loopback.add("local");
            words_loopback.add("remote");

            List<String> words_enable_disable = new ArrayList<>();
            words_enable_disable.add("enable");
            words_enable_disable.add("disable");

            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_test_set_loopback_local_remote_enable_disable);
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
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_test_set_loopback_disable);
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
            List<String> words = new ArrayList<>();
            words.add("raw");
            words.add("net");
            words.add("local");
            words.add("remote");
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_test_set_loopback_repeating);
            cmd.Text_Set("set loopback repeating [raw,net,local,remote]");
            cmd.Help_Set("test: set loopback repeating [raw,net,local,remote]");
            cmd.Is_Global_Set(false);
            cmd.Level_Set("test terminal");
            cmd.Item_Add(new Cmd_Item_Word("set", "test: set"));
            cmd.Item_Add(new Cmd_Item_Word("loopback", "test: set loopback"));
            cmd.Item_Add(new Cmd_Item_Word("repeating", "test: set loopback repeating"));

            boolean is_repeating = true;
            cmd.Item_Add(new Cmd_Item_Word_List("[raw,net,local,remote]", "test: set loopback repeating [raw,net,local,remote]", words,
                    is_repeating));

            Cmd_Add(cmd);
        }
        {
            // test set loopback repeating disable
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_test_set_loopback_repeating_disable);
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
            Cli_Cmd cmd = new Cli_Cmd(CMD_ID_phy_phynum_set_speed_speedvalue_duplex_duplexvalue);
            cmd.Text_Set("phy <phy_num> set speed <auto|10|100|1000> duplex <auto|full|half>");
            cmd.Help_Set("sw phy set speed and duplex");
            cmd.Is_Global_Set(false);
            cmd.Level_Set(New_Level);
            cmd.Item_Add(new Cmd_Item_Word("phy", "sw phy"));
            cmd.Item_Add(new Cmd_Item_Int_List(3, 4, "<phy_num:3-4>", "sw phy num"));
            cmd.Item_Add(new Cmd_Item_Word("set", "sw phy set"));
            cmd.Item_Add(new Cmd_Item_Word("speed", "sw phy set speed"));

            List<String> speed_words = new ArrayList<>();
            speed_words.add("auto");
            speed_words.add("10");
            speed_words.add("100");
            speed_words.add("1000");
            cmd.Item_Add(new Cmd_Item_Word_Range("<auto|10|100|1000>", "speed value", speed_words));
            cmd.Item_Add(new Cmd_Item_Word("duplex", "sw phy set duplex"));

            List<String> duplex_words = new ArrayList<>();
            duplex_words.add("auto");
            duplex_words.add("full");
            duplex_words.add("half");
            cmd.Item_Add(new Cmd_Item_Word_Range("<auto|full|half>", "duplex value", duplex_words));

            Cmd_Add(cmd);
        }

    }

    boolean test() {
        List<Cmd_Item_Base> cmd_items = new ArrayList<>();

        cmd_items.add(new Cmd_Item_Base("TestBase", ""));

        cmd_items.add(new Cmd_Item_Rem("$", ""));

        cmd_items.add(new Cmd_Item_Int("7", ""));
        cmd_items.add(new Cmd_Item_Int_Range(1, 4095, "2000", ""));
        cmd_items.add(new Cmd_Item_Int_List(1, 4095, "2,7,2000,3000-4000", ""));
        cmd_items.add(new Cmd_Item_Str("\"TestStr\"", ""));
        cmd_items.add(new Cmd_Item_Word("TestWord1", ""));

        List<String> words = new ArrayList<>();
        words.add("TestWord1");
        words.add("TestWord2");
        words.add("TestWord3");
        cmd_items.add(new Cmd_Item_Word_Range("TestWord2", "", words));
        cmd_items.add(new Cmd_Item_Word_List("TestWord3", "", words));

        cmd_items.add(new Cmd_Item_IP4("192.168.1.1", ""));
        cmd_items.add(new Cmd_Item_IP6("::192.168.1.1", ""));
        cmd_items.add(new Cmd_Item_MAC("AA:BB:CC:DD:EE:FF", ""));

        cmd_items.add(new Cmd_Item_Date("\"2020-01-01\"", ""));
        cmd_items.add(new Cmd_Item_DateTime("\"2020-01-01 23:59:59\"", ""));
        cmd_items.add(new Cmd_Item_Time("\"23:59:59\"", ""));

        int w_type_max = 0;
        int w_text_max = 0;
        for (int i = 0; i < cmd_items.size(); i++) {
            Cmd_Item_Base cmd_item = cmd_items.get(i);
            if (w_type_max < cmd_item.Type_Get().length()) {
                w_type_max = cmd_item.Type_Get().length();
            }
            if (w_text_max < cmd_item.Text_Get().length()) {
                w_text_max = cmd_item.Text_Get().length();
            }
        }

        String s_type_format = "%" + Integer.toString(w_type_max) + "s";
        String s_text_format = "%-" + Integer.toString(w_text_max) + "s";

        Cli_Output.Output_NewLine();
        for (int i = 0; i < cmd_items.size(); i++) {
            StringBuilder sb = new StringBuilder();
            Cmd_Item_Base cmd_item = cmd_items.get(i);
            sb.append(String.format(s_type_format, cmd_item.Type_Get()))
                    .append(": ")
                    .append(String.format(s_text_format, cmd_item.Text_Get()));
            Cmd_Item_Valid_Result res_parse = cmd_item.Parse(cmd_item.Text_Get());
            sb.append(" Parse: ").append(Cmd_Item_Valid_Result_Func.To_String(res_parse));
            Cli_Output.Output_Str(sb.toString());
            Cli_Output.Output_NewLine();
        }

        return true;
    }

    boolean test_get_all() {
        StringBuilder sb = new StringBuilder();
        int w = 20;

        String s_format = "%" + Integer.toString(w) + "s";

        sb.append(String.format(s_format, "Int: ")).append(Integer.toString(Value_Int)).append("\n");
        sb.append(String.format(s_format, "Int Range: ")).append(Integer.toString(Value_Int_Range)).append("\n");

        sb.append(String.format(s_format, "Int List: "));
        for (int i = 0; i < Values_Int_List_Items.size(); i++) {
            Cmd_Item_Int_List_Item item = Values_Int_List_Items.get(i);
            if (i > 0) {
                sb.append(",");
            }
            if (item.Min == item.Max) {
                sb.append(Integer.toString(item.Min));
            } else {
                sb.append(Integer.toString(item.Min)).append("-").append(Integer.toString(item.Max));
            }
        }
        sb.append("\n");

        sb.append(String.format(s_format, "Str: ")).append(Value_Str).append("\n");
        sb.append(String.format(s_format, "Str: ")).append(Value_Str).append("\n");
        sb.append(String.format(s_format, "Date: ")).append(Value_Date).append("\n");
        sb.append(String.format(s_format, "Time: ")).append(Value_Time).append("\n");
        sb.append(String.format(s_format, "DateTime: ")).append(Value_DateTime).append("\n");
        sb.append(String.format(s_format, "IP4: ")).append(Value_IP4).append("\n");
        sb.append(String.format(s_format, "Mask: ")).append(Value_Mask).append("\n");
        sb.append(String.format(s_format, "IP6: ")).append(Value_IP6).append("\n");
        sb.append(String.format(s_format, "MAC: ")).append(Value_MAC).append("\n");
        sb.append(String.format(s_format, "Enable: ")).append(Value_Enable).append("\n");
        sb.append(String.format(s_format, "Loopback: ")).append(Value_Loopback).append("\n");
        sb.append(String.format(s_format, "Loopback Repeating: ")).append(Value_Loopback_Repeating).append("\n");

        Cli_Output.Output_NewLine();
        Cli_Output.Output_Str(sb.toString());

        return true;
    }

    boolean test_get_list() {

        if (Values_Int_List_Items.size() > 0) {

            Cli_Output.Output_NewLine();
            Cli_Output.Output_Str("Int List:");
            Cli_Output.Output_NewLine();

            for (int i = 0; i < Values_Int_List_Items.size(); i++) {
                Cmd_Item_Int_List_Item item = Values_Int_List_Items.get(i);
                for (int j = item.Min; j <= item.Max; j++) {
                    Cli_Output.Output_Str(Integer.toString(j));
                    Cli_Output.Output_NewLine();
                }
            }

            Cli_Output.Output_NewLine();

        } else {
            Cli_Output.Output_NewLine();
            Cli_Output.Output_Str("Int List: <empty>");
            Cli_Output.Output_NewLine();
        }

        return true;
    }

    boolean test_set_int(String value) {
        Value_Int = Integer.parseInt(value);
        Cli_Output.Output_NewLine();
        Cli_Output.Output_Str("Int=" + Integer.toString(Value_Int));
        Cli_Output.Output_NewLine();
        return true;
    }

    boolean test_set_range(String value) {
        Value_Int_Range = Integer.parseInt(value);
        Cli_Output.Output_NewLine();
        Cli_Output.Output_Str("Range=" + Integer.toString(Value_Int_Range));
        Cli_Output.Output_NewLine();
        return true;
    }

    boolean test_set_list(Cli_Cmd cmd) {
        Cmd_Item_Int_List int_list = (Cmd_Item_Int_List) cmd.Items.get(2);
        Values_Int_List_Items.clear();
        for (int i = 0; i < int_list.Values_Int_List_Items.size(); i++) {
            Values_Int_List_Items.add(int_list.Values_Int_List_Items.get(i));
        }
        Cli_Output.Output_NewLine();
        StringBuilder sb = new StringBuilder();
        sb.append("Int List=");
        for (int i = 0; i < Values_Int_List_Items.size(); i++) {
            Cmd_Item_Int_List_Item item = Values_Int_List_Items.get(i);
            if (i > 0) {
                sb.append(",");
            }
            if (item.Min == item.Max) {
                sb.append(Integer.toString(item.Min));
            } else {
                sb.append(Integer.toString(item.Min) + "-" + Integer.toString(item.Max));
            }
        }
        Cli_Output.Output_Str(sb.toString());
        Cli_Output.Output_NewLine();
        return true;
    }

    boolean test_set_str(String value, boolean is_verbose) {
        Value_Str = value;
        Cli_Output.Output_NewLine();
        if (!is_verbose) {
            Cli_Output.Output_Str("Str=\"" + Value_Str + "\"");
        } else {
            Cli_Output.Output_Str("Str=\"" + Value_Str + "\" verbose");
        }
        Cli_Output.Output_NewLine();
        return true;
    }

    boolean test_set_date(String value) {
        Value_Date = value;
        Cli_Output.Output_NewLine();
        Cli_Output.Output_Str("Date=" + Value_Date);
        Cli_Output.Output_NewLine();
        return true;
    }

    boolean test_set_time(String value) {
        Value_Time = value;
        Cli_Output.Output_NewLine();
        Cli_Output.Output_Str("Time=" + Value_Time);
        Cli_Output.Output_NewLine();
        return true;
    }

    boolean test_set_datetime(String value) {
        Value_DateTime = value;
        Cli_Output.Output_NewLine();
        Cli_Output.Output_Str("DateTime=" + Value_DateTime);
        Cli_Output.Output_NewLine();
        return true;
    }

    boolean test_set_ip4(String value) {
        Value_IP4 = value;
        Cli_Output.Output_NewLine();
        Cli_Output.Output_Str("IP4=" + Value_IP4);
        Cli_Output.Output_NewLine();
        return true;
    }

    boolean test_set_mask(String value) {
        Value_Mask = value;
        Cli_Output.Output_NewLine();
        Cli_Output.Output_Str("Mask=" + Value_Mask);
        Cli_Output.Output_NewLine();
        return true;
    }

    boolean test_set_ip6(String value) {
        Value_IP6 = value;
        Cli_Output.Output_NewLine();
        Cli_Output.Output_Str("IP6=" + Value_IP6);
        Cli_Output.Output_NewLine();
        return true;
    }

    boolean test_set_mac(String value) {
        Value_MAC = value;
        Cli_Output.Output_NewLine();
        Cli_Output.Output_Str("MAC=" + Value_MAC);
        Cli_Output.Output_NewLine();
        return true;
    }

    boolean test_set_enable(String value) {
        Value_Enable = value;
        Cli_Output.Output_NewLine();
        Cli_Output.Output_Str("Enable=" + Value_Enable);
        Cli_Output.Output_NewLine();
        return true;
    }

    boolean test_set_loopback(Cli_Cmd cmd) {

        Cmd_Item_Word_List word_list = (Cmd_Item_Word_List) cmd.Items.get(2);
        Cmd_Item_Word_Range word_range = (Cmd_Item_Word_Range) cmd.Items.get(3);

        Value_Loopback = "";
        for (int i = 0; i < word_list.Values_Str.size(); i++) {
            if (i == 0) {
                Value_Loopback += word_list.Values_Str.get(i);
            } else {
                Value_Loopback += " " + word_list.Values_Str.get(i);
            }
        }

        Value_Loopback += " " + word_range.Value_Str;

        Cli_Output.Output_NewLine();
        Cli_Output.Output_Str("Loopback=" + Value_Loopback);
        Cli_Output.Output_NewLine();

        return true;
    }

    boolean test_set_loopback_disable() {
        Value_Loopback = "disable";
        Cli_Output.Output_NewLine();
        Cli_Output.Output_Str("Loopback=" + Value_Loopback);
        Cli_Output.Output_NewLine();
        return true;
    }

    boolean test_set_loopback_repeating(Cli_Cmd cmd) {

        Cmd_Item_Word_List word_list = (Cmd_Item_Word_List) cmd.Items.get(3);
        Value_Loopback_Repeating = "";
        for (int i = 0; i < word_list.Values_Str.size(); i++) {
            if (i == 0) {
                Value_Loopback_Repeating += word_list.Values_Str.get(i);
            } else {
                Value_Loopback_Repeating += " " + word_list.Values_Str.get(i);
            }
        }

        Cli_Output.Output_NewLine();
        Cli_Output.Output_Str("Loopback Repeating=" + Value_Loopback_Repeating);
        Cli_Output.Output_NewLine();

        return true;
    }

    boolean test_set_loopback_repeating_disable() {
        Value_Loopback_Repeating = "disable";
        Cli_Output.Output_NewLine();
        Cli_Output.Output_Str("Loopback Repeating=" + Value_Loopback_Repeating);
        Cli_Output.Output_NewLine();
        return true;
    }

    @Override
    public boolean Execute(Cli_Cmd cmd, List<Level_Description> Levels, boolean is_debug) {
        int cmd_id = cmd.ID_Get();
        Level_Description level = new Level_Description();
        String parameter = "";
        switch (cmd_id) {
            case CMD_ID_test_terminal:
                if (is_debug) {
                    return true;
                }
                return test_terminal(Levels);
            case CMD_ID_end:
                if (is_debug) {
                    return true;
                }
                return end(Levels);

            case CMD_ID_test:
                if (is_debug) {
                    return true;
                }
                return test();

            case CMD_ID_test_get:
            case CMD_ID_test_get_all:
                if (is_debug) {
                    return true;
                }
                return test_get_all();

            case CMD_ID_test_get_list:
                if (is_debug) {
                    return true;
                }
                return test_get_list();

            case CMD_ID_test_set_int:
                if (is_debug) {
                    return true;
                } else {
                    String value = cmd.Items.get(2).Value_Str;
                    return test_set_int(value);
                }
            case CMD_ID_test_set_range:
                if (is_debug) {
                    return true;
                } else {
                    String value = cmd.Items.get(2).Value_Str;
                    return test_set_range(value);
                }
            case CMD_ID_test_set_list:
                if (is_debug) {
                    return true;
                }
                return test_set_list(cmd);

            case CMD_ID_test_set_str:
            case CMD_ID_test_set_str_verbose:
            case CMD_ID_test_set_esc_str:
            case CMD_ID_test_set_esc_str_verbose:
                if (is_debug) {
                    return true;
                } else {
                    String value = cmd.Items.get(2).Value_Str;
                    boolean is_verbose = ((cmd_id == CMD_ID_test_set_str_verbose)
                            || (cmd_id == CMD_ID_test_set_esc_str_verbose));
                    return test_set_str(value, is_verbose);
                }

            case CMD_ID_test_set_date:
                if (is_debug) {
                    return true;
                } else {
                    String value = cmd.Items.get(2).Value_Str;
                    return test_set_date(value);
                }
            case CMD_ID_test_set_time:
                if (is_debug) {
                    return true;
                } else {
                    String value = cmd.Items.get(2).Value_Str;
                    return test_set_time(value);
                }
            case CMD_ID_test_set_datetime:
                if (is_debug) {
                    return true;
                } else {
                    String value = cmd.Items.get(2).Value_Str;
                    return test_set_datetime(value);
                }

            case CMD_ID_test_set_ip4:
                if (is_debug) {
                    return true;
                } else {
                    String value = cmd.Items.get(2).Value_Str;
                    return test_set_ip4(value);
                }

            case CMD_ID_test_set_mask:
                if (is_debug) {
                    return true;
                } else {
                    String value = cmd.Items.get(2).Value_Str;
                    return test_set_mask(value);
                }

            case CMD_ID_test_set_ip6:
                if (is_debug) {
                    return true;
                } else {
                    String value = cmd.Items.get(2).Value_Str;
                    return test_set_ip6(value);
                }

            case CMD_ID_test_set_mac:
                if (is_debug) {
                    return true;
                } else {
                    String value = cmd.Items.get(2).Value_Str;
                    return test_set_mac(value);
                }

            case CMD_ID_test_set_enable:
                if (is_debug) {
                    return true;
                } else {
                    String value = cmd.Items.get(1).Value_Str;
                    return test_set_enable(value);
                }

            case CMD_ID_test_set_loopback_local_remote_enable_disable:
                if (is_debug) {
                    return true;
                }
                return test_set_loopback(cmd);
            case CMD_ID_test_set_loopback_disable:
                if (is_debug) {
                    return true;
                }
                return test_set_loopback_disable();

            case CMD_ID_test_set_loopback_repeating:
                if (is_debug) {
                    return true;
                }
                return test_set_loopback_repeating(cmd);
            case CMD_ID_test_set_loopback_repeating_disable:
                if (is_debug) {
                    return true;
                }
                return test_set_loopback_repeating_disable();

        }
        return false; // Not Implemented
    }

    @Override
    public void To_Map(Map<String, String> values_map) {

        String Prefix = "Test_Terminal";

        values_map.put(Prefix + ".Value_Int", Integer.toString(Value_Int));
        values_map.put(Prefix + ".Value_Int_Range", Integer.toString(Value_Int_Range));
        values_map.put(Prefix + ".Value_Str", Value_Str);
        values_map.put(Prefix + ".Value_Date", Value_Date);
        values_map.put(Prefix + ".Value_Time", Value_Time);
        values_map.put(Prefix + ".Value_DateTime", Value_DateTime);
        values_map.put(Prefix + ".Value_IP4", Value_IP4);
        values_map.put(Prefix + ".Value_Mask", Value_Mask);
        values_map.put(Prefix + ".Value_IP6", Value_IP6);
        values_map.put(Prefix + ".Value_MAC", Value_MAC);
        values_map.put(Prefix + ".Value_Enable", Value_Enable);
        values_map.put(Prefix + ".Value_Loopback", Value_Loopback);
        values_map.put(Prefix + ".Value_Loopback_Repeating", Value_Loopback_Repeating);

    }

}
