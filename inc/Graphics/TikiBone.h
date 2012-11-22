#pragma once

#define FBXSDK_NEW_API
#include "fbxsdk.h"
#include <Core\List.h>
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
			TikiBone(FbxNode* node);
			~TikiBone();

			void Initialize();


			void Draw(const DrawArgs& args);
			void Update(const UpdateArgs& args);
		
			void Clean();
			void CreateMapping(List<TikiBone*>& list);

			TikiBone* GetParent();
			void SetParent(TikiBone* parent);

			Matrix& BoneInitTransform();
			Matrix& BoneCurrentTransform();

			Matrix ShiftMatrix();

			AnimationLayer* Layer();

			TikiBone* GetBoneByName(const char* name);
			TikiBone* GetBoneByIndex(int index);

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

			FbxAMatrix initInverse;
			FbxAMatrix shiftMatrix;

			TikiBone* parent;
			List<TikiBone*> childs;

			AnimationLayer* layer;
		};
	}
}