#pragma once

#include "Core/TypeInc.h"
#include "Core/Key.h"

namespace TikiEngine
{
	struct InputState
	{
		float MouseWheel;
		Vector2 MousePosition;
		Vector2 MousePositionDisplay;
		Vector2 MouseDistance;

		bool MouseButtons[3];

		InputState()
			: MousePosition(0, 0), MouseDistance(0, 0)
		{
			this->mouseButtonsPrev[0] = 0;
			this->mouseButtonsPrev[1] = 0;
			this->mouseButtonsPrev[2] = 0;
			this->MouseButtons[0] = 0;
			this->MouseButtons[1] = 0;
			this->MouseButtons[2] = 0;
		}

		InputState(Vector2 mousePosition, Vector2 viewPort, Vector2 mouseDistance, float wheel, unsigned char* mouseButtonsPrev, unsigned char* mouseButtonsCurrent, Byte* keyboardStatePrev, Byte* keyboardStateCurrent)
			: MousePosition(mousePosition), MouseDistance(mouseDistance), MouseWheel(wheel), MousePositionDisplay(Vector2(mousePosition.X * viewPort.X, mousePosition.Y * viewPort.Y))
		{
			this->mouseButtonsPrev[0] = (mouseButtonsPrev[0] != 0);
			this->mouseButtonsPrev[1] = (mouseButtonsPrev[1] != 0);
			this->mouseButtonsPrev[2] = (mouseButtonsPrev[2] != 0);
			this->MouseButtons[0] = (mouseButtonsCurrent[0] != 0);
			this->MouseButtons[1] = (mouseButtonsCurrent[1] != 0);
			this->MouseButtons[2] = (mouseButtonsCurrent[2] != 0);

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

		bool GetKey(Key keyCode) const
		{
			return (keyboardStateCurrent[keyCode] & 0x80) != 0;
		}

		bool GetKeyPressed(Key keyCode) const
		{
			return !(keyboardStatePrev[keyCode] & 0x80) && (keyboardStateCurrent[keyCode] & 0x80);
		}

		bool GetKeyReleased(Key keyCode) const
		{
			return (keyboardStatePrev[keyCode] & 0x80) && !(keyboardStateCurrent[keyCode] & 0x80);
		}

	private:

		bool mouseButtonsPrev[3];

		Byte keyboardStatePrev[256];
		Byte keyboardStateCurrent[256];

	};
}