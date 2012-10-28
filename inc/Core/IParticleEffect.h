#pragma once

#include "Core/Component.h"

#include "Core/ITexture.h"
#include "Core/ParticleBehavior.h"

namespace TikiEngine
{
	namespace Components
	{
		using namespace TikiEngine::Resources;
		using namespace TikiEngine::Particles;

		class IParticleEffect : public Component
		{
		public:

			IParticleEffect(Engine* engine, GameObject* gameObject) : Component(engine, gameObject) {}
			~IParticleEffect() {}

			virtual ITexture* GetTexture() = 0;
			virtual void SetTexture(ITexture* texture) = 0;

			virtual ParticleBehavior* GetParticleBehavior() = 0;
			virtual void SetParticleBehavior(ParticleBehavior* behavior) = 0;

		};
	}
}