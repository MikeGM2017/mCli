/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_Input_Test_Key_Processor.h
 * Author: mike
 *
 * Created on May 24, 2021, 4:43 PM
 */

#ifndef CLI_INPUT_TEST_KEY_PROCESSOR_H
#define CLI_INPUT_TEST_KEY_PROCESSOR_H

#include "Cli_Key_Processor_Abstract.h"

class Cli_Input_Test_Key_Processor : public Cli_Key_Processor_Abstract {
public:

    Cli_Input_Test_Key_Processor(Cli_Input_Abstract &cli_input, Cli_Output_Abstract &cli_output) :
    Cli_Key_Processor_Abstract(cli_input, cli_output) {
    }

    virtual ~Cli_Input_Test_Key_Processor() {
    }

    virtual bool On_Key_Pressed(int key_code, QString key_str, bool is_ctrl, bool is_shift) {

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

                    Cli_Output.Output_NewLine();

                    QString s1 = input_item.Text_Get();
                    string s2 = s1.toStdString();

                    if (s2 == "Q" || s2 == "quit") {
                        Cli_Output.Output_Str("Quit - Processed");
                        Cli_Output.Output_NewLine();
                        Cli_Input.Input_sleep(1);
                        exit(0);
                    }

                    if (input_item.Text_Get() == "Q" || input_item.Text_Get() == "quit") {
                        Cli_Output.Output_Str("Quit - Processed");
                        Cli_Output.Output_NewLine();
                        Cli_Input.Input_sleep(1);
                        exit(0);
                    } else if (input_item.Text_Get() == "C" || input_item.Text_Get() == "clear") {
                        Cli_Output.Output_Clear();
                        Cli_Output.Output_Str("Clear - Processed");
                        Cli_Output.Output_NewLine();
                    } else if (input_item.Text_Get() == "A" || input_item.Text_Get() == "ask") {
                        Cli_Output.Output_Str("Is it right?(yes/no)");
                        Cli_Input.Input_Str_Set_Empty();
                        Cli_Input.Input_Mode_Set(INPUT_MODE_PROMPT);
                        break;
                    } else if (input_item.Text_Get() == "P" || input_item.Text_Get() == "passwd") {
                        Cli_Output.Output_Str("Password:");
                        Cli_Input.Input_Str_Set_Empty();
                        Cli_Input.Input_Mode_Set(INPUT_MODE_PASSWD);
                        Cli_Input.Is_Echo_Off();
                        break;
                    } else if (input_item.Text_Get() == "W" || input_item.Text_Get() == "wait") {
                        Cli_Output.Output_Str("Wait (Press Enter to stop):");
                        //Cli_Output.Output_NewLine();
                        Cli_Input.Input_Str_Set_Empty();
                        Cli_Input.Input_Mode_Set(INPUT_MODE_WAIT);
                        Cli_Input.Wait_Count_Set(10);
                        break;
                    } else if (input_item.Text_Get() == "H" || input_item.Text_Get() == "help") {
                        Cli_Output.Output_Str("Help: Q - quit, C - clear, H - help, A - prompt(y/n), P - password(no echo), W - wait");
                        Cli_Output.Output_NewLine();
                    } else if (input_item.Text_Get().length() > 0) {
                        Cli_Output.Output_Str(input_item.Text_Get() + " - Not Processed");
                        Cli_Output.Output_NewLine();
                    }

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
                QString s = "TAB: " + input_item.Text_Get();
                Cli_Output.Output_NewLine();
                Cli_Output.Output_Str(s);
                Cli_Output.Output_NewLine();
                Cli_Output.Output_Str(Cli_Input.Invitation_Full_Get());
                Cli_Output.Output_Str(Cli_Input.Input_Str_Get());
                Cli_Output.Caret_Pos_Set(Cli_Input.Input_Str_Get().length(), Cli_Input.Input_Str_Pos_Get());
            }
                break;
            case CLI_INPUT_ITEM_TYPE_UP:
                Cli_Output.Output_NewLine();
                Cli_Output.Output_Str("UP");
                Cli_Output.Output_NewLine();
                Cli_Output.Output_Str(Cli_Input.Invitation_Full_Get());
                Cli_Output.Output_Str(Cli_Input.Input_Str_Get());
                Cli_Output.Caret_Pos_Set(Cli_Input.Input_Str_Get().length(), Cli_Input.Input_Str_Pos_Get());
                break;
            case CLI_INPUT_ITEM_TYPE_DOWN:
                Cli_Output.Output_NewLine();
                Cli_Output.Output_Str("DOWN");
                Cli_Output.Output_NewLine();
                Cli_Output.Output_Str(Cli_Input.Invitation_Full_Get());
                Cli_Output.Output_Str(Cli_Input.Input_Str_Get());
                Cli_Output.Caret_Pos_Set(Cli_Input.Input_Str_Get().length(), Cli_Input.Input_Str_Pos_Get());
                break;
            case CLI_INPUT_ITEM_TYPE_QUIT:
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
        return true; // Processed
    }

};

#endif /* CLI_INPUT_TEST_KEY_PROCESSOR_H */
