
#include "Game/SkillHealAura.h"

#include "Game/TikiBot.h"
#include "Game/GD.h"

#include "Core/IContentManager.h"

namespace TikiEngine
{
	namespace Game
	{
		SkillDescription SkillHealAura::Desc = SkillDescription(
			SKILL_HEALAURA_DESC,
			(SkillFlags)(SF_Active | SF_TargetAura),
			L"heal_aura",
			L""
		);

		SkillHealAura::SkillHealAura(TikiBot* owner)
			: Skill(owner, Desc)
		{
            prHeal = engine->librarys->CreateComponent<IParticleRenderer>(owner->GetGameObject());
            prHeal->SetParticleEffect(TIKI_NEW PEHealAura(engine));
            prHeal->SetTexture(engine->content->LoadTexture(L"particle/HealAura"));
            prHeal->GetParticleEffect()->SIsAlive(false);
		}

		SkillHealAura::~SkillHealAura()
		{
		}

		void SkillHealAura::internActivationAuraFrame(const UpdateArgs& args, TikiBot* target)
		{
			if (target->GetFaction() == owner->GetFaction())
			{
				target->IncreaseHealth(
					(float)(SkillHealAuraHealPerSecound[currentLevel - 1] * args.Time.ElapsedTime)
				);
			}
		}

        void SkillHealAura::internUpdate(const UpdateArgs& args)
        {
            prHeal->GetParticleEffect()->SIsAlive(atWork);
        }

    }
}