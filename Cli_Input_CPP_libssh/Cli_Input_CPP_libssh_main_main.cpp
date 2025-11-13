/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_Input_CPP_libssh_main.cpp
 * Author: mike
 *
 * Created on November 13, 2025, 9:27 AM
 */

#include "config.h"

#include <libssh/callbacks.h>
#include <libssh/poll.h>
#include <libssh/server.h>

#ifdef HAVE_ARGP_H
#include <argp.h>
#endif
#include <fcntl.h>
#ifdef HAVE_LIBUTIL_H
#include <libutil.h>
#endif
#ifdef HAVE_PTY_H
#include <pty.h>
#endif
#include <signal.h>
#include <stdlib.h>
#ifdef HAVE_UTMP_H
#include <utmp.h>
#endif
#ifdef HAVE_UTIL_H
#include <util.h>
#endif
#include <sys/ioctl.h>
#include <sys/wait.h>
#include <stdio.h>

#include <string>
#include <vector>
#include <sstream>

using namespace std;

#ifndef KEYS_FOLDER
#ifdef _WIN32
#define KEYS_FOLDER
#else
#define KEYS_FOLDER "/etc/ssh/"
#endif
#endif

//#define USER "myuser"
//#define PASS "mypassword"
#define USER "m"
#define PASS "m"
#define BUF_SIZE 1048576
#define SESSION_END (SSH_CLOSED | SSH_CLOSED_ERROR)
#define SFTP_SERVER_PATH "/usr/lib/sftp-server"

static void set_default_keys(ssh_bind sshbind,
        int rsa_already_set,
        int dsa_already_set,
        int ecdsa_already_set) {
    if (!rsa_already_set) {
        ssh_bind_options_set(sshbind, SSH_BIND_OPTIONS_RSAKEY,
                KEYS_FOLDER "ssh_host_rsa_key");
    }
    if (!dsa_already_set) {
        ssh_bind_options_set(sshbind, SSH_BIND_OPTIONS_DSAKEY,
                KEYS_FOLDER "ssh_host_dsa_key");
    }
    if (!ecdsa_already_set) {
        ssh_bind_options_set(sshbind, SSH_BIND_OPTIONS_ECDSAKEY,
                KEYS_FOLDER "ssh_host_ecdsa_key");
    }
}

#ifdef HAVE_ARGP_H
const char *argp_program_version = "libssh server example "
        SSH_STRINGIFY(LIBSSH_VERSION);
const char *argp_program_bug_address = "<libssh@libssh.org>";

/* Program documentation. */
static char doc[] = "libssh -- a Secure Shell protocol implementation";

/* A description of the arguments we accept. */
static char args_doc[] = "BINDADDR";

/* The options we understand. */
static struct argp_option options[] = {
    {
        .name = "port",
        .key = 'p',
        .arg = "PORT",
        .flags = 0,
        .doc = "Set the port to bind.",
        .group = 0
    },
    {
        .name = "hostkey",
        .key = 'k',
        .arg = "FILE",
        .flags = 0,
        .doc = "Set a host key.  Can be used multiple times.  "
        "Implies no default keys.",
        .group = 0
    },
    {
        .name = "dsakey",
        .key = 'd',
        .arg = "FILE",
        .flags = 0,
        .doc = "Set the dsa key.",
        .group = 0
    },
    {
        .name = "rsakey",
        .key = 'r',
        .arg = "FILE",
        .flags = 0,
        .doc = "Set the rsa key.",
        .group = 0
    },
    {
        .name = "ecdsakey",
        .key = 'e',
        .arg = "FILE",
        .flags = 0,
        .doc = "Set the ecdsa key.",
        .group = 0
    },
    {
        .name = "no-default-keys",
        .key = 'n',
        .arg = NULL,
        .flags = 0,
        .doc = "Do not set default key locations.",
        .group = 0
    },
    {
        .name = "verbose",
        .key = 'v',
        .arg = NULL,
        .flags = 0,
        .doc = "Get verbose output.",
        .group = 0
    },
    {NULL, 0, NULL, 0, NULL, 0}
};

