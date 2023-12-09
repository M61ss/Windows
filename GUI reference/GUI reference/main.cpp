#include <iostream>
#include <windows.h>

// This is an handle to identify my window
HWND hwndWNDMain;

// This object is needed for store messages from other instance
MSG msg;

// This is the structure of the main for a windows application:
// hInstance = handle of the current instance
// hPrevInstance = handle of the previous instance (maybe this is a child of another)
// lCmdLine = a string that contains the command line arguments
// nCmdShow = ???
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lCmdLine, int nCmdShow) {
	// Here is a data structure that contains basic informations of the window that we want to create
	WNDCLASSEX wc;

	// I have to set to zero all the memory of the data structure to avoid crashes
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	// Here I fill the fields of past declered wc struct. All of these are feature that are documented on Microsoft Learn.
	// So, if you want to use different values from these used in this example you can visit https://learn.microsoft.com/it-it/training/?source=learn
	wc.cbSize = sizeof(WNDCLASSEX);					// Simply the size of the structure (like the size given to the malloc for classical C memory allocations)
	wc.cbClsExtra = 0;								// An extra memory (?)
	wc.hInstance = hInstance;						// The handle instance of the window has to be the instance assigned to WinMain (the handle is an identifier used by kernel)
	wc.cbWndExtra = 0;								// An extra memory (?)
	wc.style = CS_HREDRAW | CS_VREDRAW;				// Using '|' (logical 'or') I can combine some styles which I want to have for my window. These are simply concateneted exadecimal codes. Combining them, I can give to my window the styles feature that I want. These are only examples, on Microsoft Learn is possible to find the complete documentation. 
	wc.hIcon = nullptr;								// This is the taskbar icon for the application
	wc.hIconSm = nullptr;							// This is the smaller icon (so what?)
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);	// This is the standard cursor, but on the documentation is possible to find all cursor you want
	wc.hbrBackground = nullptr;						// This is the background color. So the background color will be standard (white)
	wc.lpszMenuName = nullptr;						// This is the contestual menu of the window (the higher menu bar, like file, edit, view, ecc)
	wc.lpszClassName = L"wndRepairClass";			// This is the name of the class
	wc.lpfnWndProc = ;								// This is a pointer to the information of the current windows process (spannometric definition...)

	// Verifing that wc has been successfully registered
	if (!RegisterClassEx(&wc)) {
		MessageBox(
			nullptr,											// ???
			L"Error during the registration of window class",	// Error message
			L"ERROR",											// Caption of the message
			MB_OK | MB_ICONERROR								// Feature of the message (in this case the mb (message box) has a ok buttton and the icon error)
		);

		return -1;
	}

	// Here I create my window
	hwndWNDMain = CreateWindow(
		L"wndRepairClass",													// Here I report the class name that I assigned before in wc struct
		L"WinRepair",														// This is the name shown of the window
		WS_BORDER | WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU | WS_VISIBLE,	// These are styles of the window
		CW_USEDEFAULT,														// This is the starter x coord when I open the window 
		CW_USEDEFAULT,														// This is the starter y coord when I open the window 
		500,																// Width
		500,																// Height
		nullptr,															// Father window handle
		nullptr,															// Menu handle
		hInstance,															// Current instance handle
		nullptr																// ???
	);

	// Verifing that hwndWNDMain has been successfully created
	if (!hwndWNDMain) {
		MessageBox(
			nullptr,
			L"Error creating window",
			L"ERROR",
			MB_OK | MB_ICONERROR
		);

		return -2;
	}

	// Now I display the window
	ShowWindow(
		hwndWNDMain,		// The handle of the window
		SW_SHOWNORMAL		// ???
	);

	// This is the last essential part to make the window work correctly
	// This is a loop to allow the window to recieve messages from windows and controls (including OS)
	while (GetMessage(&msg, nullptr, 0, 0)) {		// Structure of the function GetMessage ???
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}