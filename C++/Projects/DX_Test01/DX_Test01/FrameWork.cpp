#include "FrameWork.h"
#include "SystemDefs.h"

#include "iostream"
using namespace std;

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

FrameWork::FrameWork()
{
}


FrameWork::~FrameWork()
{
	UnregisterClass(m_applicationName, m_hInstance);
	m_hInstance = NULL;
}

bool FrameWork::Initialize()
{
	if (!CreateDXWindow("DX_Test01", WINDOW_POSX, WINDOW_POSY, SCREEN_WIDTH, SCREEN_HEIGHT))
	{
		return false;
	}
	return true;
}

void FrameWork::Run()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	//update loop
	while(msg.message!=WM_QUIT)
		{
			if (PeekMessage(&msg,NULL,0U,0U,PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				//update and render functions
			}
		}
}

bool FrameWork::CreateDXWindow(char* windowTitle, int x, int y, int width, int height)
{
	HWND hwnd;
	WNDCLASSEX wc;

	m_applicationName = windowTitle;

	m_hInstance = GetModuleHandle(NULL);

	//setup the window class with default settings
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = m_applicationName;
	wc.cbSize = sizeof(WNDCLASSEX);

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "RegisterClassEx() failed", "Error", MB_OK);
		return false;
	}
	int nStyle = WS_OVERLAPPED | WS_SYSMENU | WS_VISIBLE | WS_CAPTION | WS_MINIMIZEBOX;

	//TODO: Full Screen

	//int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	//int screenHight = GetSystemMetrics(SM_CYSCREEN);

	hwnd = CreateWindowEx(WS_EX_APPWINDOW, windowTitle, windowTitle, nStyle, x, y, width, height, NULL, NULL, m_hInstance, NULL);

	if (hwnd = NULL)
	{
		MessageBox(NULL, "Create WindowEX() Failed", "Error", MB_OK);
		PostQuitMessage(0);
		
		return false;
	}

	ShowWindow(hwnd, SW_SHOW);
	SetForegroundWindow(hwnd);
	SetFocus(hwnd);
	
	return true;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	
	switch (message)
	{
	case WM_PAINT:
	{
		hdc = BeginPaint(hwnd, &ps);
		EndPaint(hwnd, &ps);
	}break;
	case WM_CLOSE:
	{
		PostQuitMessage(0);
		DestroyWindow(hwnd);
	}break;
	default:
	{
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
	};
}