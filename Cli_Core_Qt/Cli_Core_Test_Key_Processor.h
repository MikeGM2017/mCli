/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_Core_Test_Key_Processor.h
 * Author: mike
 *
 * Created on July 2, 2021, 5:29 PM
 */

#ifndef CLI_CORE_TEST_KEY_PROCESSOR_H
#define CLI_CORE_TEST_KEY_PROCESSOR_H

#include "Cli_Input_Test_Key_Processor.h"

#include "Cli_CMD_Processor.h"
#include "Cli_TAB_Processor.h"
#include "Cli_History.h"

class Cli_Core_Test_Key_Processor : public Cli_Input_Test_Key_Processor {
protected:

    Cli_CMD_Processor &CMD_Processor;
    Cli_TAB_Processor &TAB_Processor;
    Cli_History &History;

    bool &Cmd_Quit;

    bool is_invitation_print;

public:

    Cli_Core_Test_Key_Processor(Cli_CMD_Processor &cmd_processor, Cli_TAB_Processor &tab_processor,
            Cli_History &history,
            Cli_Input_Abstract &cli_input, Cli_Output_Abstract &cli_output,
            bool &cmd_quit) :
    Cli_Input_Test_Key_Processor(cli_input, cli_output),
    CMD_Processor(cmd_processor), TAB_Processor(tab_processor), History(history), Cmd_Quit(cmd_quit),
    is_invitation_print(true) {
    }

    virtual ~Cli_Core_Test_Key_Processor() {
    }