/* Parse a single option. */
static error_t parse_opt(int key, char *arg, struct argp_state *state) {
    /* Get the input argument from argp_parse, which we
     * know is a pointer to our arguments structure. */
    ssh_bind sshbind = (ssh_bind) state->input;
    static int no_default_keys = 0;
    static int rsa_already_set = 0, dsa_already_set = 0, ecdsa_already_set = 0;

    switch (key) {
        case 'n':
            no_default_keys = 1;
            break;
        case 'p':
            ssh_bind_options_set(sshbind, SSH_BIND_OPTIONS_BINDPORT_STR, arg);
            break;
        case 'd':
            ssh_bind_options_set(sshbind, SSH_BIND_OPTIONS_DSAKEY, arg);
            dsa_already_set = 1;
            break;
        case 'k':
            ssh_bind_options_set(sshbind, SSH_BIND_OPTIONS_HOSTKEY, arg);
            /* We can't track the types of keys being added with this
               option, so let's ensure we keep the keys we're adding
               by just not setting the default keys */
            no_default_keys = 1;
            break;
        case 'r':
            ssh_bind_options_set(sshbind, SSH_BIND_OPTIONS_RSAKEY, arg);
            rsa_already_set = 1;
            break;
        case 'e':
            ssh_bind_options_set(sshbind, SSH_BIND_OPTIONS_ECDSAKEY, arg);
            ecdsa_already_set = 1;
            break;
        case 'v':
            ssh_bind_options_set(sshbind, SSH_BIND_OPTIONS_LOG_VERBOSITY_STR,
                    "3");
            break;
        case ARGP_KEY_ARG:
            if (state->arg_num >= 1) {
                /* Too many arguments. */
                argp_usage(state);
            }
            ssh_bind_options_set(sshbind, SSH_BIND_OPTIONS_BINDADDR, arg);
            break;
        case ARGP_KEY_END:
            if (state->arg_num < 1) {
                /* Not enough arguments. */
                argp_usage(state);
            }

            if (!no_default_keys) {
                set_default_keys(sshbind,
                        rsa_already_set,
                        dsa_already_set,
                        ecdsa_already_set);
            }

            break;
        default:
            return ARGP_ERR_UNKNOWN;
    }
    return 0;
}

/* Our argp parser. */
static struct argp argp = {options, parse_opt, args_doc, doc, NULL, NULL, NULL};
#endif /* HAVE_ARGP_H */

/* A userdata struct for channel. */
struct channel_data_struct {
    /* pid of the child process the channel will spawn. */
    pid_t pid;
    /* For PTY allocation */
    socket_t pty_master;
    socket_t pty_slave;
    /* For communication with the child process. */
    socket_t child_stdin;
    socket_t child_stdout;
    /* Only used for subsystem and exec requests. */
    socket_t child_stderr;
    /* Event which is used to poll the above descriptors. */
    ssh_event event;
    /* Terminal size struct. */
    struct winsize *winsize;
};

/* A userdata struct for session. */
struct session_data_struct {
    /* Pointer to the channel the session will allocate. */
    ssh_channel channel;
    int auth_attempts;
    int authenticated;
};

string Input_Str;
int Input_Str_Pos = 0;

void Input_Str_Clear() {
    Input_Str.clear();
    Input_Str_Pos = 0;
}

void Input_Str_Add(char c) {
    if (Input_Str_Pos == Input_Str.length()) { // Add to end
        Input_Str.push_back(c);
        Input_Str_Pos++;
        return;
    }
    if (Input_Str_Pos >= 0) { // Add to Input_Str_Pos
        Input_Str.insert(Input_Str.begin() + Input_Str_Pos, 1, c);
        Input_Str_Pos++;
        return;
    }
}

void Input_Str_Left() {
    if (Input_Str_Pos > 0) {
        Input_Str_Pos--;
    }
}

void Input_Str_Right() {
    if (Input_Str_Pos < Input_Str.length()) {
        Input_Str_Pos++;
    }
}

void Input_Str_Home() {
    Input_Str_Pos = 0;
}

void Input_Str_End() {
    Input_Str_Pos = Input_Str.length();
}

void Input_Str_Back() {
    if (Input_Str.length()) {
        if (Input_Str_Pos > 0) {
            Input_Str.erase(Input_Str.begin() + Input_Str_Pos - 1);
            Input_Str_Pos--;
        }
    }
}

