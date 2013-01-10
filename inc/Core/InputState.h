#pragma once

#include "Core/TypeInc.h"
#include "Core/Key.h"

namespace TikiEngine
{
	enum MouseButtons
	{
		MB_None = 0xFF,
		MB_Left = 0,
		MB_Right = 1,
		MB_Middle = 2
	};

	struct InputState
	{
		#pragma region Vars
		float MouseWheel;
		Vector2 MousePosition;
		Vector2 MousePositionDisplay;
		Vector2 MouseDistance;
		#pragma endregion

		#pragma region Class
		InputState()
			: MousePosition(0, 0), MouseDistance(0, 0)
		{
			this->mouseButtonsPrev[0] = 0;
			this->mouseButtonsPrev[1] = 0;
			this->mouseButtonsPrev[2] = 0;
			this->mouseButtonsCurrent[0] = 0;
			this->mouseButtonsCurrent[1] = 0;
			this->mouseButtonsCurrent[2] = 0;
		}

		InputState(Vector2 mousePosition, Vector2 viewPort, Vector2 mouseDistance, float wheel, unsigned char* mouseButtonsPrev, unsigned char* mouseButtonsCurrent, Byte* keyboardStatePrev, Byte* keyboardStateCurrent)
			: MousePosition(mousePosition), MouseDistance(mouseDistance), MouseWheel(wheel), MousePositionDisplay(Vector2(mousePosition.X * viewPort.X, mousePosition.Y * viewPort.Y))
		{
			this->mouseButtonsPrev[0] = (mouseButtonsPrev[0] != 0);
			this->mouseButtonsPrev[1] = (mouseButtonsPrev[1] != 0);
			this->mouseButtonsPrev[2] = (mouseButtonsPrev[2] != 0);
			this->mouseButtonsCurrent[0] = (mouseButtonsCurrent[0] != 0);
			this->mouseButtonsCurrent[1] = (mouseButtonsCurrent[1] != 0);
			this->mouseButtonsCurrent[2] = (mouseButtonsCurrent[2] != 0);

			memcpy(
				this->keyboardStatePrev,
				keyboardStatePrev,
				sizeof(Byte) * 256
				);

			memcpy(
				this->keyboardStateCurrent,
				keyboardStateCurrent,
				sizeof(Byte) * 256
				);
		}
		#pragma endregion

		#pragma region Member - Get - Key
		inline bool GetKey(Key keyCode) const
		{
			return (keyboardStateCurrent[keyCode] & 0x80) != 0;
		}

		inline bool GetKeyPressed(Key keyCode) const
		{
			return !(keyboardStatePrev[keyCode] & 0x80) && (keyboardStateCurrent[keyCode] & 0x80);
		}

		inline bool GetKeyReleased(Key keyCode) const
		{
			return (keyboardStatePrev[keyCode] & 0x80) && !(keyboardStateCurrent[keyCode] & 0x80);
		}

		inline List<Key> GetKeys() const
		{
			List<Key> keys;

			UInt32 i = 0;
			while (i < 256)
			{
				if (keyboardStateCurrent[i] & 0x80) keys.Add((Key)i);
				i++;
			}

			return keys;
		}
		#pragma endregion

		#pragma region Member - Get - Mouse
		inline bool GetMouse(MouseButtons button) const
		{
			return mouseButtonsCurrent[button];
		}

		inline bool GetMousePressed(MouseButtons button) const
		{
			return (mouseButtonsCurrent[button] && !mouseButtonsPrev[button]);
		}

		inline bool GetMouseRelease(MouseButtons button) const
		{
			return (!mouseButtonsCurrent[button] && mouseButtonsPrev[button]);
		}
		#pragma endregion

	private:

		bool mouseButtonsPrev[3];
		bool mouseButtonsCurrent[3];

		Byte keyboardStatePrev[256];
		Byte keyboardStateCurrent[256];

	};
}