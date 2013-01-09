#include "Game/PEFlash.h"
#include "Game/Utils.h"

namespace TikiEngine
{
	namespace Particles
	{
		PEFlash::PEFlash(Engine* engine)
			: ParticleEffect(engine)
		{
			SParticleBudget(500);
			renderType = PRT_PointList;
			releasePerSecound = 1000;
			lifeTime = 0.5;
		}

		static float inc = 0;
		static float radius = 0;


		inline Vector3 RandomPointOnSpiral()
		{

			if (radius > 6 * TwoPi)
			{
				inc = 0.0f;
				radius = 0.0f;
			}

			Vector3 ret = Vector3(cosf(radius)  * inc,
								  radius / 20,
								  sinf(radius) * inc);

			inc += 0.001f;
			radius += 0.05f;

			return ret;
		}

		void PEFlash::CreateParticle(Particle* particle)
		{
			particle->Position += RandomPointOnSpiral();
			particle->Color = Color(1.0f, 1.0f, 1.0f, 0);
			particle->Rotation = Random(0, 1);
			particle->Size = Vector2::One / Random(10, 20);
			particle->Velocity = Vector3::Zero;

		}

		void PEFlash::UpdateParticle(Particle* particle)
		{
			particle->Color.A = (1 - particle->Age);
			
			if (particle->Velocity.Y > -5)
				particle->Velocity.Y -= Random(0.1f, particle->Rotation); //0.1f * particle->Rotation;
		}

	}
}