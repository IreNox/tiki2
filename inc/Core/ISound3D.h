#pragma once

#include "Core/IResource.h"

namespace TikiEngine
{
	namespace Resources
	{
		class ISound3D : public IResource
		{
		public:

			ISound3D(Engine* engine) : IResource(engine) {}
			~ISound3D() {}

			virtual void CreateInstance(ISound3D* sound) = 0;

			/*! @brief Duration in Seconds */
			virtual float GetDuration() = 0;

		};
	}
}