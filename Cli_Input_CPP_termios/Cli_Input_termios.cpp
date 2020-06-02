/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Cli_Input_termios.h"

Cli_Input_Abstract *Cli_Input_termios::CliInput_Object = NULL;

void Cli_Input_termios::SIGINT_Handler(int sig) { // Ctrl+C
    if (CliInput_Object) {
        CliInput_Object->Input_Str_Clear();
        cout << endl << CliInput_Object->Invitation_Full_Get();
        cout.flush();
    }
}

void Cli_Input_termios::SIGTSTP_Handler(int sig) { // Ctrl+Z
    if (CliInput_Object) {
        CliInput_Object->Input_Str_Clear();
        cout << endl << CliInput_Object->Invitation_Full_Get();
        cout.flush();
    }
}

bool Cli_Input_termios::Input_Init() {
    CliInput_Object = this;

    signal(SIGINT, SIGINT_Handler); // Ctrl+C
    signal(SIGTSTP, SIGTSTP_Handler); // Ctrl+Z

    int res_tcgetattr = tcgetattr(STDIN_FILENO, &terminal_state_prev);
    terminal_state_new = terminal_state_prev;
    terminal_state_new.c_lflag &= ~(ICANON | ECHO);
    int res_tcsetattr = tcsetattr(STDIN_FILENO, TCSANOW, &terminal_state_new);

    if (res_tcgetattr == 0 && res_tcsetattr == 0)
        return true; // Ok

    return false; // Failed
}

bool Cli_Input_termios::Input_Restore() {
    int res_tcsetattr = tcsetattr(STDIN_FILENO, TCSANOW, &terminal_state_prev);

    if (res_tcsetattr == 0)
        return true; // Ok

    return false; // Failed
}

Cli_Input_Item Cli_Input_termios::Input_Item_Get() {
    bool stop = false;

    Cli_Input_Item Input_Item(CLI_INPUT_ITEM_TYPE_NO, "");

    do {
        int c = getchar();
        switch (c) {
            case '\n':
                Input_Item.Text_Set(Input_Str);
                Input_Item.Type_Set(CLI_INPUT_ITEM_TYPE_STR);
                Input_Str_Clear();
                stop = true;
                break;
            default:
                Input_Str += c;
                cout << (char) c;
                cout.flush();
        }
    } while (!stop);

    return Input_Item;
};