void Input_Str_Delete() {
    if (Input_Str.length()) {
        if (Input_Str_Pos < Input_Str.length()) {
            Input_Str.erase(Input_Str.begin() + Input_Str_Pos);
        }
    }
}

vector<string> History;
int History_Pos = 0;

bool Is_Space(char c) {
    switch (c) {
        case ' ':
        case '\t':
            return true;
    }
    return false;
}

string Str_Trim(string s_in) {
    if (s_in.empty()) {
        return "";
    }
    string s;
    int pos_beg = 0;
    for (int i = 0; i < s_in.length(); i++) {
        char c = s_in[i];
        if (Is_Space(c)) {
            pos_beg++;
        } else {
            break;
        }
    }
    int pos_end = s_in.length();
    for (int i = s_in.length() - 1; i >= 0; i--) {
        char c = s_in[i];
        if (Is_Space(c)) {
            pos_end--;
        } else {
            break;
        }
    }
    if (pos_beg < pos_end) {
        s = s_in.substr(pos_beg, pos_end - pos_beg);
    }
    return s;
}

void History_Add(string s_in) {
    string s = Str_Trim(s_in);
    if (!s.empty()) {
        if (History.empty() || History.back() != s) {
            History.push_back(s);
        }
    }
    History_Pos = History.size();
}

string History_Print() {
    stringstream s_str;
    if (History.empty()) {
        s_str << "\r\nHistory[" << History_Pos << "/" << History.size() << "]: empty\r\n";
    } else {
        s_str << "\r\nHistory[" << History_Pos << "/" << History.size() << "]:\r\n";
        for (int i = 0; i < History.size(); i++) {
            s_str << "[" << i << "] \"" << History[i] << "\"\r\n";
        }
    }
    return s_str.str();
}

string History_Up() {
    if (History_Pos > -1) {
        History_Pos--;
    }
    if (History_Pos < History.size()) {
        return History[History_Pos];
    } else {
        return "";
    }
}

string History_Down() {
    if (History_Pos == -1 || History_Pos < History.size()) {
        History_Pos++;
    }
    if (History_Pos < History.size()) {
        return History[History_Pos];
    } else {
        return "";
    }
}

