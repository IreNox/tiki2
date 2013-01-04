#pragma once

#include "Core/ParticleEffect.h"

namespace TikiEngine
{
	namespace Particles
	{
		class PEExplosion : public ParticleEffect
		{
		public:
			PEExplosion(Engine* engine);
			void CreateParticle(Particle* particle);
			void UpdateParticle(Particle* particle);

		private:
			float minInitialSpeed;
			float maxInitialSpeed;
			float minScale;
			float maxScale;

			float explosionRadius;
		};
	}
}