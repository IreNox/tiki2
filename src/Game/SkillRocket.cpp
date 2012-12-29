
#include "Game/SkillRocket.h"

#include "Game/Projectile.h"
#include "Game/Rocket.h"
#include "Game/GameState.h"
#include "Game/ProjectileManager.h"

namespace TikiEngine
{
	namespace Game
	{
		SkillRocket::SkillRocket(TikiBot* owner)
			: Skill(owner, SkillRocket::Desc)
		{
		}

		SkillRocket::~SkillRocket()
		{
		}

		void SkillRocket::internActivation(const Vector3& target)
		{
			ProjectileDescription desc;
			desc.Target = target; 
			desc.Shooter = owner;
			desc.ShooterID = owner->ID();
			desc.Origin = owner->Pos3D();
			desc.Heading = owner->Heading();
			desc.Damage = 20; 
			desc.LifeTime = 10.0f;

			GameObject* go = new GameObject(engine);
			Rocket* proj = new Rocket(gameState, go);
			proj->Init(desc, 30, false);

			gameState->GetProjectiles()->AddProjectile(proj);
		}

		void SkillRocket::internDraw(const DrawArgs& args)
		{
		}

		void SkillRocket::internUpdate(const UpdateArgs& args)
		{
		}

		SkillDescription SkillRocket::Desc = SkillDescription(
			100,
			(SkillFlags)(ST_Active | ST_TargetAOE),
			20,
			L"rocket",
			L"rocket",
			4.5,
			2
		);
	}
}