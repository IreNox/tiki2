#pragma once

#include "Core/IAnimation.h"
#include "Core/TikiObject.h"

namespace TikiEngine
{
	namespace Resources
	{
		class TikiAnimation : public IAnimation
		{
		public:
			TikiAnimation();
			~TikiAnimation();

			string GetName();
			void SetName(string name);

			float GetWeight();
			void SetWeight(float weight);

			double& GetStartTime();
			double& GetStopTime();

			List<double>& GetTimeStamps();
			void SetTimeStamps(List<double>& timeStamps);
			void AddTimeStampKey(double time);

			void Update(const double& deltaTime = -1.0);

			int GetBSV() { return bsv; }
			void SetBSV(int bsv);

			int GetIndex();
			void SetIndex(int index);

			int Left;
			int Right;
			float Koeff;

			double GCurrentTime();



		private:

			string name;

			List<double> timeStamps;

			float weight;

			int index;

			double startTime;
			double stopTime;

			int bsv;

			double lastUpdateTime;
			double currentTime;
		};
	}
}