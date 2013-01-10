
#include "Game/SkillRocket.h"

#include "Game/Projectile.h"
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
			: Skill(owner, Desc), rocket(0)
		{
		}

		SkillRocket::~SkillRocket()
		{
		}

		void SkillRocket::internUpdate(const UpdateArgs& args)
		{
			if (rocket != 0 && rocket->IsDead())
			{
				atWork = false;
				rocket = 0;
			}
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
            desc.MaxSpeed = 70.0f;
            desc.Mass = 1.0f;

			GameObject* go = new GameObject(engine);
			Rocket* proj = new Rocket(gameState, go);
			proj->Init(desc, 30, false);

			rocket = proj;

			gameState->GetProjectiles()->AddProjectile(proj);
		}
	}
}