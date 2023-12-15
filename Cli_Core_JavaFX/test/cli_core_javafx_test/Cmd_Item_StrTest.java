/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cli_core_javafx_test;

import org.junit.Test;
import static org.junit.Assert.*;

/**
 *
 * @author mike
 */
public class Cmd_Item_StrTest {

    String Test_Name = this.getClass().getSimpleName();

    Cmd_Item_Str v = new Cmd_Item_Str("", "");

    class Cmd_Item_Test_Pair {

        String Text;
        Cmd_Item_Valid_Result Res;

        Cmd_Item_Test_Pair(String text, Cmd_Item_Valid_Result res) {
            Text = text;
            Res = res;
        }
    }

    class Cmd_Item_Str_Test_Item {

        String S_in;
        String S_out;
        Cmd_Item_Valid_Result Res_out;

        Cmd_Item_Str_Test_Item(String s_in, String s_out, Cmd_Item_Valid_Result res_out) {
            S_in = s_in;
            S_out = s_out;
            Res_out = res_out;
        }

    };

    final Cmd_Item_Test_Pair[] test_items = {
        new Cmd_Item_Test_Pair("", Cmd_Item_Valid_Result.CMD_ITEM_EMPTY),
        new Cmd_Item_Test_Pair("\"<str>\"", Cmd_Item_Valid_Result.CMD_ITEM_OK),
        new Cmd_Item_Test_Pair("\"  <str1>   <str2>    \"", Cmd_Item_Valid_Result.CMD_ITEM_OK),
        new Cmd_Item_Test_Pair("\"\"", Cmd_Item_Valid_Result.CMD_ITEM_OK),
        new Cmd_Item_Test_Pair("\"", Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE_STR),
        new Cmd_Item_Test_Pair("\"<str>", Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE_STR),
        new Cmd_Item_Test_Pair("<str>\"", Cmd_Item_Valid_Result.CMD_ITEM_ERROR),
        new Cmd_Item_Test_Pair("FF:FF:FF:FF:FF:FF", Cmd_Item_Valid_Result.CMD_ITEM_OK_STR_WITHOUT_COMMAS),
        new Cmd_Item_Test_Pair("<str>'", Cmd_Item_Valid_Result.CMD_ITEM_ERROR),
        // Escaped:
        new Cmd_Item_Test_Pair("\\\"Str\\\"", Cmd_Item_Valid_Result.CMD_ITEM_OK_STR_WITHOUT_COMMAS)
    };

    final Cmd_Item_Str_Test_Item[] test_items2 = {
        new Cmd_Item_Str_Test_Item("", "", Cmd_Item_Valid_Result.CMD_ITEM_EMPTY),
        new Cmd_Item_Str_Test_Item("\"<str>\"", "\"<str>\"", Cmd_Item_Valid_Result.CMD_ITEM_OK),
        new Cmd_Item_Str_Test_Item("\"  <str1>   <str2>    \"", "\"  <str1>   <str2>    \"", Cmd_Item_Valid_Result.CMD_ITEM_OK),
        new Cmd_Item_Str_Test_Item("\"\"", "", Cmd_Item_Valid_Result.CMD_ITEM_OK),
        new Cmd_Item_Str_Test_Item("\"", "\"", Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE_STR),
        new Cmd_Item_Str_Test_Item("\"<str>", "\"<str>", Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE_STR),
        new Cmd_Item_Str_Test_Item("<str>\"", "<str>\"", Cmd_Item_Valid_Result.CMD_ITEM_ERROR),
        new Cmd_Item_Str_Test_Item("FF:FF:FF:FF:FF:FF", "FF:FF:FF:FF:FF:FF", Cmd_Item_Valid_Result.CMD_ITEM_OK_STR_WITHOUT_COMMAS),
        new Cmd_Item_Str_Test_Item("<str>'", "<str>'", Cmd_Item_Valid_Result.CMD_ITEM_ERROR),
        // Escaped:
        new Cmd_Item_Str_Test_Item("\\\"Str\\\"", "\\\"Str\\\"", Cmd_Item_Valid_Result.CMD_ITEM_OK_STR_WITHOUT_COMMAS)
    };

