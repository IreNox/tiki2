
#include "Graphics/SpriteBatchModule.h"

#include "Core/IGraphics.h"
#include "Core/IContentManager.h"

namespace TikiEngine
{
	namespace Modules
	{
		#pragma region Class
		SpriteBatchModule::SpriteBatchModule(Engine* engine)
			: ISpriteBatch(engine), shader(0), buffer(0)
#if TIKI_DX10 || TIKI_DX11
			, declaration(0)
#endif
		{
		}

		SpriteBatchModule::~SpriteBatchModule()
		{

		}
		#pragma endregion

		#pragma region Member - Init/Dispose
		bool SpriteBatchModule::Initialize(EngineDescription& desc)
		{
			shader = (Shader*)engine->content->LoadShader(L"os_spritebatch");
			shader->AddRef();

#if TIKI_DX10 || TIKI_DX11
			declaration = TIKI_NEW VertexDeclaration(
				engine,
				shader,
				SpriteBatchVertex::Declaration,
				SpriteBatchVertex::DeclarationCount
			);
#endif

			buffer = TIKI_NEW DynamicBuffer<SpriteBatchVertex, TIKI_VERTEX_BUFFER>(engine);

			engine->graphics->ScreenSizeChanged.AddHandler(this);
			this->Handle(engine->graphics, ScreenSizeChangedArgs(engine->graphics, engine->graphics->GetViewPort()));

			return true;
		}

		void SpriteBatchModule::Dispose()
		{
			SafeRelease(&buffer);
			SafeRelease(&shader);

#if TIKI_DX10 || TIKI_DX11
			SafeRelease(&declaration);
#endif
		}
		#pragma endregion

		#pragma region Member - Begin/End
		void SpriteBatchModule::Begin()
		{			
			spriteInfos.Clear();
			spriteVertices.Clear();
		}
		#pragma endregion

		#pragma region Member - Draw
		void SpriteBatchModule::Draw(ITexture* texture, const Vector2& position)
		{
			Vector3 tl = transformPoint(
				Vector3(position.X, position.Y, 1.0f)
			);

			Vector2 br = Vector2(
				tl.X + texture->GetWidth(),
				tl.Y - texture->GetHeight()
			);

			drawInternal(
				texture,
				tl,
				Vector3(br.X, tl.Y, -1.0f),
				Vector3(tl.X, br.Y, -1.0f),
				Vector3(br.X, br.Y, -1.0f),
				Vector4(0.0f, 0.0f, 1.0f, 1.0f),
				Color::White,
				0.0f
			);
		}

		void SpriteBatchModule::Draw(ITexture* texture, const Rectangle& destRect)
		{
			Vector3 tl = transformPoint(
				Vector3(
					(float)destRect.X,
					(float)destRect.Y,
					1.0f
				)
			); 

			Vector3 br = Vector3(
				tl.X + destRect.Width,
				tl.Y - destRect.Height,
				-1.0f
			);

			drawInternal(
				texture,
				tl,
				Vector3(br.X, tl.Y, -1.0f),
				Vector3(tl.X, br.Y, -1.0f),
				br,
				Vector4(0.0f, 0.0f, 1.0f, 1.0f),
				Color::White,
				0.0f
			);
		}

		void SpriteBatchModule::Draw(ITexture* texture, const Rectangle& destRect, const Rectangle& srcRect)
		{
			Vector3 tl = transformPoint(
				Vector3(
				(float)destRect.X,
				(float)destRect.Y,
				1.0f
				)
			); 

			Vector3 br = Vector3(
				tl.X + destRect.Width,
				tl.Y - destRect.Height,
				-1.0f
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
				Vector3(br.X, tl.Y, -1.0f),
				Vector3(tl.X, br.Y, -1.0f),
				br,
				texCorrd,
				Color::White
			);
		}

		void SpriteBatchModule::Draw(ITexture* texture, const RectangleF& destRect, const Color& color)
		{
			this->Draw(texture, destRect, texture->GetRectangle(), color, 1.0f);
		}

		void SpriteBatchModule::Draw(ITexture* texture, const RectangleF& destRect, const Color& color, float layerDepth)
		{
			this->Draw(texture, destRect, texture->GetRectangle(), color, layerDepth);
		}

		void SpriteBatchModule::Draw(ITexture* texture, const RectangleF& destRect, const RectangleF& srcRect, const Color& color)
		{
			this->Draw(texture, destRect, srcRect, color, 1.0f);			
		}

		void SpriteBatchModule::Draw(ITexture* texture, const RectangleF& destRect, const RectangleF& srcRect, const Color& color, float layerDepth)
		{
			Vector3 tl = transformPoint(
				Vector3(destRect.X, destRect.Y, layerDepth)
			); 

			Vector3 br = Vector3(
				tl.X + destRect.Width,
				tl.Y - destRect.Height,
				-layerDepth
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
				Vector3(br.X, tl.Y, -layerDepth),
				Vector3(tl.X, br.Y, -layerDepth),
				br,
				texCorrd,
				color
			);
		}

