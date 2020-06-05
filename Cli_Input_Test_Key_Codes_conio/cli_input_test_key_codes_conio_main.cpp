/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   cli_input_test_key_codes_conio_main.cpp
 * Author: mike
 *
 * Created on June 5, 2020, 9:31 AM
 */

#include <stdio.h>
#include <conio.h>
#include <signal.h>

void SIGINT_Handler(int sig) { // Ctrl+C
    printf("Ctrl+C\n");
}

bool Input_Init() {
    signal(SIGINT, SIGINT_Handler); // Ctrl+C
    return true; // Ok
}

bool Input_Restore() {
    return true; // Ok
}

int Input_Char_Get() {
    return getch();
}

int main(int argc, char** argv) {

    Input_Init();
    
    printf("Test Key Codes: conio\n");

    bool stop = false;
    do {
        int c = Input_Char_Get();
        printf("0x%02X\n", c);
    } while (!stop);

    Input_Restore();

    return 0;
}
