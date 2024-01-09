/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cli_core_javafx_test;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import javafx.scene.input.KeyEvent;
import org.junit.Test;
import static org.junit.Assert.*;

/**
 *
 * @author mike
 */
public class Cli_TAB_ProcessorTest {

    String Test_Name = this.getClass().getSimpleName();

    class Cli_Output_JavaFX_Mock extends Cli_Output_JavaFX {

        public Cli_Output_JavaFX_Mock() {
            super(null);
        }

        @Override
        boolean Output_Init() {
            return false;
        }

        @Override
        boolean Output_Close() {
            return false;
        }

        @Override
        boolean Output_Clear() {
            return false;
        }

        @Override
        void Output_NewLine() {
        }

        @Override
        void Output_Char(char c) {
        }

        @Override
        void Output_Char(String c) {
        }

        @Override
        void Output_Str(String s) {
        }

        @Override
        void Output_Return() {
        }

        @Override
        void Caret_Pos_Set(int input_str_len, int input_str_pos) {
        }
    }

    class Cli_Input_JavaFX_Mock extends Cli_Input_JavaFX {

        public Cli_Input_JavaFX_Mock(Cli_Output_JavaFX cli_output, String chars_not_allowed_str) {
            super(cli_output, chars_not_allowed_str);
        }

        @Override
        public void Title_Set(String s) {
            Title = s;
        }

        @Override
        public String Title_Get() {
            return Title;
        }

        @Override
        public void User_Set(String s) {
            User = s;
        }

        @Override
        public String User_Get() {
            return User;
        }

        @Override
        public void Level_Set(String s) {
            Level = s;
        }

        @Override
        public String Level_Get() {
            return Level;
        }

        @Override
        public void Invitation_Set(String s) {
            Invitation = s;
        }

        @Override
        public String Invitation_Get() {
            return Invitation;
        }

        @Override
        public void Divider_L_Set(String s) {
            Divider_L = s;
        }

        @Override
        public String Divider_L_Get() {
            return Divider_L;
        }

        @Override
        public void Divider_R_Set(String s) {
            Divider_R = s;
        }

        @Override
        public String Divider_R_Get() {
            return Divider_R;
        }

        @Override
        public void Prompt_Str_Set(String s) {
            Prompt_Str = s;
        }

        @Override
        public String Prompt_Str_Get() {
            return Prompt_Str;
        }

        @Override
        public void Is_Echo_Set(boolean v) {
            Is_Echo = v;
        }

        @Override
        public boolean Is_Echo_Get() {
            return Is_Echo;
        }

        @Override
        public void Input_Str_Pos_Set(int v) {
            Input_Str_Pos = v;
        }

        @Override
        public int Input_Str_Pos_Get() {
            return Input_Str_Pos;
        }

        @Override
        public void Chars_Not_Allowed_Str_Set(String s) {
            Chars_Not_Allowed_Str = s;
        }

        @Override
        public String Chars_Not_Allowed_Str_Get() {
            return Chars_Not_Allowed_Str;
        }

        @Override
        public void Input_Mode_Set(Input_Mode_Type input_mode) {
            Input_Mode = input_mode;
        }

        @Override
        public Input_Mode_Type Input_Mode_Get() {
            return Input_Mode;
        }

        @Override
        public boolean Input_Init() {
            return false;
        }

        @Override
        public boolean Input_Restore() {
            return false;
        }

        @Override
        public boolean Input_Clear() {
            return false;
        }

        @Override
        public String Invitation_Full_Get() { // Attention: Should be used for print cli invitation
            return Prompt_Str;
        }

        @Override
        public void Invitation_Print() {
        }

        @Override
        public String Input_Str_Get() {
            return Input_Str;
        }

        @Override
        public void Input_Str_Set(String s) {
            Input_Str = s;
        }

        @Override
        public void Input_Str_Set_Empty() {
            Input_Str = "";
            Input_Str_Pos = 0;
        }

