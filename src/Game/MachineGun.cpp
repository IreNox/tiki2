#include "Game/MachineGun.h"

#include "Game/Projectile.h"
#include "Game/TikiBot.h"

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
				ProjectileDescription desc;
				desc.Target = pos; //owner->GetTargetBot()->Pos3D();
				desc.Origin = owner->Pos3D();
				desc.Heading = owner->Facing();
				desc.ShooterID = owner->ID();
				GameObject* go = new GameObject(owner->GetGameState()->GetEngine());
				Projectile* proj = new Projectile(owner->GetGameState(), go);
				proj->Init(desc, args);
				owner->GetGameState()->AddProjectile(go);


				UpdateTimeWeaponIsAvailable(args);

			}
		}

	}
}