#pragma once

#include "Graphics/TikiBone.h"
#include "Graphics/TikiMesh.h"
#include "Graphics/TikiAnimation.h"
#include "Graphics/AnimationLayer.h"

namespace TikiEngine
{
	namespace Resources
	{
		class Model
		{
		public:

			Model() {}
			~Model() {}

			UInt32 AddRef() { return 0; }
			UInt32 Release() { return 0; }

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

			void SetMeshes(List<TikiMesh*>& meshes)
			{
				this->meshes = meshes;
			}

			void AddAnimation(TikiAnimation* animation)
			{
				if(!this->animations.Contains(animation))
				{
					this->animations.Add(animation);
				}
			}

			List<TikiAnimation*>* GetAnimations()
			{
				return &animations;
			}

			void SetConstantBufferIndices(List<TikiBone*>& list)
			{
				this->constantBufferElements = list;
			}

		protected:

			TikiBone* rootBone;
			List<TikiBone*> constantBufferElements;

			List<TikiMesh*> meshes;
			List<TikiAnimation*> animations;
		};
	}
}