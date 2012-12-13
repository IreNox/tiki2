#pragma  once

#include "Core/UpdateArgs.h"
#include <map>

namespace TikiEngine
{
    namespace AI
    {
        class TikiBot;
		struct TikiBotDescription;
        class Weapon;

        class WeaponSystem
        {
        public:
            WeaponSystem(TikiBot* owner);
            ~WeaponSystem();

            // sets up the weapon map with bot attributes and just one  machinegun
            void Init(const TikiBotDescription& desc);
            
            // returns a pointer to the current weapon
            Weapon* GetCurrentWeapon() const { return currentWeapon; }

            void ShootAt(const UpdateArgs& args, Vector3 pos);
            void TakeAimAndShoot(const UpdateArgs& args);

        private:
            TikiBot* owner;

            // a pointer to the weapon the bot is currently holding
            Weapon* currentWeapon;

            float reactionTime;
            float aimAccuracy;
            float aimPersistance;

        };

    }
}