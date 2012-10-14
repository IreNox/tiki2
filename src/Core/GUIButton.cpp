
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
			texLT = engine->content->LoadTexture(L"Controls/button-lt");
			texLC = engine->content->LoadTexture(L"Controls/button-lc");
			texLB = engine->content->LoadTexture(L"Controls/button-lb");

			texCT = engine->content->LoadTexture(L"Controls/button-ct");
			texCB = engine->content->LoadTexture(L"Controls/button-cb");

			texRT = engine->content->LoadTexture(L"Controls/button-rt");
			texRC = engine->content->LoadTexture(L"Controls/button-rc");
			texRB = engine->content->LoadTexture(L"Controls/button-rb");

			texMoLT = engine->content->LoadTexture(L"Controls/button-mo-lt");
			texMoLC = engine->content->LoadTexture(L"Controls/button-mo-lc");
			texMoLB = engine->content->LoadTexture(L"Controls/button-mo-lb");

			texMoCT = engine->content->LoadTexture(L"Controls/button-mo-ct");
			texMoCC = engine->content->LoadTexture(L"Controls/button-mo-cc");
			texMoCB = engine->content->LoadTexture(L"Controls/button-mo-cb");

			texMoRT = engine->content->LoadTexture(L"Controls/button-mo-rt");
			texMoRC = engine->content->LoadTexture(L"Controls/button-mo-rc");
			texMoRB = engine->content->LoadTexture(L"Controls/button-mo-rb");
		}

		GUIButton::~GUIButton()
		{
			SafeRelease(&texLT);
			SafeRelease(&texLC);
			SafeRelease(&texLB);

			SafeRelease(&texCT);
			SafeRelease(&texCB);

			SafeRelease(&texRT);
			SafeRelease(&texRC);
			SafeRelease(&texRB);

			SafeRelease(&texMoLT);
			SafeRelease(&texMoLC);
			SafeRelease(&texMoLB);

			SafeRelease(&texMoCT);
			SafeRelease(&texMoCC);
			SafeRelease(&texMoCB);

			SafeRelease(&texMoRT);
			SafeRelease(&texMoRC);
			SafeRelease(&texMoRB);
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
			if (mouseOver)
			{
				engine->sprites->Draw(texMoLT, position);
				engine->sprites->Draw(texMoLB, posLB);
				engine->sprites->Draw(texMoRT, posRT);
				engine->sprites->Draw(texMoRB, posRB);

				engine->sprites->Draw(texMoLC, rectLC);
				engine->sprites->Draw(texMoCT, rectCT);
				engine->sprites->Draw(texMoCC, rectCC);
				engine->sprites->Draw(texMoCB, rectCB);
				engine->sprites->Draw(texMoRC, rectRC);
			}
			else
			{
				engine->sprites->Draw(texLT, position);
				engine->sprites->Draw(texLB, posLB);
				engine->sprites->Draw(texRT, posRT);
				engine->sprites->Draw(texRB, posRB);

				engine->sprites->Draw(texLC, rectLC);
				engine->sprites->Draw(texCT, rectCT);
				engine->sprites->Draw(texCB, rectCB);
				engine->sprites->Draw(texRC, rectRC);
			}

			engine->sprites->DrawString(
				GUIControl::GetDefaultFont(),
				text,
				posText
			);
		}
		#pragma endregion

		#pragma region Protected Member
		RectangleF GUIButton::createBoundingBox()
		{
			RectangleF rect = GUIControl::createBoundingBox();

			Vector2 sizeText = GUIControl::GetDefaultFont()->MeasureString(text) / 2;

			posText = position + (size / 2) - sizeText;

			posLB = Vector2(
				position.X,
				rect.Bottom() - texLB->GetHeight()
			);

			posRT = Vector2(
				rect.Right() - texRT->GetWidth(),
				position.Y
			);

			posRB = Vector2(
				rect.Right() - texRB->GetWidth(),
				rect.Bottom() - texRB->GetHeight()
			);

			rectLC = RectangleF(
				position.X,
				position.Y + texLT->GetHeight(),
				(float)texLC->GetWidth(),
				(rect.Height - texLT->GetHeight()) - texLB->GetHeight()
			);

			rectCT = RectangleF(
				position.X + texLT->GetWidth(),
				position.Y,
				(rect.Width - texLT->GetWidth()) - texRT->GetWidth(),
				(float)texCT->GetHeight()
			);

			rectCC = RectangleF(
				position.X + texLT->GetWidth(),
				position.Y + texLT->GetHeight(),
				(rect.Width - texLT->GetWidth()) - texRT->GetWidth(),
				(rect.Height - texRT->GetHeight()) - texRB->GetHeight()
			);

			rectCB = RectangleF(
				position.X + texLT->GetWidth(),
				rect.Bottom() - texCB->GetHeight(),
				(rect.Width - texLB->GetWidth()) - texRB->GetWidth(),
				(float)texCB->GetHeight()
			);

			rectRC = RectangleF(
				rect.Right() - texRC->GetWidth(),
				position.Y + texRT->GetHeight(),
				(float)texRC->GetWidth(),
				(rect.Height - texRT->GetHeight()) - texRB->GetHeight()
			);

			return rect;
		}
		#pragma endregion
	}
}