#include "Game/PERoundSparks.h"

namespace TikiEngine
{
	namespace Particles
	{
		PERoundSparks::PERoundSparks(Engine* engine)
			: ParticleEffect(engine)
		{
			SParticleBudget(30);
			renderType = PRT_PointList;
			releasePerSecound = 1;
			lifeTime = 1.5;

			interp.ValueInit = 0.0f;
			interp.ValueMiddle = 1.0f;
			interp.ValueFinal = 0.0f;
			interp.MiddlePosition = 0.3f;

		}


		void PERoundSparks::CreateParticle(Particle* particle)
		{
			float ranColor = Random(0, 1);
			if (ranColor <= 0.25f)
				particle->Color = Color(1, 0, 0, 0);
			else if (ranColor > 0.25f && ranColor <= 0.75f)
				particle->Color = Color(1, 0.2f, 0.2f, 0);
			else
				particle->Color = Color(0.9f, 0.2f, 0.2f, 0);

			particle->Size = Vector2(7, 7); //Vector2::One / 1.0f;
			particle->Velocity = Vector3(Random(-3, 3), Random(5, 10), Random(-3, 3)); 
			particle->Rotation = Random(0, 1);
		}

		void PERoundSparks::UpdateParticle(Particle* particle)
		{
			particle->Color.A = interp.GetValue(particle->Age); //(1 - particle->Age);
			//particle->Size += ((1-particle->Age) * 0.4f);

		}

	}
}