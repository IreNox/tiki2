#pragma once

#include "Core/Component.h"

#include "Core/IMesh.h"
#include "Core/Material.h"

namespace TikiEngine
{
	namespace Components
	{
		using namespace TikiEngine::Graphics;

		class IMeshRenderer : public Component
		{
		public:
			IMeshRenderer(Engine* engine, GameObject* gameObject)
				: Component(engine, gameObject, CT_Renderer)
			{
			}
			~IMeshRenderer() {}

			virtual IMesh* GetMesh() = 0;
			virtual Material* GetMaterial() = 0;

			virtual void SetMesh(IMesh* mesh) = 0;
			virtual void SetMaterial(Material* material) = 0;
		};
	}
}