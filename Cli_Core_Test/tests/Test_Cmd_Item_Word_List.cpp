/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Test_Cmd_Item_Word_List.cpp
 * Author: mike
 *
 * Created on July 14, 2020, 2:37 PM
 */

#include <stdlib.h>
#include <iostream>

/*
 * Simple C++ Test Suite
 */

#include "Cmd_Item_Valid_Result.h"
#include "Cmd_Item_Valid_Result_Func.h"

#include "Cmd_Item_Word_List.h"

typedef std::pair< std::string, Cmd_Item_Valid_Result > Cmd_Item_Test_Pair;

static const Cmd_Item_Test_Pair TestVector_1[] = {
    Cmd_Item_Test_Pair("", CMD_ITEM_EMPTY),

    Cmd_Item_Test_Pair("raw", CMD_ITEM_OK),
    Cmd_Item_Test_Pair("net", CMD_ITEM_OK),
    Cmd_Item_Test_Pair("local", CMD_ITEM_OK),
    Cmd_Item_Test_Pair("remote", CMD_ITEM_OK),

    Cmd_Item_Test_Pair("raw,net,local,remote", CMD_ITEM_OK),
    Cmd_Item_Test_Pair("raw,net,local", CMD_ITEM_OK),
    Cmd_Item_Test_Pair("raw,net", CMD_ITEM_OK),

    Cmd_Item_Test_Pair("r", CMD_ITEM_INCOMPLETE),
    Cmd_Item_Test_Pair("ra", CMD_ITEM_INCOMPLETE),

    Cmd_Item_Test_Pair("n", CMD_ITEM_INCOMPLETE),
    Cmd_Item_Test_Pair("ne", CMD_ITEM_INCOMPLETE),

    Cmd_Item_Test_Pair("l", CMD_ITEM_INCOMPLETE),
    Cmd_Item_Test_Pair("lo", CMD_ITEM_INCOMPLETE),
    Cmd_Item_Test_Pair("loc", CMD_ITEM_INCOMPLETE),
    Cmd_Item_Test_Pair("loca", CMD_ITEM_INCOMPLETE),

    Cmd_Item_Test_Pair("r", CMD_ITEM_INCOMPLETE),
    Cmd_Item_Test_Pair("re", CMD_ITEM_INCOMPLETE),
    Cmd_Item_Test_Pair("rem", CMD_ITEM_INCOMPLETE),
    Cmd_Item_Test_Pair("remo", CMD_ITEM_INCOMPLETE),
    Cmd_Item_Test_Pair("remot", CMD_ITEM_INCOMPLETE),

    Cmd_Item_Test_Pair("raw,", CMD_ITEM_INCOMPLETE),
    Cmd_Item_Test_Pair("net,", CMD_ITEM_INCOMPLETE),
    Cmd_Item_Test_Pair("local,", CMD_ITEM_INCOMPLETE),
    Cmd_Item_Test_Pair("remote,", CMD_ITEM_INCOMPLETE),

    Cmd_Item_Test_Pair("raw,n", CMD_ITEM_INCOMPLETE),
    Cmd_Item_Test_Pair("net,l", CMD_ITEM_INCOMPLETE),
    Cmd_Item_Test_Pair("local,r", CMD_ITEM_INCOMPLETE),
    Cmd_Item_Test_Pair("remote,r", CMD_ITEM_INCOMPLETE),

    Cmd_Item_Test_Pair("raw,raw", CMD_ITEM_ERROR),
    Cmd_Item_Test_Pair("net,net", CMD_ITEM_ERROR),
    Cmd_Item_Test_Pair("local,local", CMD_ITEM_ERROR),
    Cmd_Item_Test_Pair("remote,remote", CMD_ITEM_ERROR),

    Cmd_Item_Test_Pair("rawz", CMD_ITEM_ERROR),
    Cmd_Item_Test_Pair("netz", CMD_ITEM_ERROR),
    Cmd_Item_Test_Pair("localz", CMD_ITEM_ERROR),
    Cmd_Item_Test_Pair("remotez", CMD_ITEM_ERROR),

    Cmd_Item_Test_Pair("e", CMD_ITEM_ERROR),
    Cmd_Item_Test_Pair("enb", CMD_ITEM_ERROR),
    Cmd_Item_Test_Pair("enableb", CMD_ITEM_ERROR),
    Cmd_Item_Test_Pair("disb", CMD_ITEM_ERROR),
};

