#pragma once

#include "Core/IResource.h"
#include "Core/Material.h"

#include "Core/DrawArgs.h"
#include "Core/UpdateArgs.h"

#include "Core/DefaultVertex.h"
#include "Core/SkinningVertex.h"
#include "Core/IAnimation.h"
#include "Core/IBone.h"

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

			virtual int AnimationCount() = 0;

			virtual List<SkinningVertex>* GetVertices() = 0;
			virtual List<UInt32>* GetIndices() = 0;

			virtual IAnimation* GetAnimation(string name) = 0;
			virtual IAnimation* GetAnimation(int index) = 0;

			virtual void SetAnimation(IAnimation* animation) = 0;
			virtual void BlendToAnimation(IAnimation* animation, double time = 0.5) = 0;

			virtual IBone* GetBone(string name) = 0;
		};
	}
}