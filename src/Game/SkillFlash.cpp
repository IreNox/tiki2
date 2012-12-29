
#include "Game/SkillFlash.h"
#include "Game/TikiBot.h"

namespace TikiEngine
{
	namespace Game
	{
		SkillFlash::SkillFlash(TikiBot* owner)
			: Skill(owner, SkillFlash::Desc)
		{
		}

		SkillFlash::~SkillFlash()
		{
		}

		void SkillFlash::internActivation(const Vector3& target)
		{
			owner->Teleport(target);
		}

		void SkillFlash::internDraw(const DrawArgs& args)
		{

		}

		void SkillFlash::internUpdate(const UpdateArgs& args)
		{

		}

		SkillDescription SkillFlash::Desc = SkillDescription(
			50.0f,
			(SkillFlags)(ST_Active | ST_TargetNoBot),
			0.0f,
			L"flash",
			L"",
			12.3,
			0.0
		);
	}
}