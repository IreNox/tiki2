#include "Game/PEBlood.h"
#include "Game/Utils.h"

namespace TikiEngine
{
	namespace Particles
	{
		PEBlood::PEBlood(Engine* engine)
			: ParticleEffect(engine)
		{
			SParticleBudget(8000);
			renderType = PRT_PointList;
			releasePerSecound = 100;
			lifeTime = 0.75;
		}

		void PEBlood::CreateParticle(Particle* particle)
		{
			particle->Color = Color(Random(0.1f, 1), Random(0.1f, 1), Random(0.1f, 1), 0);

			particle->Rotation = Random(0.1f, 1);
			particle->Size = Vector2::One / Random(5, 10);

			Vector3 direction = Vector3(Random(0.1f, 0.15f), 
										Random(0.1f, 0.25f), 
										Random(0.1f, 0.15f));

			direction = Vector3::Normalize(direction);

			particle->Velocity = direction * Random(10, 12);
		}

		void PEBlood::UpdateParticle(Particle* particle)
		{
			particle->Color.A = (1 - particle->Age);
			if (particle->Velocity.Y > -5.81f)
				particle->Velocity.Y -= Random(0.01f, 0.05f);
		}

	}
}