        @Override
        public void Wait_Count_Set(int v) {
            Wait_Count = v;
        }

        @Override
        public int Wait_Count_Get() {
            return Wait_Count;
        }

        @Override
        public void Input_Add_Char_To_End(String s) {
        }

        @Override
        public void Input_Add_Char_Middle(String s) {
        }

        @Override
        public void Input_Back() {
        }

        @Override
        public void Input_Delete() {
        }

        @Override
        public void Input_Str_To_Output() {
        }

        @Override
        public void Input_Str_Modified_To_Output(String s_prev) {
        }

        @Override
        public void Input_End() {
        }

        @Override
        protected void On_Key_RIGHT() {
        }

        @Override
        protected void On_Key_LEFT() {
        }

        @Override
        protected void On_Key_HOME() {
        }

        @Override
        protected void On_Key_END() {
        }

        @Override
        protected void On_Key_BACK() {
        }

        @Override
        protected void On_Key_DELETE() {
        }

        @Override
        protected void On_Key_CTRL_C() {
        }

        @Override
        protected void On_Key_CTRL_Z() {
        }

        @Override
        protected void On_Key_CTRL_Backslash() {
        }

        @Override
        public boolean Is_Char_Valid(String char_str) {
            if (!Chars_Not_Allowed_Str.isEmpty()) {
                if (Chars_Not_Allowed_Str.contains(char_str)) {
                    return false;
                }
            }
            return true;
        }

        @Override
        protected boolean On_Key_Any(String s) {
            return true;
        }

        @Override
        public Cli_Input_Item On_Key_Pressed(KeyEvent event) {
            Cli_Input_Item item = null;
            return item;
        }

        @Override
        public void Input_sleep(int sleep_sec) {
        }

    }

    class Test_Item {

        String Level;
        String Cmd_Text;
        Cmd_Token_Parser_Result Parse_Res;
        List<TAB_Cmd> TAB_Cmd_List;

        Test_Item(String level, String cmd_text, Cmd_Token_Parser_Result parse_res, List<TAB_Cmd> tab_cmd_list) {
            Level = level;
            Cmd_Text = cmd_text;
            Parse_Res = parse_res;
            TAB_Cmd_List = tab_cmd_list;
        }
    }

