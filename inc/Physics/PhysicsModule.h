#pragma once

#include "Core/IPhysics.h"

namespace TikiEngine
{
	namespace Modules
	{
		class PhysicsModule : public IPhysics
		{
		public:
			PhysicsModule(Engine* engine);
			~PhysicsModule();

			bool Initialize(EngineDescription& desc);

			void Begin();
			void End();

			void DoWhatIWant();
			
			void Dispose();
		};
	}
}


