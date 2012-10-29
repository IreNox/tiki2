#pragma once

#include "Core/GUIControl.h"
#include "Core/GUIControlRectangles.h"

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
			ITexture* tex;
			
			Vector2 posText;
			GUIControlRectangles rects;

			/*! @brief Rectangle Data from Database */
			static GUIControlRectangles* rdNormal;
			static GUIControlRectangles* rdHover;
			static GUIControlRectangles* rdClick;

		};
	}
}