    virtual bool On_Key_Pressed(int key_code, string key_str, bool is_ctrl, bool is_shift) {

        Cli_Input_Item input_item = Cli_Input.On_Key_Pressed(key_code, key_str, is_ctrl, is_shift);

        if (input_item.Type_Get() != CLI_INPUT_ITEM_TYPE_DELETE) {
            if (Cli_Input.Input_Mode_Get() == INPUT_MODE_PASSWD) {
                Cli_Output.Caret_Pos_Set(0, 0);
            } else {
                Cli_Output.Caret_Pos_Set(Cli_Input.Input_Str_Get().length(), Cli_Input.Input_Str_Pos_Get());
            }
        }

        switch (input_item.Type_Get()) {
            case CLI_INPUT_ITEM_TYPE_STR:

                if (Cli_Input.Input_Mode_Get() == INPUT_MODE_NORMAL) {

                    bool is_no_history = false;
                    bool is_debug = false;

                    //string s_trim = Cli.Str_Trim(input_item.Text_Get());
                    string s_trim = CMD_Processor.Str_Trim(input_item.Text_Get());

                    if (!is_no_history && !is_debug && !s_trim.empty()) {
                        History.History_Put(s_trim);
                    }

                    bool debug_res = false;
                    CMD_Processor.Process_Input_Item(input_item, is_debug, debug_res);

                    if (Cli_Input.Input_Mode_Get() == INPUT_MODE_WAIT && Cli_Input.Wait_Count_Get() > 0) {
                        break;
                    }

                    Cli_Output.Output_NewLine();

                } else if (Cli_Input.Input_Mode_Get() == INPUT_MODE_PROMPT) {
                    Cli_Output.Output_NewLine();
                    if (input_item.Text_Get() == "Y" || input_item.Text_Get() == "y"
                            || input_item.Text_Get() == "YES" || input_item.Text_Get() == "Yes" || input_item.Text_Get() == "yes") {
                        Cli_Output.Output_Str("Answer: Yes");
                    } else {
                        Cli_Output.Output_Str("Answer: No");
                    }
                    Cli_Output.Output_NewLine();

                } else if (Cli_Input.Input_Mode_Get() == INPUT_MODE_PASSWD) {
                    Cli_Output.Output_NewLine();
                    Cli_Output.Output_Str("Password:" + input_item.Text_Get());
                    Cli_Output.Output_NewLine();

                } else if (Cli_Input.Input_Mode_Get() == INPUT_MODE_WAIT) {
                    Cli_Input.Wait_Count_Set(-1);
                    Cli_Output.Output_NewLine();
                    Cli_Output.Output_Str("Wait stopped");
                    Cli_Output.Output_NewLine();
                }

                Cli_Output.Output_Str(Cli_Input.Invitation_Full_Get());
                Cli_Input.Input_Str_Set_Empty();
                Cli_Input.Input_Mode_Set(INPUT_MODE_NORMAL);
                Cli_Input.Is_Echo_On();

                break;
            case CLI_INPUT_ITEM_TYPE_TAB:
            {
                TAB_Processor.Process_Input_Item(input_item, is_invitation_print);
                if (is_invitation_print) {
                    //                QString s = "TAB: " + input_item.Text_Get();
                    //                Cli_Output.Output_NewLine();
                    //                Cli_Output.Output_Str_Qt(s);
                    Cli_Output.Output_NewLine();
                    Cli_Output.Output_Str(Cli_Input.Invitation_Full_Get());
                    Cli_Output.Output_Str(Cli_Input.Input_Str_Get());
                }
                Cli_Output.Caret_Pos_Set(Cli_Input.Input_Str_Get().length(), Cli_Input.Input_Str_Pos_Get());
            }
                break;
            case CLI_INPUT_ITEM_TYPE_UP:
            {
                string s_prev = Cli_Input.Input_Str_Get();
                Cli_Input.Input_Str_Set(History.History_Up().c_str());
                Cli_Input.Input_Str_Modified_To_Output(s_prev.c_str());
                Cli_Input.Input_End();
                Cli_Output.Caret_Pos_Set(Cli_Input.Input_Str_Get().length(), Cli_Input.Input_Str_Pos_Get());
                is_invitation_print = false;
            }
                break;
            case CLI_INPUT_ITEM_TYPE_DOWN:
            {
                string s_prev = Cli_Input.Input_Str_Get();
                Cli_Input.Input_Str_Set(History.History_Down().c_str());
                Cli_Input.Input_Str_Modified_To_Output(s_prev.c_str());
                Cli_Input.Input_End();
                Cli_Output.Caret_Pos_Set(Cli_Input.Input_Str_Get().length(), Cli_Input.Input_Str_Pos_Get());
                is_invitation_print = false;
            }
                break;
            case CLI_INPUT_ITEM_TYPE_QUIT:
            {
                Cli_Output.Output_NewLine();
                Cli_Output.Output_Str("Quit");
                Cli_Output.Output_NewLine();
                exit(0); // Quit
            }
                break;

            case CLI_INPUT_ITEM_TYPE_LEFT:
            case CLI_INPUT_ITEM_TYPE_RIGHT:
            case CLI_INPUT_ITEM_TYPE_HOME:
            case CLI_INPUT_ITEM_TYPE_END:
                return true; // Processed!
                break;

            case CLI_INPUT_ITEM_TYPE_BACK:
            case CLI_INPUT_ITEM_TYPE_DELETE:
                if (Cli_Input.Input_Mode_Get() == INPUT_MODE_PASSWD) {
                    return true; // Processed!
                }
                return false; // Not Processed
                break;

            case CLI_INPUT_ITEM_TYPE_CTRL:
            case CLI_INPUT_ITEM_TYPE_SHIFT:
                return true; // Processed!
                break;

            case CLI_INPUT_ITEM_TYPE_CTRL_C:
            case CLI_INPUT_ITEM_TYPE_CTRL_Z:
            case CLI_INPUT_ITEM_TYPE_CTRL_BACKSLASH:
                if (Cli_Input.Input_Mode_Get() == INPUT_MODE_WAIT) {
                    Cli_Input.Wait_Count_Set(-1);
                    Cli_Output.Output_NewLine();
                    Cli_Output.Output_Str("Wait stopped");
                    //Cli_Output.Output_NewLine();
                }
                Cli_Input.Input_Str_Set_Empty();
                Cli_Input.Input_Mode_Set(INPUT_MODE_NORMAL);
                Cli_Output.Output_NewLine();
                Cli_Output.Output_Str(Cli_Input.Invitation_Full_Get());
                break;

            case CLI_INPUT_ITEM_TYPE_CHAR_ADD:
                if (!Cli_Input.Is_Echo_Get()) {
                    return true; // Processed!
                }
                return false; // Not Processed
                break;

            case CLI_INPUT_ITEM_TYPE_NO_ACTION:
                return true; // Processed!
                break;

            default:
                return false; // Not Processed
                break;
        }

        if (Cmd_Quit) {
            Cli_Output.Output_Str("Quit - Processed");
            Cli_Output.Output_NewLine();
            //Cli_Input.Input_sleep(1);
            exit(0); // Quit
        }

        return true; // Processed
    }

};

#endif /* CLI_CORE_TEST_KEY_PROCESSOR_H */
