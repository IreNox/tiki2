
#include "Core/GUIWindow.h"

#include "Core/IContentManager.h"

namespace TikiEngine
{
	namespace UserInterface
	{
		GUIControlRectangles* GUIWindow::rd = 0;

		#pragma region Class
		GUIWindow::GUIWindow(Engine* engine)
			: GUIControl(engine)
		{
			tex = engine->content->LoadTexture(L"controls");

			if (rd == 0)
			{
				rd = new GUIControlRectangles("window");
			}
			else
			{
				rd->AddRef();
			}
		}

		GUIWindow::~GUIWindow()
		{
			rd->Release();
		}
		#pragma endregion
		
		#pragma region Member - Draw
		void GUIWindow::Draw(const DrawArgs& args)
		{
			GUIControlRectangles::Draw(
				engine->sprites,
				tex,
				&rects,
				rd
			);

			GUIControl::Draw(args);
		}
		#pragma endregion

		#pragma region Protected Member
		RectangleF GUIWindow::createBoundingBox()
		{
			RectangleF rect = GUIControl::createBoundingBox();

			rects = GUIControlRectangles(rect, rd);

			return rect;
		}
		#pragma endregion

	}
}