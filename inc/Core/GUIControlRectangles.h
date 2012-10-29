#pragma once

#include "Core/TikiObject.h"
#include "Core/RectangleF.h"

#include "Core/ISpriteBatch.h"

namespace TikiEngine
{
	namespace UserInterface
	{
		using namespace TikiEngine::Modules;
		using namespace TikiEngine::Resources;

		class GUIControlRectangles : public TikiObject
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

			/*! @brief Create new non initialized GUIControlRectangles */
			GUIControlRectangles();
			
			/*! @brief Create new GUIControlRectangles from Database */
			GUIControlRectangles(string control);

			/*! @brief Create new GUIControlRectangles from Database-data */
			GUIControlRectangles(const RectangleF& destRect, GUIControlRectangles* srcRects);
			
			~GUIControlRectangles();

			static void Draw(ISpriteBatch* batch, ITexture* texture, GUIControlRectangles* dst, GUIControlRectangles* src);

		};
	}
}