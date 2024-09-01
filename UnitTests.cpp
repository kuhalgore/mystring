#include <iostream>
#include <string>
#include "mystring.h"
#include "catch.hpp"


TEST_CASE("test 01", "test length and capacity of string constructed from const char *") 
{
    MyString mystr("My own Mystr obj");
    std::string stdstr("My own Mystr obj");
    
    REQUIRE(mystr.length() == 16);
    REQUIRE(stdstr.length() == 16);
    REQUIRE(mystr.capacity() >= 16);
    REQUIRE(stdstr.capacity() >= 16);
    
    
}

TEST_CASE("test 02", "test length and capacity when string string constructed from const char * contains \\0 in betweeen")
{
    MyString mystr("abc\0xyz");
    std::string stdstr("abc\0xyz");
    
    REQUIRE(mystr.length() == 3);
    REQUIRE(stdstr.length() == 3);
    REQUIRE(mystr.capacity() >= 3);
    REQUIRE(stdstr.capacity() >= 3);
    
}

TEST_CASE("test 03", "test length and capacity when string string constructed from initializer list")
{
    MyString mystr{"abcxyz"};
    std::string stdstr{"abcxyz"};
    
    REQUIRE(mystr.length() == 6);
    REQUIRE(stdstr.length() == 6);
    REQUIRE(mystr.capacity() >= 6);
    REQUIRE(stdstr.capacity() >= 6);
    
}

TEST_CASE("test 04", "test copy c'tor opeartor[] and c_str() and data()")
{
    MyString mystr2("My own Mystr obj");
    MyString mystr {mystr2};
    
    std::string stdstr2("My own Mystr obj");
    std::string stdstr {stdstr2};
    
    
    REQUIRE(mystr.length() == 16);
    REQUIRE(stdstr.length() == 16);
    
    
    REQUIRE(mystr.capacity() >= 16);
    REQUIRE(stdstr.capacity() >= 16);
    
    REQUIRE(mystr[16] == '\0');    
    REQUIRE(stdstr[16] == '\0');
    
    REQUIRE(0 == strcmp(mystr.c_str() , stdstr.c_str()));      
}

TEST_CASE("test 05", "test that clear reduces length to zero but capacity remains unchanged")
{
    MyString mystr{"abcxyz"};
    std::string stdstr{"abcxyz"};
    
    auto cap1 = mystr.capacity();
    auto cap2 = stdstr.capacity();
    
    mystr.clear();
    stdstr.clear();
    
    
    REQUIRE(mystr.length() == 0);
    REQUIRE(stdstr.length() == 0);
    
    
    REQUIRE(mystr.capacity() == cap1);
    REQUIRE(stdstr.capacity() == cap2);
    
}

TEST_CASE("test 06", "test that string can store \0")
{
    MyString mystr;
    std::string stdstr;
    
    REQUIRE(mystr.length() == 0);
    REQUIRE(mystr.capacity() == 0);
    REQUIRE(stdstr.length() >= 0);
    REQUIRE(stdstr.capacity() >= 0);
        
    mystr.push_back('A');
    mystr.push_back(' ');
    mystr.push_back('s');
    mystr.push_back('t');
    mystr.push_back('r');
    mystr.push_back('i');
    mystr.push_back('n');
    mystr.push_back('g');
    mystr.push_back(' ');
    mystr.push_back('w');
    mystr.push_back('i');
    mystr.push_back('t');
    mystr.push_back('h');
    mystr.push_back(' ');
    mystr.push_back('\0');
    mystr.push_back('i');
    mystr.push_back('n');
    mystr.push_back('b');
    mystr.push_back('e');
    mystr.push_back('t');
    mystr.push_back('w');
    mystr.push_back('e');
    mystr.push_back('e');
    mystr.push_back('n');
       
    REQUIRE(mystr.length() == 24);
    
    REQUIRE(mystr[0] == 'A'); // Frist char
    REQUIRE(mystr[14] == '\0'); //\0 in between at 14th position
    REQUIRE(mystr[23] == 'n'); // last non-terminating char
    REQUIRE(mystr[24] == '\0'); //null terminator at the end
    
    stdstr.push_back('A');
    stdstr.push_back(' ');
    stdstr.push_back('s');
    stdstr.push_back('t');
    stdstr.push_back('r');
    stdstr.push_back('i');
    stdstr.push_back('n');
    stdstr.push_back('g');
    stdstr.push_back(' ');
    stdstr.push_back('w');
    stdstr.push_back('i');
    stdstr.push_back('t');
    stdstr.push_back('h');
    stdstr.push_back(' ');
    stdstr.push_back('\0');
    stdstr.push_back('i');
    stdstr.push_back('n');
    stdstr.push_back('b');
    stdstr.push_back('e');
    stdstr.push_back('t');
    stdstr.push_back('w');
    stdstr.push_back('e');
    stdstr.push_back('e');
    stdstr.push_back('n');
    
    REQUIRE(stdstr[0] == 'A'); // Frist char
    REQUIRE(stdstr[14] == '\0'); //\0 in between at 14th position
    REQUIRE(stdstr[23] == 'n'); // last non-terminating char
    REQUIRE(stdstr[24] == '\0'); //null terminator at the end
}

TEST_CASE("test 07", "test construction of bing string using oerator += and append function")
{
    const size_t LOOP_COUNT = 1000'000;
    MyString mystr("My own Mystr obj - ");  
    MyString stdstr("My own Mystr obj - ");  
    std::string tmp("the blue heaven, with icy gold ambience! ");
    for(size_t i=0; i< LOOP_COUNT; ++i)
    {
        mystr += tmp.c_str();
        stdstr += tmp.c_str();
    }
    
    REQUIRE(mystr.length() == strlen("My own Mystr obj - ") +  LOOP_COUNT*tmp.length());
    REQUIRE(mystr.capacity() >= strlen("My own Mystr obj - ") +  LOOP_COUNT*tmp.length());
    
    REQUIRE(stdstr.length() == strlen("My own Mystr obj - ") +  LOOP_COUNT*tmp.length());
    REQUIRE(stdstr.capacity() >= strlen("My own Mystr obj - ") +  LOOP_COUNT*tmp.length());
    
}

TEST_CASE("test 08", "test move c'tor opeartor[] and c_str() and data()")
{
    
    MyString mystr (MyString("My own Mystr obj"));
    std::string stdstr (std::string("My own Mystr obj"));
    
    
    REQUIRE(mystr.length() == 16);
    REQUIRE(stdstr.length() == 16);
    
    
    REQUIRE(mystr.capacity() >= 16);
    REQUIRE(stdstr.capacity() >= 16);
    
    REQUIRE(mystr[16] == '\0');    
    REQUIRE(stdstr[16] == '\0');
    
    REQUIRE(0 == strcmp(mystr.c_str() , stdstr.c_str()));      
    
}

