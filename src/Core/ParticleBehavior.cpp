
#include "Core/ParticleBehavior.h"

namespace TikiEngine
{
	namespace Particles
	{
		#pragma region Class
		ParticleBehavior::ParticleBehavior(Engine* engine)
			: EngineObject(engine), isAlive(true), worldPosition(false), lifeTime(1), triggerTime(0.1f),
			  particleBudget(1000), particleUsed(0), triggerCount(100)
		{
			particles = new Particle[particleBudget];
		}

		ParticleBehavior::~ParticleBehavior()
		{
			SafeDeleteArray(&particles);
		}
		#pragma endregion
		
		#pragma region Member - Get/Set
		UInt32 ParticleBehavior::GParticleUsed()
		{
			return particleUsed;
		}

		const Particle* ParticleBehavior::GParticles() const
		{
			return particles;
		}

		bool ParticleBehavior::GIsAlive()
		{
			return isAlive;
		}

		void ParticleBehavior::SIsAlive(bool alive)
		{
			isAlive = alive;
		}

		bool ParticleBehavior::GWorldSpace()
		{
			return worldPosition;
		}

		void ParticleBehavior::SWorldSpace(bool worldSpace)
		{
			worldPosition = worldSpace;
		}

		double ParticleBehavior::GLifeTime()
		{
			return lifeTime;
		}

		void ParticleBehavior::SLifeTime(double time)
		{
			lifeTime = time;
		}

		double ParticleBehavior::GTriggerTime()
		{
			return triggerTime;
		}

		void ParticleBehavior::STriggerTime(double time)
		{
			triggerTime = time;
		}

		UInt32 ParticleBehavior::GTriggerCount()
		{
			return triggerCount;
		}

		void ParticleBehavior::STriggerCount(UInt32 count)
		{
			triggerCount = count;
		}

		UInt32 ParticleBehavior::GParticleBudget()
		{
			return particleBudget;
		}

		void ParticleBehavior::SParticleBudget(UInt32 budget)
		{
			if (particleBudget == budget) return;

			SafeDeleteArray(&particles);
			
			particleUsed = 0;
			particleBudget = budget;
			particles = new Particle[particleBudget];
		}
		#pragma endregion

		#pragma region Member - Update
		void ParticleBehavior::Update(const UpdateArgs& args)
		{
			if (args.Time.TotalTime - lastTrigger >= triggerTime)
			{
				lastTrigger = args.Time.TotalTime;

				UInt32 i = 0;
				while (i < triggerCount && particleUsed < particleBudget)
				{
					Particle* particle = &particles[particleUsed];
					particle->BirthTime = args.Time.TotalTime;

					this->CreateParticle(particle);

					particleUsed++;
					i++;
				}
			}

			UInt32 i = 0;
			Particle* particle = particles;
			while (i < particleUsed)
			{
				particle->Age = (args.Time.TotalTime - particle->BirthTime) / lifeTime;

				if (particle->Age > 1.0f)
				{
					*particle = particles[--particleUsed];
				}
				else
				{
					particle->Position += particle->Velocity * args.Time.ElapsedTime;
					this->UpdateParticle(particle);
				}

				particle++;
				i++;
			}
		}
		#pragma endregion

	}
}