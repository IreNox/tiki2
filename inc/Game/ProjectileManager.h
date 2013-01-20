#pragma once

#include "Core/GameObject.h"
#include "Game/GameState.h"

#include "Game/Projectile.h"

#include "Game/PEFire.h"
#include "Game/PESmoke.h"
#include "Game/PEShootMG.h"
#include "Game/PEExplosion.h"
#include "Game/PEBlood.h"
#include "Game/PEShockWave.h"
#include "Game/PERoundSparks.h"

#include "Core/IParticleRenderer.h"

namespace TikiEngine
{
	namespace Game
	{
		class ProjectileManager : public GameObject
		{
		public:

			ProjectileManager(GameState* state);
			~ProjectileManager();

			void AddProjectile(Projectile* proj);

			void AddBloodEffect(double elapsedTime, double releasePerSecound, const Vector3& pos);

			//void Draw(const DrawArgs& args);
			void Update(const UpdateArgs& args);

		private:
			
			GameState* gameState;

			PEShootMG* peAssault;
			IParticleRenderer* prAssault;

            PEFire* peFire;
            IParticleRenderer* prFire;

			PESmoke* peSmoke;
			IParticleRenderer* prSmoke;

			PEExplosion* peExplosion;
			IParticleRenderer* prExplosion;

			PEBlood* peBlood;
			IParticleRenderer* prBlood;

			PEShockWave* peShockwave;
			IParticleRenderer* prShockWave;

			PERoundSparks* peRoundSparks;
			IParticleRenderer* prRoundSparks;

			struct ProjInfo
			{
				Particle* p1;
				Particle* p2;
				Projectile* proj;
			};
			List<ProjInfo> projectiles;

            // List<GameObject*> explosionObjects;

		};
	}
}
