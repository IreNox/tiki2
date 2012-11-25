#pragma once

#include <Core/Dictionary.h>
#include <Core/List.h>
#include "Core/TikiObject.h"
#include "Core/TypeGlobals.h"
#include "Graphics/TikiAnimation.h"
#include "Graphics/AnimationLayer.h"
#include "Core/IGraphics.h"

namespace TikiEngine
{
	namespace Resources
	{

		using namespace TikiEngine::Graphics;

		class TikiBone : public TikiObject
		{
		public:
			TikiBone();
			~TikiBone();

			void Draw(const DrawArgs& args);
			void Update(List<TikiAnimation*>& animations);
		
			void Clean();
			void CreateMapping(List<TikiBone*>& list);

			TikiBone* GetParent();
			void SetParent(TikiBone* parent);

			void AddChild(TikiBone* bone);
			List<TikiBone*>* GetChilds();

			Matrix& BoneInitTransform();
			Matrix& BoneCurrentTransform();

			void SetBoneInitTransform(Matrix& mat);
			void SetBoneCurrentTransform(Matrix& mat);

			Matrix ShiftMatrix();


			TikiBone* GetBoneByName(const char* name);
			TikiBone* GetBoneByIndex(int index);
			AnimationLayer& GetAnimationLayer(TikiAnimation* animation);


			void AddAnimation(TikiAnimation* animation, AnimationLayer& layer);

			int Count();

			string GetName();
			void SetName(string name);


			int GetConstantBufferIndex();
			void SetConstantBufferIndex(int index);

		private:
			
			string name;
			int constantBufferIndex;

			Matrix boneInit;
			Matrix boneInitInverse;
			Matrix boneCurrent;

			TikiBone* parent;
			List<TikiBone*> childs;

			Dictionary<TikiAnimation*, AnimationLayer> animationData;
		};
	}
}