#pragma once
#pragma warning(disable : 4996)
#include <cstring>

class MyString
{

    char *strptr{};
    unsigned int strSize{};
    unsigned int strCapacity{};

public:
    // "Vanilla-" Konstruktor
    MyString()
    {

        strptr = new char[10];
        strptr[0] = '\0';
        strSize = 0;
        strCapacity = 10;
    }
    // Konvertierkonstruktor
    MyString(const char *arr)
    {

        for (strSize = 0; arr[strSize] != '\0'; strSize++)
            ;

        strCapacity = strSize;
        strptr = new char[strCapacity + 1];

        strncpy(strptr, arr, strSize + 1);
    }
    // Kopierkonstruktor
    MyString(const MyString &arr)
    {
        strSize = arr.strSize;
        strCapacity = strSize;

        strptr = new char[strCapacity + 1];

        strncpy(strptr, arr.strptr, strSize + 1);
    }
    // Destruktor
    ~MyString()
    {

        delete[] strptr;
    }
    void reserve(unsigned int c);
    MyString &append(MyString &str);
    MyString &assign(const MyString &str);
    const char* c_str() const;
    const int size();
    const int capacity();
    void clear();
    bool empty();
    char &at(unsigned int i);
};
