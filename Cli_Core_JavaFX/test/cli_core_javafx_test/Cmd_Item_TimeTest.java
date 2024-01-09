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
public class Cmd_Item_TimeTest {

    String Test_Name = this.getClass().getSimpleName();

    Cmd_Item_Time v = new Cmd_Item_Time("", "");

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
        new Cmd_Item_Test_Pair("\"12-01-33\"", Cmd_Item_Valid_Result.CMD_ITEM_OK),
        new Cmd_Item_Test_Pair("\"12-01\"", Cmd_Item_Valid_Result.CMD_ITEM_OK),
        new Cmd_Item_Test_Pair("\"15-03", Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE_STR),
        new Cmd_Item_Test_Pair("\"15-03-", Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE_STR),
        new Cmd_Item_Test_Pair("\"15-03-4", Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE_STR),
        new Cmd_Item_Test_Pair("\"15-03-44", Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE_STR),
        new Cmd_Item_Test_Pair("\"1\"", Cmd_Item_Valid_Result.CMD_ITEM_ERROR),
        new Cmd_Item_Test_Pair("\"15\"", Cmd_Item_Valid_Result.CMD_ITEM_ERROR),
        new Cmd_Item_Test_Pair("\"15-\"", Cmd_Item_Valid_Result.CMD_ITEM_ERROR),
        new Cmd_Item_Test_Pair("\"15-0\"", Cmd_Item_Valid_Result.CMD_ITEM_ERROR),
        new Cmd_Item_Test_Pair("\"15-03\"", Cmd_Item_Valid_Result.CMD_ITEM_OK),
        new Cmd_Item_Test_Pair("\"15-03-\"", Cmd_Item_Valid_Result.CMD_ITEM_ERROR),
        new Cmd_Item_Test_Pair("\"15-03-4\"", Cmd_Item_Valid_Result.CMD_ITEM_ERROR),
        new Cmd_Item_Test_Pair("\"00-00-00\"", Cmd_Item_Valid_Result.CMD_ITEM_OK), // TIME MIN
        new Cmd_Item_Test_Pair("\"24-00-00\"", Cmd_Item_Valid_Result.CMD_ITEM_OUT_OF_RANGE),
        new Cmd_Item_Test_Pair("\"00-60-00\"", Cmd_Item_Valid_Result.CMD_ITEM_OUT_OF_RANGE),
        new Cmd_Item_Test_Pair("\"00-00-60\"", Cmd_Item_Valid_Result.CMD_ITEM_OUT_OF_RANGE),
        new Cmd_Item_Test_Pair("\"23-59-59\"", Cmd_Item_Valid_Result.CMD_ITEM_OK), // TIME MAX
        new Cmd_Item_Test_Pair("\"24-59-59\"", Cmd_Item_Valid_Result.CMD_ITEM_OUT_OF_RANGE),
        new Cmd_Item_Test_Pair("\"23-60-59\"", Cmd_Item_Valid_Result.CMD_ITEM_OUT_OF_RANGE),
        new Cmd_Item_Test_Pair("\"23-59-60\"", Cmd_Item_Valid_Result.CMD_ITEM_OUT_OF_RANGE),
        new Cmd_Item_Test_Pair("\"23:59:59\"", Cmd_Item_Valid_Result.CMD_ITEM_OK)
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
