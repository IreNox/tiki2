#pragma once

#include "Core/TypeInc.h"

#include "Core/Component.h"

#include "Core/Material.h"
#include "Core/ITriangleMeshCollider.h"

namespace TikiEngine
{
	namespace Components
	{
		using TikiEngine::Resources::Material;

		class ITerrainRenderer : public Component
		{
		public:

			ITerrainRenderer(Engine* engine, GameObject* gameObject)
				: Component(engine, gameObject)
			{
			}

			~ITerrainRenderer() {}

			virtual void LoadTerrain(string fileName, int scale, int size, float elevation) = 0;
			
			virtual Material* GetMaterial() = 0;
			virtual void SetMaterial(Material* mat) = 0;

			virtual float SampleHeight(const Vector3& position) = 0;

			virtual void UpdateCollider(ITriangleMeshCollider* collider, List<Vector3>* poi) = 0;

		};
	}
}