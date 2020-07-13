/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Test_Cmd_Item_Str.cpp
 * Author: mike
 *
 * Created on July 13, 2020, 9:22 AM
 */

#include <stdlib.h>
#include <iostream>

/*
 * Simple C++ Test Suite
 */

#include "Cmd_Item_Valid_Result.h"
#include "Cmd_Item_Valid_Result_Func.h"

#include "Cmd_Item_Str.h"

typedef std::pair< std::string, Cmd_Item_Valid_Result > Cmd_Item_Str_Test_Pair;

static const Cmd_Item_Str_Test_Pair TestVector[] = {
    Cmd_Item_Str_Test_Pair("", CMD_ITEM_EMPTY),
    Cmd_Item_Str_Test_Pair("\"<str>\"", CMD_ITEM_OK),
    Cmd_Item_Str_Test_Pair("\"  <str1>   <str2>    \"", CMD_ITEM_OK),
    Cmd_Item_Str_Test_Pair("\"\"", CMD_ITEM_OK),
    Cmd_Item_Str_Test_Pair("\"", CMD_ITEM_INCOMPLETE),
    Cmd_Item_Str_Test_Pair("\"<str>", CMD_ITEM_INCOMPLETE),
    Cmd_Item_Str_Test_Pair("<str>\"", CMD_ITEM_ERROR),
    Cmd_Item_Str_Test_Pair("FF:FF:FF:FF:FF:FF", CMD_ITEM_OK),

    Cmd_Item_Str_Test_Pair("<str>'", CMD_ITEM_ERROR),

    // Escaped:
    Cmd_Item_Str_Test_Pair("\\\"Str\\\"", CMD_ITEM_OK),
};

void test1() {
    std::cout << "Test_Cmd_Item_Str test 1" << std::endl;
    Cmd_Item_Str v("", "");
    //InputTest::TestInputBase(v, TestVector, sizeof (TestVector) / sizeof (InputTestPair));
    
    int test_vector_size = sizeof (TestVector) / sizeof (Cmd_Item_Str_Test_Pair);

    for (int i = 0; i < test_vector_size; i++) {
        Cmd_Item_Valid_Result res = v.Parse(TestVector[i].first);
        if (res != TestVector[i].second)
            std::cout << "%TEST_FAILED% time=0 testname=test1 (Test_Cmd_Item_Str) message="
                << v.To_String() << " res=" << Cmd_Item_Valid_Result_Func::To_String(res)
            << " (must be " << Cmd_Item_Valid_Result_Func::To_String(TestVector[i].second) << ")" << std::endl;
        else std::cout << "\"" << v.Value_Str << "\": " << Cmd_Item_Valid_Result_Func::To_String(res) << " - Passed" << std::endl;
    }
}

int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTING% Test_Cmd_Item_Str" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% test1 (Test_Cmd_Item_Str)" << std::endl;
    test1();
    std::cout << "%TEST_FINISHED% time=0 test1 (Test_Cmd_Item_Str)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}
