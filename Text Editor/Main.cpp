// ==================================================
//                A simple Text Editor
// ==================================================

#ifndef UNICODE
#define UNICODE
#endif//UNICODE

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <string>

HWND createMainWindow(int, int, std::wstring);
void createEditControl(HWND);

LRESULT CALLBACK windowProc(HWND, UINT, WPARAM, LPARAM);

// global variables
HWND g_hEdit;

int APIENTRY wWinMain(
	_In_     HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_     LPWSTR    pCmdLine,
	_In_     int       nCmdShow
)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(pCmdLine);

	HWND hwnd = createMainWindow(1000, 600, L"Text Editor");

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	MSG msg{};
	while (GetMessage(&msg, NULL, NULL, NULL))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return static_cast<int>(msg.wParam);
}

HWND createMainWindow(int nWidth, int nHeight, std::wstring szTitleName)
{
	HINSTANCE hInstance = GetModuleHandle(NULL);
	LPCWSTR szClassName = L"Text Editor";

	WNDCLASSEX wcex{};
	wcex.cbSize        = sizeof(WNDCLASSEX);
	wcex.style         = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc   = windowProc;
	wcex.cbClsExtra    = NULL;
	wcex.cbWndExtra    = NULL;
	wcex.hInstance     = hInstance;
	wcex.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = CreateSolidBrush(RGB(255, 255, 255));
	wcex.lpszMenuName  = NULL;
	wcex.lpszClassName = szClassName;
	wcex.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

	RegisterClassEx(&wcex);

	RECT clientRect = { 0, 0, nWidth, nHeight };
	AdjustWindowRectEx(&clientRect, WS_OVERLAPPEDWINDOW, FALSE, WS_EX_OVERLAPPEDWINDOW);

	return CreateWindowEx(
		WS_EX_OVERLAPPEDWINDOW,
		szClassName,
		szTitleName.c_str(),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, nWidth, nHeight,
		NULL,
		NULL,
		hInstance,
		NULL
	);
}

void createEditControl(HWND hwndParent)
{
	g_hEdit = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		L"Edit",
		L"",
		WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL,
		NULL, NULL, 1000, 600,
		hwndParent,
		NULL,
		NULL,
		NULL
	);
}

LRESULT CALLBACK windowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_CREATE:
			createEditControl(hwnd);
			break;

		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		default:
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	return 0;
}