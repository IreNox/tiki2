#pragma once

#include "Core/ParticleEffect.h"
#include "Core/Interpolator.h"

namespace TikiEngine
{
	namespace Particles
	{
		class PERoundSparks : public ParticleEffect
		{
		public:
			PERoundSparks(Engine* engine);
			void CreateParticle(Particle* particle);
			void UpdateParticle(Particle* particle);

		private:
			Interpolator<float> interp;
		};
	}
}