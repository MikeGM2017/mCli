/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cli_core_javafx_test;

import java.net.Inet4Address;
import java.net.Inet6Address;
import java.net.InetAddress;
import java.net.UnknownHostException;

/**
 *
 * @author mike
 */
public class Cmd_Item_IP6 extends Cmd_Item_Base {

    @Override
    protected boolean Is_Char_Valid(char c, int pos, int len) {
        if (c >= '0' && c <= '9') {
            return true;
        }
        if (c >= 'a' && c <= 'f') {
            return true;
        }
        if (c >= 'A' && c <= 'F') {
            return true;
        }
        if (c == ':' || c == '.' || c == '/') {
            return true;
        }
        return false;
    }

    Cmd_Item_IP6(String text, String help) {
        super(text, help);
        Type = "IP6";
    }

    @Override
    public String Debug_Value_Get() {
        return "::ffff:1.2.3.4";
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

        boolean res_ipv6 = isIPv6(s);
        if (!res_ipv6) {
            return Cmd_Item_Valid_Result.CMD_ITEM_ERROR;
        }

        return Cmd_Item_Valid_Result.CMD_ITEM_OK;
    }

    protected static boolean isIPv6(String input) {
        try {
            InetAddress inetAddress = InetAddress.getByName(input);
            return (inetAddress instanceof Inet6Address);
        } catch (UnknownHostException ex) {
            return false;
        }
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
