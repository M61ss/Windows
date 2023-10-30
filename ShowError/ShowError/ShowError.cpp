// ShowError.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#ifndef UNICODE
#define UNICODE
#endif // !UNICODE

#ifndef _UNICODE
#define _UNICODE
#endif // !_UNICODE

#include <stdio.h>
#include <windows.h>

using namespace std;

// This program takes an error number from the command-line arguments and shows its string representation (if exist)
// Full program is available on the github of the book

int main(int argc, const char* argv[]) {
    if (argc < 2) {
        printf("usage: ShowError <number>\n");
        return 0;
    }

    int message = atoi(argv[1]);

    LPWSTR text;
    DWORD chars = ::FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER |        // including this flag the function will allocate the buffer of the correct size
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        nullptr, message, 0,
        (LPWSTR)&text,                  // this is a terrible cast (notice that is a double pointer)
        0, nullptr
    );
    // without the flag FORMAT_MESSAGE_ALLOCATE_BUFFER it's up to the caller to allocate the buffer for the returned string

    if (chars > 0) {
        printf("Message %d: %ws\n", message, text);
        // This function frees the memory used
        ::LocalFree(text);
    }
    else {
        printf("No such error exists\n");
    }

    return 0;
}
