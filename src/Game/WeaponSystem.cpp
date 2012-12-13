#include "Game/WeaponSystem.h"

#include "Game/TikiBot.h"
#include "Game/MachineGun.h"

#include "Game/GoalTypes.h"
#include "Game/GoalThink.h"

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
            for(UInt32 i = 0; i < weaponMap.size(); i++)
                SafeDelete(&weaponMap[i]);
        }

        void WeaponSystem::Init(const TikiBotDescription& desc)
        {
            // set attributes
            this->reactionTime = desc.ReactionTime;
            this->aimAccuracy = desc.AimAccuracy;
            this->aimPersistance = desc.AimPresistance;

            // delete any existing weapons and clear the map
            WeaponMap::iterator currWeap = weaponMap.begin();
            for(currWeap; currWeap != weaponMap.end(); ++currWeap)
                SafeDelete(&currWeap->second);

            weaponMap.clear();
			
            // setup the container
			if (desc.weapon == 0)
			{
				MachineGunDescription mgDesc;
				currentWeapon = new MachineGun(owner, mgDesc);
			}
			else
			{
				currentWeapon = desc.weapon;
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
                Vector3 aimingPos = owner->GetTargetBot()->Pos3D();

                // if the weapon is aimed correctly, there is line of sight between the
                // bot and the aiming position
				if (owner->GetBrain()->NotPresent(Goal_Move_To_Position))
					if (owner->RotateFacingTowardPosition(Vector2(aimingPos.X, aimingPos.Z)))
					{
						currentWeapon->ShootAt(args, aimingPos);
					}

            }

        }


    }
}