#pragma once

#include "Core/IPhysics.h"

#include "PhysX/Cooking/NxCooking.h"
#include "PhysX/Physics/NxPhysics.h"
#include "PhysX/NxCharacter/ControllerManager.h"

#include "Physics/ErrorStream.h"
#include "Physics/VRDSettings.h"

#include "Core/ColorVertex.h"

#include "Core/UpdateArgs.h"

namespace TikiEngine
{
	namespace Modules
	{
		using namespace TikiEngine::Vertices;

		class PhysicsModule : public IPhysics
		{
		public:
			PhysicsModule(Engine* engine);
			~PhysicsModule();

			/*! @brief Initialize PhysX SDK and Scene, also connects to the remote debugger */
			bool Initialize(EngineDescription& desc);

			/*! @brief  detect if GPU PhysX acceleration is available by querying for the version of the hardware */
			bool IsHardwarePresent();

			/*! @brief retrieves the current scene */
			NxScene* GetScene();

#if _DEBUG
			void DrawDebug();
#endif

			void Begin();
			void End(const UpdateArgs& args);

			void Dispose();

		private:
			bool pause;
			NxPhysicsSDK* physicsSDK;
			NxScene* scene; 
			NxCookingInterface* cooking;
			NxControllerManager* controllerManager;
			NxUserAllocator* userAllocator;
			int frameCnt;
			float timeSinceLastUpdate;

#if _DEBUG
			Vector3 physxToTiki(const NxVec3& vector);
#endif

		};
	}
}


