#pragma once

#include "Core/IResource.h"
#include "Core/Material.h"

#include "Core/DrawArgs.h"
#include "Core/UpdateArgs.h"

namespace TikiEngine
{
	class GameObject;

	namespace Resources
	{
		class IModel : public IResource
		{
		public:

			IModel(Engine* engine) : IResource(engine) {}
			~IModel() {}

			virtual void Draw(GameObject* gameObject, const DrawArgs& args) = 0;
			virtual void Update(const UpdateArgs& args) = 0;

			virtual Material* GetMaterial() = 0;
			virtual void SetMaterial(Material* material) = 0;

		};
	}
}