static int data_function(ssh_session session, ssh_channel channel, void *data,
        uint32_t len, int is_stderr, void *userdata) {
    struct channel_data_struct *cdata = (struct channel_data_struct *) userdata;

    (void) session;
    (void) channel;
    (void) is_stderr;

    if (len == 0 || cdata->pid < 1 || kill(cdata->pid, 0) < 0) {
        return 0;
    } // return 0; - Failed

    char *d = (char *) data;
    char wr_buf[1024];
    int wr_buf_len = 0;
    int i;
    char c;
    int processed = 0;

    if (len > 0) {
        wr_buf_len += sprintf(wr_buf + wr_buf_len, "\r\n");
    } // Add "\r\n"

    switch (len) {
        case 1: // Esc
            if (d[0] == 0x1B) { // Esc
                wr_buf_len += sprintf(wr_buf + wr_buf_len, " 0x%02X - Esc", d[0]);
                Input_Str_Clear();
                processed = 1;
            }
            break;
        case 3: // SHIFT+TAB UP DOWN RIGHT LEFT HOME END
            if (d[0] == 0x1B && d[1] == 0x5B) {
                switch (d[2]) {
                    case 0x5A: // SHIFT+TAB
                    {
                        wr_buf_len += sprintf(wr_buf + wr_buf_len, " 0x%02X 0x%02X 0x%02X - SHIFT+TAB", d[0], d[1], d[2]);
                        if (Input_Str.length()) {
                            wr_buf_len += sprintf(wr_buf + wr_buf_len, "\r\nSHIFT+TAB Process: \"%s\"", Input_Str.c_str());
                            Input_Str_End();
                        } else {
                            wr_buf_len += sprintf(wr_buf + wr_buf_len, "\r\nSHIFT+TAB Process: \"default help\"");
                        }
                        processed = 1;
                    }
                        break;
                    case 0x41: // UP
                    {
                        wr_buf_len += sprintf(wr_buf + wr_buf_len, " 0x%02X 0x%02X 0x%02X - UP", d[0], d[1], d[2]);
                        string s = History_Up();
                        Input_Str = s;
                        Input_Str_Pos = s.length();
                        processed = 1;
                    }
                        break;
                    case 0x42: // DOWN
                    {
                        wr_buf_len += sprintf(wr_buf + wr_buf_len, " 0x%02X 0x%02X 0x%02X - DOWN", d[0], d[1], d[2]);
                        string s = History_Down();
                        Input_Str = s;
                        Input_Str_Pos = s.length();
                        processed = 1;
                    }
                        break;
                    case 0x43: // RIGHT
                    {
                        wr_buf_len += sprintf(wr_buf + wr_buf_len, " 0x%02X 0x%02X 0x%02X - RIGHT", d[0], d[1], d[2]);
                        Input_Str_Right();
                        processed = 1;
                    }
                        break;
                    case 0x44: // LEFT
                    {
                        wr_buf_len += sprintf(wr_buf + wr_buf_len, " 0x%02X 0x%02X 0x%02X - LEFT", d[0], d[1], d[2]);
                        Input_Str_Left();
                        processed = 1;
                    }
                        break;
                    case 0x48: // HOME
                    {
                        wr_buf_len += sprintf(wr_buf + wr_buf_len, " 0x%02X 0x%02X 0x%02X - HOME", d[0], d[1], d[2]);
                        Input_Str_Home();
                        processed = 1;
                    }
                        break;
                    case 0x46: // END
                    {
                        wr_buf_len += sprintf(wr_buf + wr_buf_len, " 0x%02X 0x%02X 0x%02X - END", d[0], d[1], d[2]);
                        Input_Str_End();
                        processed = 1;
                    }
                        break;
                }
            }
            break;
        case 4: // DELETE INSERT END HOME PAGEUP PAGEDOWN
            if (d[0] == 0x1B && d[1] == 0x5B && d[3] == 0x7E) {
                switch (d[2]) {
                    case 0x33: // DELETE
                    {
                        wr_buf_len += sprintf(wr_buf + wr_buf_len, " 0x%02X 0x%02X 0x%02X 0x%02X - DELETE", d[0], d[1], d[2], d[3]);
                        Input_Str_Delete();
                        processed = 1;
                    }
                        break;
                    case 0x32: // INSERT
                    {
                        wr_buf_len += sprintf(wr_buf + wr_buf_len, " 0x%02X 0x%02X 0x%02X 0x%02X - INSERT", d[0], d[1], d[2], d[3]);
                        processed = 1;
                    }
                        break;
                    case 0x34: // END
                    {
                        wr_buf_len += sprintf(wr_buf + wr_buf_len, " 0x%02X 0x%02X 0x%02X 0x%02X - END", d[0], d[1], d[2], d[3]);
                        Input_Str_End();
                        processed = 1;
                    }
                        break;
                    case 0x31: // HOME
                    {
                        wr_buf_len += sprintf(wr_buf + wr_buf_len, " 0x%02X 0x%02X 0x%02X 0x%02X - HOME", d[0], d[1], d[2], d[3]);
                        Input_Str_Home();
                        processed = 1;
                    }
                        break;
                    case 0x35: // PAGEUP
                    {
                        wr_buf_len += sprintf(wr_buf + wr_buf_len, " 0x%02X 0x%02X 0x%02X 0x%02X - PAGEUP", d[0], d[1], d[2], d[3]);
                        string s = History_Print();
                        wr_buf_len += sprintf(wr_buf + wr_buf_len, "%s", s.c_str());
                        processed = 1;
                    }
                        break;
                    case 0x36: // PAGEDOWN
                    {
                        wr_buf_len += sprintf(wr_buf + wr_buf_len, " 0x%02X 0x%02X 0x%02X 0x%02X - PAGEDOWN", d[0], d[1], d[2], d[3]);
                        string s = History_Print();
                        wr_buf_len += sprintf(wr_buf + wr_buf_len, "%s", s.c_str());
                        processed = 1;
                    }
                        break;
                }
            }
            break;
    } // Esc SHIFT+TAB UP DOWN RIGHT LEFT HOME END DELETE INSERT END HOME PAGEUP PAGEDOWN

    if (!processed) {
        for (i = 0; i < len; i++) {
            c = d[i];
            wr_buf_len += sprintf(wr_buf + wr_buf_len, " 0x%02X", c & 0xFF);
            switch (c) {
                case 0x09:
                    wr_buf_len += sprintf(wr_buf + wr_buf_len, " - TAB");
                    if (Input_Str.length()) {
                        wr_buf_len += sprintf(wr_buf + wr_buf_len, "\r\nTAB Process: \"%s\"", Input_Str.c_str());
                        Input_Str_End();
                    } else {
                        wr_buf_len += sprintf(wr_buf + wr_buf_len, "\r\nTAB Process: \"default help\"");
                    }
                    break;
                case 0x0D:
                    wr_buf_len += sprintf(wr_buf + wr_buf_len, " - Enter");
                    if (Input_Str.length()) {
                        wr_buf_len += sprintf(wr_buf + wr_buf_len, "\r\nEnter Process: \"%s\"", Input_Str.c_str());
                        History_Add(Input_Str);
                        Input_Str_Clear();
                    }
                    break;
                case 0x03:
                    wr_buf_len += sprintf(wr_buf + wr_buf_len, " - Ctrl+C");
                    Input_Str_Clear();
                    break;
                case 0x1A:
                    wr_buf_len += sprintf(wr_buf + wr_buf_len, " - Ctrl+Z");
                    Input_Str_Clear();
                    break;
                case 0x1C:
                    wr_buf_len += sprintf(wr_buf + wr_buf_len, " - Ctrl+Backslash");
                    Input_Str_Clear();
                    break;
                case 0x7F:
                    wr_buf_len += sprintf(wr_buf + wr_buf_len, " - Back");
                    Input_Str_Back();
                    break;
                case 0x08:
                    wr_buf_len += sprintf(wr_buf + wr_buf_len, " - Shift+Back");
                    break;
                case 0x1B:
                    wr_buf_len += sprintf(wr_buf + wr_buf_len, " - Esc");
                    Input_Str_Clear();
                    break;
                default: // Others
                {
                    if (isprint(c)) {
                        wr_buf_len += sprintf(wr_buf + wr_buf_len, " - \'%c\'", c);
                        Input_Str_Add(c);
                    } else {
                        wr_buf_len += sprintf(wr_buf + wr_buf_len, " - .");
                        Input_Str_Add('.');
                    }
                }
            } // TAB Enter Ctrl+C Ctrl+Z Ctrl+Backslash Back Shift+Back Esc Others
        }
    } // TAB Enter Ctrl+C Ctrl+Z Ctrl+Backslash Back Shift+Back Esc Others

    wr_buf_len += sprintf(wr_buf + wr_buf_len, " Input_Str:\"%s\"/%d", Input_Str.c_str(), Input_Str_Pos);

    if (wr_buf_len > 0) {
        ssh_channel_write(channel, wr_buf, wr_buf_len);
    } // ssh_channel_write(...)

    return len; // Ok
}

