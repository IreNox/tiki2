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
			lifeTime = 1.5;

			minInitialSpeed = 1; //5; //200;
			maxInitialSpeed = 16; //10; //600;

			minScale = 10; //0.5f; //1.1f;//2;
			maxScale = 20; //0.5f; //1.2f;//5;

			explosionRadius = 10;

			interp.ValueInit = Vector4(156.0f / 255.0f, 
				74.0f / 255.0f, 
				8.0f / 255.0f,
				0);


			interp.ValueMiddle = Vector4(204.0f / 255.0f, 
				24.0f / 255.0f, 
				24.0f / 255.0f, 
				0); 

			interp.ValueFinal = Vector4(1, 1, 1, 0);

			interp.MiddlePosition = 0.3f;
		}


		void PEExplosion::CreateParticle(Particle* particle)
		{
			float randColor = Random(0.5f, 1.0f);
			particle->Color = Color(randColor, randColor, randColor, 1.0f); //Color::White;
			particle->Rotation = Random(0, 1);
			particle->Size = Vector2::One / Random(minScale, maxScale);

			Vector3 direction;
 			
			float expDir = Random(0, 1);
			if (expDir < 0.2f)
				direction = Vector3(Random(-1, 1), 0, Random(-1, 1));
			else
				direction = Vector3(Random(-0.3f, 0.3f), 1.0f, Random(-0.3f, 0.3f));

 			direction = Vector3::Normalize(direction);

			if (expDir < 0.2f)
				particle->Velocity = direction *  Random(0, 15);
			else
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
			particle->Size = 1.0f + (particle->Age * 1.5f);
			
			//particle->Velocity.Y *= particle->Age;

// 			if (particle->Age > 0.25f)
// 			{
// 				if (Random(0, 1) < 0.2f)
// 				{
// 					particle->Velocity.X *= -((1 - particle->Age ) * 0.01f);
// 					particle->Velocity.Z *= -((1 - particle->Age ) * 0.01f);
// 				}
// 			}

// 			particle->Velocity *= (1-particle->Age) * Random(1.04f, 1.06f);
// 
// 
// 			if (particle->Velocity.Y < 9.81f)
// 			{
// 				if (particle->Age > 0.5f)
// 					particle->Velocity.Y += particle->Age * Random(3.5f, 5.5f);
// 				else
// 					particle->Velocity.Y += particle->Age * Random(0.5f, 1.5f);
// 
// 			}
// 			else if (particle->Velocity.Y >= 9.81f)
// 			{
// 				particle->Velocity.X += (1-particle->Age) * Random(-1, 1) * 10.0f;
// 				particle->Velocity.Z += (1-particle->Age) * Random(-1, 1) * 10.0f;
// 			}
		}

	}
}