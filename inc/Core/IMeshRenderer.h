#pragma once

#include "Core/Component.h"

#include "Core/Mesh.h"
#include "Core/Material.h"

namespace TikiEngine
{
	namespace Components
	{
		using namespace TikiEngine::Resources;

		class IMeshRenderer : public Component
		{
		public:
			IMeshRenderer(Engine* engine, GameObject* gameObject)
				: Component(engine, gameObject)
			{
			}
			~IMeshRenderer() {}

			virtual Mesh* GetMesh() = 0;
			virtual Material* GetMaterial() = 0;

			virtual void SetMesh(Mesh* mesh) = 0;
			virtual void SetMaterial(Material* material) = 0;

			virtual bool GetDynamic() = 0;
			virtual void SetDynamic(bool dynamic) = 0;
		};
	}
}