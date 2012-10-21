#pragma once

#include "Core/IModule.h"
#include "Core/EngineDescription.h"

namespace TikiEngine
{
	namespace Modules
	{
		using TikiEngine::Description::EngineDescription;

		class Window : public IModule
		{
		public:
			Window(Engine* engine);
			~Window(void);

			bool Initialize(EngineDescription& desc);

			void Begin();
			void End();

			void Dispose();

			HWND GetHWND();
			bool GetReady();

		private:
			static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

		protected:

			static bool resetScreen;

			MSG msg;
			HWND hWnd;
			HINSTANCE hInst;
		};
	}
}


