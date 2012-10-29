#pragma once

#include "Core/Component.h"

#include "Core/ITexture.h"
#include "Core/ParticleEffect.h"

namespace TikiEngine
{
	namespace Components
	{
		using namespace TikiEngine::Resources;
		using namespace TikiEngine::Particles;

		class IParticleRenderer : public Component
		{
		public:

			IParticleRenderer(Engine* engine, GameObject* gameObject) : Component(engine, gameObject) {}
			~IParticleRenderer() {}

			virtual ITexture* GetTexture() = 0;
			virtual void SetTexture(ITexture* texture) = 0;

			virtual ParticleEffect* GetParticleEffect() = 0;
			virtual void SetParticleEffect(ParticleEffect* behavior) = 0;

		};
	}
}