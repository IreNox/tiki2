#pragma once

#include "Core/IResource.h"

namespace TikiEngine
{
	namespace Resources
	{


		class ISound : public IResource
		{
		public:

			ISound(Engine* engine) : IResource(engine) {}
			~ISound() {}

		};
	}
}