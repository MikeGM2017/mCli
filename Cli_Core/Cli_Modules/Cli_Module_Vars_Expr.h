/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_Module_Vars_Expr.h
 * Author: mike
 *
 * Created on October 9, 2024, 9:48 AM
 */

#ifndef CLI_MODULE_VARS_EXPR_H
#define CLI_MODULE_VARS_EXPR_H

#include <vector>
#include <cassert>
#include <sstream>

using namespace std;

#include <stdlib.h> // for atoi(...)

#include "Cli_Module.h"

#include "Cmd_Item_Word.h"
#include "Cmd_Item_Str.h"
#include "Cmd_Item_Point_Var_Name.h"
#include "Cmd_Item_Assignment_Mark.h"

#include "Cli_Output_Abstract.h"

#include "Str_Get_Without_Commas.h"
#include "Str_Get_Int.h"

class Cli_Module_Vars_Expr : public Cli_Module {
protected:

    map<string, string> &Values_Map;
    Str_Get_Without_Commas &Str_Without_Commas;
    Cli_Output_Abstract &Cli_Output;
    Str_Get_Int &Str_Int;

    char C_Single;
    char C_Multy;

public:

    enum Local_Cmd_ID {
        CMD_ID_NO,

        CMD_ID_point_var_name_equ_expr_str,
        CMD_ID_point_var_name_equ_expr_str_verbose,

        CMD_ID_LAST
    };

    virtual int Cmd_ID_Count_Get() {
        return CMD_ID_LAST - CMD_ID_NO - 1;
    }

