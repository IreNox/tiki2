#pragma once

#define FBXSDK_NEW_API
#include "fbxsdk.h"
#include <Core\List.h>
#include "Core/TikiObject.h"
#include "Core/TypeGlobals.h"
#include "Graphics/TikiAnimationCurve.h"
#include "Graphics/TikiAnimation.h"

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

			void Update(FbxTime& time);
		
			TikiBone* GetParent();
			void SetParent(TikiBone* parent);

			FbxAMatrix& BoneInitTransform();
			FbxAMatrix& BoneCurrentTransform();
			FbxAMatrix ShiftMatrix();

			Vector3& InitGlobalTranslation();
			Vector3& CurrGlobalTranslation();

			TikiBone* GetBoneByName(const char* name);

			void InitializeAnimation(TikiAnimation* animation);

			void SetBind(FbxAMatrix& init);

			int Count();

			const char* Name();

		private:
			FbxNode* node;
			const char* name;

			Vector3 initGlobalTranslation;
			Vector3 currGlobalTranslation;

			FbxAMatrix boneInitTransform;
			FbxAMatrix boneInitTransformInverse;
			FbxAMatrix boneCurrentTransform;

			TikiAnimationCurve* curve;

			TikiBone* parent;
			List<TikiBone*> childs;

		};
	}
}