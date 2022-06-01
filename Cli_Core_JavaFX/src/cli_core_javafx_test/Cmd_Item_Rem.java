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
public class Cmd_Item_Rem extends Cmd_Item_Base {

    public Cmd_Item_Rem(String str_rem, String help) {
        super(str_rem, help);
        Type = "Rem";
    }

    public String Debug_Value_Get() {
        return Text + " - rem";
    }

    public Cmd_Item_Valid_Result Parse(String s) {
        Value_Str = s;

        if (s.length() == 0) {
            return Cmd_Item_Valid_Result.CMD_ITEM_EMPTY;
        }

        if (s.substring(0, Text.length()).equals(Text)) {
            return Cmd_Item_Valid_Result.CMD_ITEM_OK;
        }

        return Cmd_Item_Valid_Result.CMD_ITEM_ERROR;
    }

}
