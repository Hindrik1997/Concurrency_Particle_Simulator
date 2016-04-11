#pragma once
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <windowsx.h>
#include <string>
#include <mutex>


using std::string;
using std::wstring;

using std::mutex;

const int WIDTH = 1920;
const int HEIGHT = 1080;

extern mutex BufferMut;

extern float Gravitation;

extern HWND gHwnd;
bool CheckMessage();
extern COLORREF ScreenBuffer[WIDTH][HEIGHT];
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
HWND InitializeWindow(HINSTANCE hInstance, wstring WindowClassName, wstring WindowTitle, int Width, int Height);