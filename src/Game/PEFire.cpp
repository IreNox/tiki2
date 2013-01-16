#include "Game/PEFire.h"
#include "Game/Utils.h"

namespace TikiEngine
{
	namespace Particles
	{
		PEFire::PEFire(Engine* engine)
			: ParticleEffect(engine)
		{
            SParticleBudget(2000);
			renderType = PRT_PointList;
			releasePerSecound = 4000;
			lifeTime = 0.5;

			initialSpeed = 2;

			minScale = 1;
			maxScale = 3;

			interp.ValueInit = 0.0f;
			interp.ValueMiddle = 1.0f;
			interp.ValueFinal = 0.0f;
			interp.MiddlePosition = 0.1f;

		}

		void PEFire::CreateParticle(Particle* particle)
		{

			//particle->Position += Vector3(Random(-0.2f, 0.2f), Random(-0.2f, 0.2f), Random(-0.2f, 0.2f));
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

		void PEFire::UpdateParticle(Particle* particle)
		{
			particle->Color.A = interp.GetValue(particle->Age);
			//particle->Velocity.Y += 10 * (1 - particle->Age);
		}
	}
}