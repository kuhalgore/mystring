#pragma once
#include <cstring>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <iterator>
// A simple implementation of a string class

class MyString
{
    
public:

    //getters
    size_t length() const {return buff_.empty()? 0 : buff_.size()-1;}
    size_t capacity() const {return buff_.capacity();}
    bool empty() const {return buff_.empty();}
    
    const char* data() const noexcept
    {
        return buff_.data();
    }
        
    const char* c_str() const noexcept
    {
        return buff_.data();
    }
    
    //destructor
    ~MyString() = default;
     
    //constructors
    //default
    MyString() = default;
    
    MyString(std::nullptr_t ) = delete;
    
    //from const char*, with specified len
    MyString(const char* src, size_t len)
    {
        if(len == 0)
            return;
        
        for(size_t i =0 ; i< len; ++i)
        {
            buff_.push_back(src[i]);
        }
        buff_.push_back('\0');
    }
    
    //from const char*
    MyString(const char* src) : MyString(src, strlen(src)) //constructor delegation 
    {
    }
    
    //from initializer list
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

    //modifiers
    char& operator[](size_t indx) //this function shuld not be called on empty string
    {
        return buff_[indx];
    }


    char& front() //this function shuld not be called on empty string
    {
       return buff_[0];
    }
    
    char& back()//this function shuld not be called on empty string
    {
        return buff_[length()-1];
    }
    
    void swap(MyString &other)
    {
        buff_.swap(other.buff_);
    }

    //apend a char at the end 
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
    
    //remove the char from the end
    void pop_back()
    {
        auto bufflen =  buff_.size();
        
        if(bufflen > 0) 
        {
            if(bufflen == 2)
            {
                //string contains only single char and one \0 character
                //remove all the 2 elements from buff_
                buff_.pop_back();
                buff_.pop_back();
            }
            else
            {           
                //Now, swap last two chars so that second last char will be null terminating char \0
                auto len = bufflen - 1;
                std::swap(buff_[len-1], buff_[len]); 
                buff_.pop_back(); //remove the last char
            }
        }
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
    
    void clear() { buff_.clear(); }

    void shrink_to_fit() 
    {
        buff_.shrink_to_fit();
    }
    
    //non modifiers
    
    const char& operator[](size_t indx) const //this function shuld not be called on empty string
    {
        return buff_[indx];
    }

    MyString& operator +=(const char* src)
    {
        return this->append(src);
    }
        
    int compare (const MyString& other) const
    {
        if(buff_ < other.buff_)
            return -1;
        else if (buff_ > other.buff_)
            return 1;
        else
            return 0;
    }
    
    MyString substr (size_t pos = 0, size_t len = npos) const
    {
        if(pos > length())
        {
            throw std::out_of_range("pos is beyond the length of the string");
        }
        
        MyString substr;
        if(pos < length() && (len > 0 || len == npos))
        {
            size_t newEnd;
            
            if(len == npos)
                newEnd = length();
            else
                newEnd = pos + len;
            
            for(size_t i = pos; i < newEnd; ++i)
            {
                substr.push_back(buff_[i]);
            }
        }
        return substr;
        
    }
    
    size_t find (const MyString& text, size_t pos = 0) const
    {
        auto iLen = text.length();
        if(pos + iLen > length())
            return npos;
        
        for(size_t i = pos; i <= length() - iLen; ++i)
        {
            if(substr(i,iLen) == text)
                return i;
        }
        
        return npos;
    }

    size_t find(char c, size_t pos = 0) const
    {
        if (pos + 1 > length())
            return npos;

        for (size_t i = pos; i <= length() - 1; ++i)
        {
            if (this->operator[](i) == c)
                return i;
        }

        return npos;
    }

    size_t find_first_of(const MyString& text, size_t pos = 0) const
    {
        
        if (pos + 1 > length())
            return npos;

        size_t retIndx = npos;
        

        for (size_t i =0; i< text.length(); ++i)
        {

            auto foundIndx = this->find(text[i], pos);
            if (foundIndx < retIndx)
                retIndx = foundIndx;
        }

        return retIndx;
    }

    //friend operators   
    friend std::ostream& operator << (std::ostream& oo, const MyString& obj)
    {              
        for(auto c : obj.buff_)
            oo<<c;
        
        return oo;
    }
    
    //relational operators
    friend bool operator == (const MyString& lhs, const MyString& rhs)
    {              
        return lhs.buff_ == rhs.buff_;
    }
    
    friend bool operator == (const MyString& lhs, const char* rhs)
    {              
        return lhs == MyString(rhs);
    }
    
    friend bool operator == (const char* lhs, const MyString& rhs)
    {              
        return MyString(lhs) == rhs;
    }
    
    
    static inline const size_t npos = -1;
private:
    std::vector<char>  buff_;   
};
