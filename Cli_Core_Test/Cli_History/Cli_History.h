/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cli_History.h
 * Author: mike
 *
 * Created on June 10, 2020, 8:19 AM
 */

#ifndef CLI_HISTORY_H
#define CLI_HISTORY_H

#include <string>
#include <vector>

using namespace std;

class Cli_History {
protected:

    vector<string> History;
    int History_Pos;

public:

    Cli_History() : History_Pos(0) {
    }

    virtual void Clear() {
        History.clear();
        History_Pos = 0;
    }

    virtual int History_Size_Get() {
        return History.size();
    }

    virtual string History_Item_Get(int index) {
        if (index >= 0 && index < History.size())
            return History[index];
        return "";
    }

    virtual void History_Put(string s_trim, bool is_no_history, bool is_debug) {
        if (!is_no_history && !is_debug) {
            if (History.size() == 0 || s_trim != History.back())
                History.push_back(s_trim);
        }
        History_Pos = History.size();
    }

    virtual string History_Up() {
        if (History.size() == 0) {
            return "";
        } else {
            if (History_Pos > 0) {
                History_Pos--;
            }
            return History[History_Pos];
        }
    }

    virtual string History_Down() {
        if (History.size() == 0) {
            return "";
        } else {
            if (History_Pos < History.size() - 1) {
                History_Pos++;
                return History[History_Pos];
            } else {
                History_Pos = History.size();
                return "";
            }
        }
    }

};

#endif /* CLI_HISTORY_H */
