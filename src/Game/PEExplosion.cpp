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

			minInitialSpeed = 3; //5; //200;
			maxInitialSpeed = 20; //10; //600;

			minScale = 10; //0.5f; //1.1f;//2;
			maxScale = 20; //0.5f; //1.2f;//5;

			explosionRadius = 10;

			interp.ValueInit = Vector4(204.0f / 255.0f, 
									   24.0f / 255.0f, 
									   24.0f / 255.0f, 
									   0); 

			interp.ValueMiddle = Vector4(156.0f / 255.0f, 
										  74.0f / 255.0f, 
										   8.0f / 255.0f, 0);

			interp.ValueFinal = Vector4(1, 1, 1, 0);

			interp.MiddlePosition = 0.5f;
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
			c = c * particle->Rotation / 2;
			particle->Color.R = c.X;
			particle->Color.G = c.Y;
			particle->Color.B = c.Z;
			particle->Color.A = 1 - particle->Age;
			particle->Size = 1.5f + (particle->Age * 0.5f);

			particle->Velocity *= (1-particle->Age) * Random(1.04f, 1.06f);


			if (particle->Velocity.Y < 9.81f)
			{
				if (particle->Age > 0.5f)
					particle->Velocity.Y += particle->Age * Random(3.5f, 5.5f);
				else
					particle->Velocity.Y += particle->Age * Random(0.5f, 1.5f);

			}
			else if (particle->Velocity.Y >= 9.81f)
			{
				particle->Velocity.X += (1-particle->Age) * Random(-1, 1) * 10.0f;
				particle->Velocity.Z += (1-particle->Age) * Random(-1, 1) * 10.0f;
			}
		}

	}
}