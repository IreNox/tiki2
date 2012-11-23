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
			TikiBone();
			TikiBone(FbxNode* node);
			~TikiBone();

			void Initialize();

			void Draw(const DrawArgs& args);
			void Update(const UpdateArgs& args);
		
			void Clean();
			void CreateMapping(List<TikiBone*>& list);

			TikiBone* GetParent();
			void SetParent(TikiBone* parent);
			void AddChild(TikiBone* bone);

			Matrix& BoneInitTransform();
			Matrix& BoneCurrentTransform();

			void SetBoneInitTransform(Matrix& mat);
			void SetBoneCurrentTransform(Matrix& mat);

			Matrix ShiftMatrix();

			AnimationLayer* Layer();

			TikiBone* GetBoneByName(const char* name);
			TikiBone* GetBoneByIndex(int index);

			void SetFbxNode(FbxNode* node);
			FbxNode* GetFbxNode();

			void InitializeAnimation(TikiAnimation* animation);

			int Count();

			const char* GetName();
			void SetName(const char* name);


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