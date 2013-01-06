
#include "Core/ParticleEffect.h"

namespace TikiEngine
{
	namespace Particles
	{
		#pragma region Class
		ParticleEffect::ParticleEffect(Engine* engine)
			: EngineObject(engine), isAlive(true), worldPosition(false), lifeTime(1), releasePerSecound(10.0),
			  particleBudget(1000), particleUsed(0), renderType(PRT_PointList), deltaTime(0), totalTime(0),
			  multiplayReleaseCount(false)
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

		ParticleRenderType ParticleEffect::GRenderType()
		{
			return renderType;
		}

		void ParticleEffect::SRenderType(ParticleRenderType type)
		{
			renderType = type;
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

		double ParticleEffect::GReleasePerSecound()
		{
			return releasePerSecound;
		}

		void ParticleEffect::SReleasePerSecound(double count)
		{
			releasePerSecound = count;
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

		#pragma region Member - Trigger
		void ParticleEffect::Trigger(UInt32 count, const Vector3 pos)
		{
			if (multiplayReleaseCount) count *= renderType + 1;

			UInt32 i = 0;
			while (i < count && particleUsed < particleBudget)
			{
				Particle* particle = &particles[particleUsed++];
				particle->BirthTime = totalTime;
				particle->Position = pos;

				this->CreateParticle(particle);

				i++;
			}
		}
		#pragma endregion

		#pragma region Member - Update
		void ParticleEffect::Update(const UpdateArgs& args)
		{
			totalTime = args.Time.TotalTime;

			if (isAlive)
			{
				deltaTime -= args.Time.ElapsedTime;

				UInt32 count = 0;
				while (deltaTime < 0)
				{
					deltaTime += 1.0f / releasePerSecound;
					count++;
				}

				this->Trigger(count);
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