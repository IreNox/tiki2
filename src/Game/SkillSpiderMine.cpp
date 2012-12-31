
#include "Game/SkillSpiderMine.h"
#include "Game/TikiBotFactory.h"

#include "Game/GD.h"

namespace TikiEngine
{
	namespace Game
	{
		SkillDescription SkillSpiderMine::Desc = SkillDescription(
			SKILL_SPIDERMINE_DESC,
			(SkillFlags)(SF_Active | SF_TargetBot),
			L"spider_mine",
			L""
		);

		SkillSpiderMine::SkillSpiderMine(TikiBot* owner)
			: Skill(owner, Desc)
		{
		}

		SkillSpiderMine::~SkillSpiderMine()
		{
		}

		bool SkillSpiderMine::internActivationBot(TikiBot* target)
		{
			if (target->GetFaction() == owner->GetFaction())
			{
				return false;
			}

			GameObject* go = new GameObject(engine);
			go->PRS.SPosition() = owner->Pos3D() + Vector3(5);
			
			gameState->GetBotFactory()->CreatePlayerSpiderMine(go, target);

			return true;
		}
	}
}