    @Test
    public void Test() {
        System.out.println(Test_Name + ":");
        Boolean test_res_total = true; // Ok
        int test_res_total_count_failed = 0; // Ok
        for (int i = 0; i < test_items.length; i++) {
            Cmd_Item_Test_Pair test_item = test_items[i];
            Cmd_Item_Valid_Result res_cmd_valid = v.Parse(test_item.Text);
            StringBuilder sb = new StringBuilder();
            sb.append("[");
            sb.append(Integer.toString(i));
            sb.append("] ");
            sb.append("Test Str: \"");
            sb.append(test_item.Text);
            sb.append("\" res: \"");
            sb.append(Cmd_Item_Valid_Result_Func.To_String(res_cmd_valid));
            sb.append("\" ");
            Boolean test_res = (res_cmd_valid == test_item.Res);
            if (test_res) {
                sb.append("== \"");
            } else {
                sb.append("!= \"");
            }
            sb.append(Cmd_Item_Valid_Result_Func.To_String(test_item.Res));
            sb.append("\"");
            if (test_res) {
                sb.append(" - Ok");
            } else {
                sb.append("- Failed");
            }
            if (!test_res) {
                test_res_total = false; // Failed
                test_res_total_count_failed++;
            }
            System.out.println(sb.toString());
        }
        String res_str;
        if (test_res_total) {
            res_str = Test_Name + " - Ok (" + Integer.toString(test_items.length) + ")\n";
        } else {
            res_str = Test_Name + " - Failed (" + Integer.toString(test_res_total_count_failed) + " of " + Integer.toString(test_items.length) + ")\n";
        }
        System.out.println(res_str);
        if (!test_res_total) {
            fail(res_str);
        }
    }

    @Test
    public void Test2() {
        System.out.println(Test_Name + "2:");
        Boolean test_res_total = true; // Ok
        int test_res_total_count_failed = 0; // Ok
        for (int i = 0; i < test_items2.length; i++) {
            Cmd_Item_Str_Test_Item test_item = test_items2[i];
            Cmd_Item_Valid_Result res_cmd_valid = v.Parse(test_item.S_in);
            StringBuilder sb = new StringBuilder();
            sb.append("[");
            sb.append(Integer.toString(i));
            sb.append("] ");
            sb.append("Test Str: \"");
            sb.append(test_item.S_in);
            sb.append("\" ");
            Boolean test_res = (res_cmd_valid == test_item.Res_out) && (v.Value_Str.equals(test_item.S_out));
            if (v.Value_Str.equals(test_item.S_out)) {
                sb.append("== \"");
            } else {
                sb.append("!= \"");
            }
            sb.append(test_item.S_out);
            sb.append("\"");
            sb.append(" res: \"");
            sb.append(Cmd_Item_Valid_Result_Func.To_String(res_cmd_valid));
            sb.append("\"");
            if (res_cmd_valid == test_item.Res_out) {
                sb.append("== \"");
            } else {
                sb.append("!= \"");
            }
            sb.append(Cmd_Item_Valid_Result_Func.To_String(test_item.Res_out));
            sb.append("\"");
            if (test_res) {
                sb.append(" - Ok");
            } else {
                sb.append("- Failed");
            }
            if (!test_res) {
                test_res_total = false; // Failed
                test_res_total_count_failed++;
            }
            System.out.println(sb.toString());
        }
        String res_str;
        if (test_res_total) {
            res_str = Test_Name + " - Ok (" + Integer.toString(test_items2.length) + ")\n";
        } else {
            res_str = Test_Name + " - Failed (" + Integer.toString(test_res_total_count_failed) + " of " + Integer.toString(test_items2.length) + ")\n";
        }
        System.out.println(res_str);
        if (!test_res_total) {
            fail(res_str);
        }
    }

}
