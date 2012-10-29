#pragma once

#include "Core/GUIControl.h"
#include "Core/GUIControlRectangles.h"

namespace TikiEngine
{
	namespace UserInterface
	{
		class GUIWindow : public GUIControl
		{
		public:

			GUIWindow(Engine* engine);
			~GUIWindow();

			void Draw(const DrawArgs& args);

		protected:

			ITexture* tex;
			GUIControlRectangles rects;

			RectangleF createBoundingBox();

			static GUIControlRectangles* rd;

		};
	}
}