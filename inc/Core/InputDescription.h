#pragma once

namespace TikiEngine
{
	namespace Description
	{
		struct InputDescription
		{
			float MouseSpeed;

			bool MouseInvertVerticle;
			bool MouseInvertHorizontal;

			InputDescription()
				: MouseSpeed(1), MouseInvertVerticle(false), MouseInvertHorizontal(false)
			{
			}
		};
	}
}

