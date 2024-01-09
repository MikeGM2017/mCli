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
public class Cmd_Item_DateTest {

    String Test_Name = this.getClass().getSimpleName();

    Cmd_Item_Date v = new Cmd_Item_Date("", "");

    class Cmd_Item_Test_Pair {

        String Text;
        Cmd_Item_Valid_Result Res;

        Cmd_Item_Test_Pair(String text, Cmd_Item_Valid_Result res) {
            Text = text;
            Res = res;
        }
    }

    final Cmd_Item_Test_Pair[] test_items = {
        new Cmd_Item_Test_Pair("", Cmd_Item_Valid_Result.CMD_ITEM_EMPTY),
        new Cmd_Item_Test_Pair("\"<str>\"", Cmd_Item_Valid_Result.CMD_ITEM_ERROR),
        new Cmd_Item_Test_Pair("\"\"", Cmd_Item_Valid_Result.CMD_ITEM_ERROR),
        new Cmd_Item_Test_Pair("\"", Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE_STR),
        new Cmd_Item_Test_Pair("\"<str>", Cmd_Item_Valid_Result.CMD_ITEM_ERROR),
        new Cmd_Item_Test_Pair("FF:FF:FF:FF:FF:FF", Cmd_Item_Valid_Result.CMD_ITEM_ERROR),
        new Cmd_Item_Test_Pair("\"2018-01-18\"", Cmd_Item_Valid_Result.CMD_ITEM_OK),
        new Cmd_Item_Test_Pair("\"2018-01-1\"", Cmd_Item_Valid_Result.CMD_ITEM_ERROR),
        new Cmd_Item_Test_Pair("\"2018-01-\"", Cmd_Item_Valid_Result.CMD_ITEM_ERROR),
        new Cmd_Item_Test_Pair("\"2018-01\"", Cmd_Item_Valid_Result.CMD_ITEM_ERROR),
        new Cmd_Item_Test_Pair("\"2018-01-1", Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE_STR),
        new Cmd_Item_Test_Pair("\"2018-01-", Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE_STR),
        new Cmd_Item_Test_Pair("\"2018-01", Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE_STR),
        new Cmd_Item_Test_Pair("\"2018-00-01\"", Cmd_Item_Valid_Result.CMD_ITEM_OUT_OF_RANGE),
        new Cmd_Item_Test_Pair("\"2018-13-01\"", Cmd_Item_Valid_Result.CMD_ITEM_OUT_OF_RANGE),
        new Cmd_Item_Test_Pair("\"2018-01-00\"", Cmd_Item_Valid_Result.CMD_ITEM_OUT_OF_RANGE),
        new Cmd_Item_Test_Pair("\"2018-01-32\"", Cmd_Item_Valid_Result.CMD_ITEM_OUT_OF_RANGE),
        new Cmd_Item_Test_Pair("\"0000-01-01\"", Cmd_Item_Valid_Result.CMD_ITEM_OK), // DATE MIN
        new Cmd_Item_Test_Pair("\"0000-00-01\"", Cmd_Item_Valid_Result.CMD_ITEM_OUT_OF_RANGE),
        new Cmd_Item_Test_Pair("\"0000-01-00\"", Cmd_Item_Valid_Result.CMD_ITEM_OUT_OF_RANGE),
        new Cmd_Item_Test_Pair("\"0000-13-01\"", Cmd_Item_Valid_Result.CMD_ITEM_OUT_OF_RANGE),
        new Cmd_Item_Test_Pair("\"0000-01-32\"", Cmd_Item_Valid_Result.CMD_ITEM_OUT_OF_RANGE),
        new Cmd_Item_Test_Pair("\"9999-12-31\"", Cmd_Item_Valid_Result.CMD_ITEM_OK), // DATE MAX
        new Cmd_Item_Test_Pair("\"9999-00-31\"", Cmd_Item_Valid_Result.CMD_ITEM_OUT_OF_RANGE),
        new Cmd_Item_Test_Pair("\"9999-12-32\"", Cmd_Item_Valid_Result.CMD_ITEM_OUT_OF_RANGE),
        new Cmd_Item_Test_Pair("\"9999-13-31\"", Cmd_Item_Valid_Result.CMD_ITEM_OUT_OF_RANGE),
        new Cmd_Item_Test_Pair("\"9999-12-32\"", Cmd_Item_Valid_Result.CMD_ITEM_OUT_OF_RANGE),
        new Cmd_Item_Test_Pair("\"2018:01:18\"", Cmd_Item_Valid_Result.CMD_ITEM_OK)
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

}
