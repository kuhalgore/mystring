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
    MyString mystr2{"abc\0xyz", 7};
    std::string stdstr("abc\0xyz");
    std::string stdstr2{"abc\0xyz", 7};
    
    REQUIRE(mystr.length() == 3);
    REQUIRE(stdstr.length() == 3);
    REQUIRE(mystr.capacity() >= 3);
    REQUIRE(stdstr.capacity() >= 3);
    
    REQUIRE(mystr2.length() == 7);
    REQUIRE(stdstr2.length() == 7);
    REQUIRE(mystr2.capacity() >= 7);
    REQUIRE(stdstr2.capacity() >= 7);

}

TEST_CASE("test 03", "test length and capacity when string string constructed from initializer list")
{
    MyString mystr{'a', 'b', 'c', 'x', '\0', '\0', 'y', 'z'};
    std::string stdstr = {'a', 'b', 'c', '\0', '\0', 'x', 'y', 'z'};
    
    REQUIRE(mystr.length() == 8);
    REQUIRE(stdstr.length() == 8);
    REQUIRE(mystr.capacity() >= 8);
    REQUIRE(stdstr.capacity() >= 8);
    
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
    REQUIRE(mystr.capacity() >= 0);
    REQUIRE(stdstr.length() == 0);
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

TEST_CASE("test 08", "test move c'tor")
{
    MyString tmpmystr("My own Mystr obj");
    MyString mystr (std::move(tmpmystr));
    
    std::string tmpstdstr("My own Mystr obj");
    std::string stdstr (std::move(tmpstdstr));
    
    //check moved obj data
    REQUIRE(tmpmystr.length() == 0);
    REQUIRE(tmpmystr.capacity() == 0);

    REQUIRE(tmpstdstr.length() == 0);
    
    //check new object data
    REQUIRE(mystr.length() == 16);
    REQUIRE(stdstr.length() == 16);
    
    REQUIRE(mystr.capacity() >= 16);
    REQUIRE(stdstr.capacity() >= 16);
    
    REQUIRE(mystr[16] == '\0');    
    REQUIRE(stdstr[16] == '\0');
    
    REQUIRE(0 == strcmp(mystr.c_str() , stdstr.c_str()));      
    
}

TEST_CASE("test 09", "test move assignment")
{
    MyString tmpmystr("My own Mystr obj");
    MyString mystr ("old obj data");
    mystr = std::move(tmpmystr);
    
    std::string tmpstdstr("My own Mystr obj");
    std::string stdstr ("old obj data");
    stdstr = std::move(tmpstdstr);
    
    //check moved obj data
    REQUIRE(tmpmystr.length() == 0);

    REQUIRE(tmpstdstr.length() == 0);    
    
    //check new object data
    REQUIRE(mystr.length() == 16);
    REQUIRE(stdstr.length() == 16);
    
    
    REQUIRE(mystr.capacity() >= 16);
    REQUIRE(stdstr.capacity() >= 16);
    
    REQUIRE(mystr[16] == '\0');    
    REQUIRE(stdstr[16] == '\0');
    
    REQUIRE(0 == strcmp(mystr.c_str() , stdstr.c_str()));      
    
}

TEST_CASE("test 10", "test move assignment")
{
    MyString mystr("My own Mystr object");
    auto initialLength = mystr.length();
    
    mystr.pop_back();
    REQUIRE(mystr.length() == initialLength-1);
    
    mystr.pop_back();
    REQUIRE(mystr.length() == initialLength-2);

    mystr.pop_back();
    REQUIRE(mystr.length() == initialLength-3);
    
    MyString mystr2;
    mystr2.pop_back();
    mystr2.pop_back();
    mystr2.pop_back();
    REQUIRE(mystr2.length() == 0); //safe to call pop_back() on empty string
    
    MyString mystr3("T"); // string with single char
    mystr3.pop_back();
    REQUIRE(mystr2.length() == 0); //length becomes 0
    
    REQUIRE(mystr2 == MyString()); // it is equal to empty string
    
}

TEST_CASE("test 11", "test ==")
{
    MyString mystr("abc_123");
    const char* tmp = "abc_123";
    
    REQUIRE(mystr == tmp); 
    REQUIRE(tmp == mystr);  
    REQUIRE(mystr.c_str() == mystr); 
    REQUIRE(mystr == "abc_123"); 
    REQUIRE("abc_123"== mystr); 
    
    REQUIRE(MyString("")== MyString());  //empty string
    REQUIRE(MyString("").length()== 0);  //empty string length zero
    REQUIRE(MyString("").empty()== true);  //string of length zero is empty
    REQUIRE(MyString().empty()== true);  
}

TEST_CASE("test 12", "test compare")
{
    //MyString
    MyString mystr1("abc_123");
    MyString mystr2("abc_133");
    MyString mystr3("aBc_123");
    MyString mystr4("pqr");
    MyString mystr5("Abc");
    
    REQUIRE(0 == mystr1.compare(mystr1)); // self check
    REQUIRE(mystr1.compare(mystr2) < 0); // mystr1 < mystr2
    REQUIRE(mystr1.compare(mystr3) > 0); // mystr1 > mystr3
    REQUIRE(mystr1.compare(mystr4) < 0); // mystr1 < mystr4 because firt char of mystr1 < firt char of mystr4 
    REQUIRE(mystr1.compare(mystr5) > 0); // mystr1 > mystr5 because firt char of mystr1 > firt char of mystr5
    
    //std::string
    std::string str1("abc_123");
    std::string str2("abc_133");
    std::string str3("aBc_123");
    std::string str4("pqr");
    std::string str5("Abc");
    
    REQUIRE(0 == str1.compare(str1)); // self check
    REQUIRE(str1.compare(str2) < 0); // str1 < str2
    REQUIRE(str1.compare(str3) > 0); // str1 > str3
    REQUIRE(str1.compare(str4) < 0); // str1 < str4 because firt char of str1 < firt char of str4 
    REQUIRE(str1.compare(str5) > 0); // str1 > str5 because firt char of str1 > firt char of str5
    
}


TEST_CASE("test 13", "test front and back")
{
    //MyString
    MyString mystr("abc_123");
    REQUIRE(mystr.front() == 'a');
    REQUIRE(mystr.back() == '3');
    
    mystr.front() = 'A';
    REQUIRE(mystr.front() == 'A');

    mystr.back() = '4';
    REQUIRE(mystr.back() == '4');
    
    REQUIRE(mystr == "Abc_124");
    
    //std::string
    std::string str("abc_123");
    REQUIRE(str.front() == 'a');
    REQUIRE(str.back() == '3');
    
    str.front() = 'A';
    REQUIRE(str.front() == 'A');

    str.back() = '4';
    REQUIRE(str.back() == '4');
    
    REQUIRE(str == "Abc_124");
}


TEST_CASE("test 14", "test substr")
{
    //MyString
    MyString mystr("white apple");
    REQUIRE(mystr.substr() == mystr);
    REQUIRE(mystr.substr(6) == "apple");
    REQUIRE(mystr.substr(2,7) == "ite app");
    REQUIRE(mystr.substr(0,11) == mystr);
    REQUIRE(mystr.substr(11) == "");
    REQUIRE(mystr.substr(0,MyString::npos) == mystr);
    REQUIRE(mystr.substr(2, MyString::npos) == "ite apple");
    
    //std::string
    std::string str("white apple");
    REQUIRE(str.substr() == str);
    REQUIRE(str.substr(6) == "apple");
    REQUIRE(str.substr(2,7) == "ite app");
    REQUIRE(str.substr(2, std::string::npos) == "ite apple");
}

TEST_CASE("test 15", "test find")
{
    {
        //MyString
        MyString mystr("white apple and black apple");
        auto posFirstApple = mystr.find("apple");
        REQUIRE(posFirstApple == 6);
        auto posSecondApple = mystr.find("apple", posFirstApple + 1);
        REQUIRE(posSecondApple == 22);

        REQUIRE(mystr.find('p') == 7);
        REQUIRE(mystr.find('p',9) == 23);
    }
    {
        //std::string
        std::string str("white apple and black apple");
        auto posFirstApple = str.find("apple");
        REQUIRE(posFirstApple == 6);
        auto posSecondApple = str.find("apple", posFirstApple + 1);
        REQUIRE(posSecondApple == 22);
    }
    
}

TEST_CASE("test 16", "test find_first_of")
{
    {
        //MyString
        MyString mystr("white apple");
        auto posFirst = mystr.find_first_of("xyz");
        REQUIRE(posFirst == MyString::npos);

        auto posSecond = mystr.find_first_of("aeiou");
        REQUIRE(posSecond == 2);
    }
    {
        //std::string
        std::string str("white apple");
        auto posFirst = str.find_first_of("xyz");
        REQUIRE(posFirst == MyString::npos);

        auto posSecond = str.find_first_of("aeiou");
        REQUIRE(posSecond == 2);
    }

}

TEST_CASE("test 17", "test swap")
{
    {
        //MyString
        MyString mystr("white");
        MyString tmp;
        tmp.swap(mystr);
        
        REQUIRE(tmp == "white");
        REQUIRE(mystr == "");
        
    }
    {
        //std::string
        std::string str("white");
        std::string tmp;
        tmp.swap(str);
        
        REQUIRE(tmp == "white");
        REQUIRE(str == "");
    }

}

TEST_CASE("test 18", "test shrink_to_fit")
{
    {
        //MyString
        MyString mystr("white black red blue indigo");
        REQUIRE(mystr.capacity() >= mystr.length());
        
        mystr = "white";
        auto capBefore = mystr.capacity();
        mystr.shrink_to_fit();
        REQUIRE(capBefore >= mystr.capacity());
    }
    {
        //std::string
        std::string str("white black red blue indigo");
        REQUIRE(str.capacity() >= str.length());
        
        str = "white";
        auto capBefore = str.capacity();
        str.shrink_to_fit();
        REQUIRE(capBefore >= str.capacity());
    }

}

TEST_CASE("test 19", "test find_first_not_of")
{
    {
        //MyString
        MyString mystr("white apple");
        auto posFirst = mystr.find_first_not_of("xyz");
        REQUIRE(posFirst == 0);

        auto posSecond = mystr.find_first_not_of(" whiteple");
        REQUIRE(posSecond == 6);
        
        auto posThird = mystr.find_first_not_of(" whiteplea");
        REQUIRE(posThird == MyString::npos);
    }
    {
        //std::string
        std::string mystr("white apple");
        auto posFirst = mystr.find_first_not_of("xyz");
        REQUIRE(posFirst == 0);

        auto posSecond = mystr.find_first_not_of(" whiteple");
        REQUIRE(posSecond == 6);
        
        auto posThird = mystr.find_first_not_of(" whiteplea");
        REQUIRE(posThird == MyString::npos);
    }

}

TEST_CASE("test 20", "test rfind")
{
    {
        //MyString
        MyString mystr("white apple and black apple");
        auto posFirstApple = mystr.rfind("apple");
        REQUIRE(posFirstApple == 22);
        auto posSecondApple = mystr.rfind("apple", posFirstApple-1);
        REQUIRE(posSecondApple == 6);

        auto posFirstA = mystr.rfind('a');
        auto posSecondA = mystr.rfind('a', posFirstA - 1);
        REQUIRE(posFirstA == 22);
        REQUIRE(posSecondA == 18);

        auto posofW = mystr.rfind('w');
        REQUIRE(posofW == 0);

    }
    {
        //std::string
        std::string str("white apple and black apple");
        auto posFirstApple = str.rfind("apple");
        REQUIRE(posFirstApple == 22);
        auto posSecondApple = str.rfind("apple", posFirstApple - 1);
        REQUIRE(posSecondApple == 6);
        auto posFirstA = str.rfind('a');
        auto posSecondA =str.rfind('a', posFirstA - 1);
        REQUIRE(posFirstA == 22);
        REQUIRE(posSecondA == 18);

        auto posofW = str.rfind('w');
        REQUIRE(posofW == 0);
    }

}


TEST_CASE("test 21", "test find_last_of")
{
    {
        //MyString
        MyString mystr("white apple and black apple");

        auto posFirstApple = mystr.find_last_of("kp");
        REQUIRE(posFirstApple == 24);

        auto posSecondApple = mystr.find_last_of("ib");
        REQUIRE(posSecondApple == 16);

    }
    {
        //std::string
        std::string mystr("white apple and black apple");

        auto posFirstApple = mystr.find_last_of("kp");
        REQUIRE(posFirstApple == 24);

        auto posSecondApple = mystr.find_last_of("ib");
        REQUIRE(posSecondApple == 16);
    }
}

TEST_CASE("test 22", "test find_last_not_of")
{
    {
        //MyString
        MyString mystr("white apple");
        auto posFirst = mystr.find_last_not_of("xyz");
        REQUIRE(posFirst == 10);

        auto posSecond = mystr.find_last_not_of(" whiteple");
        REQUIRE(posSecond == 6);

        auto posThird = mystr.find_last_not_of(" whiteplea");
        REQUIRE(posThird == MyString::npos);
    }
    {
        //std::string
        std::string mystr("white apple");
        auto posFirst = mystr.find_last_not_of("xyz");
        REQUIRE(posFirst == 10);

        auto posSecond = mystr.find_last_not_of(" whiteple");
        REQUIRE(posSecond == 6);

        auto posThird = mystr.find_last_not_of(" whiteplea");
        REQUIRE(posThird == MyString::npos);
    }

}