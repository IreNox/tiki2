#pragma once

#include "Core/EngineObject.h"
#include "Core/Particle.h"

#include "Core/TypeGlobals.h"
#include "Core/UpdateArgs.h"

namespace TikiEngine
{
	namespace Particles
	{
		enum ParticleRenderType
		{
			PRT_PointList = 0,
			PRT_LineList = 1,
			PRT_LineStrip = 2
		};

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

			ParticleRenderType GRenderType();
			void SRenderType(ParticleRenderType type);

			/*! @brief Get the Life Time */
			double GLifeTime();
			/*! @brief Set the Life Time */
			void SLifeTime(double time);

			/*! @brief Get the Triggered Particle per Second */
			double GReleasePerSecound();
			/*! @brief Set the Triggered Particle per Second */
			void SReleasePerSecound(double count);

			/*! @brief Get the Particle Budget */
			UInt32 GParticleBudget();
			/*! @brief Set the Particle Budget */
			void SParticleBudget(UInt32 budget);
			
			UInt32 GParticleUsed();
			const Particle* GParticles() const;

			void Trigger(double elapsedTime, double releasePerSecound, const Vector3 pos = Vector3::Zero);
			virtual void Update(const UpdateArgs& args);


		protected:

			bool isAlive;
			bool worldPosition;
			bool multiplayReleaseCount;

			double lifeTime;
			double totalTime;
			double deltaTime;
			double releasePerSecound;

			ParticleRenderType renderType;

			virtual void CreateParticle(Particle* particle) = 0;
			virtual void UpdateParticle(Particle* particle) = 0;


		private:

			UInt32 particleUsed;
			UInt32 particleBudget;
			Particle* particles;

		};
	}

}