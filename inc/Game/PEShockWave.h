#pragma once

#include "Core/ParticleEffect.h"
#include "Core/Interpolator.h"

namespace TikiEngine
{
	namespace Particles
	{
		class PEShockWave : public ParticleEffect
		{
		public:
			PEShockWave(Engine* engine);
			void CreateParticle(Particle* particle);
			void UpdateParticle(Particle* particle);

		private:
			Interpolator<float> interp;
		};
	}
}