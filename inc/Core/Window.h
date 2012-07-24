#pragma once

#include "windows.h"

#include "WindowDescription.h"

using TikiEngine::Description::WindowDescription;

class Window
{
public:
	Window(HINSTANCE hInst);
	~Window(void);

	bool Initialize(const WindowDescription* desc);

	void Show();
	void ShowDialog();

	HWND GetHWND();
private:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

protected:
	HWND hWnd;
	HINSTANCE hInst;
};

