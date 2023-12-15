/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cli_core_javafx_test;

import java.net.Inet4Address;
import java.net.InetAddress;
import java.net.UnknownHostException;

/**
 *
 * @author mike
 */
public class Cmd_Item_IP4 extends Cmd_Item_Base {

    @Override
    protected boolean Is_Char_Valid(char c, int pos, int len) {
        if (c >= '0' && c <= '9') {
            return true;
        }
        if (pos >= 1 && c == '.') {
            return true;
        }
        return false;
    }

    Cmd_Item_IP4(String text, String help) {
        super(text, help);
        Type = "IP4";
    }

    @Override
    public String Debug_Value_Get() {
        return "1.2.3.4";
    }

    protected static boolean isIPv4(String input) {
        try {
            InetAddress inetAddress = InetAddress.getByName(input);
            return (inetAddress instanceof Inet4Address) && inetAddress.getHostAddress().equals(input);
        } catch (UnknownHostException ex) {
            return false;
        }
    }

    @Override
    public Cmd_Item_Valid_Result Parse(String s) {
        Value_Str = s;

        if (s.length() == 0) {
            return Cmd_Item_Valid_Result.CMD_ITEM_EMPTY;
        }

        for (int pos = 0; pos < s.length(); pos++) {
            if (!Is_Char_Valid(s.charAt(pos), pos, s.length())) {
                return Cmd_Item_Valid_Result.CMD_ITEM_ERROR;
            }
        }

        int pointCount = 0;
        int n = 0;
        int nCount = 0;
        boolean nPrev = false;
        boolean is_Point_Double = false;

        int nn_count = 0;
        for (int pos = 0; pos < s.length(); pos++) {
            char c = s.charAt(pos);
            if (c >= '0' && c <= '9') {
                n = n * 10 + c - '0';
                nn_count++;
                if (nn_count > 3) {
                    return Cmd_Item_Valid_Result.CMD_ITEM_ERROR;
                }
                if (n > 255) {
                    return Cmd_Item_Valid_Result.CMD_ITEM_OUT_OF_RANGE;
                }
                if (!nPrev) {
                    nPrev = true;
                    nCount++;
                }
            }
            if (c == '.') {
                if (!nPrev) {
                    is_Point_Double = true;
                }
                pointCount++;
                n = 0;
                nPrev = false;
                nn_count = 0;
            }
        }

        if (is_Point_Double) {
            return Cmd_Item_Valid_Result.CMD_ITEM_ERROR;
        }

        if (pointCount < 3) {
            return Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE_STR;
        }
        if (pointCount > 3) {
            return Cmd_Item_Valid_Result.CMD_ITEM_ERROR;
        }

        if (nCount < 4) {
            return Cmd_Item_Valid_Result.CMD_ITEM_INCOMPLETE_STR;
        }
        if (nCount > 4) {
            return Cmd_Item_Valid_Result.CMD_ITEM_ERROR;
        }

        boolean res_ipv4 = isIPv4(s);
        if (!res_ipv4) {
            return Cmd_Item_Valid_Result.CMD_ITEM_ERROR;
        }

        return Cmd_Item_Valid_Result.CMD_ITEM_OK;
    }

    @Override
    public boolean Is_Space_After_Add(String s) {
        if (s.length() >= 7) {
            Cmd_Item_Valid_Result res = Parse(s);
            if (res == Cmd_Item_Valid_Result.CMD_ITEM_OK) {
                return true;
            }
        }
        return false;
    }
}
