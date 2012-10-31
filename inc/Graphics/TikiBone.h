#pragma once

#define FBXSDK_NEW_API
#include "fbxsdk.h"
#include <Core\List.h>

namespace TikiEngine
{
	namespace Resources
	{
		class TikiBone
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

			int Count();

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