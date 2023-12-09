#include <iostream>
#include <windows.h>

HWND hwndWNDMain;

LRESULT CALLBACK WndMainProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_CREATE:
		std::cout << "WM_CREATE!\n";
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
		500,
		500,
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