/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdlib.h>

#include "Cli_Input_C_termios.h"
#include "Cli_Input_C_file.h"

#include "Cli_Cmd_Privilege_ID.h"
#include "Cli_Module.h"

#include "Cli_Module_Base_Rem.h"
#include "Cli_Module_Base_Help.h"
#include "Cli_Module_Base_Quit.h"
#include "Cli_Module_Base_History.h"
#include "Cli_Module_Base_Modules.h"

#include "Cli_Modules.h"

#include "Cli_Output_C_printf.h"
#include "Cli_Output_C_file.h"

#include "Cmd_Token_Array.h"
#include "Cmd_Token_Parser.h"

#include "Level_Description_Array.h"

#include "Cli_Core.h"

#include "Cli_History.h"

#include "Cli_CMD_Processor.h"

#include "Cli_TAB_Processor.h"

#include "Mem_Manager_malloc_free.h"
#include "Mem_Manager_buf.h"
#include "Cli_Module_Mem_Manager.h"

void Help_Print() {
    printf("Program Cli_Core_C_Test\n");
    printf("Use: cli_core_c_test [switches]\n");
    printf("-h               - print this help;\n");
    printf("-a               - print arguments;\n");
    printf("-f        <file> - set input file;\n");
    printf("-flog     <file> - set output log file;\n");
    printf("-ftablog  <file> - set output tablog file;\n");
    printf("-fhistory <file> - set output history file;\n");
}

