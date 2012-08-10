#pragma once

#include "Core/IPhysics.h"

#include "PhysX/Physics/NxPhysics.h"

#include "Physics/ErrorStream.h"
#include "Physics/VRDSettings.h"

#include "Core/ColorVertex.h"


//#include "Physics/BoxCollider.h"


namespace TikiEngine
{
	namespace Modules
	{
		using namespace TikiEngine::Vertices;

		//using namespace TikiEngine::Physics;

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
			void FillDebugMesh(Dictionary<PrimitiveTopologies, Mesh*>* list);
#endif

			void Begin();
			void End();

			void Dispose();

		private:
			Engine* tikiEngine;

			bool pause;
			NxPhysicsSDK* physicsSDK;
			NxScene* scene; 
			//BoxCollider* box;

#if _DEBUG
			Mesh* debugCheckMesh(Dictionary<PrimitiveTopologies, Mesh*>* list, PrimitiveTopologies topology);
			void debugFillVertex(ColorVertex& vertex, const NxVec3& pos, const NxU32& color);
#endif

		};
	}
}