    Cli_Module_Vars_Expr(map<string, string> &values_map,
            Str_Get_Without_Commas &str_without_commas, Str_Get_Int &str_int,
            Cli_Output_Abstract &cli_output,
            char c_single = '?', char c_multy = '*') :
    Cli_Module("Vars_Expr"), Values_Map(values_map),
    Str_Without_Commas(str_without_commas), Str_Int(str_int),
    Cli_Output(cli_output), C_Single(c_single), C_Multy(c_multy) {

        Version = "0.02";

        {
            // var assign expr_str
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_point_var_name_equ_expr_str);
            cmd->Text_Set(".<var_name> = expr <expr_str>");
            cmd->Help_Set("set <var_name> to <expr_str>");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Point_Var_Name(".<var_name>", "var name", C_Single, C_Multy));
            cmd->Item_Add(new Cmd_Item_Assignment_Mark("=", "set"));
            cmd->Item_Add(new Cmd_Item_Word("expr", "set expression"));
            cmd->Item_Add(new Cmd_Item_Str("<expr_str>", "expression"));
            Cmd_Add(cmd);
        }
        {
            // var assign expr_str verbose
            Cli_Cmd *cmd = new Cli_Cmd((Cli_Cmd_ID) CMD_ID_point_var_name_equ_expr_str_verbose);
            cmd->Text_Set(".<var_name> = expr <expr_str> verbose");
            cmd->Help_Set("set <var_name> to <expr_str> with verbose information");
            cmd->Is_Global_Set(true);
            cmd->Item_Add(new Cmd_Item_Point_Var_Name(".<var_name>", "var name", C_Single, C_Multy));
            cmd->Item_Add(new Cmd_Item_Assignment_Mark("=", "set"));
            cmd->Item_Add(new Cmd_Item_Word("expr", "set expression"));
            cmd->Item_Add(new Cmd_Item_Str("<expr_str>", "expression"));
            cmd->Item_Add(new Cmd_Item_Word("verbose", "with verbose information"));
            Cmd_Add(cmd);
        }

    }

    ~Cli_Module_Vars_Expr() {
    }

    // <editor-fold defaultstate="collapsed" desc="EXPR_TT">

    enum EXPR_TT {
        EXPR_TT_NO,

        EXPR_TT_SPACE,

        EXPR_TT_DIGIT,
        EXPR_TT_ALPHANUM,
        EXPR_TT_BL,
        EXPR_TT_BR,

        EXPR_TT_SPEC, // + - * / % ^ & | && || << >> ~ !

        EXPR_TT_POINT_VAR_NAME,

        EXPR_TT_END,

        EXPR_TT_ERROR,

        EXPR_TT_LAST,
        EXPR_TT_UNDEFINED,
    };

    const char *EXPR_TT_To_Str(EXPR_TT tt) {

        static const char *EXPR_TT_Str[] = {
            "EXPR_TT_NO",

            "EXPR_TT_SPACE",

            "EXPR_TT_DIGIT",
            "EXPR_TT_ALPHANUM",
            "EXPR_TT_BL",
            "EXPR_TT_BR",

            "EXPR_TT_SPEC", // + - * / % ^ & | && || << >> ~ !

            "EXPR_TT_POINT_VAR_NAME",

            "EXPR_TT_END",

            "EXPR_TT_ERROR",

            "EXPR_TT_LAST",
            "EXPR_TT_UNDEFINED",
        };

        assert(sizeof (EXPR_TT_Str) / sizeof (const char *) == EXPR_TT_UNDEFINED + 1);
        return (tt >= EXPR_TT_NO && tt <= EXPR_TT_LAST) ? EXPR_TT_Str[tt] : EXPR_TT_Str[EXPR_TT_UNDEFINED];
    }

    // </editor-fold>

    // <editor-fold defaultstate="collapsed" desc="EXPR_Token">

    class EXPR_Token {
    public:
        EXPR_TT Type;
        string Text;
        int Error_Pos;

        EXPR_Token() {
            Type = EXPR_TT_NO;
            Error_Pos = -1;
        }

    };

    // </editor-fold>

    // <editor-fold defaultstate="collapsed" desc="EXPR_C_Is_XXX">

    bool EXPR_C_Is_Space(char c) {
        if (c == ' ' || c == '\t') return true;
        return false;
    }

    bool EXPR_C_Is_Digit(char c) {
        if (c >= '0' && c <= '9') return true;
        return false;
    }

    bool EXPR_C_Is_Alpha(char c) {
        if (c >= 'a' && c <= 'z') return true;
        if (c >= 'A' && c <= 'Z') return true;
        if (c == '_') return true;
        return false;
    }

    bool EXPR_C_Is_BL(char c) {
        if (c == '(') return true;
        return false;
    }

    bool EXPR_C_Is_BR(char c) {
        if (c == ')') return true;
        return false;
    }

    bool EXPR_C_Is_SPEC(char c) {
        if (c == '+') return true;
        if (c == '-') return true;
        if (c == '*') return true;
        if (c == '/') return true;
        if (c == '%') return true;
        if (c == '^') return true;
        if (c == '|') return true;
        if (c == '&') return true;
        if (c == '~') return true;
        if (c == '!') return true;
        if (c == '<') return true;
        if (c == '>') return true;
        return false;
    }

    bool EXPR_C_Is_POINT(char c) {
        if (c == '.') return true;
        return false;
    }

    // </editor-fold>

    // <editor-fold defaultstate="collapsed" desc="EXPR_Token_XXX_Get()">

    EXPR_Token EXPR_Token_SPACE_Get(const string s, int &pos) {
        EXPR_Token t;
        int pos_end = pos;
        bool stop = false;
        do {
            if (pos_end < s.length()) {
                char c = s[pos_end];
                if (EXPR_C_Is_Space(c)) {
                    pos_end++;
                } else {
                    stop = true; // Emd Of Spaces
                }
            } else {
                stop = true; // End Of String
            }
        } while (!stop);
        t.Type = EXPR_TT_SPACE;
        t.Text = s.substr(pos, pos_end - pos);
        pos = pos_end;
        return t;
    }

    EXPR_Token EXPR_Token_DIGIT_Get(const string s, int &pos) {
        EXPR_Token t;
        int pos_end = pos;
        bool stop = false;
        do {
            if (pos_end < s.length()) {
                char c = s[pos_end];
                if (EXPR_C_Is_Digit(c)) {
                    pos_end++;
                } else {
                    stop = true; // Emd Of Spaces
                }
            } else {
                stop = true; // End Of String
            }
        } while (!stop);
        t.Type = EXPR_TT_DIGIT;
        t.Text = s.substr(pos, pos_end - pos);
        pos = pos_end;
        return t;
    }

    EXPR_Token EXPR_Token_ALPHANUM_Get(const string s, int &pos) {
        EXPR_Token t;
        int pos_end = pos;
        bool stop = false;
        do {
            if (pos_end < s.length()) {
                char c = s[pos_end];
                if (EXPR_C_Is_Alpha(c) || EXPR_C_Is_Digit(c)) {
                    pos_end++;
                } else {
                    stop = true; // Emd Of Spaces
                }
            } else {
                stop = true; // End Of String
            }
        } while (!stop);
        t.Type = EXPR_TT_ALPHANUM;
        t.Text = s.substr(pos, pos_end - pos);
        pos = pos_end;
        return t;
    }

    bool POINT_VAR_NAME_Is_Valid(string s) {
        if (s == "")
            return false; // Empty string
        if (s == ".")
            return false; // Too short string: Case .
        if (s == "..")
            return false; // Too short string: Case ..
        if (s.length() < 2)
            return false; // Empty or too short string
        if (s[0] != '.')
            return false; // No point at start
        if (s[0] == '.' && s[1] == '.' && s.length() < 3)
            return false; // Too short string: Case ..

        // Here: s.length() >= 2)

        if (s.length() >= 2 && s[0] == '.' && EXPR_C_Is_Digit(s[1]))
            return false; // Case: .<digit>
        if (s.length() >= 3 && s[0] == '.' && s[1] == '.' && EXPR_C_Is_Digit(s[2]))
            return false; // Case: ..<digit>
        if (s.length() >= 3 && s[0] == '.' && s[1] == '.' && s[2] == '.')
            return false; // Case: ...

        int pos_beg = 0;
        if (s[0] == '.') pos_beg = 1;
        if (s[0] == '.' && s[1] == '.') pos_beg = 2;
        string tail = s.substr(pos_beg);
        bool tail_is_valid = (tail.find("..") == tail.npos); // Case: .. not found
        if (!tail_is_valid)
            return false; // Case: found ..

        if (s[s.length() - 1] == '.')
            return false; // Case: ..v1.

        return true;
    }

    EXPR_Token EXPR_Token_POINT_VAR_NAME_Get(const string s, int &pos) {
        EXPR_Token t;
        int pos_end = pos;
        bool stop = false;
        do {
            if (pos_end < s.length()) {
                char c = s[pos_end];
                if (EXPR_C_Is_POINT(c) || EXPR_C_Is_Alpha(c) || EXPR_C_Is_Digit(c)) {
                    pos_end++;
                } else {
                    stop = true; // Emd Of Spaces
                }
            } else {
                stop = true; // End Of String
            }
        } while (!stop);

        string var_name = s.substr(pos, pos_end - pos);

        bool var_name_is_valid = POINT_VAR_NAME_Is_Valid(var_name);
        if (var_name_is_valid) {
            t.Type = EXPR_TT_POINT_VAR_NAME;
            t.Text = var_name;
            pos = pos_end;
        } else {
            t.Type = EXPR_TT_ERROR;
            t.Text = var_name;
            t.Error_Pos = pos;
        }

        return t;
    }

    EXPR_Token EXPR_Token_SPEC_Get(const string s, int &pos) {
        EXPR_Token t;
        int pos_end = pos;
        bool stop = false;
        do {
            if (pos_end < s.length()) {
                char c = s[pos_end];
                if (EXPR_C_Is_SPEC(c)) {
                    pos_end++;
                } else {
                    stop = true; // Emd Of Spaces
                }
            } else {
                stop = true; // End Of String
            }
        } while (!stop);
        t.Type = EXPR_TT_SPEC;
        t.Text = s.substr(pos, pos_end - pos);
        pos = pos_end;
        return t;
    }

    EXPR_Token EXPR_Token_BL_Get(const string s, int &pos) {
        EXPR_Token t;
        t.Type = EXPR_TT_BL;
        t.Text = s.substr(pos, 1);
        pos++;
        return t;
    }

    EXPR_Token EXPR_Token_BR_Get(const string s, int &pos) {
        EXPR_Token t;
        t.Type = EXPR_TT_BR;
        t.Text = s.substr(pos, 1);
        pos++;
        return t;
    }

    EXPR_Token EXPR_Token_ERROR_Get(const string s, int &pos) {
        EXPR_Token t;
        t.Type = EXPR_TT_ERROR;
        t.Text = s.substr(pos, 1);
        t.Error_Pos = pos;
        return t;
    }

    EXPR_Token EXPR_Token_Get(const string s, int &pos) {
        EXPR_Token t;
        if (pos < s.length()) {
            char c = s[pos];
            if (EXPR_C_Is_Space(c))return EXPR_Token_SPACE_Get(s, pos);
            else if (EXPR_C_Is_Digit(c)) return EXPR_Token_DIGIT_Get(s, pos);
            else if (EXPR_C_Is_Alpha(c)) return EXPR_Token_ALPHANUM_Get(s, pos);
            else if (EXPR_C_Is_BL(c)) return EXPR_Token_BL_Get(s, pos);
            else if (EXPR_C_Is_BR(c)) return EXPR_Token_BR_Get(s, pos);
            else if (EXPR_C_Is_SPEC(c)) return EXPR_Token_SPEC_Get(s, pos);
            else if (EXPR_C_Is_POINT(c)) return EXPR_Token_POINT_VAR_NAME_Get(s, pos);
            else return EXPR_Token_ERROR_Get(s, pos);
        } else {
            t.Type = EXPR_TT_END;
        }
        return t;
    }

    bool EXPR_Tokens_Get(string expr_str, vector<EXPR_Token> &tokens, EXPR_Token &token_error, bool is_verbose) {
        int expr_str_pos = 0;
        bool res = true; // Ok
        bool stop = false;
        do {
            EXPR_Token t = EXPR_Token_Get(expr_str, expr_str_pos);
            if (t.Type != EXPR_TT_SPACE) {
                tokens.push_back(t);
            }
            if (is_verbose) {
                if (t.Type > EXPR_TT_NO && t.Type <= EXPR_TT_ERROR && t.Type != EXPR_TT_SPACE && t.Type != EXPR_TT_END) {
                    Cli_Output.Output_Str("\"" + t.Text + "\" " + EXPR_TT_To_Str(t.Type));
                    Cli_Output.Output_NewLine();
                }
            }
            if (t.Type == EXPR_TT_END || t.Type == EXPR_TT_NO || t.Type == EXPR_TT_ERROR || t.Type >= EXPR_TT_LAST) {
                stop = true;
            }
            if (t.Type == EXPR_TT_ERROR) {
                token_error = t;
                res = false; // Failed
            }
        } while (!stop);
        return res;
    }

    // </editor-fold>

    // <editor-fold defaultstate="collapsed" desc="EXPR_Tokens_Calc()/EXPR_Calc()">

    bool Str_Is_Var(string s) {
        return POINT_VAR_NAME_Is_Valid(s);
    }

    string Str_To_Var_Name(string s) {
        return s.substr(1);
    }

    bool Str_To_Value_Or_Error(string s, string &value_str,
            string &error_str, const string EXPR_Error, const string EXPR_Error_Str, const string EXPR_Error_true) {
        bool res = true; // Ok
        if (Str_Is_Var(s)) { // Cases: .v or ..v
            string var_name = Str_To_Var_Name(s);
            if (Str_Is_Var(var_name)) { // Case: ..v
                string var_name2 = Str_To_Var_Name(var_name);
                map<string, string>::iterator var_iter2 = Values_Map.find(var_name2);
                bool var_found2 = (var_iter2 != Values_Map.end());
                if (var_found2) {
                    string var_name3 = Str_To_Var_Name(var_iter2->second);
                    map<string, string>::iterator var_iter3 = Values_Map.find(var_name3);
                    bool var_found3 = (var_iter3 != Values_Map.end());
                    if (var_found3) {
                        value_str = var_iter3->second;
                    } else {
                        error_str = var_name + " -> ." + var_name3 + " - Not found";
                        Values_Map[EXPR_Error] = EXPR_Error_true;
                        Values_Map[EXPR_Error_Str] = error_str;
                        res = false;
                    }
                } else {
                    error_str = "." + var_name2 + " - Not found";
                    Values_Map[EXPR_Error] = EXPR_Error_true;
                    Values_Map[EXPR_Error_Str] = error_str;
                    res = false;
                }
            } else { // Cases: .v
                map<string, string>::iterator var_iter = Values_Map.find(var_name);
                bool var_found = (var_iter != Values_Map.end());
                if (var_found) {
                    value_str = var_iter->second;
                } else {
                    error_str = "." + var_name + " - Not found";
                    Values_Map[EXPR_Error] = EXPR_Error_true;
                    Values_Map[EXPR_Error_Str] = error_str;
                    res = false;
                }
            }
        } else { // Case: s is not var
            value_str = s;
        }
        return res;
    }

    bool EXPR_Tokens_Calc(vector<EXPR_Token> &tokens, string &res_str, string &error_str) {
        static const string EXPR_Error = "EXPR_Error";
        static const string EXPR_Error_Str = "EXPR_Error_Str";
        static const string EXPR_Error_true = "true";

        bool res = true; // Ok
        if (tokens.size() == 1) { // Empty expression
            res_str = "";
        } else if (tokens.size() == 2) { // Assign
            res_str = tokens[0].Text;
        } else if (tokens.size() == 3) { // Unary pre operations
            string op_str = tokens[0].Text;
            string left_str = tokens[1].Text;

            string left_value_str = left_str;

            bool left_res = Str_To_Value_Or_Error(left_str, left_value_str, error_str, EXPR_Error, EXPR_Error_Str, EXPR_Error_true);

            if (!left_res) {
                res = false; // Failed
                return res;
            }

            if (Str_Int.Str_Is_Int(left_value_str)) { // Case: op / int

                int left_value_int = Str_Int.Str_To_Int(left_value_str);

                int res_int = 0;

                // + - ~ ! ++ --
                if (op_str == "+") {
                    res_int = +left_value_int;
                } else if (op_str == "-") {
                    res_int = -left_value_int;
                } else if (op_str == "~") {
                    res_int = ~left_value_int;
                } else if (op_str == "!") {
                    res_int = !left_value_int;
                } else if (op_str == "++") {
                    res_int = ++left_value_int;
                } else if (op_str == "--") {
                    res_int = --left_value_int;
                } else {
                    error_str = op_str + " - Operator Not Allowed";
                    Values_Map[EXPR_Error] = EXPR_Error_true;
                    Values_Map[EXPR_Error_Str] = error_str;
                    res = false;
                }

                res_str = Str_Int.Int_To_Str(res_int);

            } else { // Case: op / str - not allowed
                error_str = op_str + " - Operator Not Allowed";
                Values_Map[EXPR_Error] = EXPR_Error_true;
                Values_Map[EXPR_Error_Str] = error_str;
                res = false;
            }

        } else if (tokens.size() == 4) { // Binary operations
            string left_str = tokens[0].Text;
            string op_str = tokens[1].Text;
            string right_str = tokens[2].Text;

            string left_value_str = left_str;
            string right_value_str = right_str;

            bool left_res = Str_To_Value_Or_Error(left_str, left_value_str, error_str, EXPR_Error, EXPR_Error_Str, EXPR_Error_true);
            bool right_res = Str_To_Value_Or_Error(right_str, right_value_str, error_str, EXPR_Error, EXPR_Error_Str, EXPR_Error_true);

            if (!left_res || !right_res) {
                res = false; // Failed
                return res;
            }

            if (Str_Int.Str_Is_Int(left_value_str) && Str_Int.Str_Is_Int(right_value_str)) {

                int left_value_int = Str_Int.Str_To_Int(left_value_str);
                int right_value_int = Str_Int.Str_To_Int(right_value_str);

                int res_int = 0;

                // + - * / % ^ & | && || << >>
                if (op_str == "+") {
                    res_int = left_value_int + right_value_int;
                } else if (op_str == "-") {
                    res_int = left_value_int - right_value_int;
                } else if (op_str == "*") {
                    res_int = left_value_int * right_value_int;
                } else if (op_str == "/") {
                    if (right_value_int != 0) {
                        res_int = left_value_int / right_value_int;
                    } else {
                        error_str = "Division by 0 Not Allowed";
                        Values_Map[EXPR_Error] = EXPR_Error_true;
                        Values_Map[EXPR_Error_Str] = error_str;
                        res = false;
                    }
                } else if (op_str == "%") {
                    res_int = left_value_int % right_value_int;
                } else if (op_str == "^") {
                    res_int = left_value_int ^ right_value_int;
                } else if (op_str == "&") {
                    res_int = left_value_int & right_value_int;
                } else if (op_str == "|") {
                    res_int = left_value_int | right_value_int;
                } else if (op_str == "&&") {
                    res_int = left_value_int && right_value_int;
                } else if (op_str == "||") {
                    res_int = left_value_int || right_value_int;
                } else if (op_str == "<<") {
                    res_int = left_value_int << right_value_int;
                } else if (op_str == ">>") {
                    res_int = left_value_int >> right_value_int;
                } else {
                    error_str = op_str + " - Operator Not Allowed";
                    Values_Map[EXPR_Error] = EXPR_Error_true;
                    Values_Map[EXPR_Error_Str] = error_str;
                    res = false;
                }

                res_str = Str_Int.Int_To_Str(res_int);
            } else { // Case: str op str
                // + only
                if (op_str == "+") {
                    res_str = left_value_str + right_value_str;
                } else {
                    error_str = op_str + " - Operator Not Allowed";
                    Values_Map[EXPR_Error] = EXPR_Error_true;
                    Values_Map[EXPR_Error_Str] = error_str;
                    res = false;
                }
            }
        } else {
            if (tokens.size() > 4) {
                error_str = Str_Int.Int_To_Str(tokens.size() - 1) + " tokens - Too Complex Expression";
                Values_Map[EXPR_Error] = EXPR_Error_true;
                Values_Map[EXPR_Error_Str] = error_str;
                res = false;
            }
        }

        return res;
    }

    bool EXPR_Calc(string expr_str, string &res_str, string &error_str, bool is_verbose) {
        bool res = true; // Ok
        vector<EXPR_Token> tokens;
        EXPR_Token token_error;
        bool res_tokens = EXPR_Tokens_Get(expr_str, tokens, token_error, is_verbose);
        if (res_tokens) {
            res = EXPR_Tokens_Calc(tokens, res_str, error_str);
        } else {
            error_str = expr_str + " - ERROR at position " + Str_Int.Int_To_Str(token_error.Error_Pos);
            res = false; // Failed
        }
        return res;
    }

    // </editor-fold>

    bool var_set_expr(string point_var_name_str, string expr_str, bool is_verbose) {

        if (is_verbose) {
            Cli_Output.Output_Str(point_var_name_str + " = expr \"" + expr_str + "\"");
            Cli_Output.Output_NewLine();
        }

        string res_str;
        string error_str;

        bool res_calc = EXPR_Calc(expr_str, res_str, error_str, is_verbose);

        if (res_calc) {
            string var_name = point_var_name_str.substr(1);
            Values_Map[var_name] = res_str;
            if (is_verbose) {
                Cli_Output.Output_Str(point_var_name_str + " = \"" + res_str + "\"");
                Cli_Output.Output_NewLine();
            }
        } else {
            Cli_Output.Output_Str(expr_str + " - " + error_str);
            Cli_Output.Output_NewLine();
        }

        return true;
    }

    virtual bool Execute(Cli_Cmd *cmd, vector<Level_Description> &Levels, bool is_debug) {
        enum Local_Cmd_ID cmd_id = (enum Local_Cmd_ID)cmd->ID_Get();
        switch (cmd_id) {

            case CMD_ID_point_var_name_equ_expr_str:
                if (is_debug) return true;
            {
                string point_var_name_str = cmd->Items[0]->Value_Str;
                string expr_str = Str_Without_Commas.Get(cmd->Items[3]->Value_Str);
                bool is_verbose;
                return var_set_expr(point_var_name_str, expr_str, is_verbose = false);
            }
            case CMD_ID_point_var_name_equ_expr_str_verbose:
                if (is_debug) return true;
            {
                string point_var_name_str = cmd->Items[0]->Value_Str;
                string expr_str = Str_Without_Commas.Get(cmd->Items[3]->Value_Str);
                bool is_verbose;
                return var_set_expr(point_var_name_str, expr_str, is_verbose = true);
            }

            default:
                return false; // Not Implemented

        }
        return false; // Not Implemented
    }

    virtual void To_Map(map<string, string> &values_map) {
        // Nothing
    }

};

#endif /* CLI_MODULE_VARS_EXPR_H */
