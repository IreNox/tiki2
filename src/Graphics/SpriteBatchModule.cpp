
#include "Core/TypeGlobals.h"

#include "Core/IContentManager.h"

#include "Graphics/RenderTarget.h"
#include "Graphics/GraphicsModule.h"
#include "Graphics/SpriteBatchModule.h"

namespace TikiEngine
{
	namespace Modules
	{
		#pragma region Class
		SpriteBatchModule::SpriteBatchModule(Engine* engine)
			: ISpriteBatch(engine), shader(0), declaration(0), buffer(0), vertices(), matrices()
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

			shader = (Shader*)engine->content->LoadShader(L"os_spritebatch");
			shader->AddRef();

			renderTarget = new RenderTarget(engine);
			renderTarget->CreateScreenSize();
			renderTarget->AddRef();
			DllMain::ModuleGraphics->AddDefaultProcessTarget("spriteBatch", renderTarget);

			List<InputElement> elements = List<InputElement>(SpriteBatchVertex::Declaration, SpriteBatchVertex::DeclarationCount, true);

			declaration = new VertexDeclaration(
				engine,
				shader,
				&elements
			);

			buffer = new DynamicBuffer<SpriteBatchVertex, D3D11_BIND_VERTEX_BUFFER>(engine);

			viewMatrix = Matrix::CreateLookAt(
				-Vector3::Forward,
				Vector3::Zero,
				Vector3::Up
			);

			this->Handle(engine->graphics, ScreenSizeChangedArgs(engine->graphics, engine->graphics->GetViewPort()));

			return true;
		}

		void SpriteBatchModule::Dispose()
		{
			SafeRelease(&buffer);
			SafeRelease(&shader);
			SafeRelease(&declaration);
			SafeRelease(&renderTarget);
		}
		#pragma endregion

		#pragma region Member - Begin/End
		void SpriteBatchModule::Begin()
		{
			vertices.Clear();
			textures.Clear();
			matrices.Clear();
		}

		void SpriteBatchModule::End()
		{
			UInt32 count = vertices.Count();
			if (count == 0) return;

			DllMain::ModuleGraphics->SetStateAlphaBlend(true);
			DllMain::ModuleGraphics->SetStateDepthEnabled(false);
			DllMain::ModuleGraphics->GetScreenTarget()->ApplyFirstAndOnly();

			SpriteBatchVertex* bufferData = this->buffer->Map(count);
			
			memcpy(
				bufferData,
				vertices.GetInternalData(),
				sizeof(SpriteBatchVertex) * count
			);

			this->buffer->Unmap();

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

			DllMain::Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

			declaration->Apply();

			renderTarget->Clear(Color::TransparentBlack);
			renderTarget->Apply(0);

			bool mSet = true;

			UInt32 i = 0;
			UInt32 spritesCount = count / 4;
			while (i < spritesCount)
			{
				if (matrices.ContainsKey(i))
				{
					shader->SetMatrix("spViewM", viewMatrix);
					shader->SetMatrix("spProjM", projMatrix);
					shader->SetMatrix("spLocalM", matrices[i].LocalM);
					shader->SetMatrix("spWorldM", matrices[i].WorldM);
					mSet = true;
				}
				else if (mSet)
				{
					shader->SetMatrix("spViewM", Matrix::Identity);
					shader->SetMatrix("spProjM", Matrix::Identity);
					shader->SetMatrix("spLocalM", Matrix::Identity);
					shader->SetMatrix("spWorldM", Matrix::Identity);
					mSet = false;
				}

				shader->SetTexture("tex", textures[i]);
				shader->Apply();

				DllMain::Context->Draw(4, i * 4);

				i++;
			}

			DllMain::ModuleGraphics->SetStateAlphaBlend(false);
		}
		#pragma endregion

		#pragma region Member - Draw
		void SpriteBatchModule::Draw(ITexture* texture, const Vector2& position)
		{
			Vector3 tl = transformPoint(
				Vector3(position.X, position.Y, 0.0f)
			);

			Vector2 br = Vector2(
				tl.X + (pixelSize.X * texture->GetWidth()),
				tl.Y - (pixelSize.Y * texture->GetHeight())
			);

			drawInternal(
				texture,
				tl,
				Vector3(br.X, tl.Y, 0.0f),
				Vector3(tl.X, br.Y, 0.0f),
				Vector3(br.X, br.Y, 0.0f),
				Vector4(0.0f, 0.0f, 1.0f, 1.0f),
				Color::White
			);
		}

		void SpriteBatchModule::Draw(ITexture* texture, const Rectangle& destRect)
		{
			Vector3 tl = transformPoint(
				Vector3(
					(float)destRect.X,
					(float)destRect.Y,
					0.0f
				)
			); 

			Vector3 br = Vector3(
				tl.X + (pixelSize.X * destRect.Width),
				tl.Y - (pixelSize.Y * destRect.Height),
				0.0f
			);

			drawInternal(
				texture,
				tl,
				Vector3(br.X, tl.Y, 0.0f),
				Vector3(tl.X, br.Y, 0.0f),
				br,
				Vector4(0.0f, 0.0f, 1.0f, 1.0f),
				Color::White
			);
		}

