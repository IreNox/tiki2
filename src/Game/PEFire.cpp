#include "Game/PEFire.h"
#include "Game/Utils.h"

namespace TikiEngine
{
	namespace Particles
	{
		PEFire::PEFire(Engine* engine)
			: ParticleEffect(engine)
		{
			renderType = PRT_PointList;
			releasePerSecound = 2000;
			lifeTime = 0.5;

			initialSpeed = 10;

			minScale = 20;
			maxScale = 30;

			interp.MiddlePosition = 0.1f;

		}

		void PEFire::CreateParticle(Particle* particle)
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

		void PEFire::UpdateParticle(Particle* particle)
		{
			particle->Color.A = interp.GetValue(particle->Age);
			particle->Velocity.Y += 10 * (1 - particle->Age);
		}
	}
}