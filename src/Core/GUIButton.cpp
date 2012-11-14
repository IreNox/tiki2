
#include "Core/GUIButton.h"

#include "Core/ISpriteBatch.h"
#include "Core/IContentManager.h"

namespace TikiEngine
{
	namespace UserInterface
	{
		#pragma region Class
		GUIButton::GUIButton(Engine* engine)
			: GUIControl(engine)
		{
			tex = engine->content->LoadTexture(L"controls");
			tex->AddRef();

			if (rdNormal == 0)
			{
				rdNormal = new GUIControlRectangles("button_normal");
				rdHover = new GUIControlRectangles("button_hover");
				rdClick = new GUIControlRectangles("button_click");
			}

			rdNormal->AddRef();
			rdHover->AddRef();
			rdClick->AddRef();
		}

		GUIButton::~GUIButton()
		{
			SafeRelease(&tex);
			
			rdNormal->Release();
			rdHover->Release();
			rdClick->Release();
		}
		#pragma endregion

		#pragma region Member - Get/Set
		wstring GUIButton::Text() const
		{
			return text;	
		}

		wstring& GUIButton::Text()
		{
			isDirty = true;
			return text;
		}
		#pragma endregion

		#pragma region Member - Draw
		void GUIButton::Draw(const DrawArgs& args)
		{
			GUIControlRectangles* rd = (mouseOver ? (args.Update.Input.GetMouse(MB_Left) ? rdClick : rdHover) : rdNormal);

			GUIControlRectangles::Draw(
				engine->sprites,
				tex,
				&rects,
				rd
			);

			engine->sprites->DrawString(
				GUIControl::GetDefaultFont(),
				text,
				posText,
				Color::White
			);

			GUIControl::Draw(args);
		}
		#pragma endregion

		#pragma region Protected Member
		RectangleF GUIButton::createBoundingBox()
		{
			RectangleF rect = GUIControl::createBoundingBox();

			Vector2 sizeText = GUIControl::GetDefaultFont()->MeasureString(text) / 2;

			posText = rect.Position() + (size / 2) - sizeText;
			rects = GUIControlRectangles(rect, rdNormal);

			return rect;
		}
		#pragma endregion

		#pragma region Static
		GUIControlRectangles* GUIButton::rdNormal = 0;
		GUIControlRectangles* GUIButton::rdHover = 0;
		GUIControlRectangles* GUIButton::rdClick = 0;		
		#pragma endregion
	}
}