#pragma once

#define FBXSDK_NEW_API
#include "fbxsdk.h"
#include <Core\List.h>
#include "Core/TikiObject.h"
#include "Core/TypeGlobals.h"
#include "Graphics/TikiAnimation.h"
#include "Graphics/AnimationLayer.h"

namespace TikiEngine
{
	namespace Resources
	{
		class TikiBone : public TikiObject
		{
		public:
			TikiBone(FbxNode* node);
			~TikiBone();

			void Initialize();

			void Update(const double& time = -1.0);
		
			void Clean();
			void CreateMapping(List<TikiBone*>& list);

			TikiBone* GetParent();
			void SetParent(TikiBone* parent);

			Matrix& BoneInitTransform();
			Matrix& BoneCurrentTransform();

			Matrix ShiftMatrix();

			TikiBone* GetBoneByName(const char* name);

			void InitializeAnimation(TikiAnimation* animation);

			void SetBind(FbxAMatrix& init);

			int Count();

			const char* Name();

			int GetConstantBufferIndex();
			void SetConstantBufferIndex(int index);

		private:
			FbxNode* node;
			const char* name;
			int constantBufferIndex;

			Matrix boneInit;
			Matrix boneInitInverse;
			Matrix boneCurrent;

			TikiBone* parent;
			List<TikiBone*> childs;

			AnimationLayer* layer;
		};
	}
}