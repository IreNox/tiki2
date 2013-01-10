#pragma once

#include "Game/Skill.h"
#include "Game/TikiBot.h"

#include "Game/Rocket.h"

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

			void internUpdate(const UpdateArgs& args);
			void internActivationPoint(const Vector3& target);

		private:

			Rocket* rocket;

			static SkillDescription Desc;

		};
	}
}