#pragma once

#include "Game/Skill.h"

namespace TikiEngine
{
	namespace Game
	{
		class SkillSpiderMine : public Skill
		{
		public:

			SkillSpiderMine(TikiBot* owner);
			~SkillSpiderMine();

		protected:

			bool internActivationBot(TikiBot* target);

		private:

			static SkillDescription Desc;

		};
	}
}