void test1() {
    std::cout << "Test_Cmd_Item_Word_List test 1" << std::endl;

    vector<string> words;
    words.push_back("raw");
    words.push_back("net");
    words.push_back("local");
    words.push_back("remote");
    Cmd_Item_Word_List v("[raw,net,local,remote]", "test: set loopback [raw,net,local,remote]", words);

    int test_vector_size = sizeof (TestVector_1) / sizeof (Cmd_Item_Test_Pair);

    for (int i = 0; i < test_vector_size; i++) {
        Cmd_Item_Valid_Result res = v.Parse(TestVector_1[i].first);
        if (res != TestVector_1[i].second)
            //std::cout << "%TEST_FAILED% time=0 testname=test1 (TestInputBase) message="
            //                    << "tab_cmd_list[0]->Text=\"" << tab_cmd_list[0]->Text << "\""
            //                    " != test_item:\"" << test_item.Tab_Cmd_0 << "\"" << std::endl;
            std::cout << "%TEST_FAILED% time=0 testname=test1 (TestInputBase) message="
                << v.To_String() << " res=\"" << Cmd_Item_Valid_Result_Func::To_String(res) << "\""
            " != test_item:\"" << Cmd_Item_Valid_Result_Func::To_String(TestVector_1[i].second) << "\"" << std::endl;
            //std::cout << "%TEST_FAILED% time=0 testname=test1 (Test_Cmd_Item_Word_List) message="
            //    << v.To_String() << " res=" << Cmd_Item_Valid_Result_Func::To_String(res)
            //<< " (must be " << Cmd_Item_Valid_Result_Func::To_String(TestVector[i].second) << ")" << std::endl;
        else std::cout << "\"" << v.Value_Str << "\": " << Cmd_Item_Valid_Result_Func::To_String(res) << " - Passed" << std::endl;
    }
}

