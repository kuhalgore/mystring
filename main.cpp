#include "mystring.h"

int main()
{
    typedef MyString MYSTR;
    
    MYSTR str {"abc\0xyz"};
    std::cout << "\n1.1 str = " << str << ", cap = " << str.capacity() << " len = " << str.length();
    std::cout << "\n1.2 str.c_str() = " << str.c_str() << ", cap = " << str.capacity() << " len = " << str.length();
    
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