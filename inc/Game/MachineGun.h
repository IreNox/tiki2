#pragma  once

#include "Game/Weapon.h"

namespace TikiEngine
{
	namespace AI
	{

		struct MachineGunDescription
		{
			int DefaultRounds;
			int MaxRoundsCarried;
			float FiringFrequency;
			float IdealRange;
			float MaxSpeed;

			MachineGunDescription()
			{
				DefaultRounds = 0;		// not used, a machinegun always has ammo
				MaxRoundsCarried = 0;	// not used, a machinegun always has ammo
				FiringFrequency = 3;
				IdealRange = 50;
				MaxSpeed = 5;
			}
		};

		class MachineGun : public Weapon
		{
		public:
			MachineGun(TikiBot* owner, MachineGunDescription desc);

			void ShootAt(const UpdateArgs& args, Vector3 pos);

			void Draw(const DrawArgs& args) { }
		};



	}
}