#include "Game/PEDebris.h"
#include "Game/Utils.h"

namespace TikiEngine
{
	namespace Particles
	{
		PEDebris::PEDebris(Engine* engine)
			: ParticleEffect(engine)
		{
			SParticleBudget(100);
			renderType = PRT_PointList;
			releasePerSecound = 2000;
			lifeTime = 0.6;

			interp.ValueInit = Vector4(1, 131 / 255, 0, 0);
			interp.ValueMiddle = Vector4(0.5f, 0.5f, 0.5f, 0); 
			interp.ValueFinal = Vector4(0.7f, 0.7f, 0.7f, 0);

			interp.MiddlePosition = 0.5f;
		}


		void PEDebris::CreateParticle(Particle* particle)
		{
			particle->Color = Color(1, 131 / 255, 0, 0); 
			particle->Rotation = Random(0, 1);
			particle->Size = Vector2(0.75f, 0.75f);

			Vector3 direction = Vector3(
				Random(-1, 1), 
				Random(0, 1), 
				Random(-1, 1)
			);
			direction = Vector3::Normalize(direction);

			float randXZ = Random(20, 40);
			particle->Velocity.X = direction.X * randXZ;
			particle->Velocity.Z = direction.Z * randXZ;
			particle->Velocity.Y = direction.Y * Random(30, 45);
		}

		void PEDebris::UpdateParticle(Particle* particle)
		{
			Vector4 c = interp.GetValue(particle->Age);
			c = c * particle->Rotation / 2;
			particle->Color.R = c.X;
			particle->Color.G = c.Y;
			particle->Color.B = c.Z;
			particle->Color.A = 1 - particle->Age;
			//particle->Size = 1.0f + (particle->Age * 1.5f);

			if (particle->Velocity.Y > -20.81f)
				particle->Velocity.Y -= 1.0f; //(1 - particle->Age); //(1 - particle->Age);
		}

	}
}