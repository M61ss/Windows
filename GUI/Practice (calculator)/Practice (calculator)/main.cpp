#include <iostream>
#include <string>
#include <windows.h>
#include <commctrl.h>
#include <windowsx.h>

HWND hwndWNDMain;

HWND hwndTXT_input;
HWND hwndTXT_output;
HWND hwndBTN[4][4];

LPCWSTR symbols[4][4] = {
	{L"1",L"2",L"3",L"+"},
	{L"4",L"5",L"6",L"-"},
	{L"7",L"8",L"9",L"*"},
	{L"",L"0",L"=",L"/"}
};

double a = 0, b = 0;	
CHAR check = 0;			

LRESULT CALLBACK WndMainProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_CREATE:
		hwndTXT_input = CreateWindow(
			WC_EDIT,								
			L"",									
			WS_CHILD | WS_VISIBLE | ES_RIGHT,		
			15,										
			10,										
			270,									
			25,										
			hWnd,									
			nullptr,								
			nullptr,								
			nullptr									
		);

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

		for (int i = 0, id = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				hwndBTN[i][j] = CreateWindow(
					WC_BUTTON,
					symbols[i][j],
					WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
					15 + (j * 70),
					130 + (i * 70),
					60,
					60,
					hWnd,
					(HMENU)id,
					nullptr,
					nullptr
				);
				id++;
			}
		}

		break;
	case WM_COMMAND:
		switch (HIWORD(wParam)) {
		case BN_CLICKED:
			WCHAR buffer[1000];	buffer[0] = L'\0';
			switch (LOWORD(wParam)) {
			case 0:
				Edit_GetText(hwndTXT_input, buffer, 999);
				wcscat_s(buffer, L"1");	
				Edit_SetText(hwndTXT_input, buffer);
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
			case 3:
				if (check == 0) {
					Edit_GetText(hwndTXT_input, buffer, 999);
					a = _wtof(buffer);
					Edit_SetText(hwndTXT_input, L"");
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
			case 7:
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
			case 11:
				if (check == 0) {
					Edit_GetText(hwndTXT_input, buffer, 999);
					a = _wtof(buffer);
					Edit_SetText(hwndTXT_input, L"");
					check = '*';
				}
				break;
			case 12:
				break;
			case 13:
				Edit_GetText(hwndTXT_input, buffer, 999);
				wcscat_s(buffer, L"0");
				Edit_SetText(hwndTXT_input, buffer);
				break;
			case 14:
				double numerical_res;
				switch (check) {
				case '+':
					Edit_GetText(hwndTXT_input, buffer, 999);	
					b = _wtof(buffer);							
					Edit_SetText(hwndTXT_input, L"");			
					numerical_res = a + b;						
					swprintf_s(buffer, L"%lf", numerical_res);	
					Edit_SetText(hwndTXT_output, buffer);		
					check = 0;									
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
					if (b != 0) {
						numerical_res = a / b;
						swprintf_s(buffer, L"%lf", numerical_res);
					}
					else {
						swprintf_s(buffer, L"ERROR: cannot divide by 0");
					}
					Edit_SetText(hwndTXT_output, buffer);
					check = 0;
					break;
				default:
					Edit_GetText(hwndTXT_input, buffer, 999);
					Edit_SetText(hwndTXT_output, buffer);
					break;
				}
				Edit_SetText(hwndTXT_input, L"");
				break;
			case 15:
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