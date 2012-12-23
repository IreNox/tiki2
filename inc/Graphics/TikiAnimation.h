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
			TikiAnimation(TikiAnimation* copy);

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

			void Update(const double& deltaTime = 0.0);

			int GetBSV() { return bsv; }
			void SetBSV(int bsv);

			int GetIndex();
			void SetIndex(int index);

			double GetDuration();
			void SetDuration(double time);

			double GetAnimationSpeed();
			void SetAnimationSpeed(double speed);

			bool GetLoop();
			void SetLoop(bool isLoop);

			bool IsFinished();

			void SetNextAnimation(IAnimation* animation);
			IAnimation* GetNextAnimation();

			void Reset();

			int Left;
			int Right;
			float Koeff;

			double GCurrentTime();

		private:

			string name;

			List<double> timeStamps;

			int index;
			int bsv;

			double startTime;
			double stopTime;

			double lastUpdateTime;
			double currentTime;

			float weight;
			float animationSpeed;

			bool isLoop;
			bool finished;

			IAnimation* nextAnimation;
		};
	}
}