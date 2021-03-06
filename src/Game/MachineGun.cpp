#include "Game/MachineGun.h"

#include "Game/Bullet.h"
#include "Game/TikiBot.h"
#include "Game/ProjectileManager.h"

namespace TikiEngine
{
	namespace AI
	{

		MachineGun::MachineGun(TikiBot* owner, MachineGunDescription desc)
			: Weapon(WT_MachineGun, desc.DefaultRounds, desc.MaxRoundsCarried, desc.FiringFrequency, desc.IdealRange, desc.MaxSpeed, desc.Damage, owner)
		{
		}

		inline void MachineGun::ShootAt(const UpdateArgs& args, Vector3 pos)
		{
			if (IsReadyForNextShot(args))
			{
				Vector3 start = owner->Pos3D();

				if (owner->EntityType() != ET_Tower)
				{
					IBone* bone = owner->GetGameObject()->GModel()->GetBone("weapon_standard_bn");				

					if (bone == 0)
						_CrtDbgBreak();

					start = Matrix::TransformCoordinate(bone->Position(), Matrix::Transpose(owner->GetGameObject()->PRS.GetWorld()));

					//if (start.X )
				}
				else
				{
					// TODO: Tower bone
				}
				
				ProjectileDescription desc;
				desc.Target = pos; //owner->GetTargetBot()->Pos3D();
                desc.Shooter = owner;
				desc.Origin = start;
				desc.Heading = owner->Heading();
				desc.ShooterID = owner->ID();
				desc.Damage = damage;
				GameObject* go = TIKI_NEW GameObject(owner->GetGameState()->GetEngine());
				Bullet* proj = TIKI_NEW Bullet(owner->GetGameState(), go);
				proj->Init(desc, args);
				owner->GetGameState()->GetProjectiles()->AddProjectile(proj);

				//owner->GetEngine()->HLog.Write("WeaponSystem - Raised Attack Animation. \n");
				owner->GetGameObject()->GModel()->AnimationHandler->RaiseAnimationEvent(owner->GetGameObject()->GModel(), AnimationArgs(AT_Attack));

				UpdateTimeWeaponIsAvailable(args);

			}
		}

	}
}