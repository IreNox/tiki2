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
			const wchar_t* WindowClass;

			/*!
			 * @brief The window title.
			 */
			const wchar_t* WindowTitle;
	
			/*!
			 * @brief The window handle.
			 */
			HWND hWnd;

			/*!
			 * @brief Creates an instance of WINDOW_DESCRIPTION
			 */
			WindowDescription()
				: hWnd(0)
			{
				this->Width = 800;
				this->Height = 600;
				this->WindowClass = L"WindowClassTikiEngine";
				this->WindowTitle = L"TikiEngine 2.0";
			}
		};
	}
}