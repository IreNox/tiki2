#pragma once

#include "Game/TikiBot.h"

namespace TikiEngine
{
	namespace AI
	{
		enum WeaponTypes
		{
			WT_MachineGun
		};


		class Weapon
		{

		public:
			Weapon(unsigned int TypeOfGun,
				   unsigned int DefaultNumRounds,
				   unsigned int MaxRoundsCarried,
				   double        RateOfFire,
				   float		Idealrange,
				   float		ProjectileSpeed,
				   double		damage,
				   TikiBot*		OwnerOfGun);

			virtual ~Weapon() { }

			// this method aims the weapon at the given target by rotating the weapon's
			// owner's facing direction (constrained by the bot's turning rate). It returns  
			// true if the weapon is directly facing the target.
			//bool AimAt(Vector2 target) const;

			// this discharges a projectile from the weapon at the given target position
			// (provided the weapon is ready to be discharged. Every weapon has its own rate of fire)
			virtual void ShootAt(const UpdateArgs& args, Vector3 pos) = 0;

			// each weapon has its own shape and color
			virtual void Draw(const DrawArgs& args) = 0;

			// Weapon rounds, IdealRange and type
			int NumRoundsLeft() const {return numRoundsLeft; }
			void DecrementNumRounds() { if (numRoundsLeft > 0) --numRoundsLeft; }
			void IncrementRounds(int num);
			unsigned int GetType() const { return wType; }
			float GetIdealRange() const { return idealRange; }

			inline double GetDamage() { return damage; }
			inline void SetDamage(double val) { damage = val; }

		protected:
			// The number of times a weapon can be discharges depends on its rate of fire.
			// This method returns true if the weapon is able to be discharged at the 
			// current time. (called from ShootAt() )
			bool IsReadyForNextShot(const UpdateArgs& args);

			// this is called when a shot is fired to update timeNextAvailable
			void UpdateTimeWeaponIsAvailable(const UpdateArgs& args);

		protected:
			// a weapon is always carried by a bot
			TikiBot* owner;

			// an enumeration indicating the type of weapon
			unsigned int wType;

			// amount of ammo carried for this weapon
			unsigned int numRoundsLeft;

			// maximum number of rounds a bot can carry for this weapon
			unsigned int maxRoundsCarried;

			// the number of times this weapon can be fired per second
			double rateOfFire;

			// the earliest time the next shot can be taken
			double timeNextAvailable;

			// the prefered distance from the enemy when using this weapon
			float idealRange;

			// the max speed of the projectile this weapon fires
			float maxProjectileSpeed;

			double damage;

		};


	}
}