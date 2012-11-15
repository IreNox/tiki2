#include "Game/WeaponSystem.h"

#include "Game/TikiBot.h"
#include "Game/MachineGun.h"

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

        void WeaponSystem::Init(float reactionTime, float aimAccuracy, float aimPersistance)
        {
            // set attributes
            this->reactionTime = reactionTime;
            this->aimAccuracy = aimAccuracy;
            this->aimPersistance = aimPersistance;

            // delete any existing weapons and clear the map
            WeaponMap::iterator currWeap = weaponMap.begin();
            for(currWeap; currWeap != weaponMap.end(); ++currWeap)
                SafeDelete(&currWeap->second);

            weaponMap.clear();

            // setup the container
            MachineGunDescription mgDesc;
            currentWeapon = new MachineGun(owner, mgDesc);
            weaponMap[WT_MachineGun] = currentWeapon;


        }

        void WeaponSystem::ShootAt(const UpdateArgs& args, Vector3 pos)
        {

        }

        void WeaponSystem::TakeAimAndShoot(const UpdateArgs& args)
        {
            // only aim if target is shootable or if it has very recently gone out of view.
            if (owner->GetTargetSys()->IsTargetShootable() ||
                (owner->GetTargetSys()->GetTimeTargetHasBeenOutOfView(args) < aimPersistance))
            {
                Vector3 aimingPos = owner->GetTargetBot()->Pos3D();

                // if the weapon is aimed correctly, there is line of sight between the
                // bot and the aiming position and it has been in view for a period longer
                // than the bot reaction time, shoot the weapon
                
                if (owner->RotateFacingTowardPosition(Vector2(aimingPos.X, aimingPos.Z)) &&
                    (owner->GetTargetSys()->GetTimeTargetHasBeenVisible(args) > reactionTime))
                {
                    currentWeapon->ShootAt(args, aimingPos);
                }

            }
           // else
            //    owner->RotateFacingTowardPosition(owner->Pos() + owner->Heading());

            //currentWeapon->ShootAt(args, )
        }


    }
}