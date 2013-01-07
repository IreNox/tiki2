#pragma once

#include "Core/GameObject.h"
#include "Game/GameState.h"

#include "Game/Projectile.h"

#include "Game/PEFire.h"
#include "Game/PESmoke.h"
#include "Game/PEShootMG.h"
#include "Game/PEExplosion.h"

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
