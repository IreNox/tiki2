#pragma once

#include "Core/IResource.h"
#include "Core/Material.h"

#include "Core/DrawArgs.h"
#include "Core/UpdateArgs.h"

#include "Core/DefaultVertex.h"
#include "Core/SkinningVertex.h"

#include "Core/IBone.h"
#include "Core/IAnimation.h"
#include "Core/IModelMesh.h"

#include "Core/EventAnimation.h"

namespace TikiEngine
{
	namespace Resources
	{
		using namespace TikiEngine;
		using namespace TikiEngine::Vertices;

		class IModel : public IResource
		{
		public:

			AnimationEvent AnimationHandler;

			IModel(Engine* engine)
				: IResource(engine)
			{
			}
			virtual ~IModel() { }
			
			virtual void CreateInstance(IModel* model) = 0;

			virtual void Draw(GameObject* gameObject, const DrawArgs& args) = 0;
			virtual void Update(const UpdateArgs& args) = 0;
			virtual void LateUpdate(const UpdateArgs& args) = 0;

			virtual int AnimationCount() = 0;

			virtual IAnimation* GetAnimation(string name) = 0;
			virtual IAnimation* GetAnimation(UInt32 index) = 0;

			virtual void SetAnimation(IAnimation* animation) = 0;
			virtual void BlendToAnimation(IAnimation* animation, double time = 0.5) = 0;

			virtual IBone* GetBone(string name) = 0;
			virtual IModelMesh* GetMesh(string name) = 0;

			virtual Vector3 GetBounds() = 0;
			virtual void SetBounds(const Vector3& size) = 0;

		};
	}
}
