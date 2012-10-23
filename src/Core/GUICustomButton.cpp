
#include "Core/GUICustomButton.h"
#include "Core/TypeGlobals.h"
#include "Core/ISpriteBatch.h"

namespace TikiEngine
{
	namespace UserInterface
	{
		#pragma region Class
		GUICustomButton::GUICustomButton(Engine* engine)
			: GUIControl(engine), texDefault(0), texMouseOver(0), texClick(0)
		{
		}

		GUICustomButton::~GUICustomButton()
		{
			SafeRelease(&texDefault);
			SafeRelease(&texMouseOver);
			SafeRelease(&texClick);
		}
		#pragma endregion

		#pragma region Mmeber - Get/Set
		ITexture* GUICustomButton::GetTextureDefault()
		{
			return texDefault;
		}

		void GUICustomButton::SetTextureDefault(ITexture* texture)
		{
			SafeRelease(&texDefault);
			SafeAddRef(texture, &texDefault);
		}

		ITexture* GUICustomButton::GetTextureMouseOver()
		{
			return texMouseOver;
		}

		void GUICustomButton::SetTextureMouseOver(ITexture* texture)
		{
			SafeRelease(&texMouseOver);
			SafeAddRef(texture, &texMouseOver);
		}

		ITexture* GUICustomButton::GetTextureClick()
		{
			return texClick;
		}

		void GUICustomButton::SetTextureClick(ITexture* texture)
		{
			SafeRelease(&texClick);
			SafeAddRef(texture, &texClick);
		}
		#pragma endregion

		#pragma region Member - Draw
		void GUICustomButton::Draw(const DrawArgs& args)
		{
			if (args.Update.Input.GetMousePressed(MB_Left) && mouseOver)
			{
				engine->sprites->Draw(texClick, position);
			}
			else if (mouseOver)
			{
				engine->sprites->Draw(texMouseOver, position);
			}
			else
			{
				engine->sprites->Draw(texDefault, position);
			}
		}
		#pragma endregion
	}
}