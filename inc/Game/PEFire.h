#pragma once

#include "Core/ParticleEffect.h"
#include "Core/Interpolator.h"

namespace TikiEngine
{
	namespace Particles
	{
		class PEFire : public ParticleEffect
		{
		public:
			PEFire(Engine* engine);
			void CreateParticle(Particle* particle);
			void UpdateParticle(Particle* particle);

		private:
			float initialSpeed;
			float minScale;
			float maxScale;
			Interpolator interp;
		};
	}
}