/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Test_Cmd_Item_Int.cpp
 * Author: mike
 *
 * Created on July 15, 2020, 9:30 AM
 */

#include <stdlib.h>
#include <iostream>

/*
 * Simple C++ Test Suite
 */

#include "Cmd_Item_Valid_Result.h"
#include "Cmd_Item_Valid_Result_Func.h"

#include "Cmd_Item_Int.h"

typedef std::pair< std::string, Cmd_Item_Valid_Result > Cmd_Item_Test_Pair;

static const Cmd_Item_Test_Pair TestVector[] = {
    Cmd_Item_Test_Pair("", CMD_ITEM_EMPTY),
    Cmd_Item_Test_Pair("0", CMD_ITEM_OK),
    Cmd_Item_Test_Pair("00", CMD_ITEM_OK),
    Cmd_Item_Test_Pair("00x0", CMD_ITEM_ERROR),
    Cmd_Item_Test_Pair("1", CMD_ITEM_OK),
    Cmd_Item_Test_Pair("2a", CMD_ITEM_ERROR),
    Cmd_Item_Test_Pair("999999999999", CMD_ITEM_TOO_LONG),
    Cmd_Item_Test_Pair("99999999999", CMD_ITEM_TOO_LONG),
    Cmd_Item_Test_Pair("9999999999", CMD_ITEM_TOO_LONG),
    Cmd_Item_Test_Pair("999999999", CMD_ITEM_OK),
    Cmd_Item_Test_Pair("2147483647", CMD_ITEM_OK),
    Cmd_Item_Test_Pair("2147483648", CMD_ITEM_TOO_LONG),
    Cmd_Item_Test_Pair("2147483649", CMD_ITEM_TOO_LONG),
    Cmd_Item_Test_Pair("+1", CMD_ITEM_ERROR)
};

void test1() {
    std::cout << "Test_Cmd_Item_Int test 1" << std::endl;

    Cmd_Item_Int v("", "");

    int test_vector_size = sizeof (TestVector) / sizeof (Cmd_Item_Test_Pair);

    for (int i = 0; i < test_vector_size; i++) {
        Cmd_Item_Valid_Result res = v.Parse(TestVector[i].first);
        if (res != TestVector[i].second)
            std::cout << "%TEST_FAILED% time=0 testname=test1 (Test_Cmd_Item_Int) message="
                << v.To_String() << " res=" << Cmd_Item_Valid_Result_Func::To_String(res)
            << " (must be " << Cmd_Item_Valid_Result_Func::To_String(TestVector[i].second) << ")" << std::endl;
        else std::cout << "\"" << v.Value_Str << "\": " << Cmd_Item_Valid_Result_Func::To_String(res) << " - Passed" << std::endl;
    }
}

int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTING% Test_Cmd_Item_Int" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% test1 (Test_Cmd_Item_Int)" << std::endl;
    test1();
    std::cout << "%TEST_FINISHED% time=0 test1 (Test_Cmd_Item_Int)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}
