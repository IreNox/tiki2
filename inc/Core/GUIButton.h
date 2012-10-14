#pragma once

#include "Core/GUIControl.h"

#include "Core/ITexture.h"

namespace TikiEngine
{
	namespace UserInterface
	{
		using TikiEngine::Resources::ITexture;

		class GUIButton : public GUIControl
		{
		public:

			GUIButton(Engine* engine);
			~GUIButton();
			
			wstring Text() const;
			wstring& Text();

			void Draw(const DrawArgs& args);
			
		protected:

			RectangleF createBoundingBox();

		private:

			wstring text;

			ITexture* texLT;
			ITexture* texLC;
			ITexture* texLB;

			ITexture* texCT;
			ITexture* texCB;

			ITexture* texRT;
			ITexture* texRC;
			ITexture* texRB;

			ITexture* texMoLT;
			ITexture* texMoLC;
			ITexture* texMoLB;

			ITexture* texMoCT;
			ITexture* texMoCC;
			ITexture* texMoCB;

			ITexture* texMoRT;
			ITexture* texMoRC;
			ITexture* texMoRB;
			
			Vector2 posLB;
			Vector2 posRT;
			Vector2 posRB;
			Vector2 posText;

			RectangleF rectLC;
			RectangleF rectCT;
			RectangleF rectCC;
			RectangleF rectCB;
			RectangleF rectRC;

		};
	}
}