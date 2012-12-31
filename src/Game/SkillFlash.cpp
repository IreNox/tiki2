
#include "Game/SkillFlash.h"
#include "Game/TikiBot.h"

#include "Game/GD.h"

namespace TikiEngine
{
	namespace Game
	{
		SkillDescription SkillFlash::Desc = SkillDescription(
			SKILL_FLASH_DESC,
			(SkillFlags)(SF_Active | SF_TargetPoint),
			L"flash",
			L""
		);

		SkillFlash::SkillFlash(TikiBot* owner)
			: Skill(owner, Desc)
		{
		}

		SkillFlash::~SkillFlash()
		{
		}

		void SkillFlash::internActivationPoint(const Vector3& target)
		{
			owner->Teleport(target);
		}

		void SkillFlash::internUpgrade()
		{
			description.ActivationRange = SkillFlashRange[currentLevel - 1];
		}
	}
}