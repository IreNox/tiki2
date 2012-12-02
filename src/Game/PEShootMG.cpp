
#include "Game/PEShootMG.h"

namespace TikiEngine
{
	namespace Particles
	{
		PEShootMG::PEShootMG(Engine* engine)
			: ParticleEffect(engine), birthTime(0), allocIndex(0)
		{
			this->SParticleBudget(1000);
			lifeTime = 10000000000000000.0;
			releasePerSecound = 1000;
			renderType = PRT_LineList;
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
			particle->Position = Vector3::Zero;
			particle->Color = Color::White;
			particle->Rotation = 0;
			particle->Size = Vector2::One / 2;
			particle->Velocity = Vector3::Zero;
			//particle->Velocity = Vector3(100.0f, 0, 0);
			//particle->BirthTime = birthTime;

			//if (this->GParticleUsed() % 2 == 0)
			//{
			//	deltaTime += 0.10;
			//	birthTime = totalTime + 0.10;

			//	offset = Vector3(
			//		Random(-1.0f, 1.0f),
			//		Random(-0.4f, 0.4f),
			//		Random(-0.4f, 0.4f)
			//	);
			//}
		}

		void PEShootMG::UpdateParticle(Particle* particle)
		{
			//particle->Color.A = 1 - particle->Age;
			//particle->Position.Y = sin(particle->Age * 20) * 0.2f;
			//particle->Position.Z = cos(particle->Age * 20) * 0.2f;
			//particle->Rotation = particle->Age * 3.14159f;
		}

		void PEShootMG::Allocate(Particle** p1, Particle** p2)
		{
			Particle* ps = (Particle*)this->GParticles();

			*p1 = &ps[allocIndex];
			*p2 = &ps[allocIndex+1];

			allocIndex += 2;
			if (allocIndex >= this->GParticleBudget()) allocIndex = 0;
		}
	}
}
