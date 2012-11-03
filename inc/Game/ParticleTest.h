#pragma once

#include "Core/ParticleEffect.h"

namespace TikiEngine
{
	namespace Particles
	{
		class ParticleTest : public ParticleEffect
		{
		public:

			ParticleTest(Engine* engine);
			~ParticleTest();

			void CreateParticle(Particle* particle);
			void UpdateParticle(Particle* particle);

			void Update(const UpdateArgs& args);

		private:

			Vector3 offset; 
			double birthTime;

		};
	}
}