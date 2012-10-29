#pragma once

#include "Core/EngineObject.h"
#include "Core/Particle.h"

#include "Core/TypeGlobals.h"
#include "Core/UpdateArgs.h"

namespace TikiEngine
{
	namespace Particles
	{
		class ParticleEffect : public EngineObject
		{
		public:

			#pragma region Class
			ParticleEffect(Engine* engine);
			~ParticleEffect();
			#pragma endregion

			bool GIsAlive();
			void SIsAlive(bool alive);

			bool GWorldSpace();
			void SWorldSpace(bool worldSpace);

			/*! @brief Get the Life Time */
			double GLifeTime();
			/*! @brief Set the Life Time */
			void SLifeTime(double time);

			/*! @brief Get the Trigger Time */
			double GTriggerTime();
			/*! @brief Set the Trigger Time */
			void STriggerTime(double time);

			/*! @brief Get the trigger Quantity */
			UInt32 GTriggerCount();
			/*! @brief Set the trigger Quantity */
			void STriggerCount(UInt32 count);

			/*! @brief Get the Particle Budget */
			UInt32 GParticleBudget();
			/*! @brief Set the Particle Budget */
			void SParticleBudget(UInt32 budget);
			
			UInt32 GParticleUsed();
			const Particle* GParticles() const;

			void Update(const UpdateArgs& args);


		protected:

			bool isAlive;
			bool worldPosition;

			double lifeTime;
			double triggerTime;

			UInt32 triggerCount;

			virtual void CreateParticle(Particle* particle) = 0;
			virtual void UpdateParticle(Particle* particle) = 0;


		private:

			double lastTrigger;

			UInt32 particleUsed;
			UInt32 particleBudget;
			Particle* particles;

		};
	}

}