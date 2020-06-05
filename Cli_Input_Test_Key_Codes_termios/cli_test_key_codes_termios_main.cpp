/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   cli_test_key_codes_termios_main.cpp
 * Author: mike
 *
 * Created on June 5, 2020, 9:06 AM
 */

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <termios.h>

struct termios terminal_state_prev;
struct termios terminal_state_new;

void SIGINT_Handler(int sig) { // Ctrl+C
    printf("Ctrl+C\n");
}

void SIGTSTP_Handler(int sig) { // Ctrl+Z
    printf("Ctrl+Z\n");
}

bool Input_Init() {

    signal(SIGINT, SIGINT_Handler); // Ctrl+C
    signal(SIGTSTP, SIGTSTP_Handler); // Ctrl+Z

    int res_tcgetattr = tcgetattr(STDIN_FILENO, &terminal_state_prev);
    terminal_state_new = terminal_state_prev;
    terminal_state_new.c_lflag &= ~(ICANON | ECHO);
    int res_tcsetattr = tcsetattr(STDIN_FILENO, TCSANOW, &terminal_state_new);

    if (res_tcgetattr == 0 && res_tcsetattr == 0) {
        return true; // Ok
    }

    return false; // Failed
}

bool Input_Restore() {
    int res_tcsetattr = tcsetattr(STDIN_FILENO, TCSANOW, &terminal_state_prev);

    if (res_tcsetattr == 0) {
        return true; // Ok
    }

    return false; // Failed
}

int Input_Char_Get() {
    return getchar();
}

int main(int argc, char** argv) {

    Input_Init();

    printf("Test Key Codes: termios\n");

    bool stop = false;
    do {
        int c = Input_Char_Get();
        printf("0x%02X\n", c);
    } while (!stop);

    Input_Restore();

    return 0;
}
