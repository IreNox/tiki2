#pragma once

#include "Core/List.h"
#include "Core/UpdateArgs.h"
#include "Graphics/TikiAnimation.h"

namespace TikiEngine
{
	namespace Resources
	{
		class AnimationStack
		{
		public:
			AnimationStack();
			~AnimationStack();

			void Update(const UpdateArgs& args);

			void PlayAnimation(IAnimation* animation);
			void BlendAnimation(IAnimation* animation, double time = 0.5);
			
			List<TikiAnimation*>& GetStack();

		private:

			void blend(const UpdateArgs& args);

			List<TikiAnimation*> stack;

			TikiAnimation* blendTarget;
			double blendTime;
			double blendTimer;
		};
	}
}