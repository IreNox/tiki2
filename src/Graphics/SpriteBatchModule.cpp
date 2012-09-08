
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

			screenSize = DllMain::ModuleGraphics->GetViewPort()->GetSize();
			pixelSize = Vector2(
				2.0f / screenSize.X,
				2.0f / screenSize.Y
			);
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
			Vector2 tl = Vector2(
				-1.0f + (position.X * pixelSize.X),
				1.0f - (position.Y * pixelSize.Y)
			);

			Vector2 br = Vector2(
				tl.X + (pixelSize.X * texture->GetWidth()),
				tl.Y - (pixelSize.Y * texture->GetHeight())
			);

			drawInternal(
				texture,
				Vector3(tl.X, tl.Y, 0.0f),
				Vector3(br.X, tl.Y, 0.0f),
				Vector3(tl.X, br.Y, 0.0f),
				Vector3(br.X, br.Y, 0.0f)
			);
		}

		void SpriteBatchModule::Draw(ITexture* texture, const Rectangle& destRect)
		{
			Vector2 tl = Vector2(
				-1.0f + (destRect.X * pixelSize.X),
				1.0f - (destRect.Y * pixelSize.Y)
			);

			Vector2 br = Vector2(
				tl.X + (pixelSize.X * destRect.Width),
				tl.Y - (pixelSize.Y * destRect.Height)
			);

			drawInternal(
				texture,
				Vector3(tl.X, tl.Y, 0.0f),
				Vector3(br.X, tl.Y, 0.0f),
				Vector3(tl.X, br.Y, 0.0f),
				Vector3(br.X, br.Y, 0.0f)
			);
		}

		void SpriteBatchModule::Draw(ITexture* texture, const Vector2& position, float rotation, const Vector2& origin, float scale, float layerDepth)
		{
			this->Draw(
				texture,
				position,
				rotation,
				origin,
				Vector2(scale),
				layerDepth
			);
		}

		void SpriteBatchModule::Draw(ITexture* texture, const Vector2& position, float rotation, const Vector2& origin, const Vector2& scale, float layerDepth)
		{
			Vector3 origin3 = Vector3(origin, 0);
			Vector3 size = Vector3(texture->GetSize(), 0);
			
			Vector3 tl = Vector3(0.0f,   0.0f,   0.0f) - origin3;
			Vector3 tr = Vector3(size.X, 0.0f,   0.0f) - origin3;
			Vector3 bl = Vector3(0.0f,   size.Y, 0.0f) - origin3;
			Vector3 br = Vector3(size.X, size.Y, 0.0f) - origin3;

			tl = Vector3(tl.X * scale.X, tl.Y * scale.Y, layerDepth);
			tr = Vector3(tr.X * scale.X, tr.Y * scale.Y, layerDepth);
			bl = Vector3(bl.X * scale.X, bl.Y * scale.Y, layerDepth);
			br = Vector3(br.X * scale.X, br.Y * scale.Y, layerDepth);

			Quaternion rot = Quaternion::CreateFromYawPitchRoll(0, 0, rotation);
			tl = rot * tl;
			tr = rot * tr;
			bl = rot * bl;
			br = rot * br;

			Vector3 position3 = Vector3(position, 0.0f);
			tl = transformPoint(tl + position3);
			tr = transformPoint(tr + position3);
			bl = transformPoint(bl + position3);
			br = transformPoint(br + position3);

			drawInternal(texture, tl, tr, bl, br);
		}
		#pragma endregion

		#pragma region Private Member
		Vector3 SpriteBatchModule::transformPoint(Vector3 point)
		{
			return Vector3(
				-1.0f + (point.X * pixelSize.X),
				 1.0f - (point.Y * pixelSize.Y),
				 0.0f
			);
		}

		void SpriteBatchModule::drawInternal(ITexture* texture, const Vector3& tl, const Vector3& tr, const Vector3& bl, const Vector3& br)
		{
			float index = 0;

			if (!textures.Contains(texture))
			{
				textures.Add(texture);
				index = (float)textures.IndexOf(texture);
			}

			SpriteBatchVertex vertex[4] = {
				{ tl.X, tl.Y, tl.Z, 0.0f, 0.0f, index }, // TL
				{ tr.X, tr.Y, tr.Z, 1.0f, 0.0f, index }, // TR
				{ bl.X, bl.Y, bl.Z, 0.0f, 1.0f, index }, // BL
				{ br.X, br.Y, br.Z, 1.0f, 1.0f, index }, // BR
			};

			vertices.Add(vertex[0]);
			vertices.Add(vertex[1]);
			vertices.Add(vertex[2]);
			vertices.Add(vertex[1]);
			vertices.Add(vertex[2]);
			vertices.Add(vertex[3]);
		}
		#pragma endregion
	}
}