		void SpriteBatchModule::Draw(ITexture* texture, const Vector2& position, float rotation, const Vector2& origin, float scale, float layerDepth)
		{
			this->Draw(texture, position, rotation, origin, Vector2(scale), layerDepth, Color::White);
		}

		void SpriteBatchModule::Draw(ITexture* texture, const Vector2& position, float rotation, const Vector2& origin, const Vector2& scale, float layerDepth)
		{
			this->Draw(texture, position, rotation, origin, scale, layerDepth, Color::White);
		}

		void SpriteBatchModule::Draw(ITexture* texture, const Vector2& position, float rotation, const Vector2& origin, float scale, float layerDepth, const Color& color)
		{
			this->Draw(texture, position, rotation, origin, Vector2(scale),	layerDepth, color);
		}

		void SpriteBatchModule::Draw(ITexture* texture, const Vector2& position, float rotation, const Vector2& origin, const Vector2& scale, float layerDepth, const Color& color)
		{
			this->Draw(texture, position, rotation, origin, scale,layerDepth, color, 0.0f);
		}

		void SpriteBatchModule::Draw(ITexture* texture, const Vector2& position, float rotation, const Vector2& origin, const Vector2& scale, float layerDepth, const Color& color, float value)
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

			drawInternal(texture, tl, tr, bl, br, Vector4(0.0f, 0.0f, 1.0f, 1.0f), color, value);
		}
		#pragma endregion

		#pragma region Member - DrawLine/DrawString
		void SpriteBatchModule::DrawLine(const List<Vector2>& vertices, const Color& color, float layerDepth /* = 1.0f */, bool loop /* = false */)
		{
			Sprite info;
			info.Lines = true;
			info.Texture = 0;
			info.BufferIndex = spriteVertices.Count();
			info.VertexCount = 0;
			info.Value = 0;
			info.LayerDepth = layerDepth;

			UInt32 i = 0;
			UInt32 c = vertices.Count() - (loop ? 0 : 1);
			while (i < c)
			{
				Vector2 v1 = vertices[i];
				Vector2 v2 = vertices[(i < c - 1 ? i + 1 : 0)];

				SpriteBatchVertex vertex[2] = {
					{ v1.X, screenSize.Y - v1.Y, -layerDepth, -1.0f, -1.0f, color.R, color.G, color.B, color.A },
					{ v2.X, screenSize.Y - v2.Y, -layerDepth, -1.0f, -1.0f, color.R, color.G, color.B, color.A }
				};

				spriteVertices.AddRange(vertex, 0, 2);
				info.VertexCount += 2;

				i++;
			}

			spriteInfos.Add(info);
		}

		void SpriteBatchModule::DrawString(IFont* font, wstring text, const Vector2& position, const Color& color, float layerDepth)
		{
			UInt32 i = 0;
			float width = 0;
			Vector2 pos = position;
			while (i < text.Length())
			{
				width = font->DrawChar(text[i], pos, color, layerDepth);

				pos.X += width;
				i++;
			}
		}
		#pragma endregion

		#pragma region Member - EventHandler
		void SpriteBatchModule::Handle(IGraphics* graphics, const ScreenSizeChangedArgs& args)
		{
			screenSize = args.CurrentViewPort->GetSize();
			projMatrix = Matrix::CreateOrthographicOffCenter(screenSize.X,	screenSize.Y, 0.001f, 10.0f);

			shader->SetMatrix("SBProjM", projMatrix);
		}
		#pragma endregion

		#pragma region Private Member
		Vector3 SpriteBatchModule::transformPoint(const Vector3& point)
		{
			return Vector3(
				point.X,
				(screenSize.Y - point.Y),
				-point.Z
				);
		}

		void SpriteBatchModule::drawInternal(ITexture* texture, const Vector3& tl, const Vector3& tr, const Vector3& bl, const Vector3& br, const Vector4& texCoord, const Color& color, float value)
		{
			Sprite info;
			info.Lines = false;
			info.Texture = texture;
			info.BufferIndex = spriteVertices.Count();
			info.VertexCount = 4;
			info.Value = value;
			info.LayerDepth = tl.Z;
			spriteInfos.Add(info);

			SpriteBatchVertex vertex[4] = {
				{ bl.X, bl.Y, bl.Z, texCoord.X, texCoord.W, color.R, color.G, color.B, color.A }, // BL
				{ tl.X, tl.Y, tl.Z, texCoord.X, texCoord.Y, color.R, color.G, color.B, color.A }, // TL
				{ br.X, br.Y, br.Z, texCoord.Z, texCoord.W, color.R, color.G, color.B, color.A }, // BR
				{ tr.X, tr.Y, tr.Z, texCoord.Z, texCoord.Y, color.R, color.G, color.B, color.A }  // TR
			};
			spriteVertices.AddRange(vertex, 0, 4);
		}
		#pragma endregion
	}
}