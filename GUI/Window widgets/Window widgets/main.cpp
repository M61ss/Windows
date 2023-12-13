/*
To show the usage of Win32 to create widgets in this code has been developed a rudimental calculator. Clearly the calculator is not efficient, this is not the purpose
*/

#include <iostream>
#include <string>
#include <windows.h>
#include <commctrl.h>	// Here are defined all controls
#include <windowsx.h>	// Here some macros to simplify operations, for example, of writing in textbox (indeed 'x' stands for 'extended') or reading from

HWND hwndWNDMain;

// These are handles for widgets (names are arbitrary)
HWND hwndTXT_input;
HWND hwndTXT_output;
HWND hwndBTN[4][4];		// This is a matrix of handle (for buttons this case)

// This is a matrix of string that contains symbols to be displayed on top of buttons
LPCWSTR symbols[4][4] = {
	{L"1",L"2",L"3",L"+"},
	{L"4",L"5",L"6",L"-"},
	{L"7",L"8",L"9",L"*"},
	{L"",L"0",L"=",L"/"}
};

double a = 0, b = 0;	// Variables to do math ops (limited to this example)
CHAR check = 0;			// This variable checks how many times the used pressed a operation button. Basic case is check = 0. This way the program knows that the user is inserting the first number

LRESULT CALLBACK WndMainProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_CREATE:
		// Here I have to put all operations that I want to execute when the window is opening for the first time (so here I have to create standard widgets for my window)

		// Here I assign to this handle a textbox widget
		hwndTXT_input = CreateWindow(
			WC_EDIT,								// This is the standard class name for a textbox widget. Other standard widget class name are documented on: https://learn.microsoft.com/it-it/
			L"",									// Here I put nothing because I do not want to display nothing default in the textbox
			WS_CHILD | WS_VISIBLE | ES_RIGHT,		// These are styles specific for a widget. Documentation is on: https://learn.microsoft.com/it-it/
			15,										// This is the origin x coord for the widget
			10,										// This is the origin y coord for the widget
			270,									// Height of the widget
			25,										// Width of the widget
			hWnd,									// This is the parent window (passed as parameter to WndMainProc)
			nullptr,								// Menu handle
			nullptr,								// This parameter has to be set to null because it is a widget
			nullptr									// ???
		);

		// Another textbox widget
		hwndTXT_output = CreateWindow(
			WC_EDIT,
			L"",
			WS_CHILD | WS_VISIBLE | ES_RIGHT,
			15,
			55,
			270,
			25,
			hWnd,
			nullptr,
			nullptr,
			nullptr
		);

		// Classic double-for to scroll instances of matrix
		for (int i = 0, id = 0; i < 4; i++) {		// id is an unambiguos identifier for every single button. It is a temporary variable used to build the low part of HMENU parameter
			for (int j = 0; j < 4; j++) {
				// Button widgets
				hwndBTN[i][j] = CreateWindow(
					WC_BUTTON,									// This the standard class name for a button widget
					symbols[i][j],								// Here the text that we want to show into buttons
					WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
					15 + (j * 70),
					130 + (i * 70),
					60,
					60,
					hWnd,
					(HMENU)id,									// For WC_BUTTON widgets this parameter (his type is: HMENU) is used for identify the button (ignore the warning: conversion from 'int' to 'HMENU' of greater size, it is wanted) 
					nullptr,
					nullptr
				);
				id++;			// This way id grows for every cycle of double-for (id is saved into the father-for)
			}
		}

		break;
	case WM_COMMAND:
		switch (HIWORD(wParam)) {		// HIWORD (high word) is a function that allows to get wParam first 16 bits (see "Vital parts of a window" for the complete explanation)
		case BN_CLICKED:
			WCHAR buffer[1000];	buffer[0] = L'\0';		// Buffer to store the text which will be read from textbox
			switch (LOWORD(wParam)) {		// LOWORD (low word) do the same thing of HIWORD, but for 16 bits after. In this case these bits are the ids that I passed as HMENU parameter creating buttons
			// Here a case for every single id (maybe can I use a more intelligent and compact system?)
			case 0:
				Edit_GetText(			// This function gets some text from a textbox (the buffer is redeclered every time, so I have to read from input textbox before overwrite output)
					hwndTXT_input,		// Handle of textbox from I want to read
					buffer,				// Buffer to store text read from textbox
					999					// Buffer dimension
				);
				
				wcscat_s(buffer, L"1");		// Concatenating wstrings
				
				Edit_SetText(			// This function writes some text into a textbox
					hwndTXT_input,		// Handle of textbox where I want to write
					buffer				// Text to write
				);
				break;
			case 1:		
				Edit_GetText(hwndTXT_input, buffer, 999);
				wcscat_s(buffer, L"2");
				Edit_SetText(hwndTXT_input, buffer);
				break;
			case 2:
				Edit_GetText(hwndTXT_input, buffer, 999);
				wcscat_s(buffer, L"3");
				Edit_SetText(hwndTXT_input, buffer);
				break;
			case 3: // +
				if (check == 0) {
					Edit_GetText(hwndTXT_input, buffer, 999);
					a = _wtof(buffer);
					Edit_SetText(hwndTXT_input, L"");		// Cleaning input textbox to not compromise conversion to double
					check = '+';
				}
				break;
			case 4:
				Edit_GetText(hwndTXT_input, buffer, 999);
				wcscat_s(buffer, L"4");
				Edit_SetText(hwndTXT_input, buffer);
				break;
			case 5:
				Edit_GetText(hwndTXT_input, buffer, 999);
				wcscat_s(buffer, L"5");
				Edit_SetText(hwndTXT_input, buffer);
				break;
			case 6:
				Edit_GetText(hwndTXT_input, buffer, 999);
				wcscat_s(buffer, L"6");
				Edit_SetText(hwndTXT_input, buffer);
				break;
			case 7: // -
				if (check == 0) {
					Edit_GetText(hwndTXT_input, buffer, 999);
					a = _wtof(buffer);
					Edit_SetText(hwndTXT_input, L"");
					check = '-';
				}
				break;
			case 8:
				Edit_GetText(hwndTXT_input, buffer, 999);
				wcscat_s(buffer, L"7");
				Edit_SetText(hwndTXT_input, buffer);
				break;
			case 9:
				Edit_GetText(hwndTXT_input, buffer, 999);
				wcscat_s(buffer, L"8");
				Edit_SetText(hwndTXT_input, buffer);
				break;
			case 10:
				Edit_GetText(hwndTXT_input, buffer, 999);
				wcscat_s(buffer, L"9");
				Edit_SetText(hwndTXT_input, buffer);
				break;
			case 11: // *
				if (check == 0) {
					Edit_GetText(hwndTXT_input, buffer, 999);
					a = _wtof(buffer);
					Edit_SetText(hwndTXT_input, L"");
					check = '*';
				}
				break;
			case 12: // Nothing to do if this button is pressed
				break;
			case 13:
				Edit_GetText(hwndTXT_input, buffer, 999);
				wcscat_s(buffer, L"0");
				Edit_SetText(hwndTXT_input, buffer);
				break;
			case 14: // =
				double numerical_res;		// Here I will store the mathematical result (is better to do declarations out of switch's cases)
				switch (check) {
				case '+':
					Edit_GetText(hwndTXT_input, buffer, 999);	// Obtaining of the second number inserted by user
					b = _wtof(buffer);							// Doing the conversion
					Edit_SetText(hwndTXT_input, L"");			// Cleaning input textbox (for sure, I don't know what exactly does swprintf_s...)
					numerical_res = a + b;						// Sum
					swprintf_s(buffer, L"%lf", numerical_res);	// Converting the numerical result into a string
					Edit_SetText(hwndTXT_output, buffer);		// Writing on output textbox
					check = 0;									// Resetting check on 0
					break;
				case '-':
					Edit_GetText(hwndTXT_input, buffer, 999);
					b = _wtof(buffer);
					Edit_SetText(hwndTXT_input, L"");
					numerical_res = a - b;
					swprintf_s(buffer, L"%lf", numerical_res);
					Edit_SetText(hwndTXT_output, buffer);
					check = 0;
					break;
				case '*':
					Edit_GetText(hwndTXT_input, buffer, 999);
					b = _wtof(buffer);
					Edit_SetText(hwndTXT_input, L"");
					numerical_res = a * b;
					swprintf_s(buffer, L"%lf", numerical_res);
					Edit_SetText(hwndTXT_output, buffer);
					check = 0;
					break;
				case '/':
					Edit_GetText(hwndTXT_input, buffer, 999);
					b = _wtof(buffer);
					Edit_SetText(hwndTXT_input, L"");
					numerical_res = a / b;
					swprintf_s(buffer, L"%lf", numerical_res);
					Edit_SetText(hwndTXT_output, buffer);
					check = 0;
					break;
				default:
					Edit_GetText(hwndTXT_input, buffer, 999);
					Edit_SetText(hwndTXT_output, buffer);
					break;
				}
				Edit_SetText(hwndTXT_input, L"");		// Cleaning input textbox
				break;
			case 15: // /
				if (check == 0) {
					Edit_GetText(hwndTXT_input, buffer, 999);
					a = _wtof(buffer);
					Edit_SetText(hwndTXT_input, L"");
					check = '/';
				}
				break;
			}
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}
}

INT WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lCmdLine, _In_ int nCmdShow) {
	WNDCLASSEX wc;
	MSG msg;

	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbClsExtra = 0;
	wc.hInstance = hInstance;
	wc.cbWndExtra = 0;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hIcon = nullptr;
	wc.hIconSm = nullptr;
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = L"wndMainClass";
	wc.lpfnWndProc = WndMainProc;

	if (!RegisterClassEx(&wc)) {
		MessageBox(nullptr, L"Error during the registration of window class", L"ERROR", MB_OK | MB_ICONERROR);
		return -1;
	}

	hwndWNDMain = CreateWindow(
		L"wndMainClass",
		L"WinMain",
		WS_BORDER | WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU | WS_VISIBLE,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		315,
		450,
		nullptr,
		nullptr,
		hInstance,
		nullptr
	);

	if (!hwndWNDMain) {
		MessageBox(nullptr, L"Error creating window", L"ERROR", MB_OK | MB_ICONERROR);
		return -2;
	}

	ShowWindow(hwndWNDMain, SW_SHOWNORMAL);

	while (GetMessage(&msg, nullptr, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}