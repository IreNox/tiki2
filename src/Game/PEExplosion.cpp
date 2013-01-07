#include "Game/PEExplosion.h"
#include "Game/Utils.h"

namespace TikiEngine
{
	namespace Particles
	{
		PEExplosion::PEExplosion(Engine* engine)
			: ParticleEffect(engine)
		{
			SParticleBudget(2000);
			renderType = PRT_PointList;
			releasePerSecound = 100000;
			lifeTime = 0.6;

			minInitialSpeed = 200;
			maxInitialSpeed = 600;

			minScale = 2;
			maxScale = 5;

			explosionRadius = 50;
		}


		inline Vector3 RandomPointOnSphere(const Vector3& origin, float radius)
		{
			float phi = Random(0, -Pi); //Random(0, TwoPi); // azimuth
			float theta = Random(0, Pi);  // elevation

			return Vector3(radius * cosf(phi) * sinf(theta) + origin.X,
						   radius * sinf(phi) * sinf(theta) + origin.Y,
						   radius             * cosf(theta) + origin.Z);
		}

		void PEExplosion::CreateParticle(Particle* particle)
		{
			particle->Position += Vector3(Random(-5, 5), Random(-5, 5), Random(-5, 5));
			particle->Color = Color::White;
			particle->Rotation = Random(0, 1);
			particle->Size = Vector2::One / Random(minScale, maxScale);

			Vector3 direction = particle->Position - RandomPointOnSphere(particle->Position, explosionRadius);
			direction = Vector3::Normalize(direction);

            float randSpeed = Random(minInitialSpeed, maxInitialSpeed); 

			particle->Velocity = direction * randSpeed;
            particle->Velocity.Y *= 1.7f;

		}

		void PEExplosion::UpdateParticle(Particle* particle)
		{
			particle->Color.A = 1 - particle->Age;
			particle->Velocity *=  (1-particle->Age) * 1.25f;
            particle->Velocity.Y -= 25.0f;
		}

	}
}