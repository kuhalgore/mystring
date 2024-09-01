#include "mystring.h"
#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

int main(int argc, char *argv[])
{
    if (argc >= 2)
    {
        if( 0 == strcmp("run_unittests", argv[1]))
        {
            std::cout << "First argument  is run_unittests, hence running unit test cases\n";
            try
            {
                //run all unit test cases using catch2 unit testing framework 
                auto result = Catch::Session().run(argc-1, argv);
                return result;
            }
            catch (...)
            {
                return -1;
            }
        }
        std::cout << "usage mystring run_unittests, pass first argument as \"run_unittests\" to run the unit test cases\n";
        return -1;
    }
    
    // Normal flow, considerting no arguments passed
    
    //typedef MyString MYSTR;
    typedef std::string MYSTR;
    
    MYSTR str {"abc\0xyz"};
    std::cout << "\n1.1 str = " << str << ", cap = " << str.capacity() << " len = " << str.length();
    std::cout << "\n1.2 str.c_str() = " << str.c_str() << ", cap = " << str.capacity() << " len = " << str.length();
    std::cout << "\n1.2 str.data() = " << str.data() << ", cap = " << str.capacity() << " len = " << str.length();
    
    MYSTR str2("My own Mystr obj");
    
    str = str2;
    std::cout << "\n2.1 str2 = " << str2 << ", cap = " << str2.capacity() << " len = " << str2.length();

    str2.push_back('H');

    std::cout << "\n2.2 str2 = "<<str2<<", cap = " << str2.capacity() << " len = " << str2.length();

    const char *tmp2 = " the blue heaven, with icy gold ambience ";
    for(int i=0; i< 1000'000; ++i)
    {
        str2 += tmp2;
    }
    std::cout<<"\n-----------";
    std::cout<<"\n2.3 , cap = "<<str2.capacity()<<" len = "<<str2.length();
    
    return 0;
}