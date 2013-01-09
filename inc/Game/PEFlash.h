#pragma once

#include "Core/ParticleEffect.h"

namespace TikiEngine
{
	namespace Particles
	{
		class PEFlash : public ParticleEffect
		{
		public:
			PEFlash(Engine* engine);
			void CreateParticle(Particle* particle);
			void UpdateParticle(Particle* particle);
		};

	}
}