    final Test_Item[] test_items = {
        // "test terminal"
        new Test_Item("", "test terminal", Cmd_Token_Parser_Result.CMD_TOKEN_PARSER_OK,
        new ArrayList<>(Arrays.asList(
        new TAB_Cmd(TAB_Cmd_ID.TAB_CMD_ID_LOG_PRINT, " <Enter>")
        ))),
        // end
        new Test_Item("test terminal", "end", Cmd_Token_Parser_Result.CMD_TOKEN_PARSER_OK,
        new ArrayList<>(Arrays.asList(
        new TAB_Cmd(TAB_Cmd_ID.TAB_CMD_ID_LOG_PRINT, " <Enter>")
        ))),
        // test
        new Test_Item("test terminal", "test", Cmd_Token_Parser_Result.CMD_TOKEN_PARSER_OK,
        new ArrayList<>(Arrays.asList(
        new TAB_Cmd(TAB_Cmd_ID.TAB_CMD_ID_LOG_PRINT, " <Enter>")
        ))),
        // get
        new Test_Item("test terminal", "get", Cmd_Token_Parser_Result.CMD_TOKEN_PARSER_OK,
        new ArrayList<>(Arrays.asList(
        new TAB_Cmd(TAB_Cmd_ID.TAB_CMD_ID_LOG_PRINT, " all <Enter>"),
        new TAB_Cmd(TAB_Cmd_ID.TAB_CMD_ID_INPUT_CHECK_SPACE, "")
        ))),
        // get all
        new Test_Item("test terminal", "get all", Cmd_Token_Parser_Result.CMD_TOKEN_PARSER_OK,
        new ArrayList<>(Arrays.asList(
        new TAB_Cmd(TAB_Cmd_ID.TAB_CMD_ID_LOG_PRINT, " <Enter>")
        ))),

        // s -> set //@Warning: There is only one variant in this test
        new Test_Item("test terminal", "s", Cmd_Token_Parser_Result.CMD_TOKEN_PARSER_OK,
        new ArrayList<>(Arrays.asList(
        new TAB_Cmd(TAB_Cmd_ID.TAB_CMD_ID_INPUT_ADD, "et"),
        new TAB_Cmd(TAB_Cmd_ID.TAB_CMD_ID_INPUT_CHECK_SPACE, "")
        ))),
        // se -> set //@Warning: There is only one variant in this test
        new Test_Item("test terminal", "se", Cmd_Token_Parser_Result.CMD_TOKEN_PARSER_OK,
        new ArrayList<>(Arrays.asList(
        new TAB_Cmd(TAB_Cmd_ID.TAB_CMD_ID_INPUT_ADD, "t"),
        new TAB_Cmd(TAB_Cmd_ID.TAB_CMD_ID_INPUT_CHECK_SPACE, "")
        ))),
        // set
        new Test_Item("test terminal", "set", Cmd_Token_Parser_Result.CMD_TOKEN_PARSER_OK,
        new ArrayList<>(Arrays.asList(
        new TAB_Cmd(TAB_Cmd_ID.TAB_CMD_ID_LOG_PRINT, " int range list str date time datetime ip4 mask ip6 mac <enable|disable|else> loopback"),
        new TAB_Cmd(TAB_Cmd_ID.TAB_CMD_ID_INPUT_CHECK_SPACE, "")
        ))),

        // set int <int_value>
        new Test_Item("test terminal", "set int 1", Cmd_Token_Parser_Result.CMD_TOKEN_PARSER_OK,
        new ArrayList<>(Arrays.asList(
        new TAB_Cmd(TAB_Cmd_ID.TAB_CMD_ID_LOG_PRINT, " <Enter>")
        ))),
        // set range <1..4095>
        new Test_Item("test terminal", "set range 2", Cmd_Token_Parser_Result.CMD_TOKEN_PARSER_OK,
        new ArrayList<>(Arrays.asList(
        new TAB_Cmd(TAB_Cmd_ID.TAB_CMD_ID_LOG_PRINT, " <Enter>")
        ))),
        // set list <1-4095>
        new Test_Item("test terminal", "set list 1-2", Cmd_Token_Parser_Result.CMD_TOKEN_PARSER_OK,
        new ArrayList<>(Arrays.asList(
        new TAB_Cmd(TAB_Cmd_ID.TAB_CMD_ID_LOG_PRINT, " , <Enter>")
        ))),
        // set list <1-4095>
        new Test_Item("test terminal", "set list 1-2 ", Cmd_Token_Parser_Result.CMD_TOKEN_PARSER_OK,
        new ArrayList<>(Arrays.asList(
        new TAB_Cmd(TAB_Cmd_ID.TAB_CMD_ID_LOG_PRINT, " <Enter>")
        ))),
        // set str <str>
        new Test_Item("test terminal", "set str a", Cmd_Token_Parser_Result.CMD_TOKEN_PARSER_OK,
        new ArrayList<>(Arrays.asList(
        new TAB_Cmd(TAB_Cmd_ID.TAB_CMD_ID_LOG_PRINT, " <str> <Enter>")
        ))),
        // set str <str>
        new Test_Item("test terminal", "set str a ", Cmd_Token_Parser_Result.CMD_TOKEN_PARSER_OK,
        new ArrayList<>(Arrays.asList(
        new TAB_Cmd(TAB_Cmd_ID.TAB_CMD_ID_LOG_PRINT, " <Enter>")
        ))),
        // set <enable disable else>
        new Test_Item("test terminal", "set else", Cmd_Token_Parser_Result.CMD_TOKEN_PARSER_OK,
        new ArrayList<>(Arrays.asList(
        new TAB_Cmd(TAB_Cmd_ID.TAB_CMD_ID_LOG_PRINT, " <Enter>")
        ))),
        // set loopback [raw,net,local,remote]
        new Test_Item("test terminal", "set loopback raw", Cmd_Token_Parser_Result.CMD_TOKEN_PARSER_OK,
        new ArrayList<>(Arrays.asList(
        new TAB_Cmd(TAB_Cmd_ID.TAB_CMD_ID_LOG_PRINT, " , <Enter>")
        ))),
        // set loopback [raw,net,local,remote]
        new Test_Item("test terminal", "set loopback raw ", Cmd_Token_Parser_Result.CMD_TOKEN_PARSER_OK,
        new ArrayList<>(Arrays.asList(
        new TAB_Cmd(TAB_Cmd_ID.TAB_CMD_ID_LOG_PRINT, " <Enter>")
        ))),
        // set loopback disable
        new Test_Item("test terminal", "set loopback disable", Cmd_Token_Parser_Result.CMD_TOKEN_PARSER_OK,
        new ArrayList<>(Arrays.asList(
        new TAB_Cmd(TAB_Cmd_ID.TAB_CMD_ID_LOG_PRINT, " <Enter>")
        ))),
        //set loopback repeating [raw,net,local,remote]
        new Test_Item("test terminal", "set loopback repeating raw", Cmd_Token_Parser_Result.CMD_TOKEN_PARSER_OK,
        new ArrayList<>(Arrays.asList(
        new TAB_Cmd(TAB_Cmd_ID.TAB_CMD_ID_LOG_PRINT, " , <Enter>")
        ))),
        //set loopback repeating [raw,net,local,remote]
        new Test_Item("test terminal", "set loopback repeating raw ", Cmd_Token_Parser_Result.CMD_TOKEN_PARSER_OK,
        new ArrayList<>(Arrays.asList(
        new TAB_Cmd(TAB_Cmd_ID.TAB_CMD_ID_LOG_PRINT, " <Enter>")
        ))),
        // set loopback repeating disable
        new Test_Item("test terminal", "set loopback repeating disable", Cmd_Token_Parser_Result.CMD_TOKEN_PARSER_OK,
        new ArrayList<>(Arrays.asList(
        new TAB_Cmd(TAB_Cmd_ID.TAB_CMD_ID_LOG_PRINT, " <Enter>")
        ))),
        // phy <phy_num> set speed <auto 10 100 1000> duplex <auto full half>
        new Test_Item("test terminal", "phy 3-4 set speed 1000 duplex auto", Cmd_Token_Parser_Result.CMD_TOKEN_PARSER_OK,
        new ArrayList<>(Arrays.asList(
        new TAB_Cmd(TAB_Cmd_ID.TAB_CMD_ID_LOG_PRINT, " <Enter>")
        )))
    };

