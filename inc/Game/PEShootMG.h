#pragma once

#include "Core/ParticleEffect.h"

namespace TikiEngine
{
	namespace Particles
	{
		class PEShootMG : public ParticleEffect
		{
		public:

			PEShootMG(Engine* engine);
			~PEShootMG();

			void CreateParticle(Particle* particle);
			void UpdateParticle(Particle* particle);

			void Update(const UpdateArgs& args);

		private:

			Vector3 offset; 
			double birthTime;

		};
	}
}