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
public class TAB_Cmd_ID_Func {

    static String To_Str(TAB_Cmd_ID tab_cmd_id) {
        switch (tab_cmd_id) {
            case TAB_CMD_ID_NO:
                return "TAB_CMD_ID_NO";
            case TAB_CMD_ID_LOG_PRINT:
                return "TAB_CMD_ID_LOG_PRINT";
            case TAB_CMD_ID_INPUT_ADD:
                return "TAB_CMD_ID_INPUT_ADD";
            case TAB_CMD_ID_INPUT_CHECK_SPACE:
                return "TAB_CMD_ID_INPUT_CHECK_SPACE";
        }
        return "TAB_CMD_ID_???";
    }
}
