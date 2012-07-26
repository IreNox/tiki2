
#include "Core/Texture.h"
#include "Core/Engine.h"

#include "Core/Console.h"

namespace TikiEngine
{
	namespace Resources
	{
		#pragma region Class
		Texture::Texture(Engine* engine, wstring fileName)
			: engine(engine)
		{
			//HRESULT r = D3DX11CreateShaderResourceViewFromFile(
			//	engine->graphics->GetDevice(),
			//	fileName.c_str(),
			//	0,
			//	0,
			//	&texture,
			//	0
			//);

			//if (FAILED(r))
			//{
			//	Console::WriteError("Can't load Texture", r);
			//}
		}

		Texture::~Texture()
		{
			if (texture != 0)
			{
				texture->Release();
				texture = 0;
			}
		}
		#pragma endregion Class

		#pragma region Member
		ID3D11ShaderResourceView* Texture::GetTexture()
		{
			return texture;
		}
		#pragma endregion
	}
}

