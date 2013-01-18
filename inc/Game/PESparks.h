#pragma once

#include "Core/ParticleEffect.h"
#include "Core/Interpolator.h"

namespace TikiEngine
{
	namespace Particles
	{
		class PESparks : public ParticleEffect
		{
		public:
			PESparks(Engine* engine);
			void CreateParticle(Particle* particle);
			void UpdateParticle(Particle* particle);

			void Trigger2(UInt32 count, const Vector3& pos);

			void Update(const UpdateArgs& args);

		private:

			struct Spark
			{
				Particle* p1;
				Particle* p2;
			};

			UInt64 counter;
			Vector3 direction;

			List<Spark> sparks;

			Interpolator<float> interp;
		};
	}
}