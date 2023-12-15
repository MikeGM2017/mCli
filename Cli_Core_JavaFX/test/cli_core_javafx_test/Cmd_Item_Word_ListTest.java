/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cli_core_javafx_test;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import org.junit.Test;
import static org.junit.Assert.*;

/**
 *
 * @author mike
 */
public class Cmd_Item_Word_ListTest {

    String Test_Name = this.getClass().getSimpleName();

    List<String> words1 = new ArrayList<>(Arrays.asList("raw", "net", "local", "remote"));
    boolean is_repeating1 = false;
    Cmd_Item_Word_List v1 = new Cmd_Item_Word_List("[raw,net,local,remote]", "test: set loopback [raw,net,local,remote]", words1, is_repeating1);

    List<String> words2 = new ArrayList<>(Arrays.asList("raw", "net", "local", "remote"));
    boolean is_repeating2 = true;
    Cmd_Item_Word_List v2 = new Cmd_Item_Word_List("[raw,net,local,remote]", "test: set loopback [raw,net,local,remote]", words2, is_repeating2);

    class Cmd_Item_Test_Pair {

        String Text;
        Cmd_Item_Valid_Result Res;

        Cmd_Item_Test_Pair(String text, Cmd_Item_Valid_Result res) {
            Text = text;
            Res = res;
        }
    }

    final Cmd_Item_Test_Pair[] test_items1 = {
        new Cmd_Item_Test_Pair("", Cmd_Item_Valid_Result.CMD_ITEM_EMPTY),
        new Cmd_Item_Test_Pair("raw", Cmd_Item_Valid_Result.CMD_ITEM_OK_CAN_CONTINUE),
        new Cmd_Item_Test_Pair("net", Cmd_Item_Valid_Result.CMD_ITEM_OK_CAN_CONTINUE),
        new Cmd_Item_Test_Pair("local", Cmd_Item_Valid_Result.CMD_ITEM_OK_CAN_CONTINUE),
        new Cmd_Item_Test_Pair("remote", Cmd_Item_Valid_Result.CMD_ITEM_OK_CAN_CONTINUE),
        new Cmd_Item_Test_Pair("raw,net,local,remote", Cmd_Item_Valid_Result.CMD_ITEM_OK),
        new Cmd_Item_Test_Pair("raw,net,local", Cmd_Item_Valid_Result.CMD_ITEM_OK_CAN_CONTINUE),
        new Cmd_Item_Test_Pair("raw,net", Cmd_Item_Valid_Result.CMD_ITEM_OK_CAN_CONTINUE),
        new Cmd_Item_Test_Pair("r", Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE),
        new Cmd_Item_Test_Pair("ra", Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE),
        new Cmd_Item_Test_Pair("n", Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE),
        new Cmd_Item_Test_Pair("ne", Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE),
        new Cmd_Item_Test_Pair("l", Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE),
        new Cmd_Item_Test_Pair("lo", Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE),
        new Cmd_Item_Test_Pair("loc", Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE),
        new Cmd_Item_Test_Pair("loca", Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE),
        new Cmd_Item_Test_Pair("r", Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE),
        new Cmd_Item_Test_Pair("re", Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE),
        new Cmd_Item_Test_Pair("rem", Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE),
        new Cmd_Item_Test_Pair("remo", Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE),
        new Cmd_Item_Test_Pair("remot", Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE),
        new Cmd_Item_Test_Pair("raw,", Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE),
        new Cmd_Item_Test_Pair("net,", Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE),
        new Cmd_Item_Test_Pair("local,", Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE),
        new Cmd_Item_Test_Pair("remote,", Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE),
        new Cmd_Item_Test_Pair("raw,n", Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE),
        new Cmd_Item_Test_Pair("net,l", Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE),
        new Cmd_Item_Test_Pair("local,r", Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE),
        new Cmd_Item_Test_Pair("remote,r", Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE),
        new Cmd_Item_Test_Pair("raw,raw", Cmd_Item_Valid_Result.CMD_ITEM_ERROR),
        new Cmd_Item_Test_Pair("net,net", Cmd_Item_Valid_Result.CMD_ITEM_ERROR),
        new Cmd_Item_Test_Pair("local,local", Cmd_Item_Valid_Result.CMD_ITEM_ERROR),
        new Cmd_Item_Test_Pair("remote,remote", Cmd_Item_Valid_Result.CMD_ITEM_ERROR),
        new Cmd_Item_Test_Pair("rawz", Cmd_Item_Valid_Result.CMD_ITEM_ERROR),
        new Cmd_Item_Test_Pair("netz", Cmd_Item_Valid_Result.CMD_ITEM_ERROR),
        new Cmd_Item_Test_Pair("localz", Cmd_Item_Valid_Result.CMD_ITEM_ERROR),
        new Cmd_Item_Test_Pair("remotez", Cmd_Item_Valid_Result.CMD_ITEM_ERROR),
        new Cmd_Item_Test_Pair("e", Cmd_Item_Valid_Result.CMD_ITEM_ERROR),
        new Cmd_Item_Test_Pair("enb", Cmd_Item_Valid_Result.CMD_ITEM_ERROR),
        new Cmd_Item_Test_Pair("enableb", Cmd_Item_Valid_Result.CMD_ITEM_ERROR),
        new Cmd_Item_Test_Pair("disb", Cmd_Item_Valid_Result.CMD_ITEM_ERROR)
    };