static int pty_request(ssh_session session, ssh_channel channel,
        const char *term, int cols, int rows, int py, int px,
        void *userdata) {
    struct channel_data_struct *cdata = (struct channel_data_struct *) userdata;

    (void) session;
    (void) channel;
    (void) term;

    cdata->winsize->ws_row = rows;
    cdata->winsize->ws_col = cols;
    cdata->winsize->ws_xpixel = px;
    cdata->winsize->ws_ypixel = py;

    if (openpty(&cdata->pty_master, &cdata->pty_slave, NULL, NULL,
            cdata->winsize) != 0) {
        fprintf(stderr, "Failed to open pty\n");
        return SSH_ERROR;
    }
    return SSH_OK;
}

static int pty_resize(ssh_session session, ssh_channel channel, int cols,
        int rows, int py, int px, void *userdata) {
    struct channel_data_struct *cdata = (struct channel_data_struct *) userdata;

    (void) session;
    (void) channel;

    cdata->winsize->ws_row = rows;
    cdata->winsize->ws_col = cols;
    cdata->winsize->ws_xpixel = px;
    cdata->winsize->ws_ypixel = py;

    if (cdata->pty_master != -1) {
        return ioctl(cdata->pty_master, TIOCSWINSZ, cdata->winsize);
    }

    return SSH_ERROR;
}

