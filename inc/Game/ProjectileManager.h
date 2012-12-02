#pragma once

#include "Core/GameObject.h"
#include "Game/GameState.h"

#include "Game/Projectile.h"

#include "Game/PEShootMG.h"
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

			struct ProjInfo
			{
				Particle* p1;
				Particle* p2;
				Projectile* proj;
			};
			List<ProjInfo> projectiles;

		};
	}
}