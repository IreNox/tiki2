
#include "Game/SkillFlash.h"
#include "Game/TikiBot.h"

namespace TikiEngine
{
	namespace Game
	{
		SkillDescription SkillFlash::Desc = SkillDescription(
			12.3,
			7.0f,
			0.0f,
			0.0,
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
	}
}