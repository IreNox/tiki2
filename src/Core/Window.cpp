// Main.cpp
#include "Core\Window.h"

#pragma region Class
Window::Window()
{
}

Window::~Window(void)
{
	if (hWnd != 0)
	{
		DestroyWindow(hWnd);
	}	
}
#pragma endregion

#pragma region Init
bool Window::Initialize(EngineDescription& desc)
{
	WNDCLASSEX win = WNDCLASSEX();

	hInst = desc.hInst;

	win.hInstance = hInst;
	win.lpfnWndProc = &Window::WndProc;
	win.lpszClassName = desc.Window.WindowClass;
	win.cbSize = sizeof(WNDCLASSEX);
	win.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);

	HRESULT r = RegisterClassEx(&win);

	if (FAILED(r))
	{
		MessageBox(NULL, L"Can't register Class.", desc.Window.WindowTitle, MB_HELP);
		return false;
	}

	hWnd = CreateWindow(
		desc.Window.WindowClass,
		desc.Window.WindowTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInst,
		NULL
	);

	if (!hWnd)
	{
		MessageBox(NULL, L"Can't create Window.", desc.Window.WindowTitle, MB_HELP);
		return false;
	}

	desc.Window.hWnd = hWnd;

	return true;
}
#pragma endregion

#pragma region Member
HWND Window::GetHWND()
{
	return this->hWnd;
}
#pragma endregion

#pragma region Member - Show
void Window::Show()
{
	ShowWindow(hWnd, 1);
	UpdateWindow(hWnd);
}

void Window::ShowDialog()
{
	this->Show();

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}
#pragma endregion

#pragma region Member - Static - WndProc
LRESULT CALLBACK Window::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
			break;
    }

	return 0;
}
#pragma endregion