    final Cmd_Item_Test_Pair[] test_items2 = {
        new Cmd_Item_Test_Pair("", Cmd_Item_Valid_Result.CMD_ITEM_EMPTY),
        new Cmd_Item_Test_Pair("raw", Cmd_Item_Valid_Result.CMD_ITEM_OK_CAN_CONTINUE),
        new Cmd_Item_Test_Pair("net", Cmd_Item_Valid_Result.CMD_ITEM_OK_CAN_CONTINUE),
        new Cmd_Item_Test_Pair("local", Cmd_Item_Valid_Result.CMD_ITEM_OK_CAN_CONTINUE),
        new Cmd_Item_Test_Pair("remote", Cmd_Item_Valid_Result.CMD_ITEM_OK_CAN_CONTINUE),
        new Cmd_Item_Test_Pair("raw,net,local,remote", Cmd_Item_Valid_Result.CMD_ITEM_OK_CAN_CONTINUE),
        new Cmd_Item_Test_Pair("raw,net,local", Cmd_Item_Valid_Result.CMD_ITEM_OK_CAN_CONTINUE),
        new Cmd_Item_Test_Pair("raw,net", Cmd_Item_Valid_Result.CMD_ITEM_OK_CAN_CONTINUE),
        new Cmd_Item_Test_Pair("r", Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE),
        new Cmd_Item_Test_Pair("ra", Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE),
        new Cmd_Item_Test_Pair("n", Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE),
        new Cmd_Item_Test_Pair("ne", Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE),
        new Cmd_Item_Test_Pair("l", Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE),
        new Cmd_Item_Test_Pair("lo", Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE),
        new Cmd_Item_Test_Pair("loc", Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE),
        new Cmd_Item_Test_Pair("loca", Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE),
        new Cmd_Item_Test_Pair("r", Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE),
        new Cmd_Item_Test_Pair("re", Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE),
        new Cmd_Item_Test_Pair("rem", Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE),
        new Cmd_Item_Test_Pair("remo", Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE),
        new Cmd_Item_Test_Pair("remot", Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE),
        new Cmd_Item_Test_Pair("raw,", Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE),
        new Cmd_Item_Test_Pair("net,", Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE),
        new Cmd_Item_Test_Pair("local,", Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE),
        new Cmd_Item_Test_Pair("remote,", Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE),
        new Cmd_Item_Test_Pair("raw,n", Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE),
        new Cmd_Item_Test_Pair("net,l", Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE),
        new Cmd_Item_Test_Pair("local,r", Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE),
        new Cmd_Item_Test_Pair("remote,r", Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE),
        new Cmd_Item_Test_Pair("raw,raw", Cmd_Item_Valid_Result.CMD_ITEM_OK_CAN_CONTINUE),//Cmd_Item_Valid_Result.CMD_ITEM_ERROR), // @Attention: Can Repeat
        new Cmd_Item_Test_Pair("net,net", Cmd_Item_Valid_Result.CMD_ITEM_OK_CAN_CONTINUE),//Cmd_Item_Valid_Result.CMD_ITEM_ERROR), // @Attention: Can Repeat
        new Cmd_Item_Test_Pair("local,local", Cmd_Item_Valid_Result.CMD_ITEM_OK_CAN_CONTINUE),//Cmd_Item_Valid_Result.CMD_ITEM_ERROR), // @Attention: Can Repeat
        new Cmd_Item_Test_Pair("remote,remote", Cmd_Item_Valid_Result.CMD_ITEM_OK_CAN_CONTINUE),//Cmd_Item_Valid_Result.CMD_ITEM_ERROR), // @Attention: Can Repeat

        new Cmd_Item_Test_Pair("rawz", Cmd_Item_Valid_Result.CMD_ITEM_ERROR),
        new Cmd_Item_Test_Pair("netz", Cmd_Item_Valid_Result.CMD_ITEM_ERROR),
        new Cmd_Item_Test_Pair("localz", Cmd_Item_Valid_Result.CMD_ITEM_ERROR),
        new Cmd_Item_Test_Pair("remotez", Cmd_Item_Valid_Result.CMD_ITEM_ERROR),
        new Cmd_Item_Test_Pair("e", Cmd_Item_Valid_Result.CMD_ITEM_ERROR),
        new Cmd_Item_Test_Pair("enb", Cmd_Item_Valid_Result.CMD_ITEM_ERROR),
        new Cmd_Item_Test_Pair("enableb", Cmd_Item_Valid_Result.CMD_ITEM_ERROR),
        new Cmd_Item_Test_Pair("disb", Cmd_Item_Valid_Result.CMD_ITEM_ERROR)
    };

    @Test
    public void Test1() {
        System.out.println(Test_Name + "(\"" + v1.Text + "\"):");
        Boolean test_res_total = true; // Ok
        int test_res_total_count_failed = 0; // Ok
        for (int i = 0; i < test_items1.length; i++) {
            Cmd_Item_Test_Pair test_item = test_items1[i];
            Cmd_Item_Valid_Result res_cmd_valid = v1.Parse(test_item.Text);
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
            res_str = Test_Name + " - Ok (" + Integer.toString(test_items1.length) + ")\n";
        } else {
            res_str = Test_Name + " - Failed (" + Integer.toString(test_res_total_count_failed) + " of " + Integer.toString(test_items1.length) + ")\n";
        }
        System.out.println(res_str);
        if (!test_res_total) {
            fail(res_str);
        }
    }

    @Test
    public void Test2() {
        System.out.println(Test_Name + "(\"" + v2.Text + "\"):");
        Boolean test_res_total = true; // Ok
        int test_res_total_count_failed = 0; // Ok
        for (int i = 0; i < test_items1.length; i++) {
            Cmd_Item_Test_Pair test_item = test_items2[i];
            Cmd_Item_Valid_Result res_cmd_valid = v2.Parse(test_item.Text);
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