int main(int argc, char** argv) {

    int Arg_Help_Print = 0;
    int Arg_Arguments_Print = 0;
    char *Arg_File_In = NULL;
    char *Arg_File_Log = NULL;
    char *Arg_File_TabLog = NULL;
    char *Arg_File_History = NULL;

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
        } else if (!strcmp(s, "-flog")) {
            i++;
            if (i < argc && argv[i][0] != '-') {
                Arg_File_Log = argv[i];
            } else {
                printf("ERROR: switch \"%s\" without argument\n", s);
                exit(1); // Error
            }
        } else if (!strcmp(s, "-ftablog")) {
            i++;
            if (i < argc && argv[i][0] != '-') {
                Arg_File_TabLog = argv[i];
            } else {
                printf("ERROR: switch \"%s\" without argument\n", s);
                exit(1); // Error
            }
        } else if (!strcmp(s, "-fhistory")) {
            i++;
            if (i < argc && argv[i][0] != '-') {
                Arg_File_History = argv[i];
            } else {
                printf("ERROR: switch \"%s\" without argument\n", s);
                exit(1); // Error
            }
        }
    }

    // Force Arg_Help_Print (if run without switches)
    //if (argc == 1) {
    //    Arg_Help_Print = 1;
    //}

    if (Arg_Help_Print) {
        Help_Print();
        exit(0); // Ok
    }

    if (Arg_Arguments_Print) {
        printf("Arguments:\n");
        printf(" File In         : \"%s\"\n", Arg_File_In);
        printf(" File Log        : \"%s\"\n", Arg_File_Log);
        printf(" File Tab Log    : \"%s\"\n", Arg_File_TabLog);
        printf(" File History Log: \"%s\"\n", Arg_File_History);
    }

    char Version[] = "0.01";

    struct Cli_Output_C Cli_Output_printf;
    struct Cli_Output_C_file Cli_Output_file;
    struct Cli_Output_C *Cli_Output = NULL;
    if (Arg_File_Log) {
        Cli_Output_file = Cli_Output_C_file(Arg_File_Log);
        Cli_Output = (struct Cli_Output_C *) &Cli_Output_file;
    } else {
        Cli_Output_printf = Cli_Output_C_printf();
        Cli_Output = &Cli_Output_printf;
    }
    Cli_Output->Output_Init(Cli_Output);

    struct Cli_Input_C_Termios Cli_Input_C_Termios;
    struct Cli_Input_C_File Cli_Input_file;
    struct Cli_Input_C *Cli_Input = NULL;
    if (Arg_File_In) {
        Cli_Input_file = Cli_Input_C_file(Cli_Output, Arg_File_In);
        Cli_Input = &Cli_Input_file.Cli_Input_Base;
    } else {
        Cli_Input_C_Termios = Cli_Input_C_termios(Cli_Output);
        Cli_Input = &Cli_Input_C_Termios.Cli_Input_Base;
    }
    Cli_Input->Input_Init(Cli_Input);

    struct Level_Description_Array Levels = Level_Description_Array_Init();

    struct Cmd_Token_Parser Token_Parser = Cmd_Token_Parser_Init();

    char Str_Rem_DEF[] = "$";

    enum Cli_Cmd_Privilege_ID User_Privilege = CMD_PRIVILEGE_ROOT_DEF;
    struct Cli_Modules Modules = Cli_Modules_Init();

    struct Cli_History History = Cli_History_Init();

    struct Cli_CMD_Processor CMD_Processor = Cli_CMD_Processor_Init
            (User_Privilege, &Modules, &Levels, &Token_Parser, Cli_Input, Cli_Output, Str_Rem_DEF);
    struct Cli_TAB_Processor TAB_Processor = Cli_TAB_Processor_Init
            (User_Privilege, &Modules, &Levels, &Token_Parser, Cli_Input, Cli_Output, Str_Rem_DEF);
    struct Cli_Core Cli = Cli_Core_Init();
    //(User_Privilege, &Modules, &Levels, &Token_Parser, Cli_Input, Cli_Output, Str_Rem_DEF);

    // Modules Add - Begin

    struct Cli_Module_Base_Rem module_rem = Cli_Module_Base_Rem_Init(Str_Rem_DEF, Cli_Output);
    Cli_Modules_Add(&Modules, (struct Cli_Module *) &module_rem);

    struct Str_Filter Filter = Str_Filter_Init('.', '*');

    struct Cli_Module_Base_Help module_help = Cli_Module_Base_Help_Init(User_Privilege, &Modules, &Filter, Cli_Output);
    Cli_Modules_Add(&Modules, (struct Cli_Module *) &module_help);

    //    Modules.Add(new Cli_Module_Base_Rem(Str_Rem_DEF, Cli_Output));
    //
    int Cmd_Quit = 0;

    struct Cli_Module_Base_Quit module_quit = Cli_Module_Base_Quit_Init(Cli_Input, Cli_Output, &Cmd_Quit);
    Cli_Modules_Add(&Modules, (struct Cli_Module *) &module_quit);

    //    Modules.Add(new Cli_Module_Base_Quit(Cmd_Quit));
    //
    //    Str_Filter str_filter('?', '*');
    //    Modules.Add(new Cli_Module_Base_Help(User_Privilege, Modules, str_filter, Cli_Output));
    //    Modules.Add(new Cli_Module_Base_Modules(User_Privilege, Modules, str_filter, Cli_Output));

    struct Cli_Module_Base_Modules module_modules = Cli_Module_Base_Modules_Init(&Modules, &Filter, Cli_Output);
    Cli_Modules_Add(&Modules, (struct Cli_Module *) &module_modules);

    //    Cli_History History;
    //    Modules.Add(new Cli_Module_Base_History(History, Cli_Output));

    struct Cli_Module_Base_History module_history = Cli_Module_Base_History_Init(&History, Cli_Output);
    Cli_Modules_Add(&Modules, (struct Cli_Module *) &module_history);

    //
    //    Modules.Add(new Cli_Module_Base_Log(Cli_Input));
    //
    //    int Cmd_Script_Stop = 0;
    //    int Script_Buf_Size = 1024;
    //    Modules.Add(new Cli_Module_Base_Script(History, Cli_Output,
    //            Str_Rem_DEF, Cmd_Script_Stop, Cmd_Quit, Script_Buf_Size,
    //            CMD_Processor));
    //
    //    int Log_Wait_Enable = 1;
    //    int Cmd_Wait_Stop = 0;
    //    Modules.Add(new Cli_Module_Base_Wait(Log_Wait_Enable, Cmd_Wait_Stop, Cli_Input, Cli_Output));
    //
    //    Modules.Add(new Cli_Module_Test_Tab_Min_Max());
    //    Modules.Add(new Cli_Module_Test_Terminal(Cli_Input, Cli_Output));
    //
    //    Modules.Add(new Cli_Module_Base_Debug(User_Privilege, Modules, Levels, CMD_Processor, Cli_Output));

    // Modules Add - End

    Cli_Input->Title_Set(Cli_Input, "Cli Core Test");
    Cli_Input->User_Set(Cli_Input, "root");
    Cli_Input->Level_Set(Cli_Input, "top level");
    Cli_Input->Invitation_Set(Cli_Input, "> ");
    Cli_Input->Divider_L_Set(Cli_Input, "[");
    Cli_Input->Divider_R_Set(Cli_Input, "]");
    Cli_Input->Input_Init(Cli_Input);

    Cli_Output->Output_NewLine(Cli_Output);
    Cli_Output->Output_Str(Cli_Output, "mCli: Cli Core Test");
    Cli_Output->Output_Str(Cli_Output, " V");
    Cli_Output->Output_Str(Cli_Output, Version);
    Cli_Output->Output_NewLine(Cli_Output);
    Cli_Output->Output_NewLine(Cli_Output);

    struct Mem_Manager_C Mem_Manager1 = Mem_Manager_malloc_free_Init();
    const int buf_main_size = 0x1000000;
    char *buf_main = 0;
    enum Mem_Manager_Res buf_main_res = Mem_Manager1.Mem_Manager_Alloc(&Mem_Manager1, buf_main_size, &buf_main);
    struct Mem_Manager_buf Mem_Manager2_buf;
    if (buf_main_res == MEM_MANAGER_OK) {
        Cli_Output->Output_Str(Cli_Output, "Mem 1000000 - Ok");
        Cli_Output->Output_NewLine(Cli_Output);

        //struct Mem_Manager_buf Mem_Manager2_buf = Mem_Manager_buf_Init(buf_main, buf_main_size);
        Mem_Manager2_buf = Mem_Manager_buf_Init(buf_main, buf_main_size);
        char *buf_1 = 0;
        int buf_1_size = 10000;
        struct Mem_Manager_C *Mem_Manager2 = &Mem_Manager2_buf.Mem_Manager_Base;
        enum Mem_Manager_Res buf_1_res = Mem_Manager2->Mem_Manager_Alloc(Mem_Manager2, buf_1_size, &buf_1);

        if (buf_1_res == MEM_MANAGER_OK) {
            Cli_Output->Output_Str(Cli_Output, "buf 10000 - Ok");
            Cli_Output->Output_NewLine(Cli_Output);
        } else {
            Cli_Output->Output_Str(Cli_Output, "buf 10000 - Failed");
            Cli_Output->Output_NewLine(Cli_Output);
        }
        Cli_Output->Output_NewLine(Cli_Output);

    } else {
        Cli_Output->Output_Str(Cli_Output, "Mem 1000000 - Failed");
        Cli_Output->Output_NewLine(Cli_Output);
    }
    Cli_Output->Output_NewLine(Cli_Output);

    struct Cli_Module_Mem_Manager module_mem_manager = Cli_Module_Mem_Manager_Init(
            (struct Mem_Manager_C *) &Mem_Manager2_buf, Cli_Output);
    Cli_Modules_Add(&Modules, (struct Cli_Module *) &module_mem_manager);

    int stop = 0;
    int is_invitation_print = 1;
    do {
        if (is_invitation_print) {
            Cli_Output->Output_Str(Cli_Output, Cli_Input->Invitation_Full_Get(Cli_Input));
            Cli_Output->Output_Str(Cli_Output, Cli_Input->Input_Str_Get(Cli_Input));
        }
        is_invitation_print = 1;
        struct Cli_Input_C_Item input_item = Cli_Input->Input_Item_Get(Cli_Input);
        switch (Cli_Input_C_Item_Type_Get(&input_item)) {
            case CLI_INPUT_ITEM_TYPE_STR:
            {
                int is_no_history = 0;
                int is_debug = 0;

                char s_trim[CLI_INPUT_C_ITEM_TEXT_SIZE];
                Cli.Str_Trim(Cli_Input_C_Item_Text_Get(&input_item), s_trim, CLI_INPUT_C_ITEM_TEXT_SIZE);

                if (!is_no_history && !is_debug && s_trim[0] != '\0') {
                    History.History_Put(&History, s_trim);
                }

                int debug_res = 0;
                //int res_cmd_process = CMD_Processor.Process_Input_Item(&CMD_Processor, &input_item, is_debug, &debug_res);
                //if (!res_cmd_process) {
                //    Cli_Output->Output_NewLine();
                //}
                CMD_Processor.Process_Input_Item(&CMD_Processor, &input_item, is_debug, &debug_res);
                Cli_Output->Output_NewLine(Cli_Output);
            }
                break;
            case CLI_INPUT_ITEM_TYPE_TAB:
            {
                TAB_Processor.Process_Input_Item(&TAB_Processor, &input_item, &is_invitation_print);
            }
                break;
            case CLI_INPUT_ITEM_TYPE_UP:
            {
                char s_prev[CLI_INPUT_C_ITEM_TEXT_SIZE];
                int len = CLI_INPUT_C_ITEM_TEXT_SIZE - 1;
                strncpy(s_prev, Cli_Input->Input_Str_Get(Cli_Input), len);
                s_prev[len] = '\0';
                Cli_Input->Input_Str_Set(Cli_Input, History.History_Up(&History));
                Cli_Input->Input_Str_Modified_To_Output(Cli_Input, s_prev);
                Cli_Input->Input_End(Cli_Input);
                is_invitation_print = 0;
            }
                break;
            case CLI_INPUT_ITEM_TYPE_DOWN:
            {
                char s_prev[CLI_INPUT_C_ITEM_TEXT_SIZE];
                int len = CLI_INPUT_C_ITEM_TEXT_SIZE - 1;
                strncpy(s_prev, Cli_Input->Input_Str_Get(Cli_Input), len);
                s_prev[len] = '\0';
                Cli_Input->Input_Str_Set(Cli_Input, History.History_Down(&History));
                Cli_Input->Input_Str_Modified_To_Output(Cli_Input, s_prev);
                Cli_Input->Input_End(Cli_Input);
                is_invitation_print = 0;
            }
                break;
            case CLI_INPUT_ITEM_TYPE_QUIT:
            {
                Cli_Output->Output_Str(Cli_Output, "Quit - Processed");
                Cli_Output->Output_NewLine(Cli_Output);
                stop = 1; // Quit
            }
                break;
            default:
                // Nothing
                break;
        }

        if (Cmd_Quit) {
            Cli_Output->Output_Str(Cli_Output, "Quit - Processed");
            Cli_Output->Output_NewLine(Cli_Output);
            stop = 1; // Quit
        }

    } while (!stop);

    Cli_Input->Input_Restore(Cli_Input);
    Cli_Output->Output_Close(Cli_Output);

    return 0;
}
