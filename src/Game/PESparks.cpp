#include "Game/PESparks.h"
#include "Game/Utils.h"

namespace TikiEngine
{
	namespace Particles
	{
		PESparks::PESparks(Engine* engine)
			: ParticleEffect(engine), counter(0)
		{
			SParticleBudget(200);
			renderType = PRT_LineList;
			releasePerSecound = 20;
			lifeTime = 1;

			interp.ValueInit = 0.0f;
			interp.ValueMiddle = 0.5f;
			interp.ValueFinal = 1.0f;
			interp.MiddlePosition = 0.3f;
		}


		void PESparks::CreateParticle(Particle* particle)
		{
			particle->Color = Color(1, 1, 1, 0);
		
			particle->Size = Vector2::One / 1.0f;

			particle->Position = Vector3(0.0f);

			if (counter % 2 == 0)
			{
				direction = Vector3(
					Random(-1, 1), 
					Random(-1, 1), 
					Random(-1, 1)
				);
			}

			direction = Vector3::Normalize(direction);
			counter++;

			particle->Velocity = direction * 15;

		    //particle->Rotation =  atan2f(direction.Z, direction.X);
		}

		void PESparks::UpdateParticle(Particle* particle)
		{
			particle->Color.A = (1 - particle->Age);
			//if (particle->Velocity.Y > -5.81f)
			//particle->Velocity.Y -= 0.05f; //Random(0.01f, 0.05f);

		}


		void PESparks::Trigger2(UInt32 count, const Vector3& pos)
		{
			counter = 0;
			//this->Trigger(1, 20, pos);
		}

		void PESparks::Update(const UpdateArgs& args)
		{


			ParticleEffect::Update(args);
		}
	}
}