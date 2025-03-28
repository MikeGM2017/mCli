/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CmdLine_Parse.h
 * Author: mike
 *
 * Created on March 27, 2025, 11:21 AM
 */

#ifndef CMDLINE_PARSE_H
#define CMDLINE_PARSE_H

#include <string>
#include <vector>

using namespace std;

#include <windows.h>
#include <winuser.h>
#include <shlwapi.h>

vector<wstring> CmdLine_Parse(TCHAR *s);

#endif /* CMDLINE_PARSE_H */
