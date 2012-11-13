#pragma  once
#include "Core/TikiObject.h"

namespace TikiEngine
{
	namespace Resources
	{
		class AnimationKey : public TikiObject
		{
		public:
			AnimationKey(double Time, float Value);
			~AnimationKey();

			double Time;
			float Value;
		private:
		};
	}
}