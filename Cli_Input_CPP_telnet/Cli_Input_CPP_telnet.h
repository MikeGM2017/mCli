/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_Input_CPP_telnet.h
 * Author: mike
 *
 * Created on May 23, 2023, 11:25 AM
 */

#ifndef CLI_INPUT_CPP_TELNET_H
#define CLI_INPUT_CPP_TELNET_H

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <ctype.h>
#include <arpa/inet.h>

#include "Cli_Input_Abstract.h"

class Cli_Input_CPP_telnet : public Cli_Input_Abstract {
protected:

    Cli_Output_Abstract &Cli_Output;

    int Local_IP;
    unsigned short Local_Port;

    int Buf_Size;

    int Server_Sock;
    int &Session_Sock;
    struct sockaddr_in Server_Address;

    unsigned char *read_buffer;
    char *send_buffer;

public:

    Cli_Input_CPP_telnet(int local_ip, unsigned short local_port, int buf_size,
            int &telnet_session_sock,
            Cli_Output_Abstract &cli_output) :
    Cli_Input_Abstract(cli_output),
    Cli_Output(cli_output),
    Local_IP(local_ip), Local_Port(local_port), Buf_Size(buf_size),
    Server_Sock(-1), Session_Sock(telnet_session_sock), read_buffer(0), send_buffer(0) {
    }

    virtual bool Input_Init() {
        int res_setsockopt = -1; // Failed
        int res_bind = -1; // Failed
        bool res_output_init = false; // Failed

        read_buffer = new unsigned char[Buf_Size];
        send_buffer = new char[Buf_Size];

        Server_Sock = socket(AF_INET, SOCK_STREAM, 0);
        if (Server_Sock >= 0) {
            int opt = 1;
            res_setsockopt = setsockopt(Server_Sock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof (opt));

            Server_Address.sin_family = AF_INET;
            Server_Address.sin_addr.s_addr = Local_IP;
            Server_Address.sin_port = htons(Local_Port);

            res_bind = bind(Server_Sock, (struct sockaddr*) &Server_Address, sizeof (Server_Address));
        }

        res_output_init = Cli_Output.Output_Init();

        return (Server_Sock >= 0 && res_setsockopt == 0 && res_bind == 0 && res_output_init);
    }

    virtual bool Input_Restore() {

        if (Session_Sock >= 0) {
            close(Session_Sock);
            Session_Sock = -1;
        }

        if (Server_Sock >= 0) {
            close(Server_Sock);
            Server_Sock = -1;
        }

        if (read_buffer) {
            delete[] read_buffer;
            read_buffer = 0;
        }

        if (send_buffer) {
            delete[] send_buffer;
            send_buffer = 0;
        }

        return Cli_Output.Output_Close();
    }

    virtual Cli_Input_Item Input_Item_Get() // Attention: Main Cli Input Method - Blocked
    {
        Cli_Input_Item Input_Item(CLI_INPUT_ITEM_TYPE_NO, "");

        if (Session_Sock < 0) {
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

                Cli_Output.Output_Str(Invitation_Full_Get()); //@Warning: Cli_Output_telnet Specific 
                Cli_Output.Output_Str(Input_Str_Get());
            }
        }

        if (Session_Sock >= 0) {

            bool stop = false;

            while (!stop) {

                int res_read = read(Session_Sock, read_buffer, Buf_Size);

                if (res_read > 0) {

                    switch (res_read) {
                        case 1:
                        {
                            char c = read_buffer[0];
                            switch (c) {
                                case 0x03: // Ctrl+C
                                    Input_Str_Clear();
                                    Cli_Output.Output_NewLine();
                                    Cli_Output.Output_Str(Invitation_Full_Get());
                                    break;
                                case 0x1A: // Ctrl+Z
                                    Input_Str_Clear();
                                    Cli_Output.Output_NewLine();
                                    Cli_Output.Output_Str(Invitation_Full_Get());
                                    break;
                                case 0x1C: // Ctrl+"\"
                                    Input_Item.Text_Set(Input_Str);
                                    Input_Item.Type_Set(CLI_INPUT_ITEM_TYPE_QUIT);
                                    Input_Str_Clear();
                                    Cli_Output.Output_NewLine();
                                    Cli_Output.Output_Str("Ctrl+\\");
                                    Cli_Output.Output_NewLine();
                                    stop = true;
                                    break;
                                case 0x09: // TAB
                                    Input_Item.Text_Set(Input_Str);
                                    Input_Item.Type_Set(CLI_INPUT_ITEM_TYPE_TAB);
                                    stop = true;
                                    break;
                                case 0x7F: // BACK
                                    Input_Back();
                                    break;
                                default:
                                    if (isprint(c)) {
                                        Input_Add(read_buffer[0]);
                                    }
                            }
                        }
                            break;
                        case 2:
                        {
                            char c1 = read_buffer[0];
                            char c2 = read_buffer[1];
                            if (c1 == 0x0D && ((c2 == 0x0A) || (c2 == 0x00))) { // ENTER
                                Input_Item.Text_Set(Input_Str);
                                Input_Item.Type_Set(CLI_INPUT_ITEM_TYPE_STR);
                                Input_Str_Clear();
                                stop = true;
                            }
                        }
                            break;
                        case 3:
                        {
                            char c1 = read_buffer[0];
                            char c2 = read_buffer[1];
                            char c3 = read_buffer[2];
                            if (c1 == 0x1B && c2 == 0x5B && c3 == 0x41) { // UP
                                Input_Item.Text_Set(Input_Str);
                                Input_Item.Type_Set(CLI_INPUT_ITEM_TYPE_UP);
                                stop = true;
                            } else if (c1 == 0x1B && c2 == 0x5B && c3 == 0x42) { // DOWN
                                Input_Item.Text_Set(Input_Str);
                                Input_Item.Type_Set(CLI_INPUT_ITEM_TYPE_DOWN);
                                stop = true;
                            } else if (c1 == 0x1B && c2 == 0x5B && c3 == 0x43) { // RIGHT
                                Input_Right();
                            } else if (c1 == 0x1B && c2 == 0x5B && c3 == 0x44) { // LEFT
                                Input_Left();
                            } else if (c1 == 0x1B && c2 == 0x5B && c3 == 0x48) { // HOME
                                Input_Home();
                            } else if (c1 == 0x1B && c2 == 0x5B && c3 == 0x46) { // END
                                Input_End();
                            }
                        }
                            break;
                        case 4:
                        {
                            char c1 = read_buffer[0];
                            char c2 = read_buffer[1];
                            char c3 = read_buffer[2];
                            char c4 = read_buffer[3];
                            if (c1 == 0x1B && c2 == 0x5B && c3 == 0x31 && c4 == 0x7E) { // HOME
                                Input_Home();
                            } else if (c1 == 0x1B && c2 == 0x5B && c3 == 0x33 && c4 == 0x7E) { // DELETE
                                Input_Delete();
                            } else if (c1 == 0x1B && c2 == 0x5B && c3 == 0x34 && c4 == 0x7E) { // END
                                Input_End();
                            }
                        }
                            break;
                    }

                }

            }

        }

        return Input_Item;
    }

    virtual bool Input_sleep(int sleep_sec) {
        sleep(sleep_sec);
    }

    virtual bool Input_kbhit() // Attention: Not Blocked
    {
        if (Session_Sock >= 0) {
            int res_read = read(Session_Sock, read_buffer, Buf_Size);
            if (res_read > 0) {
                return true;
            }
        }
        return false;
    }

};

#endif /* CLI_INPUT_CPP_TELNET_H */
