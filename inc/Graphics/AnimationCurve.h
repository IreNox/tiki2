#pragma once
#include "Core/TypeGlobals.h"
#include "Core/TikiObject.h"
#include "Core/List.h"
#include "Graphics/AnimationKey.h"

namespace TikiEngine
{
	namespace Resources
	{
		class AnimationCurve : public TikiObject
		{
		public:
			AnimationCurve();
			AnimationCurve(float InitValue, double& start, double& end);
			~AnimationCurve();

			float Evaluate(const double& time = -1.0);
			float Evaluate(int left, int right, float koeff);

			List<AnimationKey*> Keys;
			float InitValue;

			int BSV;

			double start;
			double end;
		};
	}
}