#pragma once
//#define FBXSDK_NEW_API
//#include "fbxsdk.h"
#include "Core/TikiObject.h"


namespace TikiEngine
{
	namespace Resources
	{
		class TikiAnimation : public TikiObject
		{
		public:
			TikiAnimation();
//			TikiAnimation(FbxAnimLayer* layer);
			~TikiAnimation();

			/*FbxAnimLayer* Layer();*/

			const char* GetName();
			void SetName(const char* name);

			float GetWeight();
			void SetWeight(float weight);

			double& GetStartTime();
			double& GetStopTime();

			List<double>& GetTimeStamps();
			void SetTimeStamps(List<double>& timeStamps);
			void AddTimeStampKey(double time);

			void Update(const double& deltaTime = -1.0);

			void SetBSV(int bsv);

			int Left;
			int Right;
			float Koeff;

			double GetCurrentTime();

		private:
			const char* name;

			//FbxAnimLayer* layer;

			List<double> timeStamps;

			float weight;

			double startTime;
			double stopTime;

			int bsv;

			double lastUpdateTime;
			double currentTime;
		};
	}
}