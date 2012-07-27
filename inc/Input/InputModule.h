#pragma once

#include <dinput.h>
#include <Windows.h>

#include "Core/IInput.h"

#include "Core/Vector2.h"
#include "Core/ViewPort.h"
#include "Core/InputState.h"

namespace TikiEngine
{
	namespace Modules
	{
		class InputModule : public IInput
		{
		public:

			InputModule(Engine* engine);
			~InputModule();
			
			bool Initialize(EngineDescription& desc);

			void Begin();

			void FillInputState(InputState* state);

			void End();

			void Dispose();

		private:

			HWND hWnd;
			HINSTANCE hInst;

			IDirectInput8* input;
			IDirectInputDevice8* mouse;
			IDirectInputDevice8* keyboard;

			Vector2 mousePos;
			ViewPort viewPort;

			DIMOUSESTATE mouseState;
			unsigned char keyboardState[256];

			void initDevice(IDirectInputDevice8** device, GUID guid, LPCDIDATAFORMAT format);
			bool readData(IDirectInputDevice8* device, UINT size, void* destination);
		};
	}
}