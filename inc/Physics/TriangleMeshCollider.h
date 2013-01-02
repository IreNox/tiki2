#pragma once

#include "Physics/Collider.h"
#include "Core/ITriangleMeshCollider.h"

namespace TikiEngine
{
	namespace Physics
	{
		using namespace TikiEngine::Components;

		class TriangleMeshCollider : public ITriangleMeshCollider, public Collider
		{
		public:

			TriangleMeshCollider(Engine* engine, GameObject* gameObject);
			~TriangleMeshCollider();

			// ICollider Methods
			IRigidBody* GetRigidBody();
			
			IPhysicsMaterial* GetMaterial() { return getInternMaterial(); }
			void SetMaterial(IPhysicsMaterial* mat) { setInternMaterial(mat); updateData(); }

			Vector3 GetCenter();
			void SetCenter(const Vector3& center);

			bool GetDynamic();
			void SetDynamic(bool dynamicFlag);

			bool GetTrigger();
			void SetTrigger(bool triggerFlag);

			void SetGroup(CollisionGroups group);

			// TriangleMeshCollider Methods
			void SetIndices(UInt32* indices, UInt32 count);
			void SetVertices(Vector3* vertices, UInt32 count);
			void SetMeshData(const UInt32* indices, UInt32 indicesCount, const Vector3* vertices, UInt32 verticesCount);

			// Component Methods
			bool GetReady();
			void Update(const UpdateArgs& args);
			void Draw(const DrawArgs& args) {}

		private:

			NxU32 vertexCount;
			NxVec3* vertexData;

			UInt32 indexCount;
			UInt32* indexData;

			NxTriangleMesh* triangleMesh;


			void updateData();

		};
	}
}