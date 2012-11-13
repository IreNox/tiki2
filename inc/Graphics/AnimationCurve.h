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
			AnimationCurve(float InitValue, double& start, double& end);
			~AnimationCurve();

			float Evaluate(const double& time = -1.0);

			List<AnimationKey*> Keys;
			float InitValue;

			int BSV;

		private:
			double start;
			double end;
		};
	}
}