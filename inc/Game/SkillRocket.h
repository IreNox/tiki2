#pragma once

#include "Game/Skill.h"
#include "Game/TikiBot.h"

namespace TikiEngine
{
	namespace Game
	{
		using namespace TikiEngine::AI;

		class SkillRocket : public Skill
		{
		public:
			
			SkillRocket(TikiBot* owner);
			~SkillRocket();

		protected:

			void internActivationPoint(const Vector3& target);

		private:

			static SkillDescription Desc;

		};
	}
}