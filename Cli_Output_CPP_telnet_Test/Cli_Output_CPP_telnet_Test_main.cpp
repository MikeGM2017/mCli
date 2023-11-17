/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_Output_CPP_telnet_Test_main.cpp
 * Author: mike
 *
 * Created on May 23, 2023, 3:06 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <ctype.h>
#include <arpa/inet.h>

#include "Cli_Output_telnet.h"

int telnet_getchar(int &Session_Sock) {
    const int Buf_Size = 4096;
    char read_buffer[Buf_Size];
    while (1) {
        if (Session_Sock >= 0) {
            int res_read = read(Session_Sock, read_buffer, Buf_Size);
            if (res_read > 0) {
                return read_buffer[0];
            }
        }
    }
    return 0;
}

int main(int argc, char** argv) {

    int Session_Sock = -1;

    Cli_Output_telnet Cli_Output(Session_Sock);

    Cli_Output.Output_Init();

    // Telnet session Init - Beg
    struct sockaddr_in Server_Address;
    int res_setsockopt = -1; // Failed
    int res_bind = -1; // Failed

    int Local_IP = INADDR_ANY;
    unsigned short Local_Port = 30002;

    int Server_Sock = socket(AF_INET, SOCK_STREAM, 0);
    if (Server_Sock >= 0) {
        int opt = 1;
        res_setsockopt = setsockopt(Server_Sock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof (opt));

        Server_Address.sin_family = AF_INET;
        Server_Address.sin_addr.s_addr = Local_IP;
        Server_Address.sin_port = htons(Local_Port);

        res_bind = bind(Server_Sock, (struct sockaddr*) &Server_Address, sizeof (Server_Address));
    }

    printf("Cli_Output_CPP_telnet_Test:\n");
    printf("Connect with Telnet on port %d\n", Local_Port);

    int res_listen = listen(Server_Sock, 3);
    if (res_listen >= 0) {
        int addrlen = sizeof (Server_Address);
        Session_Sock = accept(Server_Sock, (struct sockaddr*) &Server_Address, (socklen_t*) & addrlen);

        int timeout = 1000;
        if (timeout) {
            struct timeval tv;
            tv.tv_sec = timeout / 1000000;
            tv.tv_usec = timeout;
            setsockopt(Session_Sock, SOL_SOCKET, SO_RCVTIMEO, (struct timeval *) &tv, sizeof (struct timeval));
        }

        // Set Character Mode (Ubuntu: telnet/Putty, Windows: Putty)
        // CMD Will Echo
        // CMD Will Suppress Go Ahead
        write(Session_Sock, "\xFF\xFB\x01\xFF\xFB\x03", 6);

        telnet_getchar(Session_Sock);
    }
    // Telnet session Init - End

    Cli_Output.Output_Char('X');
    Cli_Output.Output_NewLine();
    Cli_Output.Output_Str(" - Ok");
    Cli_Output.Output_NewLine();
    Cli_Output.Output_Str("End");
    Cli_Output.Output_Return();

    telnet_getchar(Session_Sock);

    bool res_clear = Cli_Output.Output_Clear();
    Cli_Output.Output_NewLine();
    if (res_clear)
        Cli_Output.Output_Str("Cleared");
    else
        Cli_Output.Output_Str("Not Cleared");

    telnet_getchar(Session_Sock);

    Cli_Output.Output_Close();

    return 0;
}
