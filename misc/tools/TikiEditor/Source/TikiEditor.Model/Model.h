#pragma once

#include "Graphics/TikiBone.h"
#include "Graphics/TikiMesh.h"
#include "Graphics/TikiAnimation.h"
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

		TikiBone* GetRootBone()
		{
			return rootBone;
		}

		void SetRootBone(TikiBone* bone)
		{
			rootBone = bone;
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