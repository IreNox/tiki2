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

			void SetAnimation(IAnimation* animation);
			void BlendAnimation(IAnimation* animation, double time);
			
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