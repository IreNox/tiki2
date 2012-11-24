#include "Graphics/TikiAnimation.h"

namespace TikiEngine
{
	namespace Resources
	{
		TikiAnimation::TikiAnimation(): Left(0), Right(0), weight(1.0f), currentTime(0.0){}

		//TikiAnimation::TikiAnimation(FbxAnimLayer* layer)
		//	:name(layer->GetName()), Left(0), Right(0), weight(1.0f), currentTime(0.0)
		//{
		//	this->layer = layer;
		//}
		TikiAnimation::~TikiAnimation()
		{

		}

		//FbxAnimLayer* TikiAnimation::Layer()
		//{
		//	return this->layer;
		//}
		const char* TikiAnimation::GetName()
		{
			return this->name;
		}
		
		void TikiAnimation::SetName(const char* name)
		{
			this->name = name;
		}

		List<double>& TikiAnimation::GetTimeStamps()
		{
			return this->timeStamps;
		}

		void TikiAnimation::SetTimeStamps(List<double>& timeStamps)
		{
			this->timeStamps = timeStamps;
		}

		double& TikiAnimation::GetStartTime()
		{
			return this->startTime;
		}

		double& TikiAnimation::GetStopTime()
		{
			return this->stopTime;
		}

		float TikiAnimation::GetWeight()
		{
			return this->weight;
		}

		void TikiAnimation::SetWeight(float weight)
		{
			this->weight = weight;
		}

		void TikiAnimation::AddTimeStampKey(double time)
		{
			if(timeStamps.Count() == 0)
				startTime = stopTime = time;

			if(!timeStamps.Contains(time))
			{
				timeStamps.Add(time);

				if(time < startTime)
					startTime = time;
				if(time > stopTime)
					stopTime = time;
			}
		}

		void TikiAnimation::SetBSV(int bsv)
		{
			this->bsv = bsv;
		}

		double TikiAnimation::GetCurrentTime()
		{
			return this->currentTime;
		}


		void TikiAnimation::Update(const double& deltaTime)
		{
			this->currentTime += deltaTime;

			if(currentTime >= stopTime)
				currentTime -= stopTime - startTime;


			if(lastUpdateTime == currentTime)
				return;
			else
				lastUpdateTime = currentTime;

			int count = timeStamps.Count();
			//one element - always the defaultvalue
			if(count == 1)
			{
				Left = Right = 0;
				return;
			}
			//before first element -> return first element
			if(timeStamps[0] >= currentTime) 
			{
				Left = 0;
				Right = -1;
				return;
			}
			//after last element -> return last element
			if(timeStamps[count - 1] <= currentTime)
			{
				Left = -1;
				Right = count -1;
				return;
			}

			int index = 0;
			int shift = bsv;

			//find index of highest value below time
			while(shift != 0)
			{
				if(index + shift < count && timeStamps[index + shift] <= currentTime)
					index += shift;
				shift /= 2;
			}

			if(timeStamps[index] == currentTime)
			{
				Left = Right = index;
				return;
			}

			Left = index;
			Right = index + 1;

			Koeff = (currentTime - timeStamps[Left]) / (timeStamps[Right] - timeStamps[Left]);
		}
	}
}