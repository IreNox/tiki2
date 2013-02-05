#pragma once

#include "Core/ParticleEffect.h"

namespace TikiEngine
{
	namespace Particles
	{
		class PEBlood : public ParticleEffect
		{
		public:
			PEBlood(Engine* engine);
			void CreateParticle(Particle* particle);
			void UpdateParticle(Particle* particle);

			void setNewRandom(float rand);

		private:
			float randomBlood;
		};

	}
}