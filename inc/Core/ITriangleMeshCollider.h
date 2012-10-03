#pragma once

#include "Core/ICollider.h"

namespace TikiEngine
{
	namespace Components
	{
		class ITriangleMeshCollider : public ICollider
		{
		public:

			ITriangleMeshCollider(Engine* engine, GameObject* gameObject) : ICollider(engine, gameObject) {}
			~ITriangleMeshCollider() {}

			virtual void SetIndices(UInt32* indices, UInt32 count) = 0;
			virtual void SetVertices(Vector3* vertices, UInt32 count) = 0;

		};
	}
}