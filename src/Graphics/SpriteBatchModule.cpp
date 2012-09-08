
#include "Core/TypeGlobals.h"
#include "Graphics/SpriteBatchModule.h"
#include "Graphics/GraphicsModule.h"

namespace TikiEngine
{
	namespace Modules
	{
		#pragma region Class
		SpriteBatchModule::SpriteBatchModule(Engine* engine)
			: ISpriteBatch(engine), shader(0), declaration(0), buffer(0), vertices()
		{
		}

		SpriteBatchModule::~SpriteBatchModule()
		{

		}
		#pragma endregion

		#pragma region Member - Init/Dispose
		bool SpriteBatchModule::Initialize(EngineDescription& desc)
		{
			UInt32 temp = 0;

			shader = new Shader(engine);
			shader->LoadFromFile(L"Data/Effects/os_spritebatch.fx");

			List<InputElement> elements = List<InputElement>(SpriteBatchVertex::Declaration, 2, true);

			declaration = new VertexDeclaration(
				engine,
				shader,
				&elements
			);

			buffer = new DynamicBuffer<SpriteBatchVertex, D3D11_BIND_VERTEX_BUFFER>(engine);

			return true;
		}

		void SpriteBatchModule::Dispose()
		{
			SafeRelease(&buffer);
			SafeRelease(&declaration);
			SafeRelease(&shader);
		}
		#pragma endregion

		#pragma region Member - Begin/End
		void SpriteBatchModule::Begin()
		{
			vertices.Clear();
			textures.Clear();
		}

		void SpriteBatchModule::End()
		{
			UInt32 count = vertices.Count();

			if (count == 0) return;

			SpriteBatchVertex* data = vertices.ToArray();
			SpriteBatchVertex* bufferData = this->buffer->Map(count);
			
			memcpy(
				bufferData,
				data,
				sizeof(SpriteBatchVertex) * count
			);

			this->buffer->Unmap();
			delete[](data);

			UINT offset = 0;
			UINT stride = declaration->GetElementSize();
			ID3D11Buffer* buffer = this->buffer->GetBuffer();
			DllMain::Context->IASetVertexBuffers(
				0,
				1,
				&buffer,
				&stride,
				&offset
			);

			DllMain::Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

			shader->SetTextureArray("tex", &textures);
			shader->Apply();
			declaration->Apply();

			DllMain::Context->Draw(count, 0);
		}
		#pragma endregion

		#pragma region Member - Draw
		void SpriteBatchModule::Draw(ITexture* texture, const Vector2& position)
		{
			float index = 0;

			if (!textures.Contains(texture))
			{
				textures.Add(texture);
				index = (float)textures.IndexOf(texture);
			}

			Vector2 screenSize = DllMain::ModuleGraphics->GetViewPort()->GetSize();
			Vector2 pixelSize = Vector2(
				2.0f / screenSize.X,
				2.0f / screenSize.Y
			);

			Vector2 tl = Vector2(
				-1.0f + (position.X * pixelSize.X),
				1.0f - (position.Y * pixelSize.Y)
			);

			Vector2 br = Vector2(
				tl.X + (pixelSize.X * texture->GetWidth()),
				tl.Y - (pixelSize.Y * texture->GetHeight())
			);

			SpriteBatchVertex vertex[4] = {
				{ tl.X, tl.Y, 0.0f, 0.0f, 0.0f, index }, // TL
				{ br.X, tl.Y, 0.0f, 1.0f, 0.0f, index }, // TR
				{ tl.X, br.Y, 0.0f, 0.0f, 1.0f, index }, // BL
				{ br.X, br.Y, 0.0f, 1.0f, 1.0f, index }, // BR
			};

			vertices.Add(vertex[0]);
			vertices.Add(vertex[1]);
			vertices.Add(vertex[2]);
			vertices.Add(vertex[1]);
			vertices.Add(vertex[2]);
			vertices.Add(vertex[3]);
		}

		void SpriteBatchModule::Draw(ITexture* texture, const Rectangle& destinationRectangle)
		{

		}

		void SpriteBatchModule::Draw(ITexture* texture, const Vector2& position, float rotation, const Vector2& origin, float scale, float layerDepth)
		{

		}

		void SpriteBatchModule::Draw(ITexture* texture, const Vector2& position, float rotation, const Vector2& origin, const Vector2& scale, float layerDepth)
		{

		}
		#pragma endregion
	}
}