#include "Game/PEExplosion.h"
#include "Game/Utils.h"

namespace TikiEngine
{
	namespace Particles
	{
		PEExplosion::PEExplosion(Engine* engine)
			: ParticleEffect(engine)
		{
			SParticleBudget(5000);
			renderType = PRT_PointList;
			releasePerSecound = 10000;
			lifeTime = 1;

			minInitialSpeed = 5; //200;
			maxInitialSpeed = 10; //600;

			minScale = 1.1f;//2;
			maxScale = 1.2f;//5;

			explosionRadius = 10;
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
			particle->Color.A = 1 - particle->Age;
			particle->Size *= Random(1.01f, 1.015f);
			particle->Velocity *=  (1-particle->Age) * Random(1.1f, 1.25f);
            //particle->Velocity.Y -= 25.0f;
		}

	}
}