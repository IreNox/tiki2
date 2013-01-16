#include "Game/PEExplosion.h"
#include "Game/Utils.h"

namespace TikiEngine
{
	namespace Particles
	{
		PEExplosion::PEExplosion(Engine* engine)
			: ParticleEffect(engine)
		{
			SParticleBudget(10000);
			renderType = PRT_PointList;
			releasePerSecound = 2000;
			lifeTime = 3;

			minInitialSpeed = 10; //5; //200;
			maxInitialSpeed = 20; //10; //600;

			minScale = 1.1f;//2;
			maxScale = 1.2f;//5;

			explosionRadius = 10;

			interp.ValueInit = Vector4(254.0f / 255.0f, 255.0f / 255.0f, 117.0f / 255.0f, 0); //Vector4(1.0f, 0.3f, 0.3f, 0);
			interp.ValueMiddle = Vector4(209.0f / 255.0f, 42.0f / 255.0f, 0.0f / 255.0f, 0);
			interp.ValueFinal = Vector4(1, 1, 1, 0);
			interp.MiddlePosition = 0.25f;
		}


		void PEExplosion::CreateParticle(Particle* particle)
		{
			float randColor = Random(0.5f, 1.0f);
			particle->Color = Color(randColor, randColor, randColor, 1.0f); //Color::White;
			particle->Rotation = Random(0, 1);
			particle->Size = Vector2::One / Random(minScale, maxScale);

 			Vector3 direction = Vector3(Random(-1, 1), Random(-1, 1), Random(-1, 1));
 			direction = Vector3::Normalize(direction);
 			particle->Velocity = direction *  Random(minInitialSpeed, maxInitialSpeed);
		}

		void PEExplosion::UpdateParticle(Particle* particle)
		{
			Vector4 c = interp.GetValue(particle->Age);
			c = c * particle->Rotation;
			particle->Color.R = c.X;
			particle->Color.G = c.Y;
			particle->Color.B = c.Z;
			particle->Color.A = 1 - particle->Age;
			particle->Size = 1.05f + (particle->Age * 0.5f);

			particle->Velocity *= (1-particle->Age) * Random(1.04f, 1.06f);


			if (particle->Velocity.Y < 9.81f)
			{
				particle->Velocity.Y += particle->Age * 5.5f;
				particle->Velocity.X += (1-particle->Age) * Random(-1, 1) * 7.0f;
				particle->Velocity.Z += (1-particle->Age) * Random(-1, 1) * 7.0f;
				//particle->Velocity.X += Random(0.01f, 0.02f);
				//particle->Velocity.Z += Random(0.01f, 0.02f);
			}
		}

	}
}