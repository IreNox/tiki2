#define DIRECTINPUT_VERSION 0x0800

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

#include "Core/Engine.h"
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
			ZeroMemory(keyboardState, sizeof(keyboardState));
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
			this->viewPort = desc.Graphics.ViewPort;

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
			
			//ShowCursor(true);

			return true;
		}

		void InputModule::Begin()
		{
			this->readData(keyboard, sizeof(keyboardState), (void*)&keyboardState);
			this->readData(mouse, sizeof(mouseState), (void*)&mouseState);
		}

		void InputModule::FillInputState(InputState* state)
		{
			Vector2 dis = Vector2(
				(float)mouseState.lX / viewPort.Width,
				(float)mouseState.lY / viewPort.Height
			);

			Vector2 pos = mousePos + dis;

			if (pos.X < 0) pos.X = 0;
			if (pos.Y < 0) pos.Y = 0;

			if (pos.X > 1) pos.X = 1;
			if (pos.Y > 1) pos.Y = 1;

			mousePos = pos;

			*state = InputState(
				pos,
				dis,
				keyboardState
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

			r = (*device)->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE);

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

