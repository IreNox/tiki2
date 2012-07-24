#pragma once

#include "Core/TypeInc.h"

namespace TikiEngine
{
	struct InputState
	{
		bool MouseButtons[3];
		Vector2 MousePosition;
		Vector2 MouseDistance;

		InputState()
			: MousePosition(0, 0), MouseDistance(0, 0)
		{
			this->MouseButtons[0] = 0;
			this->MouseButtons[1] = 0;
			this->MouseButtons[2] = 0;
		}

		InputState(Vector2 mousePosition, Vector2 mouseDistance, Byte* keyboardState)
			: MousePosition(mousePosition), MouseDistance(mouseDistance)
		{
			this->MouseButtons[0] = 0;
			this->MouseButtons[1] = 0;
			this->MouseButtons[2] = 0;

			memcpy(
				this->keyboardState,
				keyboardState,
				sizeof(keyboardState)
			);
		}

		bool GetKey(Key keyCode)
		{
			return (keyboardState[keyCode] & 0x80);
		}

	private:

		unsigned char keyboardState[256];
	};
}