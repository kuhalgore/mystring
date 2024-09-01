#pragma once
#include <cstring>
#include <vector>
#include <iostream>

// A simple implementation of a string class

class MyString
{

 public:

    //getters
    size_t length() {return buff_.size();}
    size_t capacity() {return buff_.capacity();}
    
    
    const char* c_str() const noexcept
    {
        data_ = new char[buff_.size() + 1];
        std::memcpy(data_, buff_.data(), buff_.size());
        data_[buff_.size()] = '\0';
        return data_;
        
    }
    
    //destructor
    ~MyString()
    {
        if(data_)
            delete [] data_;
    }
     
    //constructors
    MyString() = default;
    
    MyString(const char* src):MyString()
    {
        if(src == nullptr)
            return;
        size_t iLen = strlen(src);
        for(size_t i =0 ; i< iLen; ++i)
        {
            buff_.push_back(src[i]);
        }
    }

    //copy
    MyString(const MyString & other) = default;    
    MyString& operator = (const MyString & other)
    {
        if(this != &other)
        {
            buff_ = other.buff_;
        }
        return *this;
    }
    
    //move
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

    friend std::ostream& operator << (std::ostream& oo, const MyString& obj);
    
    void push_back(char c)
    {
        buff_.push_back(c);
    }
    
    //append
    MyString& append(const char* src)
    {
        if(src != nullptr && strlen(src) != 0)
        {
            
            size_t additionalLen = strlen(src);
            size_t oldLen = length();
            buff_.resize(oldLen  + additionalLen );
            for(size_t i =0; i<additionalLen; ++i)
            {
                buff_[oldLen +i] = src[i];
            }
            
        }       
        return *this;
    }
    
    MyString& operator +=(const char* src)
    {
        return this->append(src);
    }
    
    
private:
    std::vector<char> buff_;
    mutable char *data_;
    
};


std::ostream& operator << (std::ostream& oo, const MyString& obj)
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