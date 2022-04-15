/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_Input_C_file_main.c
 * Author: mike
 *
 * Created on December 14, 2021, 3:58 PM
 */

#include <stdlib.h>

#include "Cli_Input_C_file.h"

#include "Cli_Output_C_printf.h"

void Help_Print() {
    printf("Program Cli_Input_C_file\n");
    printf("Use: cli_input_c_file [switches]\n");
    printf("-h        - print this help;\n");
    printf("-a        - print arguments;\n");
    printf("-f <file> - set input file;\n");
}

int main(int argc, char** argv) {

    int Arg_Help_Print = 0;
    int Arg_Arguments_Print = 0;
    char *Arg_File_In = NULL;

    // Get Arg_XXX from cmdline
    int i;
    for (i = 1; i < argc; i++) {
        char *s = argv[i];
        if (!strcmp(s, "-h") || !strcmp(s, "-help") || !strcmp(s, "-?")
                || !strcmp(s, "-h") || !strcmp(s, "-help") || !strcmp(s, "-?")
                || !strcmp(s, "-h") || !strcmp(s, "-help") || !strcmp(s, "-?")) {
            Arg_Help_Print = 1;
        } else if (!strcmp(s, "-a")) {
            Arg_Arguments_Print = 1;
        } else if (!strcmp(s, "-f")) {
            i++;
            if (i < argc && argv[i][0] != '-') {
                Arg_File_In = argv[i];
            } else {
                printf("ERROR: switch \"%s\" without argument\n", s);
                exit(1); // Error
            }
        }
    }

    // Force Arg_Help_Print (if run without switches)
    if (argc == 1) {
        Arg_Help_Print = 1;
    }

    if (Arg_Help_Print) {
        Help_Print();
        exit(0); // Ok
    }

    if (Arg_Arguments_Print) {
        printf("Arguments:\n");
        printf("      File In: \"%s\"\n", Arg_File_In);
    }

    if (!Arg_File_In || !Arg_File_In[0]) {
        printf("ERROR: File In is not set\n");
        exit(1); // Failed
    }

    struct Cli_Output_C Cli_Output = Cli_Output_C_printf();

    struct Cli_Input_C_File Cli_Input_File = Cli_Input_C_file(Arg_File_In);
    struct Cli_Input_C *Cli_Input = (struct Cli_Input_C *) &Cli_Input_File;

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
        Cli_Output.Output_Str(&Cli_Output, Cli_Input->Invitation_Full_Get(Cli_Input));
        Cli_Output.Output_Str(&Cli_Output, Cli_Input->Input_Str_Get(Cli_Input));
        struct Cli_Input_C_Item input_item = Cli_Input->Input_Item_Get(Cli_Input);
        if (Cli_Input_C_Item_Type_Get(&input_item) == CLI_INPUT_ITEM_TYPE_STR) {
            char input_str[CLI_INPUT_C_ITEM_TEXT_SIZE];
            strncpy(input_str, Cli_Input_C_Item_Text_Get(&input_item), CLI_INPUT_C_ITEM_TEXT_SIZE - 1);
            input_str[CLI_INPUT_C_ITEM_TEXT_SIZE - 1] = '\0';
            if (input_str[0] == 'Q') {
                Cli_Output.Output_NewLine(&Cli_Output);
                Cli_Output.Output_Str(&Cli_Output, "Quit - Processed");
                Cli_Output.Output_NewLine(&Cli_Output);
                stop = 1; // Quit
            } else if (input_str[0] == 'C') {
                Cli_Input->Input_Clear(Cli_Input);
                Cli_Output.Output_NewLine(&Cli_Output);
                Cli_Output.Output_Str(&Cli_Output, "Clear - Processed");
                Cli_Output.Output_NewLine(&Cli_Output);
            } else if (input_str[0]) {
                Cli_Output.Output_NewLine(&Cli_Output);
                Cli_Output.Output_Str(&Cli_Output, Cli_Input_C_Item_Text_Get(&input_item));
                Cli_Output.Output_Str(&Cli_Output, " - Not Processed");
                Cli_Output.Output_NewLine(&Cli_Output);
            } else {
                Cli_Output.Output_NewLine(&Cli_Output);
            }
        } else if (Cli_Input_C_Item_Type_Get(&input_item) == CLI_INPUT_ITEM_TYPE_TAB) {
            Cli_Output.Output_NewLine(&Cli_Output);
            Cli_Output.Output_Str(&Cli_Output, "TAB: ");
            Cli_Output.Output_Str(&Cli_Output, Cli_Input_C_Item_Text_Get(&input_item));
            Cli_Output.Output_NewLine(&Cli_Output);
        } else if (Cli_Input_C_Item_Type_Get(&input_item) == CLI_INPUT_ITEM_TYPE_UP) {
            Cli_Output.Output_NewLine(&Cli_Output);
            Cli_Output.Output_Str(&Cli_Output, "UP: ");
            Cli_Output.Output_Str(&Cli_Output, Cli_Input_C_Item_Text_Get(&input_item));
            Cli_Output.Output_NewLine(&Cli_Output);
        } else if (Cli_Input_C_Item_Type_Get(&input_item) == CLI_INPUT_ITEM_TYPE_DOWN) {
            Cli_Output.Output_NewLine(&Cli_Output);
            Cli_Output.Output_Str(&Cli_Output, "DOWN: ");
            Cli_Output.Output_Str(&Cli_Output, Cli_Input_C_Item_Text_Get(&input_item));
            Cli_Output.Output_NewLine(&Cli_Output);
        } else if (Cli_Input_C_Item_Type_Get(&input_item) == CLI_INPUT_ITEM_TYPE_QUIT) {
            Cli_Output.Output_NewLine(&Cli_Output);
            Cli_Output.Output_Str(&Cli_Output, "Quit - Processed");
            Cli_Output.Output_NewLine(&Cli_Output);
            stop = 1; // Quit
        }
    } while (!stop);

    //    Cli_Output.Output_NewLine();
    //    do {
    //        Cli_Output.Output_Str("Press Any Key to stop");
    //        Cli_Output.Output_NewLine();
    //        Cli_Input->Input_sleep(Cli_Input, 1);
    //    } while (!Cli_Input->Input_kbhit(Cli_Input));
    //
    //    Cli_Output.Output_Str("Press Any Key to exit");
    //    Cli_Output.Output_NewLine();
    //    struct Cli_Input_C_Item input_item = Cli_Input->Input_Item_Get(Cli_Input);

    Cli_Input->Input_Restore(Cli_Input);

}