    @Test
    public void Test() {

        System.out.println("");
        System.out.println(Test_Name + ":");

        Ref_Cli_Cmd_Privilege_ID User_Privilege = new Ref_Cli_Cmd_Privilege_ID(Cli_Cmd_Privilege_ID.CMD_PRIVILEGE_ROOT_DEF);
        List<Level_Description> Levels = new ArrayList<>();
        Cmd_Token_Parser Token_Parser = new Cmd_Token_Parser();
        Cli_Output_JavaFX_Mock Cli_Output = new Cli_Output_JavaFX_Mock();
        String Chars_Not_Allowed_Str = "@`|";
        Cli_Input_JavaFX_Mock Cli_Input = new Cli_Input_JavaFX_Mock(Cli_Output, Chars_Not_Allowed_Str);
        String Str_Rem_DEF = "$";

        Cli_Modules Modules = new Cli_Modules();

        Modules.Module_Add(new Cli_Module_Test_Terminal(Cli_Input, Cli_Output));

        boolean tab_log_is_active = false;
        Cli_TAB_Processor TAB_Processor = new Cli_TAB_Processor(User_Privilege, Modules, Levels, Token_Parser, Cli_Input, Cli_Output, Str_Rem_DEF, tab_log_is_active);

        boolean test_res_total = true; // Ok
        int test_res_total_count_failed = 0;

        for (int test_item_index = 0; test_item_index < test_items.length; test_item_index++) {

            boolean test_res = true; // Ok

            Test_Item test_item = test_items[test_item_index];

            String level = test_item.Level;
            Cli_Input_Item input_item = new Cli_Input_Item(Input_Cmd_Type.INPUT_CMD_TAB, test_item.Cmd_Text);
            String s_trim = input_item.Text_Get().trim();

            Cmd_Token_Parser_Result parse_res = Cmd_Token_Parser_Result.CMD_TOKEN_PARSER_ERROR;

            List<Cmd_Token> tokens = Token_Parser.Parse(s_trim, Str_Rem_DEF, parse_res);

            System.out.println("");
            System.out.println("Cmd[" + Integer.toString(test_item_index) + "]:" + " [" + level + "] " + s_trim);

            List<TAB_Cmd> tab_cmd_list = TAB_Processor.TAB_Cmd_List_Get(User_Privilege.Value, Modules, level, input_item.Text_Get(), s_trim, tokens);

            if (tab_cmd_list != null) {
                //System.out.println("tab_cmd_list[" + Integer.toString(tab_cmd_list.size()) + "]:");
                int size_max = Math.max(test_item.TAB_Cmd_List.size(), tab_cmd_list.size());
                for (int i = 0; i < size_max; i++) {
                    StringBuilder sb = new StringBuilder();
                    TAB_Cmd tab_cmd1 = null;
                    TAB_Cmd tab_cmd2 = null;
                    if (i < test_item.TAB_Cmd_List.size()) {
                        tab_cmd1 = test_item.TAB_Cmd_List.get(i);
                    }
                    if (i < tab_cmd_list.size()) {
                        tab_cmd2 = tab_cmd_list.get(i);
                    }
                    if (tab_cmd1 != null) {
                        sb.append("TAB_Cmd[");
                        sb.append(i);
                        sb.append("] ");
                        sb.append(TAB_Cmd_ID_Func.To_Str(tab_cmd1.ID));
                        sb.append(" \"");
                        sb.append(tab_cmd1.Text);
                        sb.append("\"");
                    } else {
                        sb.append("<null>");
                        test_res = false; // Failed
                    }
                    if (tab_cmd1 != null && tab_cmd2 != null) {
                        if (tab_cmd1.ID == tab_cmd2.ID && tab_cmd1.Text.equals(tab_cmd2.Text)) {
                            sb.append(" == ");
                        } else {
                            sb.append(" != ");
                            test_res = false; // Failed
                        }
                    }
                    if (tab_cmd2 != null) {
                        sb.append("TAB_Cmd[");
                        sb.append(i);
                        sb.append("] ");
                        sb.append(TAB_Cmd_ID_Func.To_Str(tab_cmd2.ID));
                        sb.append(" \"");
                        sb.append(tab_cmd2.Text);
                        sb.append("\"");
                    } else {
                        sb.append("<null>");
                        test_res = false; // Failed
                    }
                    sb.append(test_res ? " - Ok" : " - Failed");
                    System.out.println(sb.toString());
                }
            } else {
                System.out.println("tab_cmd_list: null");
            }

            if (!test_res) {
                test_res_total = false; // Failed
                test_res_total_count_failed++;
            }

        }

        String res_str;
        if (test_res_total) {
            res_str = Test_Name + " - Ok (" + Integer.toString(test_items.length) + ")\n";
        } else {
            res_str = Test_Name + " - Failed (" + Integer.toString(test_res_total_count_failed) + " of " + Integer.toString(test_items.length) + ")\n";
        }
        System.out.println("");
        System.out.println(res_str);
        System.out.println("");
        if (!test_res_total) {
            fail(res_str);
        }

    }

}
