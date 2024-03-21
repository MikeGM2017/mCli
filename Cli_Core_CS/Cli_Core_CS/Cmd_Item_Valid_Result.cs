namespace Cli_Core_CS
{
    public enum Cmd_Item_Valid_Result
    {
        CMD_ITEM_OK,
        CMD_ITEM_OK_CAN_CONTINUE,
        CMD_ITEM_OK_STR_WITHOUT_COMMAS,
        CMD_ITEM_NOT_MATCH,
        CMD_ITEM_ERROR,
        CMD_ITEM_MATCH_BUT_ERROR,
        CMD_ITEM_EMPTY,
        CMD_ITEM_INCOMPLETE,
        CMD_ITEM_INCOMPLETE_STR,
        CMD_ITEM_TOO_LONG,
        CMD_ITEM_OUT_OF_RANGE,
        CMD_ITEM_OUT_OF_ORDER,
        CMD_ITEM_UNDEFINED
    }
}
