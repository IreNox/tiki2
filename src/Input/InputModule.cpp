#define DIRECTINPUT_VERSION 0x0800

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

#include "Core/Engine.h"
#include "Core/IGraphics.h"

#include "Core/HelperLog.h"

#include "Input/InputModule.h"

namespace TikiEngine
{
	namespace Modules
	{
		#pragma region Class
		InputModule::InputModule(Engine* engine)
			: IInput(engine), input(0), mouse(0), keyboard(0), hWnd(0), hInst(0), mousePos(0, 0), viewPort()
		{
			ZeroMemory(keyboardStatePrev, sizeof(keyboardStatePrev));
			ZeroMemory(keyboardStateCurrent, sizeof(keyboardStateCurrent));
		}

		InputModule::~InputModule()
		{
		}
		#pragma endregion

		#pragma region Member
		bool InputModule::Initialize(EngineDescription& desc)
		{
			this->hWnd = desc.Window.hWnd;
			this->hInst = desc.hInst;
			this->viewPort = engine->graphics->GetViewPort();

			HRESULT r = DirectInput8Create(
				hInst,
				DIRECTINPUT_VERSION,
				IID_IDirectInput8,
				(void**)&input,
				NULL
			);

			if (FAILED(r))
			{
				HelperLog::WriteError("Can't init DirectInput", 0);
			}

			this->initDevice(&keyboard, GUID_SysKeyboard, &c_dfDIKeyboard);
			this->initDevice(&mouse, GUID_SysMouse, &c_dfDIMouse);
			
			return true;
		}

		void InputModule::Begin()
		{
			memcpy(&mouseStatePrev, &mouseStateCurrent, sizeof(mouseStatePrev));
			memcpy(keyboardStatePrev, keyboardStateCurrent, sizeof(keyboardStatePrev));

			this->readData(keyboard, sizeof(keyboardStateCurrent), (void*)&keyboardStateCurrent);
			this->readData(mouse, sizeof(mouseStateCurrent), (void*)&mouseStateCurrent);
		}

		void InputModule::FillInputState(InputState* state)
		{
			Vector2 dis = Vector2(
				(float)mouseStateCurrent.lX / viewPort->Width,
				(float)mouseStateCurrent.lY / viewPort->Height
			);

			POINT p;
			if (GetCursorPos(&p) && ScreenToClient(hWnd, &p))
			{
				Vector2 pos = Vector2(
					(float)p.x / viewPort->Width,
					(float)p.y / viewPort->Height
				);

				if (pos.X < 0) pos.X = 0;
				if (pos.Y < 0) pos.Y = 0;

				if (pos.X > 1) pos.X = 1;
				if (pos.Y > 1) pos.Y = 1;

				mousePos = pos;
			}

			*state = InputState(
				mousePos,
				engine->graphics->GetViewPort()->GetSize(),
				dis,
				(float)mouseStateCurrent.lZ,
				mouseStatePrev.rgbButtons,
				mouseStateCurrent.rgbButtons,
				keyboardStatePrev,
				keyboardStateCurrent
			);
		}

		void InputModule::End()
		{
		}

		void InputModule::Dispose()
		{
			if (input != 0)
			{
				input->Release();
				input = 0;
			}

			if (mouse != 0)
			{
				mouse->Unacquire();
				mouse->Release();
				mouse = 0;
			}

			if (keyboard != 0)
			{
				keyboard->Unacquire();
				keyboard->Release();
				keyboard = 0;
			}
		}
		#pragma endregion

		#pragma region Member - KeyCodeToChar
		wchar_t InputModule::KeyCodeToChar(Key keyCode)
		{
			HKL hklKeyboardLayout = GetKeyboardLayout(0);
			UINT virtualKey = MapVirtualKeyEx(keyCode, 3, hklKeyboardLayout);

			WORD keyChar = 0;

			int ascii = ToAsciiEx(
				virtualKey,
				keyCode,
				keyboardStateCurrent,
				&keyChar,
				0,
				hklKeyboardLayout
			);

			return keyChar;
		}
		#pragma endregion

		#pragma region Private Member
		void InputModule::initDevice(IDirectInputDevice8** device, GUID guid, LPCDIDATAFORMAT format)
		{
			HRESULT r = input->CreateDevice(guid, device, NULL);

			if (FAILED(r))
			{
				HelperLog::WriteError("Can't inited DirectInput", 0);
			}

			r = (*device)->SetDataFormat(format);

			if (FAILED(r))
			{
				HelperLog::WriteError("Can't set Format", 0);
			}

			r = (*device)->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

			if (FAILED(r))
			{
				HelperLog::WriteError("Can't set cooperative level", 0);
			}

			r = (*device)->Acquire();

			if (FAILED(r))
			{
				HelperLog::Write("Can't acquire.\n");
			}
		}

		bool InputModule::readData(IDirectInputDevice8* device, UINT size, void* destination)
		{
			HRESULT r = device->GetDeviceState(size, destination);

			if (FAILED(r))
			{
				if ((r == DIERR_INPUTLOST) || (r == DIERR_NOTACQUIRED))
				{
					r = device->Acquire();
				}

				if (FAILED(r))
				{
					return false;			
				}
			}

			return true;
		}
		#pragma endregion
	}
}

