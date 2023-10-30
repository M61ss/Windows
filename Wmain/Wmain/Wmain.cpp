// Wmain.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#ifndef UNICODE
#define UNICODE
#endif // !UNICODE

#ifndef _UNICODE
#define _UNICODE
#endif // !_UNICODE

#include <windows.h>
#include <wchar.h>

using namespace std;

void wmain(int argc, const wchar_t* argv[]) {
	// assuming argc >= 2 everytime

	WCHAR buffer[32];
	// this overload is dedicated for static buffer
	wcscpy_s(buffer, argv[1]);

	WCHAR* buffer2 = (WCHAR*)malloc(32 * sizeof(WCHAR));
	// wcscpy_s(buffer2, argv[1]);		but this line does not compile!

	// this line compiles because i am using a dedicated overload for dinamically allocated buffers
	wcscpy_s(buffer2, 32, argv[1]);		// the size is in characters, NOT in bytes!

	free(buffer2);
}
