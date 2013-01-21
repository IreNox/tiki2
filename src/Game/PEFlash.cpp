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
			releasePerSecound = 2000;
			lifeTime = 1;
		}

		static float inc = 0;
		static float radius = 0;


		inline Vector3 RandomPointOnSpiral()
		{

			if (radius > 16 * TwoPi)
			{
				inc = 0.0f;
				radius = 0.0f;
			}

			Vector3 ret = Vector3(cosf(radius) * inc,
								  radius / 0.15f,
								  sinf(radius) * inc);

			inc += 1.2f;//Random(0.8f, 1.5f);  //1.0f;
			radius += 0.8f;//Random(0.3f, 0.8f); //0.8f;

			return ret;
		}

		void PEFlash::CreateParticle(Particle* particle)
		{
			particle->Position += RandomPointOnSpiral();
			particle->Color = Color(1.0f, 1.0f, 1.0f, 0);
			particle->Rotation = Random(0, 1);
			particle->Size = Vector2::One / Random(3, 7);
			particle->Velocity = Vector3::Zero;

		}

		void PEFlash::UpdateParticle(Particle* particle)
		{
			particle->Color.A = (1 - particle->Age);
			
			if (particle->Velocity.X > -5 || particle->Velocity.Y > -5 || particle->Velocity.Z > -5)
				particle->Velocity -= (Vector3(Random(-1, 1), Random(-1, 1), Random(-1, 1)) * Random(10, 20)); //0.1f * particle->Rotation;
		}

	}
}