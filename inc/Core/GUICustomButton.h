#pragma once

#include "Core/GUIControl.h"
#include "Core/ITexture.h"

namespace TikiEngine
{
	namespace UserInterface
	{
		using TikiEngine::Resources::ITexture;

		class GUICustomButton : public GUIControl
		{
		public:

			GUICustomButton(Engine* engine);
			~GUICustomButton();

			ITexture* GetTextureDefault();
			void SetTextureDefault(ITexture* texture);

			ITexture* GetTextureMouseOver();
			void SetTextureMouseOver(ITexture* texture);

			ITexture* GetTextureClick();
			void SetTextureClick(ITexture* texture);

			void Draw(const DrawArgs& args);

		private:

			ITexture* texDefault;
			ITexture* texMouseOver;
			ITexture* texClick;

		};
	}
}