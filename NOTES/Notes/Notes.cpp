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
#include <stdlib.h>
#include <strsafe.h>

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

    // REMEMBER: In general the 'A' suffix means "ASCII" and the 'W' means "wide". In fact in the Windows API the functions are actually macros expanding
    // to two functions with these suffixes

    // ? CreateMutex is a constructor ?
    // Exist 2 functions: CreateMutexA ('A' stands for "ASCII", ASCII variant) or CreateMutexW ('W' stands for "wide", UNICODE variant).
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

    // REMEMBER: A set of safe string functions are available in the header <strsafe.h>

    // It is a matter of taste about what set of functions use. The only important thing is avoid the unsafe functions, so classic C/C++ functions
    // Unsafe funtions are deprecated, but defining some macros (for example _CRT_SECURE_NO_WARNINGS) they will be accepted by the compiler.
    // It is a bad practice define this macros while coding something new because the only reason that you would prefer an unsafe function to a 
    // safe one is retrocompatibility, so old source code that for many reason cannot be touched

    // If i want to know the number of elements of an array (or vector) i can use the macro _countof(array)
    char array[10];
    size_t elements = _countof(array);
    printf("%zu\n", elements);

    return 0;
}