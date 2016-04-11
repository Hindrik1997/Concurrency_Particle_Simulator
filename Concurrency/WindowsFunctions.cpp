#include "WindowFunctions.h"
#include <memory>
#include <wchar.h>
#include <chrono>

COLORREF ScreenBuffer[WIDTH][HEIGHT];
mutex BufferMut;
float Gravitation = -1.5f;

auto CheckMessage() -> bool
{
	MSG Msg;
	if (PeekMessage(&Msg, NULL, NULL, NULL, PM_REMOVE))
	{
		if (Msg.message == WM_QUIT)
			return false;
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return true;
}

static HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255)); //black

auto CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) -> LRESULT
{
	switch (msg)
	{
		case WM_KEYDOWN:
			if (wParam == VK_ESCAPE)
			{
				if (MessageBox(NULL, L"Weet je zeker dat je wilt stoppen?", L"Meent u dit nou? :(", MB_YESNO | MB_ICONQUESTION) == IDYES)
				{
					DestroyWindow(hwnd);
					PostQuitMessage(0);
				}
			}
			if (wParam == VK_RETURN)
			{
				SendMessage(hwnd, WM_COMMAND, 1, 0);
			}
			return 0;
		case WM_CLOSE:
			DestroyWindow(hwnd);
			return 0;
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		case WM_COMMAND:
			switch (LOWORD(wParam))
			{
				case 1:
					{

					}
					break;
				case 5:
					{
			
					}
					break;
			}
		break;
	default:
	{
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	}
	return 0;
}

auto InitializeWindow(HINSTANCE hInstance, wstring WindowClassName, wstring WindowTitle, int Width, int Height) -> HWND
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WindowClassName.c_str();
	wc.hIconSm = LoadIcon(hInstance, IDI_APPLICATION);

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, L"Window registratie gefaald!", L"Fout!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}
	RECT r = { 0,0,Width,Height };
	AdjustWindowRect(&r, WS_SYSMENU, FALSE);



	HWND hwnd = CreateWindowEx(
		NULL,
		WindowClassName.c_str(),
		WindowTitle.c_str(),
		WS_SYSMENU, //Enkel sluit button, verder default
		CW_USEDEFAULT, CW_USEDEFAULT, r.right - r.left, r.bottom - r.top,
		NULL, NULL, hInstance, NULL);

	if (hwnd == NULL)
	{
		MessageBox(NULL, L"Window creatie gefaald!", L"Fout!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}
	return hwnd;
}