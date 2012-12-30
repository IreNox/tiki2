#include "Game/MachineGun.h"

#include "Game/Bullet.h"
#include "Game/TikiBot.h"
#include "Game/ProjectileManager.h"

namespace TikiEngine
{
	namespace AI
	{

		MachineGun::MachineGun(TikiBot* owner, MachineGunDescription desc)
			: Weapon(WT_MachineGun, desc.DefaultRounds, desc.MaxRoundsCarried, 
					 desc.FiringFrequency, desc.IdealRange, desc.MaxSpeed, owner)
		{

		}

		inline void MachineGun::ShootAt(const UpdateArgs& args, Vector3 pos)
		{
			if (IsReadyForNextShot(args))
			{
				Vector3 start;
				if (owner->EntityType() != ET_Tower)
				{
					IBone* bone = owner->GetGameObject()->GModel()->GetBone("weapon_MgTip_bn");				
					start = Vector3::TransformCoordinate(bone->Position(), Matrix::Transpose(owner->GetGameObject()->PRS.GetWorld()));
				}
				else //if (owner->EntityType() == )
				{
					// TODO: Tower bone
					start = owner->Pos3D();
				}
				
				ProjectileDescription desc;
				desc.Target = pos; //owner->GetTargetBot()->Pos3D();
                desc.Shooter = owner;
				desc.Origin = start;
				desc.Heading = owner->Heading();
				desc.ShooterID = owner->ID();
				desc.Damage = owner->MaxHealth() / 20.0f;
				GameObject* go = new GameObject(owner->GetGameState()->GetEngine());
				Bullet* proj = new Bullet(owner->GetGameState(), go);
				proj->Init(desc, args);
				owner->GetGameState()->GetProjectiles()->AddProjectile(proj);

				//owner->GetEngine()->HLog.Write("WeaponSystem - Raised Attack Animation. \n");
				owner->GetGameObject()->GModel()->AnimationHandler.RaiseEvent(owner->GetGameObject()->GModel(), AnimationArgs(Attack));

				UpdateTimeWeaponIsAvailable(args);

			}
		}

	}
}