
#include "Graphics/Texture.h"

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

		Texture::~Texture()
		{
			glDeleteTextures(1, &textureId);
		}
		#pragma endregion

		#pragma region Create
		void Texture::Create(UInt32 width, UInt32 height, bool dynamic, PixelFormat format)
		{
			createInternal(width, height, dynamic, format);
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

		}
		#pragma endregion

		#pragma region IResource
		bool Texture::GetDynamic() { return dynamic; }
		void* Texture::GetNativeResource() { return (void*)textureId; }

		bool Texture::GetReady() { return textureId != 0; }
		#pragma endregion

		#pragma region Private - Create
		void Texture::createInternal(UInt32 width, UInt32 height, bool dynamic, PixelFormat format)
		{
			if (format != PF_R8G8B8A8)
				throw string("PixelFormat not supported");

			this->width = width;
			this->height = height;
			this->dynamic = dynamic;

			glGenTextures(1, &textureId);
			glBindTexture(GL_TEXTURE_2D, textureId);

			glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

			glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST );
			glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

			glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP );
			glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );
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
				GL_RGBA8,
				GL_UNSIGNED_BYTE,
				data
			);
			delete[](data);

			if (header.dwMipMapCount)
			{
				glGenerateMipmap(GL_TEXTURE_2D);
			}
		}

		void Texture::saveToStream(wcstring fileName, Stream* stream)
		{

		}
		#pragma endregion
	}
}