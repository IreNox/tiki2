#pragma once

#include "Core/IPhysics.h"
//#include "../PhysX/Physics/NxPhysics.h"
#include "NxPhysics.h"
#include "ErrorStream.h"
#include "VRDSettings.h"
#include "Physics/Collider.h"

namespace TikiEngine
{
	namespace Modules
	{
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
			static NxScene* GetScene() { return currentScene; }

			void Begin();
			void End();

			void DoWhatIWant();
			
			void Dispose();

		private:
			bool pause;
			NxPhysicsSDK* physicsSDK;

			NxScene* scene; 
			static NxScene* currentScene;

		};
	}
}


