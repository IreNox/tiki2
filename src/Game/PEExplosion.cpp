#include "Game/PEExplosion.h"
#include "Game/Utils.h"

namespace TikiEngine
{
	namespace Particles
	{
		PEExplosion::PEExplosion(Engine* engine)
			: ParticleEffect(engine)
		{
			SParticleBudget(500);
			renderType = PRT_PointList;
			releasePerSecound = 100000;
			lifeTime = 1.0;

			minInitialSpeed = 100;
			maxInitialSpeed = 150;

			minScale = 5;
			maxScale = 10;

			explosionRadius = 100;
		}


		inline Vector3 RandomPointOnSphere(const Vector3& origin, float radius)
		{
			float phi = Random(0, TwoPi); // azimuth
			float theta = Random(0, Pi);  // elevation

			return Vector3(radius * cosf(phi) * sinf(theta) + origin.X,
						   radius * sinf(phi) * sinf(theta) + origin.Y,
						   radius             * cosf(theta) + origin.Z);
		}

		void PEExplosion::CreateParticle(Particle* particle)
		{
			particle->Position = Vector3(Random(-5, 5), Random(-5, 5), Random(-5, 5));
			particle->Color = Color::White;
			particle->Rotation = Random(0, 1);
			particle->Size = Vector2::One / Random(minScale, maxScale);

			Vector3 direction = particle->Position - RandomPointOnSphere(particle->Position, explosionRadius);
			direction = Vector3::Normalize(direction);

			particle->Velocity = direction * Random(minInitialSpeed, maxInitialSpeed); 
		}




		void PEExplosion::UpdateParticle(Particle* particle)
		{
			particle->Color.A = 1 - particle->Age;
			//particle->Velocity += 10 * (1 - particle->Age);
		}

	}
}