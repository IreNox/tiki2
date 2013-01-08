#include "Game/PEBlood.h"
#include "Game/Utils.h"

namespace TikiEngine
{
	namespace Particles
	{
		PEBlood::PEBlood(Engine* engine)
			: ParticleEffect(engine)
		{
			//SParticleBudget(2000);
			renderType = PRT_PointList;
			releasePerSecound = 5000;
			lifeTime = 1;
		}

		inline Vector3 RandomPointOnSphere(const Vector3& origin, float radius)
		{
			float phi = Random(0, TwoPi); //Random(0, TwoPi); // azimuth
			float theta = Random(0, TwoPi/16);  // elevation

			return Vector3(radius * cosf(phi) * sinf(theta) + origin.X,
				           radius * sinf(phi) * sinf(theta) + origin.Y,
				           radius             * cosf(theta) + origin.Z);
		}

		void PEBlood::CreateParticle(Particle* particle)
		{
			//particle->Position += Vector3(Random(-0.1f, 0.1f), Random(-0.1f, 0.1f), Random(-0.1f, 0.1f));
			particle->Color = Color(1.0f, 1.0f, 1.0f, 0);
			particle->Rotation = Random(0, 1);
			particle->Size = Vector2::One / Random(10, 20);

			Vector3 direction = particle->Position - RandomPointOnSphere(particle->Position, 2);
			direction = Vector3::Normalize(direction);

			particle->Velocity = direction * 2.0f;
		}

		void PEBlood::UpdateParticle(Particle* particle)
		{
			particle->Color.A = (1 - particle->Age);
			if (particle->Velocity.Y > -9.81f)
				particle->Velocity.Y -= 0.05f;
		}

	}
}