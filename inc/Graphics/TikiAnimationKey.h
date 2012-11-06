#pragma  once

#include "Core/TikiObject.h"

namespace TikiEngine
{
	namespace Resources
	{
		class TikiAnimationKey : TikiObject
		{
		public:
			TikiAnimationKey();
			TikiAnimationKey(double time, float keyValue);
			~TikiAnimationKey();

			double Time();
			float KeyValue();
		private:
			double time;
			float keyValue;
		};
	}
}