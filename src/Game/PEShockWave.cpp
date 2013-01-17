#include "Game/PEShockWave.h"

namespace TikiEngine
{
	namespace Particles
	{
		PEShockWave::PEShockWave(Engine* engine)
			: ParticleEffect(engine)
		{
			SParticleBudget(1);
			renderType = PRT_PointList;
			releasePerSecound = 1;
			lifeTime = 1;

			interp.ValueInit = 0.0f;
			interp.ValueMiddle = 0.5f;
			interp.ValueFinal = 1.0f;
			interp.MiddlePosition = 0.3f;
		}


		void PEShockWave::CreateParticle(Particle* particle)
		{
			particle->Color = Color(1, 0.8f, 0.5f, 0);
			particle->Size = Vector2::One / 1.0f;
			particle->Velocity = Vector3::Zero; 
			particle->Rotation = 0;
		}

		void PEShockWave::UpdateParticle(Particle* particle)
		{
			particle->Color.A = (1 - particle->Age);
			particle->Size += (1 - particle->Age) * 0.03f;

		}

	}
}