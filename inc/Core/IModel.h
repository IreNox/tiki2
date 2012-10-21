#pragma once

#include "Core/IResource.h"
#include "Core/Material.h"

#include "Core/DrawArgs.h"
#include "Core/UpdateArgs.h"

#include "Core/DefaultVertex.h"

namespace TikiEngine
{
	class GameObject;

	namespace Resources
	{
    using namespace TikiEngine::Vertices;

		class IModel : public IResource
		{
		public:

			IModel(Engine* engine) : IResource(engine) {}
			virtual ~IModel() {}

			virtual void Draw(GameObject* gameObject, const DrawArgs& args) = 0;
			virtual void Update(const UpdateArgs& args) = 0;

			virtual Material* GetMaterial() = 0;
			virtual void SetMaterial(Material* material) = 0;

			virtual List<DefaultVertex>* GetVertices() = 0;
			virtual List<UInt32>* GetIndices() = 0;

			virtual float GetAnimationSpeed() = 0;
			virtual void SetAnimationSpeed(float speed) = 0;

		};
	}
}