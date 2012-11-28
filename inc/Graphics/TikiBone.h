#pragma once

#include <Core/Dictionary.h>
#include <Core/List.h>
#include "Core/TikiObject.h"
#include "Core/TypeGlobals.h"
#include "Core/IGraphics.h"

#include "Graphics/TikiAnimation.h"
#include "Graphics/TikiLayer.h"

#include "Core/IBone.h"

namespace TikiEngine
{
	namespace Resources
	{

		using namespace TikiEngine::Graphics;

		class TikiBone : public IBone
		{
		public:
			TikiBone();
			~TikiBone();

			void Draw(const DrawArgs& args);
			void Update(List<TikiAnimation*>& animations);
		
			TikiBone* GetParent();
			void SetParent(TikiBone* parent);

			void AddChild(TikiBone* bone);
			List<TikiBone*>* GetChilds();

			Matrix& BoneInitTransform();
			Matrix& BoneCurrentTransform();

			void SetBoneInitTransform(Matrix& mat);
			void SetBoneCurrentTransform(Matrix& mat);

			Matrix ShiftMatrix();


			TikiBone* GetBoneByName(const string& name);
			TikiBone* GetBoneByIndex(int index);

			TikiLayer& GetAnimationLayer(UInt32 index);
			
			void AddAnimation(TikiAnimation* animation, TikiLayer& layer);

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

			List<TikiLayer> animationData;

		};
	}
}
