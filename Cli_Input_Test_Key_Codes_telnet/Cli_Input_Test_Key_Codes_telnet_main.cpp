/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_Input_Test_Key_Codes_telnet_main.cpp
 * Author: mike
 *
 * Created on May 23, 2023, 5:01 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <ctype.h>
#include <arpa/inet.h>

bool Input_Init(unsigned short Local_Port, int &Server_Sock, int &Session_Sock) {

    struct sockaddr_in Server_Address;
    int res_setsockopt = -1; // Failed
    int res_bind = -1; // Failed

    int Local_IP = INADDR_ANY;

    Server_Sock = socket(AF_INET, SOCK_STREAM, 0);
    if (Server_Sock >= 0) {
        int opt = 1;
        res_setsockopt = setsockopt(Server_Sock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof (opt));

        Server_Address.sin_family = AF_INET;
        Server_Address.sin_addr.s_addr = Local_IP;
        Server_Address.sin_port = htons(Local_Port);

        res_bind = bind(Server_Sock, (struct sockaddr*) &Server_Address, sizeof (Server_Address));

        int res_listen = listen(Server_Sock, 3);
        if (res_listen >= 0) {
            int addrlen = sizeof (Server_Address);
            Session_Sock = accept(Server_Sock, (struct sockaddr*) &Server_Address, (socklen_t*) & addrlen);

            if (Session_Sock >= 0) {
                write(Session_Sock, "\xFF\xFB\x01\xFF\xFB\x03", 6);
            }

        }

    }

    return true; // Ok
}

bool Input_Restore(int &Server_Sock, int &Session_Sock) {
    if (Session_Sock >= 0) {
        close(Session_Sock);
        Session_Sock = -1;
    }
    if (Server_Sock >= 0) {
        close(Server_Sock);
        Server_Sock = -1;
    }
    return true; // Ok
}

int Input_Get(int sock, unsigned char *buf, int buf_size) {
    int res_read = read(sock, buf, buf_size);
    return res_read;
}

int main(int argc, char** argv) {

    unsigned short Local_Port = 30002;

    int Server_Sock = -1;
    int Session_Sock = -1;

    const int buf_size = 4096;
    unsigned char read_buffer[buf_size];
    char send_buffer[buf_size];

    printf("Test Key Codes: Telnet\n");
    printf("Connect with Telnet on port %d\n", Local_Port);
    printf("(Q - quit)\n");

    Input_Init(Local_Port, Server_Sock, Session_Sock);

    bool stop = false;
    do {
        int res_get = Input_Get(Session_Sock, read_buffer, buf_size);
        if (res_get > 0) {
            int s_pos = 0;
            for (int i = 0; i < res_get; i++) {
                unsigned char c = read_buffer[i];
                s_pos += snprintf(send_buffer + s_pos, buf_size - s_pos, " 0x%02X", (c & 0xFF));
            }
            s_pos += snprintf(send_buffer + s_pos, buf_size - s_pos, "\r\n");
            printf("%s", send_buffer);
            write(Session_Sock, send_buffer, s_pos);
            if (read_buffer[0] == 'Q') {
                stop = true;
                printf("Session Closed by Command: Quit\n");
            }
        } else {
            if (res_get == 0) {
                stop = true;
                printf("Session Closed by Client\n");
            }
        }
    } while (!stop);

    Input_Restore(Server_Sock, Session_Sock);

    return 0;
}
