#pragma once
#include <cstring>
#include <vector>
#include <iostream>

// A simple implementation of a string class

class MyString
{

 public:

    //getters
    size_t length() {return buff_.empty()? 0 : buff_.size()-1;}
    size_t capacity() {return buff_.capacity();}
    void clear() {buff_.clear();}
    
    const char* data() const noexcept
    {
        return buff_.data();
    }
    
    
    const char* c_str() const noexcept
    {
        //data_ = new char[buff_.size() + 1];
        //std::memcpy(data_, buff_.data(), buff_.size());
        //data_[buff_.size()] = '\0';
        //return data_;
        return buff_.data();
        
    }
    
    //destructor
    ~MyString() = default;
    
     
    //constructors
    //default
    MyString() = default;
    
    //from const char*
    MyString(const char* src):MyString()
    {
        if(src == nullptr)
            return;
        size_t iLen = strlen(src);
        for(size_t i =0 ; i< iLen; ++i)
        {
            buff_.push_back(src[i]);
        }
        buff_.push_back('\0');
        
    }
    //with initializer list
    MyString(std::initializer_list<char> srcInitList) : buff_{srcInitList} 
    {
        buff_.push_back('\0');
    }

    //copy c'tors
    MyString(const MyString & other) = default;    
    MyString& operator = (const MyString & other)
    {
        if(this != &other)
        {
            buff_ = other.buff_;
        }
        return *this;
    }
    
    //move c'tors
    MyString(MyString&& other) 
    {
        buff_.swap(other.buff_);
    }
    
    MyString& operator = (MyString && other)
    {
        if(this != &other)
        {
            buff_.clear();
            buff_.swap(other.buff_);
        }
        return *this;
    }

    char& operator[](size_t indx)
    {
        return buff_[indx];
    }

    //friend std::ostream& operator << (std::ostream& oo, const MyString& obj);
    friend std::ostream& operator << (std::ostream& oo, const MyString& obj)
{
    if(!obj.buff_.empty())
    {
        for(auto c : obj.buff_)
            oo<<c;
        
        return oo;
    }
    else
        return oo<<"";
    
}
    
    void push_back(char c)
    {
        if(buff_.empty())
            buff_.push_back(c);
        else 
        {
            //we are sure that buff_ will always have one more null terminating character at the end
            //hence add the new character at that position and push_back('\0') latter
            buff_[length()] = c;
        }
        buff_.push_back('\0');
    }
    
    //append
    MyString& append(const char* src)
    {
        if(src != nullptr && strlen(src) != 0)
        {
            
            size_t additionalLen = strlen(src);
            size_t oldLen = length();
            buff_.resize(oldLen  + additionalLen + 1);
            for(size_t i =0; i<additionalLen; ++i)
            {
                buff_[oldLen +i] = src[i];
            }
            buff_[oldLen  + additionalLen] = '\0';
            
        }       
        return *this;
    }
    
    MyString& operator +=(const char* src)
    {
        return this->append(src);
    }
    
    
private:
    std::vector<char> buff_;
    //mutable char *data_;
    
};