
#include "Graphics/ParticleRenderer.h"

#include "Core/TypeGlobals.h"
#include "Core/IContentManager.h"

#include "Graphics/DllMain.h"
#include "Graphics/GraphicsModule.h"

namespace TikiEngine
{
	namespace Components
	{
		#pragma region Class
		ParticleRenderer::ParticleRenderer(Engine* engine, GameObject* gameObject)
			: IParticleRenderer(engine, gameObject), shader(0), texture(0), behavior(0)
		{
			shader = engine->content->LoadShader(L"os_particle");

			decl = new VertexDeclaration(engine, shader, ParticleVertex::Declaration, ParticleVertex::DeclarationCount);
			vertexBuffer = new DynamicBuffer<ParticleVertex, D3D11_BIND_VERTEX_BUFFER>(engine);
		}

		ParticleRenderer::~ParticleRenderer()
		{
			SafeRelease(&shader);
			SafeRelease(&texture);

			SafeRelease(&behavior);
		}
		#pragma endregion

		#pragma region Member - Get/Set
		bool ParticleRenderer::GetReady()
		{
			return (texture != 0) && (behavior != 0);
		}

		ITexture* ParticleRenderer::GetTexture()
		{
			return texture;
		}

		void ParticleRenderer::SetTexture(ITexture* texture)
		{
			SafeRelease(&this->texture);
			SafeAddRef(texture, &this->texture);

			if (texture)
			{
				shader->SetTexture("tex", texture);
			}
		}

		ParticleEffect* ParticleRenderer::GetParticleEffect()
		{
			return behavior;
		}

		void ParticleRenderer::SetParticleEffect(ParticleEffect* behavior)
		{
			SafeRelease(&this->behavior);
			SafeAddRef(behavior, &this->behavior);
		}
		#pragma endregion

		#pragma region Member - Draw
		void ParticleRenderer::Draw(const DrawArgs& args)
		{
			DllMain::ModuleGraphics->SetStateDepthEnabled(false);

			decl->Apply();

			UInt32 stride = sizeof(ParticleVertex);
			UInt32 offset = 0;
			ID3D11Buffer* buffer = vertexBuffer->GetBuffer();

			DllMain::Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
			DllMain::Context->IASetVertexBuffers(0, 1, &buffer, &stride, &offset);

			shader->Apply();
			shader->ApplyVars(gameObject, 0);

			DllMain::Context->Draw(behavior->GParticleUsed(), 0);

			DllMain::ModuleGraphics->SetStateDepthEnabled(true);
		}
		#pragma endregion

		#pragma region Member - Update
		void ParticleRenderer::Update(const UpdateArgs& args)
		{
			if (!this->GetReady()) return;

			behavior->Update(args);

			int count = behavior->GParticleUsed();
			const Particle* particles = behavior->GParticles();
			ParticleVertex* vertices = vertexBuffer->Map(count);

			int i = 0;
			while (i < count)
			{
				memcpy(&vertices[i], &particles[i], sizeof(ParticleVertex));

				i++;
			}

			vertexBuffer->Unmap();
		}
		#pragma endregion

	}
}