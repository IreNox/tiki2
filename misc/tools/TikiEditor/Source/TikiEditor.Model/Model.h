#pragma once

#include "Graphics/TikiBone.h"
#include "Graphics/TikiMesh.h"
#include "Graphics/AnimationLayer.h"

namespace TikiEditor
{
	using namespace TikiEngine;
	using namespace TikiEngine::Resources;

	class Model
	{
	public:

		Model() {}
		~Model() {}

		void Draw(GameObject* gameObject, const DrawArgs& args) {}
		void Update(const UpdateArgs& args) {}

		TikiBone* GetRootBone()
		{
			return rootBone;
		}

		List<TikiMesh*>* GetMeshes()
		{
			return &meshes;
		}

		List<TikiAnimation*>* GetAnimations()
		{
			return &animations;
		}

	protected:

		TikiBone* rootBone;

		List<TikiMesh*> meshes;
		List<TikiAnimation*> animations;
	};
}