static int exec_pty(const char *mode, const char *command,
        struct channel_data_struct *cdata) {
    switch (cdata->pid = fork()) {
        case -1:
            close(cdata->pty_master);
            close(cdata->pty_slave);
            fprintf(stderr, "Failed to fork\n");
            return SSH_ERROR;
        case 0:
            close(cdata->pty_master);
            if (login_tty(cdata->pty_slave) != 0) {
                exit(1);
            }
            execl("/bin/sh", "sh", mode, command, NULL);
            exit(0);
        default:
            close(cdata->pty_slave);
            /* pty fd is bi-directional */
            cdata->child_stdout = cdata->child_stdin = cdata->pty_master;
    }
    return SSH_OK;
}

static int exec_nopty(const char *command, struct channel_data_struct *cdata) {
    int in[2], out[2], err[2];

    /* Do the plumbing to be able to talk with the child process. */
    if (pipe(in) != 0) {
        goto stdin_failed;
    }
    if (pipe(out) != 0) {
        goto stdout_failed;
    }
    if (pipe(err) != 0) {
        goto stderr_failed;
    }

    switch (cdata->pid = fork()) {
        case -1:
            goto fork_failed;
        case 0:
            /* Finish the plumbing in the child process. */
            close(in[1]);
            close(out[0]);
            close(err[0]);
            dup2(in[0], STDIN_FILENO);
            dup2(out[1], STDOUT_FILENO);
            dup2(err[1], STDERR_FILENO);
            close(in[0]);
            close(out[1]);
            close(err[1]);
            /* exec the requested command. */
            execl("/bin/sh", "sh", "-c", command, NULL);
            exit(0);
    }

    close(in[0]);
    close(out[1]);
    close(err[1]);

    cdata->child_stdin = in[1];
    cdata->child_stdout = out[0];
    cdata->child_stderr = err[0];

    return SSH_OK;

fork_failed:
    close(err[0]);
    close(err[1]);
stderr_failed:
    close(out[0]);
    close(out[1]);
stdout_failed:
    close(in[0]);
    close(in[1]);
stdin_failed:
    return SSH_ERROR;
}

static int exec_request(ssh_session session, ssh_channel channel,
        const char *command, void *userdata) {
    struct channel_data_struct *cdata = (struct channel_data_struct *) userdata;


    (void) session;
    (void) channel;

    if (cdata->pid > 0) {
        return SSH_ERROR;
    }

    if (cdata->pty_master != -1 && cdata->pty_slave != -1) {
        return exec_pty("-c", command, cdata);
    }
    return exec_nopty(command, cdata);
}

static int shell_request(ssh_session session, ssh_channel channel,
        void *userdata) {
    struct channel_data_struct *cdata = (struct channel_data_struct *) userdata;

    (void) session;
    (void) channel;

    if (cdata->pid > 0) {
        return SSH_ERROR;
    }

    if (cdata->pty_master != -1 && cdata->pty_slave != -1) {
        return exec_pty("-l", NULL, cdata);
    }
    /* Client requested a shell without a pty, let's pretend we allow that */
    return SSH_OK;
}

static int subsystem_request(ssh_session session, ssh_channel channel,
        const char *subsystem, void *userdata) {
    /* subsystem requests behave simillarly to exec requests. */
    if (strcmp(subsystem, "sftp") == 0) {
        return exec_request(session, channel, SFTP_SERVER_PATH, userdata);
    }
    return SSH_ERROR;
}

static int auth_password(ssh_session session, const char *user,
        const char *pass, void *userdata) {
    struct session_data_struct *sdata = (struct session_data_struct *) userdata;

    (void) session;

    if (strcmp(user, USER) == 0 && strcmp(pass, PASS) == 0) {
        sdata->authenticated = 1;
        return SSH_AUTH_SUCCESS;
    }

    sdata->auth_attempts++;
    return SSH_AUTH_DENIED;
}

static ssh_channel channel_open(ssh_session session, void *userdata) {
    struct session_data_struct *sdata = (struct session_data_struct *) userdata;

    sdata->channel = ssh_channel_new(session);
    return sdata->channel;
}

