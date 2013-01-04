#pragma once

#include "Core/ParticleEffect.h"
#include "Core/Interpolator.h"

namespace TikiEngine
{
	namespace Particles
	{
		class PESmoke : public ParticleEffect
		{
		public:
			PESmoke(Engine* engine);
			void CreateParticle(Particle* particle);
			void UpdateParticle(Particle* particle);

		private:
			Vector3 windDirection;
			float initialSpeed;
			float minScale;
			float maxScale;

			Interpolator interp;


		};
	}
}