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

			interp.ValueInit = Vector4(1, 0.7f, 0.35f, 0);
			interp.ValueMiddle = Vector4(1, 0.54f, 0, 0); 
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
		}

	}
}