static const Cmd_Item_Test_Pair TestVector_2[] = {
    Cmd_Item_Test_Pair("", CMD_ITEM_EMPTY),

    Cmd_Item_Test_Pair("raw", CMD_ITEM_OK),
    Cmd_Item_Test_Pair("net", CMD_ITEM_OK),
    Cmd_Item_Test_Pair("local", CMD_ITEM_OK),
    Cmd_Item_Test_Pair("remote", CMD_ITEM_OK),

    Cmd_Item_Test_Pair("raw,net,local,remote", CMD_ITEM_OK),
    Cmd_Item_Test_Pair("raw,net,local", CMD_ITEM_OK),
    Cmd_Item_Test_Pair("raw,net", CMD_ITEM_OK),

    Cmd_Item_Test_Pair("r", CMD_ITEM_INCOMPLETE),
    Cmd_Item_Test_Pair("ra", CMD_ITEM_INCOMPLETE),

    Cmd_Item_Test_Pair("n", CMD_ITEM_INCOMPLETE),
    Cmd_Item_Test_Pair("ne", CMD_ITEM_INCOMPLETE),

    Cmd_Item_Test_Pair("l", CMD_ITEM_INCOMPLETE),
    Cmd_Item_Test_Pair("lo", CMD_ITEM_INCOMPLETE),
    Cmd_Item_Test_Pair("loc", CMD_ITEM_INCOMPLETE),
    Cmd_Item_Test_Pair("loca", CMD_ITEM_INCOMPLETE),

    Cmd_Item_Test_Pair("r", CMD_ITEM_INCOMPLETE),
    Cmd_Item_Test_Pair("re", CMD_ITEM_INCOMPLETE),
    Cmd_Item_Test_Pair("rem", CMD_ITEM_INCOMPLETE),
    Cmd_Item_Test_Pair("remo", CMD_ITEM_INCOMPLETE),
    Cmd_Item_Test_Pair("remot", CMD_ITEM_INCOMPLETE),

    Cmd_Item_Test_Pair("raw,", CMD_ITEM_INCOMPLETE),
    Cmd_Item_Test_Pair("net,", CMD_ITEM_INCOMPLETE),
    Cmd_Item_Test_Pair("local,", CMD_ITEM_INCOMPLETE),
    Cmd_Item_Test_Pair("remote,", CMD_ITEM_INCOMPLETE),

    Cmd_Item_Test_Pair("raw,n", CMD_ITEM_INCOMPLETE),
    Cmd_Item_Test_Pair("net,l", CMD_ITEM_INCOMPLETE),
    Cmd_Item_Test_Pair("local,r", CMD_ITEM_INCOMPLETE),
    Cmd_Item_Test_Pair("remote,r", CMD_ITEM_INCOMPLETE),

    Cmd_Item_Test_Pair("raw,raw", CMD_ITEM_OK),//CMD_ITEM_ERROR), // @Attention: Can Repeat
    Cmd_Item_Test_Pair("net,net", CMD_ITEM_OK),//CMD_ITEM_ERROR), // @Attention: Can Repeat
    Cmd_Item_Test_Pair("local,local", CMD_ITEM_OK),//CMD_ITEM_ERROR), // @Attention: Can Repeat
    Cmd_Item_Test_Pair("remote,remote", CMD_ITEM_OK),//CMD_ITEM_ERROR), // @Attention: Can Repeat

    Cmd_Item_Test_Pair("rawz", CMD_ITEM_ERROR),
    Cmd_Item_Test_Pair("netz", CMD_ITEM_ERROR),
    Cmd_Item_Test_Pair("localz", CMD_ITEM_ERROR),
    Cmd_Item_Test_Pair("remotez", CMD_ITEM_ERROR),

    Cmd_Item_Test_Pair("e", CMD_ITEM_ERROR),
    Cmd_Item_Test_Pair("enb", CMD_ITEM_ERROR),
    Cmd_Item_Test_Pair("enableb", CMD_ITEM_ERROR),
    Cmd_Item_Test_Pair("disb", CMD_ITEM_ERROR),
};

void test2() {
    std::cout << "Test_Cmd_Item_Word_List test 2" << std::endl;

    vector<string> words;
    words.push_back("raw");
    words.push_back("net");
    words.push_back("local");
    words.push_back("remote");
    bool is_repeating = true;
    Cmd_Item_Word_List v("[raw,net,local,remote]", "test: set loopback [raw,net,local,remote]", words, is_repeating);

    int test_vector_size = sizeof (TestVector_2) / sizeof (Cmd_Item_Test_Pair);

    for (int i = 0; i < test_vector_size; i++) {
        Cmd_Item_Valid_Result res = v.Parse(TestVector_2[i].first);
        if (res != TestVector_2[i].second)
            std::cout << "%TEST_FAILED% time=0 testname=test2 (TestInputBase) message="
                << v.To_String() << " res=\"" << Cmd_Item_Valid_Result_Func::To_String(res) << "\""
            " != test_item:\"" << Cmd_Item_Valid_Result_Func::To_String(TestVector_2[i].second) << "\"" << std::endl;
        else std::cout << "\"" << v.Value_Str << "\": " << Cmd_Item_Valid_Result_Func::To_String(res) << " - Passed" << std::endl;
    }
}

int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTING% Test_Cmd_Item_Word_List" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% test1 (Test_Cmd_Item_Word_List)" << std::endl;
    test1();
    std::cout << "%TEST_FINISHED% time=0 test1 (Test_Cmd_Item_Word_List)" << std::endl;
    
    std::cout << "%TEST_STARTED% test2 (Test_Cmd_Item_Word_List)" << std::endl;
    test2();
    std::cout << "%TEST_FINISHED% time=0 test2 (Test_Cmd_Item_Word_List)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}
