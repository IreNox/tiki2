#pragma once

//#define FBXSDK_NEW_API
//#include "fbxsdk.h"

#include "Graphics/FBXConverter.h"
#include "Graphics/TikiAnimation.h"

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

			//void Initialize(FbxNode* node, FbxAnimLayer* layer);

			void Update(TikiAnimation* animation);

			List<Vector3>& GetTranslation();
			List<Quaternion>& GetQuaternion();


			Vector3 LocalTranslation(TikiAnimation* animation);
			Quaternion LocalQuaternion(TikiAnimation* animation);

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

			void GetTimeStamps(List<double>& timeStamps, FbxNode* node, FbxAnimLayer* layer);
			//void Fill(List<double>& keyTimes, FbxAnimCurve* curve);
			void AddKey(List<float>& valueData,float value, double& time);
			void CreateKeys(List<double>& keyTimes, FbxNode* node);
			void CreateDefaultValues(FbxNode* node);

			List<Vector3> translation;
			List<Quaternion> quaternionen;
			List<double> timeStamps;

			Matrix transformMatrix;

			int bsv;
			int left;
			int right;
			float koeff;
			double lastUpdateTime;
			double currentTime;


		};
	}
}