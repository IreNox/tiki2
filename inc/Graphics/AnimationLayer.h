#pragma once

#define FBXSDK_NEW_API
#include "fbxsdk.h"

#include "Graphics/AnimationCurve.h"
#include "Graphics/FBXConverter.h"

#include "Core/TikiObject.h"
#include "Core/TypeGlobals.h"
#include "Core/Matrix.h"
#include "Core/Vector3.h"
#include "Core/Quaternion.h"


namespace TikiEngine
{
	namespace Resources
	{


		class AnimationLayer : public TikiObject
		{
		public:
			AnimationLayer();
			~AnimationLayer();

			void Initialize(FbxNode* node, FbxAnimLayer* layer);

			void Update(const double& deltaTime = -1.0);

			Vector3 LocalTranslation(const double& time = -1.0);
			Quaternion LocalQuaternion(const double& time = -1.0);
			Matrix LocalTransform(const double& time = -1.0);

			double& GetCurrentTime();
			void SetCurrentTime(double& time);

			void Reset();
 
		private:
			double start;
			double end;

			//all curves got the same timestamps = 1 binary search - 1 koeff evaluation

			void GetTimeStamps(List<double>* timeStamps, FbxNode* node, FbxAnimLayer* layer);
			void Fill(List<double>* keyTimes, FbxAnimCurve* curve);
			void AddKey(AnimationCurve* curve, float value, double& time);
			void CreateKeys(List<double>* keyTimes, FbxNode* node);
			void CreateDefaultValues(FbxNode* node);

			AnimationCurve* translationX;
			AnimationCurve* translationY;
			AnimationCurve* translationZ;

			AnimationCurve* rotationX;
			AnimationCurve* rotationY;
			AnimationCurve* rotationZ;

			List<Quaternion> quaternionen;

			int bsv;
			int left;
			int right;
			float koeff;
			double lastUpdateTime;
			double currentTime;

			List<double> * timeStamps;
		};
	}
}