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
public enum Cmd_Item_Valid_Result {
    CMD_ITEM_OK,
    CMD_ITEM_OK_CAN_CONTINUE,
    CMD_ITEM_OK_STR_WITHOUT_COMMAS,
    CMD_ITEM_NOT_MATCH,
    CMD_ITEM_ERROR,
    CMD_ITEM_MATCH_BUT_ERROR,
    CMD_ITEM_EMPTY,
    CMD_ITEM_INCOMPLETE,
    CMD_ITEM_INCOMPLETE_SHOW_HINT,
    CMD_ITEM_INCOMPLETE_STR,
    CMD_ITEM_TOO_LONG,
    CMD_ITEM_OUT_OF_RANGE,
    CMD_ITEM_OUT_OF_ORDER,
    CMD_ITEM_UNDEFINED
}
