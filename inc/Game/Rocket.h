#pragma once

#include "Game/Projectile.h"

namespace TikiEngine
{
	namespace AI
	{
		class Rocket : public Projectile
		{

		public:
			Rocket(GameState* gameState, GameObject* gameObject);
			~Rocket();

			void Init(ProjectileDescription desc, float radius, bool heal, const UpdateArgs& args);

			void Handle(ICollider* sender, const TriggerEnterArgs& args);

			void Update(const UpdateArgs& args);

		private:
			void InflictAoEDamage();
			void InflictAoeHeal();

			float aoeRadius;
			bool heal;
		};


	}
}