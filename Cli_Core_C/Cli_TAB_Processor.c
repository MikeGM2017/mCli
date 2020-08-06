/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Cli_TAB_Processor.h"

static int Process_Input_Item(struct Cli_TAB_Processor *tab_processor,
        struct Cli_Input_C_Item *input_item, int *is_invitation_print) {
    tab_processor->Cli_Output->Output_NewLine();
    tab_processor->Cli_Output->Output_Str("TAB: \"");
    tab_processor->Cli_Output->Output_Str(input_item->Text);
    tab_processor->Cli_Output->Output_Str("\" - Not Processed");
    tab_processor->Cli_Output->Output_NewLine();

    {
        tab_processor->Cli_Output->Output_NewLine();
        tab_processor->Cli_Output->Output_Str("Modules:");
        tab_processor->Cli_Output->Output_NewLine();
        struct Cli_Module *module_ptr = tab_processor->Modules->Module_Head;
        while (module_ptr) {
            {
                tab_processor->Cli_Output->Output_Str(module_ptr->Name);
                tab_processor->Cli_Output->Output_NewLine();
                struct Cli_Cmd *cmd_ptr = module_ptr->Cmd_Head;
                while (cmd_ptr) {
                    {
                        tab_processor->Cli_Output->Output_Str("   ");
                        tab_processor->Cli_Output->Output_Str(cmd_ptr->Text);
                        tab_processor->Cli_Output->Output_Str(" - ");
                        tab_processor->Cli_Output->Output_Str(cmd_ptr->Help);
                        tab_processor->Cli_Output->Output_NewLine();
                        struct Cli_Cmd_Item *cmd_item_ptr = cmd_ptr->Item_Head;
                        while (cmd_item_ptr) {
                            {
                                tab_processor->Cli_Output->Output_Str("      ");
                                tab_processor->Cli_Output->Output_Str(cmd_item_ptr->Text);
                                tab_processor->Cli_Output->Output_Str(" - ");
                                tab_processor->Cli_Output->Output_Str(cmd_item_ptr->Help);
                                tab_processor->Cli_Output->Output_NewLine();
                            }
                            cmd_item_ptr = cmd_item_ptr->Cmd_Item_Next;
                        }
                    }
                    cmd_ptr = cmd_ptr->Cmd_Next;
                }
            }
            module_ptr = module_ptr->Module_Next;
        }
        tab_processor->Cli_Output->Output_NewLine();
    }

    return 0; // Failed
}

struct Cli_TAB_Processor Cli_TAB_Processor_Init(enum Cli_Cmd_Privilege_ID user_privilege,
        struct Cli_Modules *modules,
        struct Level_Description_Array *levels,
        struct Cmd_Token_Parser *parser,
        struct Cli_Input_C *cli_input,
        struct Cli_Output_C *cli_output,
        char *str_rem) {
    struct Cli_TAB_Processor tab_processor;
    memset(&tab_processor, 0, sizeof (tab_processor));

    tab_processor.User_Privilege = user_privilege;
    tab_processor.Modules = modules;
    tab_processor.Levels = levels;
    tab_processor.Parser = parser;
    tab_processor.Cli_Input = cli_input;
    tab_processor.Cli_Output = cli_output;

    if (str_rem) {
        int len = CLI_TAB_PROCESSOR_STR_REM_SIZE_DEF - 1;
        strncpy(tab_processor.Str_Rem, str_rem, len);
        tab_processor.Str_Rem[len] = '\0';
    } else {
        tab_processor.Str_Rem[0] = '\0';
    }

    tab_processor.Process_Input_Item = Process_Input_Item;

    return tab_processor;
}
