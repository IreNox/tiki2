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
			this->MouseButtons[0] = 0;
			this->MouseButtons[1] = 0;
			this->MouseButtons[2] = 0;
		}

		InputState(Vector2 mousePosition, Vector2 viewPort, Vector2 mouseDistance, float wheel, unsigned char* mouseButtons, Byte* keyboardState)
			: MousePosition(mousePosition), MouseDistance(mouseDistance), MouseWheel(wheel), MousePositionDisplay(Vector2(mousePosition.X * viewPort.X, mousePosition.Y * viewPort.Y))
		{
			this->MouseButtons[0] = (mouseButtons[0] != 0);
			this->MouseButtons[1] = (mouseButtons[1] != 0);
			this->MouseButtons[2] = (mouseButtons[2] != 0);

			memcpy(
				this->keyboardState,
				keyboardState,
				sizeof(Byte) * 256
			);
		}

		bool GetKey(Key keyCode) const
		{
			return (keyboardState[keyCode] & 0x80) != 0;
		}

	private:

		Byte keyboardState[256];

	};
}