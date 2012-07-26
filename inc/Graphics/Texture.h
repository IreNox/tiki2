#pragma once

#include <d3d11.h>
#include <string>

namespace TikiEngine
{
	class Engine;

	using namespace std;

	namespace Resources
	{
		class Texture
		{
		public:

			Texture(Engine* engine, wstring fileName);
			~Texture();

			ID3D11ShaderResourceView* GetTexture();

		private:

			Engine* engine;

			ID3D11ShaderResourceView* texture;
		};
	}
}
