#pragma once

#include "Core/IResource.h"

namespace TikiEngine
{
	namespace Resources
	{
		enum SoundType
		{
			ST_Music,
			ST_Voice,
			ST_Effect
		};

		class ISound : public IResource
		{
		public:

			ISound(Engine* engine) : IResource(engine) {}
			~ISound() {}

			/*! @brief Duration in Seconds */
			virtual float GetDuration() = 0;

			virtual SoundType GetType() = 0;
			virtual void SetType(SoundType type) = 0;

		};
	}
}