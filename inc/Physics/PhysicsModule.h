#pragma once

#include "Core/IPhysics.h"

#include "PhysX/Physics/NxPhysics.h"

#include "Physics/ErrorStream.h"
#include "Physics/VRDSettings.h"


#include "Physics/BoxCollider.h"


namespace TikiEngine
{
	namespace Modules
	{
		using namespace TikiEngine::Physics;

		class PhysicsModule : public IPhysics
		{
		public:
			PhysicsModule(Engine* engine);
			~PhysicsModule();

			/*! @brief Initialize PhysX SDK and Scene, also connects to the remote debugger */
			bool Initialize(EngineDescription& desc);

			/*! @brief  detect if GPU PhysX acceleration is available by querying for the version of the hardware */
			bool IsHardwarePresent();

			/*! @brief retreives the current scene */
			static NxScene* GetScene();

			void Begin();
			void End();

			void DoWhatIWant();
			
			void Dispose();

		private:
			Engine* tikiEngine;

			bool pause;
			NxPhysicsSDK* physicsSDK;

			NxScene* scene; 
			static NxScene* currentScene;
			
			BoxCollider* box;
			BoxCollider* box2;
		};
	}
}


