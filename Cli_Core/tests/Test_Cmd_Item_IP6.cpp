/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Test_Cmd_Item_IP6.cpp
 * Author: mike
 *
 * Created on July 13, 2020, 2:53 PM
 */

#include <stdlib.h>
#include <iostream>

/*
 * Simple C++ Test Suite
 */

#include "Cmd_Item_Valid_Result.h"
#include "Cmd_Item_Valid_Result_Func.h"

#include "Cmd_Item_IP6.h"

typedef std::pair< std::string, Cmd_Item_Valid_Result > Cmd_Item_Test_Pair;

static const Cmd_Item_Test_Pair TestVector[] = {
    Cmd_Item_Test_Pair("", CMD_ITEM_EMPTY),
    Cmd_Item_Test_Pair("FFFF:FFFF:FFFF:FFFF:FFFF:FFFF:FFFF:FFFF", CMD_ITEM_OK),
    Cmd_Item_Test_Pair("FFFF:FFFF:FFFF:FFFF:FFFF:FFFF:FFFF:FFF", CMD_ITEM_OK),
    Cmd_Item_Test_Pair("FFFF:FFFF:FFFF:FFFF:FFFF:FFFF:FFFF:FF", CMD_ITEM_OK),
    Cmd_Item_Test_Pair("FFFF:FFFF:FFFF:FFFF:FFFF:FFFF:FFFF:F", CMD_ITEM_OK),
    Cmd_Item_Test_Pair("FFFF:FFFF:FFFF:FFFF:FFFF:FFFF:FFFF:", CMD_ITEM_ERROR),
    Cmd_Item_Test_Pair("FFFF:FFFF:FFFF:FFFF:FFFF:FFFF:FFFF", CMD_ITEM_ERROR),
    Cmd_Item_Test_Pair("::ffff:192.168.1.12", CMD_ITEM_OK),
    Cmd_Item_Test_Pair("::ffff:192.168.1.1", CMD_ITEM_OK),
    Cmd_Item_Test_Pair("::ffff:192.168.1.", CMD_ITEM_ERROR),
    Cmd_Item_Test_Pair("::ae21:ad12", CMD_ITEM_OK),
    Cmd_Item_Test_Pair("", CMD_ITEM_EMPTY),
    Cmd_Item_Test_Pair(":", CMD_ITEM_ERROR),
    Cmd_Item_Test_Pair("::", CMD_ITEM_OK),
    Cmd_Item_Test_Pair("::a", CMD_ITEM_OK),
    Cmd_Item_Test_Pair("::ae", CMD_ITEM_OK),
    Cmd_Item_Test_Pair("::ae2", CMD_ITEM_OK),
    Cmd_Item_Test_Pair("::ae21", CMD_ITEM_OK),
    Cmd_Item_Test_Pair("::", CMD_ITEM_OK),
    Cmd_Item_Test_Pair("::1", CMD_ITEM_OK),
};

void test1() {
    std::cout << "Test_Cmd_Item_IP6 test 1" << std::endl;

    Cmd_Item_IP6 v("", "");

    int test_vector_size = sizeof (TestVector) / sizeof (Cmd_Item_Test_Pair);

    for (int i = 0; i < test_vector_size; i++) {
        Cmd_Item_Valid_Result res = v.Parse(TestVector[i].first);
        if (res != TestVector[i].second)
            std::cout << "%TEST_FAILED% time=0 testname=test1 (Test_Cmd_Item_IP6) message="
                << v.To_String() << " res=" << Cmd_Item_Valid_Result_Func::To_String(res)
            << " (must be " << Cmd_Item_Valid_Result_Func::To_String(TestVector[i].second) << ")" << std::endl;
        else std::cout << "\"" << v.Value_Str << "\": " << Cmd_Item_Valid_Result_Func::To_String(res) << " - Passed" << std::endl;
    }
}

int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTING% Test_Cmd_Item_IP6" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% test1 (Test_Cmd_Item_IP6)" << std::endl;
    test1();
    std::cout << "%TEST_FINISHED% time=0 test1 (Test_Cmd_Item_IP6)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}

