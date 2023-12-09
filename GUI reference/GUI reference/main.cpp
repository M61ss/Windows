#include <iostream>
#include <windows.h>

// This is an handle to identify my window
HWND hwndWNDMain;

// This function is used to manage messages dispatched from the window. Its name is arbitrary
LRESULT CALLBACK WndMainProc(
	HWND hWnd,				// Handle of who dispatch message
	UINT message,			// The message
	WPARAM wParam,			// ???
	LPARAM lParam			// ???
) {
	// Here I manage messages switching UINT message
	switch (message) {
	case WM_CREATE:
		std::cout << "WM_CREATE!\n";	// (not necessary)
		break;
	case WM_DESTROY:
		// This function allows to close the window
		PostQuitMessage(0);		// The parameter is the post quit message for the console
		break;
	default:
		// This is a standard function. All messages that are not managed in case defined by programmer, will be managed by it
		return DefWindowProc(hWnd, message, wParam, lParam);		// Parameters are the same of WndMainProc
		break;
	}

	// It is clear that there will be a warning saying: not all control paths return a value. It is normal, the function correctly works
}

// This is the main for a windows application. _In_ and _In_opt_ are named SAL annotations
INT WINAPI WinMain(
	_In_ HINSTANCE hInstance,			// Handle of the current instance
	_In_opt_ HINSTANCE hPrevInstance,	// Handle of the previous instance (maybe this is a child of another)
	_In_ LPSTR lCmdLine,				// A string that contains the command line arguments
	_In_ int nCmdShow					// ???
) {
	WNDCLASSEX wc;		// Here is a data structure that contains basic informations of the window that we want to create
	MSG msg;			// This object is needed for store messages from other instance

	ZeroMemory(&wc, sizeof(WNDCLASSEX));	// I have to set to zero all the memory of the data structure to avoid crashes

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
	wc.lpszClassName = L"wndMainClass";			// This is the name of the class
	wc.lpfnWndProc = WndMainProc;					// This is a pointer to the information of the current windows process (spannometric definition...for many reason this function doesn't need parameters...)

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
		L"wndMainClass",													// Here I report the class name that I assigned before in wc struct
		L"WinMain",														// This is the name shown of the window
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