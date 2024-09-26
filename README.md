# MyString
A simple implementation of string class named as MyString.

## mystring.h
Actual definition of the MyString class.
It makes use of vector<char> internally to store the data.

### public methods of MyString

//getters
- length()
- capacity()
- c_str()
- data()


//modifieers
- push_back()
- operator +=
- append()
- clear()
- operator []

//non-modifiers
compare()
substr()
find()
find_first_of()
find_first_not_of()
rfind()
find_last_of()
find_last_not_of()



//friend functions
- operator <<
- operator ==

## main.cpp
A sample code to check the the functionality provided by MyString class.

## unit test cases
The functionality of MyString class is tested using unit test cases written in UnitTests.cpp.
The tests in this file are written using catch2 - a header only unit testing framework.
Single header file catch.hpp is included in the same folder and is #included for unit test cases.
In each unit test we have also checked the corresponding functionality using std::string class and to 
make sure that the functionality works in same way for std::string class.

## How to run the sample code?
when no arguments is passed, the code executes basic checks given in the main function.
for example,
mystring.exe

when single argument "run_unittests" is passed, the code executes the unit test cases present in UnitTests.cpp
for example,
mystring.exe "run_unittests"

