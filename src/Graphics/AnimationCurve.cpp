#include "Graphics/AnimationCurve.h"

namespace TikiEngine
{
	namespace Resources
	{
		AnimationCurve::AnimationCurve(float InitValue, double& start, double& end)
			:InitValue(InitValue), start(start), end(end)
		{

		}
		AnimationCurve::~AnimationCurve()
		{
			for(int i = 0; i < Keys.Count(); i++)
			{
				SafeRelease(&Keys[i]);
			}
		}

		float AnimationCurve::Evaluate(const double& time /* = -1.0 */)
		{
			int keyCount = Keys.Count();

			if(keyCount == 0 || time == -1.0)
				return InitValue;
			
			if(Keys[0]->Time >= time)
				return Keys[0]->Value;

			if(Keys[keyCount-1]->Time <= time)
				return Keys[keyCount-1]->Value;

			int index = 0;
			int shift = this->BSV;

			while(shift != 0)
			{
				if(index + shift < keyCount && Keys[index + shift]->Time <= time)
					index += shift;
				AnimationKey* key = Keys[index];

				shift /= 2;
			}

			if(Keys[index]->Time == time)
				return Keys[index]->Value;
			
			double left = Keys[index]->Time;
			double right = Keys[(index + 1) % keyCount]->Time;

			double deltaTime;

			if(left < right)
				deltaTime = right - left;
			else
				deltaTime = end - left + right - start;

			double koeff = (time - left) / deltaTime;

			return Keys[index]->Value * (1 - koeff) + Keys[(index + 1) % keyCount]->Value * koeff;
		}
	}
}