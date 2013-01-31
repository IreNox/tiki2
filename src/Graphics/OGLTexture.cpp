
#include "Graphics/Texture.h"

#include "Core/IGraphics.h"

struct DDS_PIXELFORMAT {
	DWORD dwSize;
	DWORD dwFlags;
	DWORD dwFourCC;
	DWORD dwRGBBitCount;
	DWORD dwRBitMask;
	DWORD dwGBitMask;
	DWORD dwBBitMask;
	DWORD dwABitMask;
};

typedef struct {
	DWORD           dwSize;
	DWORD           dwFlags;
	DWORD           dwHeight;
	DWORD           dwWidth;
	DWORD           dwPitchOrLinearSize;
	DWORD           dwDepth;
	DWORD           dwMipMapCount;
	DWORD           dwReserved1[11];
	DDS_PIXELFORMAT ddspf;
	DWORD           dwCaps;
	DWORD           dwCaps2;
	DWORD           dwCaps3;
	DWORD           dwCaps4;
	DWORD           dwReserved2;
} DDS_HEADER;

namespace TikiEngine
{
	namespace Resources
	{
		#pragma region Class
		Texture::Texture(Engine* engine)
			: ITexture(engine), dynamic(true), textureId(0)
		{
		}

		Texture::Texture(Engine* engine, UInt32 textureId)
			: ITexture(engine), textureId(textureId), dynamic(false)
		{
			if (textureId == 0)
			{
				width = engine->graphics->GetViewPort()->Width;
				height = engine->graphics->GetViewPort()->Height;
			}
		}

		Texture::~Texture()
		{
			if (textureId != 0)
				glDeleteTextures(1, &textureId);
		}
		#pragma endregion

		#pragma region Create
		void Texture::Create(UInt32 width, UInt32 height, bool dynamic, PixelFormat format)
		{
			createInternal(width, height, true, format);

			GLenum intFormat = GL_FALSE;

			switch(format)
			{
			case PF_R8G8B8A8:
				intFormat = GL_RGBA8;
				break;
			case PF_R32G32B32A32:
				intFormat = GL_RGBA32F;
				break;
			default:
				throw string("PixelFormat not supported");
			}

			glTexImage2D(GL_TEXTURE_2D, 0, intFormat, width, height, 0, GL_RGBA, GL_UNSIGNED_INT, 0);

			glBindTexture(GL_TEXTURE_2D, 0);
		}
		#pragma endregion

		#pragma region Get
		Int32 Texture::GetWidth() { return width; }
		Int32 Texture::GetHeight() { return height; }
		Vector2 Texture::GetSize() { return Vector2((float)width, (float)height); }
		Vector2 Texture::GetCenter() { return this->GetSize() / 2; }
		Rectangle Texture::GetRectangle() { return Rectangle(0, 0, width, height); }
		#pragma endregion

		#pragma region Data
		void Texture::GetData(PixelFormat format, void** data, UInt32* dataLength)
		{

		}

		void Texture::SetData(PixelFormat format, void* data, UInt32 dataLength)
		{
			if (format != PF_R8G8B8A8 && format != PF_A8R8G8B8)
				throw string("PixelFormat not supported");

			if (dataLength < 4U * width * height)
				throw string("Data to small");

			glTexImage2D(
				GL_TEXTURE_2D,
				0,
				GL_RGBA,
				width,
				height,
				0,
				GL_BGRA,
				GL_UNSIGNED_BYTE,
				data
			);
		}
		#pragma endregion

		#pragma region IResource
		bool Texture::GetDynamic() { return dynamic; }
		void* Texture::GetNativeResource() { return &textureId; }

		bool Texture::GetReady() { return textureId != 0; }
		#pragma endregion

		#pragma region Private - Create
		void Texture::createInternal(UInt32 width, UInt32 height, bool dynamic, PixelFormat format)
		{
			this->width = width;
			this->height = height;
			this->dynamic = dynamic;

			glGenTextures(1, &textureId);
			glBindTexture(GL_TEXTURE_2D, textureId);

			if (!dynamic)
			{
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);	
			}
			else
			{
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

			}
		}
		#pragma endregion

		#pragma region Private - Load/Save
		void Texture::loadFromStream(wcstring fileName, Stream* stream)
		{
			DWORD magic;
			stream->Read(&magic, 0, sizeof(DWORD));

			if (magic != 0x20534444)
				throw string("Wrong file format.");

			DDS_HEADER header;
			stream->Read(&header, 0, sizeof(DDS_HEADER));

			createInternal(
				header.dwWidth,
				header.dwHeight,
				true,
				PF_R8G8B8A8
			);

			Byte* data = new Byte[4 * width * height];
			stream->Read(data, 0, 4 * width * height);

			glTexImage2D(
				GL_TEXTURE_2D,
				0,
				GL_RGBA,
				width,
				height,
				0,
				GL_BGRA,
				GL_UNSIGNED_BYTE,
				data
			);
			delete[](data);

			if (header.dwMipMapCount)
			{
				glGenerateMipmap(GL_TEXTURE_2D);
			}

			glBindTexture(GL_TEXTURE_2D, 0);
		}

		void Texture::saveToStream(wcstring fileName, Stream* stream)
		{

		}
		#pragma endregion
	}
}