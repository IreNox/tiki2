#pragma once

#define FBXSDK_NEW_API
#include "fbxsdk.h"
#include <Core\List.h>
#include "Core/TikiObject.h"
#include "Core/TypeGlobals.h"

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

			TikiBone* GetBoneByName(const char* name);

			int Count();

			const char* Name();

		private:
			FbxNode* node;
			const char* name;

			FbxAMatrix boneInitTransform;
			FbxAMatrix boneInitTransformInverse;
			FbxAMatrix boneCurrentTransform;

			TikiBone* parent;
			List<TikiBone*> childs;

		};
	}
}