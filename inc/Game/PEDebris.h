#pragma once

#include "Core/ParticleEffect.h"
#include "Core/Interpolator.h"

namespace TikiEngine
{
	namespace Particles
	{
		class PEDebris : public ParticleEffect
		{
		public:
			PEDebris(Engine* engine);
			void CreateParticle(Particle* particle);
			void UpdateParticle(Particle* particle);

		private:

			Interpolator<Vector4> interp;

		};
	}
}