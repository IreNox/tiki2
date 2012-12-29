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

			void internActivation(const Vector3& target);

			void internDraw(const DrawArgs& args);
			void internUpdate(const UpdateArgs& args);

		private:

			static SkillDescription Desc;

		};
	}
}