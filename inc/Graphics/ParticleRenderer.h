#pragma once

#include "Core/IParticleRenderer.h"
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

		class ParticleRenderer : public IParticleRenderer
		{
		public:

			ParticleRenderer(Engine* engine, GameObject* gameObject);
			~ParticleRenderer();

			ITexture* GetTexture();
			void SetTexture(ITexture* texture);

			ParticleRenderType GRenderType();
			void SRenderType(ParticleRenderType type);

			ParticleEffect* GetParticleEffect();
			void SetParticleEffect(ParticleEffect* behavior);

			void Draw(const DrawArgs& args);
			void Update(const UpdateArgs& args);

			bool GetReady();

		private:

			IShader* shader;
			ITexture* texture;

			ParticleEffect* behavior;

			VertexDeclaration* decl;
			DynamicBuffer<ParticleVertex, D3D11_BIND_VERTEX_BUFFER>* vertexBuffer;

		};
	}
}