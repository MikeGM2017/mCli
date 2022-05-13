/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Test_Cmd_Item_Str_With_Commas.cpp
 * Author: mike
 *
 * Created on May 12, 2022, 9:10 AM
 */

#include <stdlib.h>
#include <iostream>
#include <string>

/*
 * Simple C++ Test Suite
 */

#include "Cmd_Item_Valid_Result.h"
#include "Cmd_Item_Valid_Result_Func.h"

#include "Cmd_Item_Str.h"

using namespace std;

class Cmd_Item_Str_Test_Item {
public:
    string S_in;
    string S_out;
    Cmd_Item_Valid_Result Res_out;

    Cmd_Item_Str_Test_Item(string s_in, string s_out, Cmd_Item_Valid_Result res_out) :
    S_in(s_in), S_out(s_out), Res_out(res_out) {
    }

};

static const Cmd_Item_Str_Test_Item TestVector[] = {
    Cmd_Item_Str_Test_Item("", "", CMD_ITEM_EMPTY),
    Cmd_Item_Str_Test_Item("\"<str>\"", "<str>", CMD_ITEM_OK),
    Cmd_Item_Str_Test_Item("\"  <str1>   <str2>    \"", "  <str1>   <str2>    ", CMD_ITEM_OK),
    Cmd_Item_Str_Test_Item("\"\"", "", CMD_ITEM_OK),
    Cmd_Item_Str_Test_Item("\"", "\"", CMD_ITEM_INCOMPLETE_STR),
    Cmd_Item_Str_Test_Item("\"<str>", "\"<str>", CMD_ITEM_INCOMPLETE_STR),
    Cmd_Item_Str_Test_Item("<str>\"", "<str>\"", CMD_ITEM_ERROR),
    Cmd_Item_Str_Test_Item("FF:FF:FF:FF:FF:FF", "FF:FF:FF:FF:FF:FF", CMD_ITEM_OK_STR_WITHOUT_COMMAS),

    Cmd_Item_Str_Test_Item("<str>'", "<str>'", CMD_ITEM_ERROR),

    // Escaped:
    Cmd_Item_Str_Test_Item("\\\"Str\\\"", "\\\"Str\\\"", CMD_ITEM_OK_STR_WITHOUT_COMMAS),
};

void test1() {
    std::cout << "Test_Cmd_Item_Str_With_Commas test 1" << std::endl;

    Cmd_Item_Str v("", "");

    int test_vector_size = sizeof (TestVector) / sizeof (Cmd_Item_Str_Test_Item);

    for (int i = 0; i < test_vector_size; i++) {
        Cmd_Item_Valid_Result res = v.Parse(TestVector[i].S_in);
        string s_out = v.Value_Str;
        if (res != TestVector[i].Res_out || s_out != TestVector[i].S_out)
            std::cout << "%TEST_FAILED% time=0 testname=test1 (Test_Cmd_Item_Str_With_Commas) message="
                << v.To_String() << " res=" << Cmd_Item_Valid_Result_Func::To_String(res)
            << " (must be " << Cmd_Item_Valid_Result_Func::To_String(TestVector[i].Res_out) << ")"
            << " " << s_out
                << " (must be " << TestVector[i].S_out << ")"
                << std::endl;
        else
            std::cout << "\"" << v.Value_Str << "\": " << Cmd_Item_Valid_Result_Func::To_String(res)
            << " -> " << s_out
                << " - Passed" << std::endl;
    }
}

int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTING% Test_Cmd_Item_Str_With_Commas" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% test1 (Test_Cmd_Item_Str_With_Commas)" << std::endl;
    test1();
    std::cout << "%TEST_FINISHED% time=0 test1 (Test_Cmd_Item_Str_With_Commas)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}

