
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
			prFlash = engine->librarys->CreateComponent<IParticleRenderer>(owner->GetGameObject());
			prFlash->SetParticleEffect(new PEFlash(engine));
			prFlash->SetTexture(engine->content->LoadTexture(L"particle/star"));
			prFlash->GetParticleEffect()->SIsAlive(false);
			prFlash->AddRef();
		}

		SkillFlash::~SkillFlash()
		{
			SafeRelease(&prFlash);
		}

		void SkillFlash::internActivationPoint(const Vector3& target)
		{
			prFlash->GetParticleEffect()->Trigger(
				1, prFlash->GetParticleEffect()->GParticleBudget(),
				Vector3::TransformCoordinate(
				Vector3(0, 0, 0),
				Matrix::Transpose(Matrix::CreateTranslation(target))
				)
			);

			owner->Teleport(target);
		}

		void SkillFlash::internUpgrade()
		{
			description.ActivationRange = SkillFlashRange[currentLevel - 1];
		}
	}
}