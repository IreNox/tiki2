#include "Game/PESmoke.h"
#include "Game/Utils.h"

namespace TikiEngine
{
	namespace Particles
	{
		PESmoke::PESmoke(Engine* engine)
			: ParticleEffect(engine)
		{
			//SParticleBudget(1000);
			renderType = PRT_PointList;
			releasePerSecound = 100;
			lifeTime = 10;

			initialSpeed = 20;

			minScale = 1;
			maxScale = 3;

			interp.MiddlePosition = 0.5f;

			windDirection = Vector3(0.1f, 0, 0);
		}


		void PESmoke::CreateParticle(Particle* particle)
		{
			particle->Position = Vector3(Random(-5, 5), Random(-5, 5), Random(-5, 5));
			particle->Color = Color(1.0f, 1.0f, 1.0f, 0);
			particle->Rotation = Random(0, 1);
			particle->Size = Vector2::One / Random(minScale, maxScale);

			// emit cone
			float theta = Random(0, TwoPi);
			float phi = Random(0, TwoPi);
			particle->Velocity.X = cosf(phi) * sinf(theta);
			particle->Velocity.Y = sinf(phi) * sinf(phi);
			particle->Velocity.Z = cosf(theta);
			particle->Velocity *= initialSpeed;
		}

		void PESmoke::UpdateParticle(Particle* particle)
		{
			particle->Color.A = interp.GetValue(particle->Age); //particle->Color.A = 1 - particle->Age;
			particle->Rotation = Random(0, 0.1f);

			// fake some gravity
			//particle->Velocity.X = 0;
			//particle->Velocity.Z = 0;

			particle->Velocity += windDirection;

			particle->Velocity.Y = 50;// * particle->Age;
		}

	}
}