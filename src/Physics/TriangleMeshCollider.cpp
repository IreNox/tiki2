
#include "Core/TypeGlobals.h"

#include "Physics/TriangleMeshCollider.h"
#include "Physics/DllMain.h"
#include "Physics/Stream.h"
#include "Physics/UserAllocator.h"

namespace TikiEngine
{
	namespace Physics
	{
		#pragma region Class
		TriangleMeshCollider::TriangleMeshCollider(Engine* engine, GameObject* gameObject)
			: Collider(), ITriangleMeshCollider(engine, gameObject), vertexData(0), indexData(0), triangleMesh(0)
		{
		}

		TriangleMeshCollider::~TriangleMeshCollider()
		{
		}
		#pragma endregion

		#pragma region ICollider Methods
		IRigidBody* TriangleMeshCollider::GetRigidBody()
		{
			return Collider::GetBody();
		}

		void TriangleMeshCollider::SetMaterial(int index)
		{
			Collider::SetMaterialIndex(index);
		}

		Vector3 TriangleMeshCollider::GetCenter()
		{
			return Collider::GetCenterPos();
		}

		void TriangleMeshCollider::SetCenter(const Vector3& center)
		{
			Collider::SetCenterPos(center);
		}

		bool TriangleMeshCollider::GetDynamic()
		{
			return Collider::GetDynamicFlag();
		}

		void TriangleMeshCollider::SetDynamic(bool dynamicFlag)
		{
			Collider::SetDynamicFlag(dynamicFlag);
		}

		bool TriangleMeshCollider::GetTrigger()
		{
			return Collider::GetTriggerFlag();
		}

		void TriangleMeshCollider::SetTrigger(bool triggerFlag)
		{
			Collider::SetTriggerFlag(triggerFlag);
		}

		void TriangleMeshCollider::SetGroup(CollisionGroups group)
		{
			Collider::SetCollisionGroup(group);
		}
		#pragma endregion

		#pragma region ITriangleMeshCollider Method
		void TriangleMeshCollider::SetIndices(UInt32* indices, UInt32 count)
		{
			SafeDeleteArray(&this->indexData);

			//this->indexCount = count;
			//this->indexData = new NxU32[count];
			//memcpy(this->indexData, indices, sizeof(UInt32) * count);

			this->indexCount = 3;
			this->indexData = new NxU32[3];
			this->indexData[0] = 0;
			this->indexData[1] = 1;
			this->indexData[2] = 2;

			this->updateData();
		}

		void TriangleMeshCollider::SetVertices(Vector3* vertices, UInt32 count)
		{
			SafeDeleteArray(&this->vertexData);

			//this->vertexCount = count;
			//this->vertexData = new NxVec3[count];
			//memcpy(this->vertexData, vertices, sizeof(Vector3) * count);

			this->vertexCount = 3;
			this->vertexData = new NxVec3[3];
			this->vertexData[0] = NxVec3(-1, -1, -1);
			this->vertexData[1] = NxVec3( 1, -1, -1);
			this->vertexData[2] = NxVec3( 1,  1, -1);

			this->updateData();
		}
		#pragma endregion

		#pragma region Component Methods
		bool TriangleMeshCollider::GetReady()
		{
			return Collider::GetReady() && (vertexData != 0) && (indexData != 0);
		}

		void TriangleMeshCollider::Update(const UpdateArgs& args)
		{

		}
		#pragma endregion

		#pragma region Private Member
		void TriangleMeshCollider::updateData()
		{
			if (!this->GetReady()) return;

			if (actor != 0)
			{
				DllMain::Scene->releaseActor(*actor);
				actor = 0;

				actorDescription.setToDefault();
			}

			if (triangleMesh != 0)
			{
				DllMain::PhysicsSDK->releaseTriangleMesh(*triangleMesh);
				triangleMesh = 0;
			}

			NxTriangleMeshDesc meshDesc;
			meshDesc.numVertices			= vertexCount;
			meshDesc.numTriangles			= indexCount;
			meshDesc.pointStrideBytes		= sizeof(NxVec3);
			meshDesc.triangleStrideBytes	= 3 * sizeof(NxU32);
			meshDesc.points					= vertexData;
			meshDesc.triangles				= indexData;
			meshDesc.flags				    = NX_MF_FLIPNORMALS;			

			//meshDesc.heightFieldVerticalAxis = NX_Y;
			//meshDesc.heightFieldVerticalExtent	= -1000.0f;
			
			bool valid = meshDesc.isValid();

			MemoryWriteBuffer buf;

			NxCookingParams params;  
			params.targetPlatform = PLATFORM_PC;  
			params.skinWidth = 0.1f;  
			params.hintCollisionSpeed = false;
			DllMain::Cooking->NxSetCookingParams(params);  

			DllMain::Cooking->NxCookTriangleMesh(meshDesc, buf);

			MemoryReadBuffer readBuf(buf.data);
			triangleMesh = DllMain::PhysicsSDK->createTriangleMesh(readBuf);
			
			NxTriangleMeshShapeDesc terrainShapeDesc;
			terrainShapeDesc.meshData				= triangleMesh;
			terrainShapeDesc.shapeFlags				= NX_SF_FEATURE_INDICES;
			
			actorDescription.shapes.pushBack(&terrainShapeDesc);
			actorDescription.userData = (void*)this;
			actorDescription.globalPose.t = center;

			actor = DllMain::Scene->createActor(actorDescription);
		}
		#pragma endregion
	}
}