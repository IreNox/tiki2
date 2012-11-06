#pragma once

#define FBXSDK_NEW_API
#include "fbxsdk.h"

#include "Core/List.h"
#include "Graphics/TikiAnimationKey.h"
#include "Core/TikiObject.h"

#include "Core/Vector3.h"
#include "Core/Vector4.h"
#include "Graphics/FBXConverter.h"

namespace TikiEngine
{
	namespace Resources
	{
		class TikiAnimationCurve : public TikiObject
		{
		public:
			TikiAnimationCurve(FbxNode* node);
			~TikiAnimationCurve();

			void SetAnimation(FbxAnimLayer* layer);
			Vector3 LocalTranslation(const double &time = -1.0);
			Vector3 LocalRotation(const double &time = -1.0);
			
		private:
			void FillCurve(List<TikiAnimationKey>& list, FbxAnimCurve* curve);
			void GetKeysByTime(List<TikiAnimationKey>& list, double& time, TikiAnimationKey& left, TikiAnimationKey& right);

			Vector3 initTranslation;
			Vector3 initRotation;
			
			List<TikiAnimationKey> translationX;
			List<TikiAnimationKey> translationY;
			List<TikiAnimationKey> translationZ;
								 
			List<TikiAnimationKey> rotationX;
			List<TikiAnimationKey> rotationY;
			List<TikiAnimationKey> rotationZ;


			FbxNode* node;
		};
	}
}