		void SpriteBatchModule::Draw(ITexture* texture, const Rectangle& destRect, const Rectangle& srcRect)
		{
			Vector3 tl = transformPoint(
				Vector3(
					(float)destRect.X,
					(float)destRect.Y,
					0.0f
				)
			); 

			Vector3 br = Vector3(
				tl.X + (pixelSize.X * destRect.Width),
				tl.Y - (pixelSize.Y * destRect.Height),
				0.0f
			);

			Vector2 size = texture->GetSize();

			Vector4 texCorrd = Vector4(
				(float)srcRect.X / size.X,
				(float)srcRect.Y / size.Y,
				(float)(srcRect.X + srcRect.Width) / size.X,
				(float)(srcRect.Y + srcRect.Height) / size.Y
			);

			drawInternal(
				texture,
				tl,
				Vector3(br.X, tl.Y, 0.0f),
				Vector3(tl.X, br.Y, 0.0f),
				br,
				texCorrd,
				Color::White
			);
		}

		void SpriteBatchModule::Draw(ITexture* texture, const RectangleF& destRect)
		{
			this->Draw(
				texture,
				destRect,
				texture->GetRectangle()
			);
		}

		void SpriteBatchModule::Draw(ITexture* texture, const RectangleF& destRect, const RectangleF& srcRect)
		{
			Vector3 tl = transformPoint(
				Vector3(destRect.X, destRect.Y, 0.0f)
			); 

			Vector3 br = Vector3(
				tl.X + (pixelSize.X * destRect.Width),
				tl.Y - (pixelSize.Y * destRect.Height),
				0.0f
			);

			Vector2 size = texture->GetSize();

			Vector4 texCorrd = Vector4(
				srcRect.X / size.X,
				srcRect.Y / size.Y,
				(srcRect.X + srcRect.Width) / size.X,
				(srcRect.Y + srcRect.Height) / size.Y
			);

			drawInternal(
				texture,
				tl,
				Vector3(br.X, tl.Y, 0.0f),
				Vector3(tl.X, br.Y, 0.0f),
				br,
				texCorrd,
				Color::White
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

			drawInternal(texture, tl, tr, bl, br, Vector4(0.0f, 0.0f, 1.0f, 1.0f), Color::White);
		}
		#pragma endregion
		
		#pragma region Member - Draw3D
		void SpriteBatchModule::Draw3D(ITexture* texture, const Matrix& world, const Matrix& local)
		{
			drawInternal(
				texture,
				Vector3(-0.1f, -0.1f, 0),
				Vector3( 0.1f, -0.1f, 0),
				Vector3(-0.1f,  0.1f, 0),
				Vector3( 0.1f,  0.1f, 0),
				Vector4(0, 0, 1, 1),
				Color::White
			);

			LocalWorldMatrices lw = { local, world };

			matrices.Add(
				textures.Count() - 1,
				lw
			);
		}
		#pragma endregion

		#pragma region Member - DrawString
		void SpriteBatchModule::DrawString(IFont* font, wstring text, const Vector2& position)
		{
			UInt32 i = 0;
			float width = 0;
			Vector2 pos = position;
			while (i < text.length())
			{
				width = font->DrawChar(text[i], pos);

				pos.X += width;
				i++;
			}
		}
		#pragma endregion

		#pragma region Member - EventHandler
		void SpriteBatchModule::Handle(IGraphics* graphics, const ScreenSizeChangedArgs& args)
		{
			screenSize = args.CurrentViewPort->GetSize();
			pixelSize = Vector2(
				2.0f / screenSize.X,
				2.0f / screenSize.Y
			);

			projMatrix = Matrix::CreateOrthographic(
				screenSize.X,
				screenSize.Y,
				0.01f,
				1000.0f
			);
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

		void SpriteBatchModule::drawInternal(ITexture* texture, const Vector3& tl, const Vector3& tr, const Vector3& bl, const Vector3& br, const Vector4& texCoord, const Color& color)
		{
			float index = 0;

			textures.Add(texture);
			index = (float)textures.Count() - 1;

			SpriteBatchVertex vertex[4] = {
				{ tl.X, tl.Y, tl.Z, texCoord.X, texCoord.Y, index, color.R, color.G, color.B, color.A }, // TL
				{ tr.X, tr.Y, tr.Z, texCoord.Z, texCoord.Y, index, color.R, color.G, color.B, color.A }, // TR
				{ bl.X, bl.Y, bl.Z, texCoord.X, texCoord.W, index, color.R, color.G, color.B, color.A }, // BL
				{ br.X, br.Y, br.Z, texCoord.Z, texCoord.W, index, color.R, color.G, color.B, color.A }, // BR
			};

			vertices.Add(vertex[0]);
			vertices.Add(vertex[1]);
			vertices.Add(vertex[2]);
			vertices.Add(vertex[3]);
		}
		#pragma endregion
	}
}