static int process_stdout(socket_t fd, int revents, void *userdata) {
    char buf[BUF_SIZE];
    int n = -1;
    ssh_channel channel = (ssh_channel) userdata;

    if (channel != NULL && (revents & POLLIN) != 0) {
        n = read(fd, buf, BUF_SIZE);
        if (n > 0) {
            ssh_channel_write(channel, buf, n);
        }
    }

    return n;
}

static int process_stderr(socket_t fd, int revents, void *userdata) {
    char buf[BUF_SIZE];
    int n = -1;
    ssh_channel channel = (ssh_channel) userdata;

    if (channel != NULL && (revents & POLLIN) != 0) {
        n = read(fd, buf, BUF_SIZE);
        if (n > 0) {
            ssh_channel_write_stderr(channel, buf, n);
        }
    }

    return n;
}

static void handle_session(ssh_event event, ssh_session session) {
    int n, rc;

    /* Structure for storing the pty size. */
    struct winsize wsize = {
        .ws_row = 0,
        .ws_col = 0,
        .ws_xpixel = 0,
        .ws_ypixel = 0
    };

    /* Our struct holding information about the channel. */
    struct channel_data_struct cdata = {
        .pid = 0,
        .pty_master = -1,
        .pty_slave = -1,
        .child_stdin = -1,
        .child_stdout = -1,
        .child_stderr = -1,
        .event = NULL,
        .winsize = &wsize
    };

    /* Our struct holding information about the session. */
    struct session_data_struct sdata = {
        .channel = NULL,
        .auth_attempts = 0,
        .authenticated = 0
    };

    struct ssh_channel_callbacks_struct channel_cb;
    {
        memset(&channel_cb, 0, sizeof (channel_cb));
        channel_cb.userdata = &cdata;
        channel_cb.channel_pty_request_function = pty_request;
        channel_cb.channel_pty_window_change_function = pty_resize;
        channel_cb.channel_shell_request_function = shell_request;
        channel_cb.channel_exec_request_function = exec_request;
        channel_cb.channel_data_function = data_function;
        channel_cb.channel_subsystem_request_function = subsystem_request;
    }

    struct ssh_server_callbacks_struct server_cb;
    {
        memset(&server_cb, 0, sizeof (server_cb));
        server_cb.userdata = &sdata;
        server_cb.auth_password_function = auth_password;
        server_cb.channel_open_request_session_function = channel_open;
    }

    ssh_callbacks_init(&server_cb);
    ssh_callbacks_init(&channel_cb);

    ssh_set_server_callbacks(session, &server_cb);

    if (ssh_handle_key_exchange(session) != SSH_OK) {
        fprintf(stderr, "%s\n", ssh_get_error(session));
        return;
    }

    ssh_set_auth_methods(session, SSH_AUTH_METHOD_PASSWORD);
    ssh_event_add_session(event, session);

    n = 0;
    while (sdata.authenticated == 0 || sdata.channel == NULL) {
        /* If the user has used up all attempts, or if he hasn't been able to
         * authenticate in 10 seconds (n * 100ms), disconnect. */
        if (sdata.auth_attempts >= 3 || n >= 100) {
            return;
        }

        if (ssh_event_dopoll(event, 100) == SSH_ERROR) {
            fprintf(stderr, "%s\n", ssh_get_error(session));
            return;
        }
        n++;
    }

    ssh_set_channel_callbacks(sdata.channel, &channel_cb);

    do {
        /* Poll the main event which takes care of the session, the channel and
         * even our child process's stdout/stderr (once it's started). */
        if (ssh_event_dopoll(event, -1) == SSH_ERROR) {
            ssh_channel_close(sdata.channel);
        }

        /* If child process's stdout/stderr has been registered with the event,
         * or the child process hasn't started yet, continue. */
        if (cdata.event != NULL || cdata.pid == 0) {
            continue;
        }
        /* Executed only once, once the child process starts. */
        cdata.event = event;
        /* If stdout valid, add stdout to be monitored by the poll event. */
        if (cdata.child_stdout != -1) {
            if (ssh_event_add_fd(event, cdata.child_stdout, POLLIN, process_stdout,
                    sdata.channel) != SSH_OK) {
                fprintf(stderr, "Failed to register stdout to poll context\n");
                ssh_channel_close(sdata.channel);
            }
        }

        /* If stderr valid, add stderr to be monitored by the poll event. */
        if (cdata.child_stderr != -1) {
            if (ssh_event_add_fd(event, cdata.child_stderr, POLLIN, process_stderr,
                    sdata.channel) != SSH_OK) {
                fprintf(stderr, "Failed to register stderr to poll context\n");
                ssh_channel_close(sdata.channel);
            }
        }
    } while (ssh_channel_is_open(sdata.channel) &&
            (cdata.pid == 0 || waitpid(cdata.pid, &rc, WNOHANG) == 0));

    close(cdata.pty_master);
    close(cdata.child_stdin);
    close(cdata.child_stdout);
    close(cdata.child_stderr);

    /* Remove the descriptors from the polling context, since they are now
     * closed, they will always trigger during the poll calls. */
    ssh_event_remove_fd(event, cdata.child_stdout);
    ssh_event_remove_fd(event, cdata.child_stderr);

    /* If the child process exited. */
    if (kill(cdata.pid, 0) < 0 && WIFEXITED(rc)) {
        rc = WEXITSTATUS(rc);
        ssh_channel_request_send_exit_status(sdata.channel, rc);
        /* If client terminated the channel or the process did not exit nicely,
         * but only if something has been forked. */
    } else if (cdata.pid > 0) {
        kill(cdata.pid, SIGKILL);
    }

    ssh_channel_send_eof(sdata.channel);
    ssh_channel_close(sdata.channel);

    /* Wait up to 5 seconds for the client to terminate the session. */
    for (n = 0; n < 50 && (ssh_get_status(session) & SESSION_END) == 0; n++) {
        ssh_event_dopoll(event, 100);
    }
}

