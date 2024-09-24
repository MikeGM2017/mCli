/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cli_core_javafx_test;

/**
 *
 * @author mike
 */
public class Str_Get_Without_Commas {

    public String Get(String value_str) {
        String s = value_str;
        if (value_str.length() >= 2) {
            if ((value_str.charAt(0) == '\"' && value_str.charAt(value_str.length() - 1) == '\"')
                    || (value_str.charAt(0) == '\'' && value_str.charAt(value_str.length() - 1) == '\'')) {
                s = value_str.substring(1, value_str.length() - 1);
            }
        }
        return s;
    }

}
