
#include "Game/SkillHealAura.h"

#include "Game/TikiBot.h"

namespace TikiEngine
{
	namespace Game
	{
		SkillDescription SkillHealAura::Desc = SkillDescription(
			9.0,
			0.0f,
			15.0f,
			5.0,
			(SkillFlags)(SF_Active | SF_TargetAura),
			L"heal_aura",
			L""
		);

		SkillHealAura::SkillHealAura(TikiBot* owner)
			: Skill(owner, Desc)
		{
		}

		SkillHealAura::~SkillHealAura()
		{
		}

		void SkillHealAura::internActivationAuraFrame(const UpdateArgs& args, TikiBot* target)
		{
			target->IncreaseHealth(
				(float)(10.0 * args.Time.ElapsedTime)
			);
		}
	}
}