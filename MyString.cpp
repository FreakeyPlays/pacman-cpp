#include "MyString.hpp"
#include <iostream>

using namespace std;

void MyString::reserve(unsigned int c)
{

    if (c > strCapacity)
    {
        char *anker = strptr;
        strCapacity = c;
        strptr = new char[c + 1];

        strncpy(this->strptr, anker, strSize + 1);
        delete[] anker;
    }
}

MyString &MyString::append(MyString &str)
{

    reserve(strSize + str.strSize);
    strncpy(strptr + strSize, str.strptr, str.strSize + 1);
    strSize += str.strSize;
    return *this;
}

MyString &MyString::assign(const MyString &str)
{

    reserve(str.strSize);
    strncpy(strptr, str.strptr, str.strSize + 1);
    strSize = str.strSize;
    return *this;
}

const char* MyString::c_str() const
{
    return strptr;
}

const int MyString::size()
{
    return strSize;
}

const int MyString::capacity()
{
    return strCapacity;
}

void MyString::clear()
{
    strptr[0] = '\0';
    strSize = 0;
}

bool MyString::empty()
{
    return strSize == 0;
}

char &MyString::at(unsigned int i)
{

    return (i < strSize) ? strptr[i] : strptr[strCapacity];
}
