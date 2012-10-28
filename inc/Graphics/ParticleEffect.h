#pragma once

#include "Core/IParticleEffect.h"
#include "Core/IShader.h"

#include "Graphics/DynamicBuffer.h"
#include "Graphics/VertexDeclaration.h"

#include "Graphics/ParticleVertex.h"

namespace TikiEngine
{
	namespace Components
	{
		using namespace TikiEngine::Vertices;
		using namespace TikiEngine::Graphics;

		class ParticleEffect : public IParticleEffect
		{
		public:

			ParticleEffect(Engine* engine, GameObject* gameObject);
			~ParticleEffect();

			ITexture* GetTexture();
			void SetTexture(ITexture* texture);

			ParticleBehavior* GetParticleBehavior();
			void SetParticleBehavior(ParticleBehavior* behavior);

			void Draw(const DrawArgs& args);
			void Update(const UpdateArgs& args);

			bool GetReady();

		private:

			IShader* shader;
			ITexture* texture;

			ParticleBehavior* behavior;

			VertexDeclaration* decl;
			DynamicBuffer<ParticleVertex, D3D11_BIND_VERTEX_BUFFER>* vertexBuffer;

		};
	}
}