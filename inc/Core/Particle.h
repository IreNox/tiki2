#pragma once

#include "Core/TypeInc.h"

namespace TikiEngine
{
	namespace Particles
	{
		struct Particle
		{
			Vector3 Position;
			::Color Color;
			Vector2 Size;
			float Rotation;

			Vector3 Velocity;

			float Age;
			double BirthTime;

			void* userData;

		};
	}
}