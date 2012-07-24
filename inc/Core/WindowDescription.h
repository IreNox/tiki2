#pragma once

namespace TikiEngine
{
	namespace Description
	{
		/*!
		 * @brief Window Description
		 */
		struct WindowDescription
		{
			/*!
			 * @brief The window width.
			 */
			int Width;
	
			/*!
			 * @brief The window height.
			 */
			int Height;
	
			/*!
			 * @brief The name of the Window Class.
			 */
			LPCWSTR WindowClass;

			/*!
			 * @brief The window title.
			 */
			LPCWSTR WindowTitle;
	
			HWND hWnd;
			HINSTANCE hInst;

			/*!
			 * @brief Creates an instance of WINDOW_DESCRIPTION
			 */
			WindowDescription()
				: hWnd(0), hInst(0)
			{
				this->Width = 800;
				this->Height = 600;
				this->WindowClass = L"WindowClassTikiEngine";
				this->WindowTitle = L"TikiEngine 2.0";
			}
		};
	}
}