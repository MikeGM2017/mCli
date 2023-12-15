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
public class Str_FilterTest {

    String Test_Name = this.getClass().getSimpleName();

    char C_Single = '?';
    char C_Multy = '*';
    Str_Filter str_filter = new Str_Filter(C_Single, C_Multy);

    class Str_Filter_Test_Item {

        String Text;
        String Filter;
        boolean Is_Match;

        Str_Filter_Test_Item(String text, String filter, boolean is_match) {
            Text = text;
            Filter = filter;
            Is_Match = is_match;
        }

    };

    final Str_Filter_Test_Item[] test_items = {
        new Str_Filter_Test_Item("", "", true),
        new Str_Filter_Test_Item("", "*", true),
        new Str_Filter_Test_Item("T", "*", true),
        new Str_Filter_Test_Item("Test", "*", true),
        new Str_Filter_Test_Item("Test", "?est", true),
        new Str_Filter_Test_Item("Test", "?e*", true),
        new Str_Filter_Test_Item("Test", "?e?t", true),
        new Str_Filter_Test_Item("Test", "*est", true),
        new Str_Filter_Test_Item("Test", "*st", true),
        new Str_Filter_Test_Item("Test", "*t", true),
        new Str_Filter_Test_Item("Test", "T*t", true),
        new Str_Filter_Test_Item("Test", "T??t", true),
        new Str_Filter_Test_Item("Test", "T*tx", false),
        new Str_Filter_Test_Item("Test", "T*x", false),
        new Str_Filter_Test_Item("Test", "T??tx", false),
        new Str_Filter_Test_Item("Test", "T??x", false),
        new Str_Filter_Test_Item("Test", "T*?t", true),
        new Str_Filter_Test_Item("Test", "T?*t", true),
        new Str_Filter_Test_Item("Login", "L?*?n", true),
        new Str_Filter_Test_Item("Looooper", "L?*r", true),
        new Str_Filter_Test_Item("Looooper", "L*p?r", true),
        new Str_Filter_Test_Item("Looooper", "*er", true),
        new Str_Filter_Test_Item("er", "*r*", true),
        new Str_Filter_Test_Item("Value_Str", "*tr*", true),
        new Str_Filter_Test_Item("Value_Str", "*tr", true),
        new Str_Filter_Test_Item("Value_Str", "*Val", false),
        new Str_Filter_Test_Item("[\"Test Terminal\"].Value_Str", "*tr", true),
        new Str_Filter_Test_Item("[\"Test Terminal\"].Value_Str", "*tr*", true),
        new Str_Filter_Test_Item("[\"Test Terminal\"].Value_Str", "*Val", false),
        new Str_Filter_Test_Item("help", "*uit", false)
    };

    @Test
    public void Test() {
        System.out.println(Test_Name + ":");
        Boolean test_res_total = true; // Ok
        int test_res_total_count_failed = 0; // Ok
        for (int i = 0; i < test_items.length; i++) {
            Str_Filter_Test_Item test_item = test_items[i];
            boolean res_match = str_filter.Is_Match(test_item.Filter, test_item.Text);
            StringBuilder sb = new StringBuilder();
            sb.append("[");
            sb.append(Integer.toString(i));
            sb.append("] ");
            sb.append("Test Str: \"");
            sb.append(test_item.Text);
            sb.append("\" res: \"");
            sb.append(res_match ? "Match" : "Not Match");
            sb.append("\" ");
            Boolean test_res = (res_match == test_item.Is_Match);
            if (test_res) {
                sb.append("== \"");
            } else {
                sb.append("!= \"");
            }
            sb.append(test_item.Is_Match ? "Match" : "Not Match");
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
