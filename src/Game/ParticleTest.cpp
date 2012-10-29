
#include "Game/ParticleTest.h"

namespace TikiEngine
{
	namespace Particles
	{
		ParticleTest::ParticleTest(Engine* engine)
			: ParticleEffect(engine)
		{
			this->SParticleBudget(1000000);
			lifeTime = 1;
			triggerCount = 10;
			triggerTime = 0.1f;
		}

		ParticleTest::~ParticleTest()
		{
		}

		void ParticleTest::CreateParticle(Particle* particle)
		{
			particle->Position = Vector3::Zero;
			particle->Color = Color::White;
			particle->Rotation = 0;
			particle->Size = Vector2::One / 10;
			particle->Velocity = Vector3(
				Random(-2, 2),
				Random(-2, 2),
				Random(-2, 2)
			);
		}

		void ParticleTest::UpdateParticle(Particle* particle)
		{
			particle->Color.A = 1 - particle->Age;
			particle->Rotation = particle->Age * 3.14159f;
		}
	}
}