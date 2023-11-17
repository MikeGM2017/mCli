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
public class Cmd_Item_Valid_Result_Func {

    public static String To_String(Cmd_Item_Valid_Result v) {
        switch (v) {
            case CMD_ITEM_OK:
                return "OK";
            case CMD_ITEM_OK_CAN_CONTINUE:
                return "OK_CAN_CONTINUE";
            case CMD_ITEM_OK_STR_WITHOUT_COMMAS:
                return "OK_STR_WITHOUT_COMMAS";
            case CMD_ITEM_NOT_MATCH:
                return "NOT_MATCH";
            case CMD_ITEM_ERROR:
                return "ERROR";
            case CMD_ITEM_MATCH_BUT_ERROR:
                return "MATCH_BUT_ERROR";
            case CMD_ITEM_EMPTY:
                return "EMPTY";
            case CMD_ITEM_INCOMPLETE:
                return "INCOMPLETE";
            case CMD_ITEM_INCOMPLETE_SHOW_HINT:
                return "INCOMPLETE_SHOW_HINT";
            case CMD_ITEM_INCOMPLETE_STR:
                return "INCOMPLETE_STR";
            case CMD_ITEM_TOO_LONG:
                return "TOO_LONG";
            case CMD_ITEM_OUT_OF_RANGE:
                return "OUT_OF_RANGE";
            case CMD_ITEM_OUT_OF_ORDER:
                return "OUT_OF_ORDER";
            case CMD_ITEM_UNDEFINED:
                return "UNDEFINED";
            default:
                return "???";
        }
    }

}
