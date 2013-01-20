#include "Game/Weapon.h"

namespace TikiEngine
{
	namespace AI
	{
		Weapon::Weapon(unsigned int TypeOfGun,
			   unsigned int DefaultNumRounds,
			   unsigned int MaxRoundsCarried,
			   double       RateOfFire,
			   float		Idealrange,
			   float		ProjectileSpeed,
			   double		damage,
			   TikiBot*		OwnerOfGun)
			   : damage(damage)
		{
			this->wType = TypeOfGun;
			this->numRoundsLeft = DefaultNumRounds;
			this->maxRoundsCarried = MaxRoundsCarried;
			this->rateOfFire = RateOfFire;
			this->idealRange = Idealrange;
			this->maxProjectileSpeed = ProjectileSpeed;
			this->owner = OwnerOfGun;

			this->timeNextAvailable = 0; // CurrTime
		}

// 		inline bool Weapon::AimAt(Vector2 target) const
// 		{
// 			return owner->RotateFacingTowardPosition(target);
// 		}

		bool Weapon::IsReadyForNextShot(const UpdateArgs& args)
		{
			if (args.Time.TotalTime > timeNextAvailable)
				return true;

			return false;
		}

		void Weapon::UpdateTimeWeaponIsAvailable(const UpdateArgs& args)
		{
			timeNextAvailable = args.Time.TotalTime + 1.0 / rateOfFire;
		}

		void Weapon::IncrementRounds(int num)
		{
			numRoundsLeft += num;
			ClampT(numRoundsLeft, 0, maxRoundsCarried);
		} 

	}
}