/* SIGCHLD handler for cleaning up dead children. */
static void sigchld_handler(int signo) {
    (void) signo;
    while (waitpid(-1, NULL, WNOHANG) > 0);
}

int main(int argc, char **argv) {
    ssh_bind sshbind;
    ssh_session session;
    ssh_event event;
    struct sigaction sa;

    /* Set up SIGCHLD handler. */
    sa.sa_handler = sigchld_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART | SA_NOCLDSTOP;
    if (sigaction(SIGCHLD, &sa, NULL) != 0) {
        fprintf(stderr, "Failed to register SIGCHLD handler\n");
        return 1;
    }

    ssh_init();
    sshbind = ssh_bind_new();

#ifdef HAVE_ARGP_H
    argp_parse(&argp, argc, argv, 0, 0, sshbind);
#else
    (void) argc;
    (void) argv;

    set_default_keys(sshbind, 0, 0, 0);
#endif /* HAVE_ARGP_H */

    if (ssh_bind_listen(sshbind) < 0) {
        fprintf(stderr, "%s\n", ssh_get_error(sshbind));
        return 1;
    }

    while (1) {
        session = ssh_new();
        if (session == NULL) {
            fprintf(stderr, "Failed to allocate session\n");
            continue;
        }

        /* Blocks until there is a new incoming connection. */
        if (ssh_bind_accept(sshbind, session) != SSH_ERROR) {
            switch (fork()) {
                case 0:
                    /* Remove the SIGCHLD handler inherited from parent. */
                    sa.sa_handler = SIG_DFL;
                    sigaction(SIGCHLD, &sa, NULL);
                    /* Remove socket binding, which allows us to restart the
                     * parent process, without terminating existing sessions. */
                    ssh_bind_free(sshbind);

                    event = ssh_event_new();
                    if (event != NULL) {
                        /* Blocks until the SSH session ends by either
                         * child process exiting, or client disconnecting. */
                        handle_session(event, session);
                        ssh_event_free(event);
                    } else {
                        fprintf(stderr, "Could not create polling context\n");
                    }
                    ssh_disconnect(session);
                    ssh_free(session);

                    exit(0);
                case -1:
                    fprintf(stderr, "Failed to fork\n");
            }
        } else {
            fprintf(stderr, "%s\n", ssh_get_error(sshbind));
        }
        /* Since the session has been passed to a child fork, do some cleaning
         * up at the parent process. */
        ssh_disconnect(session);
        ssh_free(session);
    }

    ssh_bind_free(sshbind);
    ssh_finalize();
    return 0;
}
