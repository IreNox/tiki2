#include "Graphics/TikiAnimationKey.h"

namespace TikiEngine
{
	namespace Resources
	{
		TikiAnimationKey::TikiAnimationKey()
		{

		}
		TikiAnimationKey::TikiAnimationKey(double time, float keyValue)
			:time(time), keyValue(keyValue)
		{

		}
		TikiAnimationKey::~TikiAnimationKey()
		{

		}

		double TikiAnimationKey::Time()
		{
			return this->time;
		}
		float TikiAnimationKey::KeyValue()
		{
			return this->keyValue;
		}
	}
}