/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   cli_input_c_conio_main.c
 * Author: mike
 *
 * Created on July 2, 2020, 5:56 PM
 */

#include "Cli_Input_C_conio.h"

#include "Cli_Output_C_printf.h"

int main(int argc, char** argv) {

    struct Cli_Output_C Cli_Output = Cli_Output_C_printf();

    struct Cli_Input_C_Conio Cli_Input_Conio = Cli_Input_C_conio();
    struct Cli_Input_C *Cli_Input = (struct Cli_Input_C *) &Cli_Input_Conio;

    Cli_Input->Cli_Output = &Cli_Output;

    Cli_Input->Title_Set(Cli_Input, "cli demo");
    Cli_Input->User_Set(Cli_Input, "root");
    Cli_Input->Level_Set(Cli_Input, "top level");
    Cli_Input->Invitation_Set(Cli_Input, "> ");
    Cli_Input->Divider_L_Set(Cli_Input, "[");
    Cli_Input->Divider_R_Set(Cli_Input, "]");
    Cli_Input->Input_Init(Cli_Input);

    int stop = 0;
    do {
        Cli_Output.Output_Str(Cli_Input->Invitation_Full_Get(Cli_Input));
        Cli_Output.Output_Str(Cli_Input->Input_Str_Get(Cli_Input));
        struct Cli_Input_C_Item input_item = Cli_Input->Input_Item_Get(Cli_Input);
        if (Cli_Input_C_Item_Type_Get(&input_item) == CLI_INPUT_ITEM_TYPE_STR) {
            char input_str[CLI_INPUT_C_ITEM_TEXT_SIZE];
            strncpy(input_str, Cli_Input_C_Item_Text_Get(&input_item), CLI_INPUT_C_ITEM_TEXT_SIZE);
            if (input_str[0] == 'Q') {
                Cli_Output.Output_NewLine();
                Cli_Output.Output_Str("Quit - Processed");
                Cli_Output.Output_NewLine();
                stop = 1; // Quit
            } else if (input_str[0]) {
                Cli_Output.Output_NewLine();
                Cli_Output.Output_Str(Cli_Input_C_Item_Text_Get(&input_item));
                Cli_Output.Output_Str(" - Not Processed");
                Cli_Output.Output_NewLine();
            } else {
                Cli_Output.Output_NewLine();
            }
        } else if (Cli_Input_C_Item_Type_Get(&input_item) == CLI_INPUT_ITEM_TYPE_TAB) {
            Cli_Output.Output_NewLine();
            Cli_Output.Output_Str("TAB: ");
            Cli_Output.Output_Str(Cli_Input_C_Item_Text_Get(&input_item));
            Cli_Output.Output_NewLine();
        } else if (Cli_Input_C_Item_Type_Get(&input_item) == CLI_INPUT_ITEM_TYPE_UP) {
            Cli_Output.Output_NewLine();
            Cli_Output.Output_Str("UP: ");
            Cli_Output.Output_Str(Cli_Input_C_Item_Text_Get(&input_item));
            Cli_Output.Output_NewLine();
        } else if (Cli_Input_C_Item_Type_Get(&input_item) == CLI_INPUT_ITEM_TYPE_DOWN) {
            Cli_Output.Output_NewLine();
            Cli_Output.Output_Str("DOWN: ");
            Cli_Output.Output_Str(Cli_Input_C_Item_Text_Get(&input_item));
            Cli_Output.Output_NewLine();
        } else if (Cli_Input_C_Item_Type_Get(&input_item) == CLI_INPUT_ITEM_TYPE_QUIT) {
            Cli_Output.Output_NewLine();
            Cli_Output.Output_Str("Quit - Processed");
            Cli_Output.Output_NewLine();
            stop = 1; // Quit
        }
    } while (!stop);

    Cli_Input->Input_Restore(Cli_Input);

}
