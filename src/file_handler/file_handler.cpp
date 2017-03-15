/**************************************************************************************************
*
* \file
* \brief EB C++ Training - C++11/14 - Move Example
*
* Copyright (c) 2016 Elektrobit. All rights reserved.
*
* This file is part of the Elektrobit C++ Training.
*
* Task: Implement a file class which manages a HANDLE from a C API according to the RAII idiom.
* - The file class shall open a file in its constructor and close it in its destructor.
* - In addition, the file class shall support move construction and move assignment.
* Additional question: Does it make sense for the file class to define copy operations? If not,
* which measures have to be taken in order to suppress them?
*
**************************************************************************************************/

#include <iostream>
//#include <utility>

typedef int HANDLE;
// an invalid handle is 0

HANDLE OpenFile(char const* name)
{
    static HANDLE handle = 1;
    std::cout << __func__ << "(\"" << name << "\")\n";
    return handle++;
}

void Close(HANDLE h)
{
    std::cout << __func__ << "(" << h << ")\n";
}

class file
{
public:
    file(char const* name)
        : handle(OpenFile(name))
    {}
    
    //file(file const&) = default;
    //file& operator=(file const& other) = default;


    file(file&& other) noexcept
        : handle(other.handle)
    {
        other.handle = 0;
    }

    file& operator=(file&& other) noexcept
    {
        std::swap(handle, other.handle);
        return *this;
    }
    
    ~file()
    {
        if (handle)
        {
            Close(handle);
        }
    }

    // read, write, etc

private:
    HANDLE handle;
};

int main()
{
    file f1("File 1");
    file f2(std::move(f1));

    file f3("File 3");
    f3 = std::move(f2);

    // Can I copy?
    //file f4(f3);
    file f4("file 4");
    //f4 = f3;
    // No because, the others wer eimplemented, then the other should be implemented
    // or Yes, if I make them default
}

// Output:
// OpenFile("File 1")
// OpenFile("File 3")
// Close(1)
// Close(2)
