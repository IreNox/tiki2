
#include "Game/SkillSpiderMine.h"
#include "Game/TikiBotFactory.h"

namespace TikiEngine
{
	namespace Game
	{
		SkillDescription SkillSpiderMine::Desc = SkillDescription(
			5.0,
			25.0f,
			0.0f,
			10.0,
			(SkillFlags)(SF_Active | SF_TargetBot),
			L"sider_mine",
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