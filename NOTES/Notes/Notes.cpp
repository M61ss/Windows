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

// I need this macro because the function "GetVersionExW" was deprecated (reason: defense from old versions)
#define BUILD_WINDOWS
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
    printf("Processor Mask: 0x%p\n", (PVOID)si.dwActiveProcessorMask);
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

    // It is a matter of taste about what set of functions use. The only important thing is avoid the unsafe functions, so some classic C/C++ functions
    // Unsafe funtions are deprecated, but defining some macros (for example _CRT_SECURE_NO_WARNINGS) they will be accepted by the compiler.
    // It is a bad practice define this macros while coding something new because the only reason that you would prefer an unsafe function to a 
    // safe one is retrocompatibility, so old source code that for many reason cannot be touched. It still be another good practice to use functions
    // contained in C/C++ standard library unless there is a good reason to use something else (for example unsafe functions)

    // If i want to know the number of elements of an array (or vector) i can use the macro _countof(array)
    char array[10];
    size_t elements = _countof(array);
    printf("%zu\n", elements);

    // Example of how to handle HRESULT errors (it is clear that this code is difficult at this moment, it is only an example of how to handle errors)
    IGlobalInterfaceTable* pGit;
    HRESULT hr = ::CoCreateInstance(CLSID_StdGlobalInterfaceTable, nullptr, CLSCTX_ALL, IID_IGlobalInterfaceTable, (void**)&pGit);
    if (FAILED(hr)) {
        printf("Error: %08X\n", hr);
    }
    else {
        // ... operations ...

        // release interface pointer
        pGit->Release();
    }

    // REMEMBER: however, it is a good practice to go on documentations of every function controlling their return values

    // Quering the system for the Windows version
    OSVERSIONINFO vi = { sizeof(vi) };

    // This function is deprecated because of its impossibility to find the correct version of Windows by itself, so it needs the defining of the macro BUILD_WINDOWS.
    // It needs the file "manifest.xml" (you can find it into the project folder) to detect the correct Windows version uncommenting
    // the line of respetive OS where the code will run.
    ::GetVersionEx(&vi);

    printf("Version: %d.%d.%d\n", vi.dwMajorVersion, vi.dwMinorVersion, vi.dwBuildNumber);

    return 0;
}
