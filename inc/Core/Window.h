#pragma once

#include "windows.h"

#include "Core/EngineDescription.h"

using TikiEngine::Description::EngineDescription;

class Window
{
public:
	Window();
	~Window(void);

	bool Initialize(EngineDescription& desc);

	void Show();
	void ShowDialog();

	HWND GetHWND();
private:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

protected:
	HWND hWnd;
	HINSTANCE hInst;
};

