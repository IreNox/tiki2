// Main.cpp
#include "Core/WindowModule.h"

#include "Core/IGraphics.h"


namespace TikiEngine
{
	namespace Modules
	{
		#pragma region Class
		bool WindowModule::resetScreen = false;

		WindowModule::WindowModule(Engine* engine)
			: IModule(engine), hWnd(0), hInst(0)
		{
			ZeroMemory(&msg, sizeof(MSG));
		}

		WindowModule::~WindowModule(void)
		{
		}
		#pragma endregion

		#pragma region Member - Init
		bool WindowModule::Initialize(EngineDescription& desc)
		{
			this->hInst = desc.hInst;

			WNDCLASSEX win = WNDCLASSEX();
			win.hInstance		= hInst;
			win.lpfnWndProc		= &WindowModule::WndProc;
			win.lpszClassName	= desc.Window.WindowClass;
			win.cbSize			= sizeof(WNDCLASSEX);
			win.hbrBackground	= (HBRUSH)COLOR_WINDOWFRAME;
			win.hCursor			= LoadCursor(NULL, IDC_ARROW);
			win.hIcon			= desc.Window.Icon;

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
				desc.Window.Width,
				desc.Window.Height,
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

			RECT rect;
			GetClientRect(hWnd, &rect);
			desc.Graphics.Width = rect.right - rect.left;
			desc.Graphics.Height = rect.bottom - rect.top;

			desc.Window.hWnd = hWnd;

			ShowWindow(hWnd, 1);
			UpdateWindow(hWnd);

			return true;
		}
		#pragma endregion

		#pragma region Member
		HWND WindowModule::GetHWND()
		{
			return this->hWnd;
		}

		bool WindowModule::GetReady()
		{
			return (hWnd != 0) && (hInst != 0) && (msg.message != WM_QUIT);
		}

		void WindowModule::Dispose()
		{
			if (hWnd != 0)
			{
				DestroyWindow(hWnd);
				hWnd = 0;
			}
		}
		#pragma endregion

		#pragma region Member - Show
		__inline void WindowModule::Begin()
		{
			if (resetScreen)
			{
				EngineDescription& desc = engine->GetEngineDescription();

				RECT rect;
				GetClientRect(hWnd, &rect);

				if (desc.Graphics.Width != rect.right || desc.Graphics.Height != rect.bottom)
				{
					desc.Graphics.Width = rect.right;
					desc.Graphics.Height = rect.bottom;
					engine->graphics->Reset();
				}

				resetScreen = false;
			}

			if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}

		__inline void WindowModule::End()
		{
		}
		#pragma endregion

		#pragma region Member - Static - WndProc
		LRESULT CALLBACK WindowModule::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
		{
			switch (message)
			{
			case WM_DESTROY:
				PostQuitMessage(0);
				break;
			case WM_SIZE:
				resetScreen = true;
			default:
				return DefWindowProc(hWnd, message, wParam, lParam);
				break;
			}

			return 0;
		}
		#pragma endregion
	}
}