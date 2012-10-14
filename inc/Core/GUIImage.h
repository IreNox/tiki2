#pragma once

#include "Core/GUIControl.h"

#include "Core/ITexture.h"

namespace TikiEngine
{
	namespace UserInterface
	{
		using TikiEngine::Resources::ITexture;

		class GUIImage : public GUIControl
		{
		public:

			GUIImage(Engine* engine);
			~GUIImage();

			ITexture* GetTexture();
			void SetTexture(ITexture* texture);
			
			void Draw(const DrawArgs& args);

			bool GetReady();

		private:

			ITexture* texture;
			Vector2 textureSize;

		};
	}
}