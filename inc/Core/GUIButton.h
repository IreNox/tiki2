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

			ITexture* tex;
			
			Vector2 posText;

			RectangleF rectLT;
			RectangleF rectLC;
			RectangleF rectLB;
			RectangleF rectCT;
			RectangleF rectCC;
			RectangleF rectCB;
			RectangleF rectRT;
			RectangleF rectRC;
			RectangleF rectRB;

			class ButtonRectangles : public TikiObject
			{
			public:

				union
				{
					struct 
					{
						RectangleF rectLT;
						RectangleF rectLC;
						RectangleF rectLB;
						RectangleF rectCT;
						RectangleF rectCC;
						RectangleF rectCB;
						RectangleF rectRT;
						RectangleF rectRC;
						RectangleF rectRB;
					};
					RectangleF rects[9];
				};

				ButtonRectangles(string control);
				~ButtonRectangles();

			};

			/*! @brief Rectangle Data from Database */
			static ButtonRectangles* rdNormal;
			static ButtonRectangles* rdHover;
			static ButtonRectangles* rdClick;

		};
	}
}