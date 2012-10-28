#pragma once

#include "Core/ParticleBehavior.h"

namespace TikiEngine
{
	namespace Particles
	{
		class ParticleTest : public ParticleBehavior
		{
		public:

			ParticleTest(Engine* engine);
			~ParticleTest();

			void CreateParticle(Particle* particle);
			void UpdateParticle(Particle* particle);

		};
	}
}