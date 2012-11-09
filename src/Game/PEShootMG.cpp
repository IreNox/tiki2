
#include "Game/PEShootMG.h"

namespace TikiEngine
{
	namespace Particles
	{
		PEShootMG::PEShootMG(Engine* engine)
			: ParticleEffect(engine), birthTime(0)
		{
			this->SParticleBudget(1000000);
			lifeTime = 10;
			releasePerSecound = 50;
			renderType = PRT_LineList;
			//renderType = PRT_PointList;

			//this->Trigger(1);
		}

		PEShootMG::~PEShootMG()
		{
		}

		void PEShootMG::Update(const UpdateArgs& args)
		{
			totalTime = args.Time.TotalTime;

			//isAlive = (this->GParticleUsed() < 2);

			ParticleEffect::Update(args);
			
			//if (this->GParticleUsed() % 2 == 0)
			//{
			//	//deltaTime += 0.5;
			//	//this->Trigger(1);
			//	//multiplayReleaseCount = true;
			//}
		}

		void PEShootMG::CreateParticle(Particle* particle)
		{
			particle->Position = offset;
			particle->Color = Color::White;
			particle->Rotation = 0;
			particle->Size = Vector2::One / 35;
			particle->Velocity = offset * 2;
			particle->Velocity = Vector3(30.0f, 0, 0);
			particle->BirthTime = birthTime;

			if (this->GParticleUsed() % 2 == 0)
			{
				deltaTime += 0.10;
				birthTime = totalTime + 0.10;

				offset = Vector3(
					Random(-1.0f, 1.0f),
					Random(-0.4f, 0.4f),
					Random(-0.4f, 0.4f)
				);
			}
		}

		void PEShootMG::UpdateParticle(Particle* particle)
		{
			//particle->Color.A = 1 - particle->Age;
			//particle->Position.Y = sin(particle->Age * 20) * 0.2f;
			//particle->Position.Z = cos(particle->Age * 20) * 0.2f;
			//particle->Rotation = particle->Age * 3.14159f;
		}
	}
}
