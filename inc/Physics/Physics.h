#pragma once

#include "Core/IPhysics.h"

namespace TikiEngine
{
	namespace Modules
	{
		class Physics : public IPhysics
		{
		public:
			Physics(Engine* engine);
			~Physics();

			void DoWhatIWant();
		};
	}
}


