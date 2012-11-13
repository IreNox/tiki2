#pragma once

#define FBXSDK_NEW_API
#include "fbxsdk.h"

#include "Graphics/AnimationCurve.h"
#include "Graphics/FBXConverter.h"

#include "Core/TikiObject.h"
#include "Core/TypeGlobals.h"
#include "Core/Matrix.h"
#include "Core/Vector3.h"


namespace TikiEngine
{
	namespace Resources
	{
		class AnimationLayer : public TikiObject
		{
		public:
			AnimationLayer(double& start, double& end);
			~AnimationLayer();

			void Initialize(FbxNode* node, FbxAnimLayer* layer);

			Vector3 LocalTranslation(const double& time = -1.0);
			Vector3 LocalRotation(const double& time = -1.0);
			Matrix LocalTransform(const double& time = -1.0);

		private:
			double start;
			double end;

			AnimationCurve* AnimationLayer::Fill(FbxAnimCurve* curve, float init);

			AnimationCurve* translationX;
			AnimationCurve* translationY;
			AnimationCurve* translationZ;

			AnimationCurve* rotationX;
			AnimationCurve* rotationY;
			AnimationCurve* rotationZ;

			Matrix preRotation;
			Matrix postRotationInverse;
		};
	}
}