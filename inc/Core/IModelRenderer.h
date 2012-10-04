#pragma once

#include "Core/Component.h"

#include "Core/IModel.h"
#include "Core/Material.h"

namespace TikiEngine
{
	namespace Components
	{
		using namespace TikiEngine::Resources;

		class IModelRenderer : public Component
		{
		public:
			IModelRenderer(Engine* engine, GameObject* gameObject)
				: Component(engine, gameObject, CT_Renderer)
			{
			}
			~IModelRenderer() {}

			virtual IModel* GetMesh() = 0;
			virtual Material* GetMaterial() = 0;

			virtual void SetMesh(IModel* mesh) = 0;
			virtual void SetMaterial(Material* material) = 0;

			virtual bool GetDynamic() = 0;
			virtual void SetDynamic(bool dynamic) = 0;
		};
	}
}