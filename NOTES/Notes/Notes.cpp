// Windows 10 System Programming - part 1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#ifndef UNICODE
// Visual Studio defines this macro by default in all new projects, but it is good pratice to define that everytime
#define UNICODE
#endif // !UNICODE

#ifndef _UNICODE
// Visual Studio defines this macro by default in all new projects, but it is good pratice to define that everytime
#define _UNICODE
#endif // !_UNICODE

#include <windows.h>
#include <stdio.h>

/*  In this table there are some typedefs that allow to use ASCII or UNICODE, based on the UNICODE compilation constant:
    +----------------+--------------------+-------------------------+
    | Common type    | ASCII type         | UNICODE type            |
    +----------------+--------------------+-------------------------+
    | TCHAR          | char, CHAR         | wchar_t, WCHAR          |
    +----------------+--------------------+-------------------------+
    | LPTSTR, PTSTR  | char*, CHAR*, PSTR | wchar_t*, WCHAR*, PWSTR |
    +----------------+--------------------+-------------------------+
    | LPCTSTR PCTSTR | const char*, PCSTR | const wchar_t*, PCWSTR  |
    +----------------+--------------------+-------------------------+

    'W' = wide;
    'L' = long;
    'P' = pointer;
    'C' = constant;
    'STR' = string.

    The 'T' is meaningless, it is there only cause a retypedefinition (ex. typedef CHAR TCHAR)                               */

int main(void) {
    // struct(?) that contains native system informationas
    SYSTEM_INFO si;

    // This is a function that obtain some essential infos about the system
    // The double colon is to emphasize the fact the function is part of the Windows API and not some member function of the current C++ class
    // It is clear that in this code there is no C++ class around, but it is a convention that normally is good to use
    ::GetNativeSystemInfo(&si);

    printf("Number of Logical Processors: %d\n", si.dwNumberOfProcessors);
    printf("Page size: %d Bytes\n", si.dwPageSize);
    printf("Preocessor Mask: 0x%p\n", (PVOID)si.dwActiveProcessorMask);
    printf("Minimum process address: 0x%p\n", si.lpMinimumApplicationAddress);
    printf("Maximum process address: 0x%p\n", si.lpMaximumApplicationAddress);

    // This string uses 12 bytes (including terminator) because is UTF-16 encoded ('w' means "wide")
    // The 'L' prefix is necessary for strings encoded with UNICODE (if the macro UNICODE is defined the 'L' prefix is required)
    const wchar_t string[] = L"Hello";

    // ? CreateMutex is a constructor ?
    // 
    // Exist 2 functions: CreateMutexA ('A' stands for "ASCII", ASCII variant) or CreateMutexW ('W' stands for "wide", UNICODE variant).
    // !!! This variant are common to be defined for a lot of functions of windows.h !!!
    // 
    // The macro TEXT is equal to put 'L' prefix before the string (a smaller version of this macro is _T, that is defined in <tchar.h>) 
    HANDLE hMutex = ::CreateMutex(nullptr, FALSE, TEXT("MyMutex"));

    /* MANIPULATING STRINGS
        ASCII functions has the prefix "str" (ex: strcpy, strcat, ecc)
        UNICODE functions has the prefix "wcs"
        Windows API functions has the prefix "_tcs" and they work for both ASCII and UNICODE
    */

    WCHAR path[MAX_PATH];
    ::GetSystemDirectory(path, MAX_PATH);
    // %ws identifies UNICODE strings
    printf("System directory: %ws\n", path);

    return 0;
}

