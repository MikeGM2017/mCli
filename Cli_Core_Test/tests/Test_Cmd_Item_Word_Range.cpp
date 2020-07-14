/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Test_Cmd_Item_Word_Range.cpp
 * Author: mike
 *
 * Created on July 14, 2020, 1:46 PM
 */

#include <stdlib.h>
#include <iostream>

/*
 * Simple C++ Test Suite
 */

#include "Cmd_Item_Valid_Result.h"
#include "Cmd_Item_Valid_Result_Func.h"

#include "Cmd_Item_Word_Range.h"

typedef std::pair< std::string, Cmd_Item_Valid_Result > Cmd_Item_Test_Pair;

static const Cmd_Item_Test_Pair TestVector[] = {
    Cmd_Item_Test_Pair("", CMD_ITEM_EMPTY),
    Cmd_Item_Test_Pair("enable", CMD_ITEM_OK),
    Cmd_Item_Test_Pair("disable", CMD_ITEM_OK),
    Cmd_Item_Test_Pair("else", CMD_ITEM_OK),
    Cmd_Item_Test_Pair("e", CMD_ITEM_INCOMPLETE),
    Cmd_Item_Test_Pair("en", CMD_ITEM_INCOMPLETE),
    Cmd_Item_Test_Pair("el", CMD_ITEM_INCOMPLETE),
    Cmd_Item_Test_Pair("d", CMD_ITEM_INCOMPLETE),
    Cmd_Item_Test_Pair("enb", CMD_ITEM_ERROR),
    Cmd_Item_Test_Pair("enableb", CMD_ITEM_ERROR),
    Cmd_Item_Test_Pair("disb", CMD_ITEM_ERROR),
};

void test1() {
    std::cout << "Test_Cmd_Item_Word_Range test 1" << std::endl;

    vector<string> words;
    words.push_back("enable");
    words.push_back("disable");
    words.push_back("else");
    Cmd_Item_Word_Range v("<enable|disable|else>", "test: set <enable|disable|else>", words);

    int test_vector_size = sizeof (TestVector) / sizeof (Cmd_Item_Test_Pair);

    for (int i = 0; i < test_vector_size; i++) {
        Cmd_Item_Valid_Result res = v.Parse(TestVector[i].first);
        if (res != TestVector[i].second)
            std::cout << "%TEST_FAILED% time=0 testname=test1 (Test_Cmd_Item_Word_Range) message="
                << v.To_String() << " res=" << Cmd_Item_Valid_Result_Func::To_String(res)
            << " (must be " << Cmd_Item_Valid_Result_Func::To_String(TestVector[i].second) << ")" << std::endl;
        else std::cout << "\"" << v.Value_Str << "\": " << Cmd_Item_Valid_Result_Func::To_String(res) << " - Passed" << std::endl;
    }
}

int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTING% Test_Cmd_Item_Word_Range" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% test1 (Test_Cmd_Item_Word_Range)" << std::endl;
    test1();
    std::cout << "%TEST_FINISHED% time=0 test1 (Test_Cmd_Item_Word_Range)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}
