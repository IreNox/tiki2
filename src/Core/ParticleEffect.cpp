
#include "Core/ParticleEffect.h"

namespace TikiEngine
{
	namespace Particles
	{
		#pragma region Class
		ParticleEffect::ParticleEffect(Engine* engine)
			: EngineObject(engine), isAlive(true), worldPosition(false), lifeTime(1), triggerTime(0.1f),
			  particleBudget(1000), particleUsed(0), triggerCount(100)
		{
			particles = new Particle[particleBudget];
		}

		ParticleEffect::~ParticleEffect()
		{
			SafeDeleteArray(&particles);
		}
		#pragma endregion
		
		#pragma region Member - Get/Set
		UInt32 ParticleEffect::GParticleUsed()
		{
			return particleUsed;
		}

		const Particle* ParticleEffect::GParticles() const
		{
			return particles;
		}

		bool ParticleEffect::GIsAlive()
		{
			return isAlive;
		}

		void ParticleEffect::SIsAlive(bool alive)
		{
			isAlive = alive;
		}

		bool ParticleEffect::GWorldSpace()
		{
			return worldPosition;
		}

		void ParticleEffect::SWorldSpace(bool worldSpace)
		{
			worldPosition = worldSpace;
		}

		double ParticleEffect::GLifeTime()
		{
			return lifeTime;
		}

		void ParticleEffect::SLifeTime(double time)
		{
			lifeTime = time;
		}

		double ParticleEffect::GTriggerTime()
		{
			return triggerTime;
		}

		void ParticleEffect::STriggerTime(double time)
		{
			triggerTime = time;
		}

		UInt32 ParticleEffect::GTriggerCount()
		{
			return triggerCount;
		}

		void ParticleEffect::STriggerCount(UInt32 count)
		{
			triggerCount = count;
		}

		UInt32 ParticleEffect::GParticleBudget()
		{
			return particleBudget;
		}

		void ParticleEffect::SParticleBudget(UInt32 budget)
		{
			if (particleBudget == budget) return;

			SafeDeleteArray(&particles);
			
			particleUsed = 0;
			particleBudget = budget;
			particles = new Particle[particleBudget];
		}
		#pragma endregion

		#pragma region Member - Update
		void ParticleEffect::Update(const UpdateArgs& args)
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
				particle->Age = (float)((args.Time.TotalTime - particle->BirthTime) / lifeTime);

				if (particle->Age > 1.0f)
				{
					*particle = particles[--particleUsed];
				}
				else
				{
					particle->Position += particle->Velocity * (float)args.Time.ElapsedTime;
					this->UpdateParticle(particle);
				}

				particle++;
				i++;
			}
		}
		#pragma endregion

	}
}