
#include "Game/SkillRocket.h"

#include "Game/Projectile.h"
#include "Game/Rocket.h"
#include "Game/GameState.h"
#include "Game/ProjectileManager.h"

#include "Game/GD.h"

namespace TikiEngine
{
	namespace Game
	{
		SkillDescription SkillRocket::Desc = SkillDescription(
			SKILL_ROCKET_DESC,
			(SkillFlags)(SF_Active | SF_TargetAOE),
			L"rocket",
			L"rocket"
		);

		SkillRocket::SkillRocket(TikiBot* owner)
			: Skill(owner, Desc)
		{
		}

		SkillRocket::~SkillRocket()
		{
		}

		void SkillRocket::internActivationPoint(const Vector3& target)
		{
			ProjectileDescription desc;
			desc.Target = target; 
			desc.Shooter = owner;
			desc.ShooterID = owner->ID();
			desc.Origin = owner->Pos3D();
			desc.Heading = owner->Heading();
			desc.Damage = SkillRocketDamage[currentLevel - 1]; 
			desc.LifeTime = 10.0f;

			GameObject* go = new GameObject(engine);
			Rocket* proj = new Rocket(gameState, go);
			proj->Init(desc, 30, false);

			gameState->GetProjectiles()->AddProjectile(proj);
		}
	}
}