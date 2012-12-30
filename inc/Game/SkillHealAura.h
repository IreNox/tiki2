#pragma once

#include "Game/Skill.h"

namespace TikiEngine
{
	namespace Game
	{
		class SkillHealAura : public Skill
		{
		public:

			SkillHealAura(TikiBot* owner);
			~SkillHealAura();

		protected:

			void internActivationAuraFrame(const UpdateArgs& args, TikiBot* target);

		private:

			static SkillDescription Desc;

		};
	}
}