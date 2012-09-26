#pragma once

#include "Core/Component.h"

#include "Core/Material.h"

namespace TikiEngine
{
	namespace Components
	{
		using TikiEngine::Resources::Material;

		class ITerrainRenderer : public Component
		{
		public:

			ITerrainRenderer(Engine* engine, GameObject* gameObject)
				: Component(engine, gameObject, CT_Renderer)
			{
			}

			~ITerrainRenderer() {}
			
			virtual Material* GetMaterial() = 0;
			virtual void SetMaterial(Material* mat) = 0;

		};
	}
}