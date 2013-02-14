#include "Game/WeaponSystem.h"

#include "Game/TikiBot.h"
#include "Game/MachineGun.h"

#include "Game/GoalTypes.h"
#include "Game/GoalThink.h"

#include "Game/Rocket.h"
#include "Game/ProjectileManager.h"
#include "Core/IContentManager.h"
#include "Core/ISoundSystem.h"

namespace TikiEngine
{
    namespace AI
    {

        WeaponSystem::WeaponSystem(TikiBot* owner)
        {
            this->owner = owner;
        }

        WeaponSystem::~WeaponSystem()
        {
			SafeDelete(&currentWeapon);
        }

        void WeaponSystem::Init(const TikiBotDescription& desc)
        {
            // set attributes
            this->reactionTime = desc.ReactionTime;
            this->aimAccuracy = desc.AimAccuracy;
            this->aimPersistance = desc.AimPresistance;
			
            // setup the container
			if (desc.StartWeapon == 0)
			{
				MachineGunDescription mgDesc;
				mgDesc.Damage = desc.StartMGDamage;
				mgDesc.FiringFrequency = (float)desc.StartMGFireRate;
				currentWeapon = TIKI_NEW MachineGun(owner, mgDesc);
			}
			else
			{
				currentWeapon = desc.StartWeapon;
			}
        }

        void WeaponSystem::ShootAt(const UpdateArgs& args, Vector3 pos)
        {

        }

        void WeaponSystem::TakeAimAndShoot(const UpdateArgs& args)
        {
            // only aim if target is shootable or if it has very recently gone out of view.
            if (owner->GetTargetSys()->IsTargetShootable())//->IsTargetPresent())// ||
                //(owner->GetTargetSys()->GetTimeTargetHasBeenOutOfView(args) < aimPersistance))
            {
                Vector3 aimingPos = owner->GetTargetBot()->GetController()->GetCenter();

                // if the weapon is aimed correctly, there is line of sight between the
                // bot and the aiming position
				if (owner->GetBrain()->NotPresent(Goal_Move_To_Position))
					if (owner->RotateFacingTowardPosition(Vector2(aimingPos.X, aimingPos.Z)))
					{
						if (owner->IsSpiderMine())
						{
							ProjectileDescription desc;
							desc.Target = aimingPos; 
							desc.Shooter = owner;
							desc.ShooterID = owner->ID();
							desc.Origin = owner->Pos3D();
							desc.Heading = owner->Heading();
							desc.Damage = 20; 
							desc.LifeTime = 10.0f;
							desc.MaxSpeed = 70.0f;
							desc.Mass = 1.0f;

							GameObject* go = TIKI_NEW GameObject(owner->GetGameObject()->GetEngine());
							Rocket* proj = TIKI_NEW Rocket(owner->GetGameState(), go);
							proj->Init(desc, 30, false);

							//rocket = proj;

							owner->GetGameState()->GetProjectiles()->AddProjectile(proj);
							owner->SetDead();



							int randomSound = (static_cast<int>(RandFloat() * 100) % 7 ) + 1;

							Vector3 pos = owner->GetGameObject()->PRS.GPosition();

							wstring file = L"Explosion/Explosion_" + StringConvert::ToWString(randomSound);
							owner->GetEngine()->sound->Play3D(owner->GetEngine()->content->LoadSound(file), pos);

						}
						else
						{
							currentWeapon->ShootAt(args, aimingPos);
						}
						
					}

            }

        }


    }
}