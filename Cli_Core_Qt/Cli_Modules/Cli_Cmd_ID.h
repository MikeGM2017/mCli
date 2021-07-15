/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_Cmd_ID.h
 * Author: mike
 *
 * Created on July 16, 2018, 3:35 PM
 */

#ifndef CLI_CMD_ID_H
#define CLI_CMD_ID_H

enum Cli_Cmd_ID {
    CMD_ID_NO,
    CMD_ID_rem,
    CMD_ID_exit,
    CMD_ID_quit,
    CMD_ID_help,
    CMD_ID_help_command,
    CMD_ID_help_command_verbose,
    CMD_ID_debug_cli,
    CMD_ID_debug_cli_counts,
    CMD_ID_debug_cli_verbose,
    CMD_ID_debug_cli_verbose_failed,
    CMD_ID_clear_log,
    CMD_ID_clear_history,
    CMD_ID_wait,
    CMD_ID_log_wait_enable,
    CMD_ID_log_wait_disable,
    CMD_ID_do_script,
    CMD_ID_do_script_no_history,
    CMD_ID_do_script_stop,
    CMD_ID_save_history_as_script,
    CMD_ID_history_show,
    CMD_ID_LAST
};

#endif /* CLI_CMD_ID_H */
