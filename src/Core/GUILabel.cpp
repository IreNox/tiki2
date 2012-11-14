
#include "Core/GUILabel.h"

#include "Core/TypeGlobals.h"
#include "Core/ISpriteBatch.h"

namespace TikiEngine
{
	namespace UserInterface
	{
		#pragma region Class
		GUILabel::GUILabel(Engine* engine)
			: GUIControl(engine), font(GUIControl::defaultFont)
		{
		}

		GUILabel::~GUILabel()
		{
		}
		#pragma endregion

		#pragma region Member
		bool GUILabel::GetReady()
		{
			return (font != 0);
		}
		#pragma endregion

		#pragma region Member - Get/Set
		IFont* GUILabel::GetFont() const
		{
			return font;
		}

		void GUILabel::SetFont(IFont* font)
		{
			SafeRelease(&this->font);
			SafeAddRef(font, &this->font);

			isDirty = true;
		}

		const wstring GUILabel::Text() const
		{
			return text;
		}

		wstring& GUILabel::Text()
		{
			isDirty = true;
			return text;
		}
		#pragma endregion

		#pragma region Member - Draw
		void GUILabel::Draw(const DrawArgs& args)
		{
			if (!this->GetReady()) return;

			engine->sprites->DrawString(font, text, position, Color::White);
		}
		#pragma endregion

		#pragma region Protected Member
		RectangleF GUILabel::createBoundingBox()
		{
			if (font)
			{
				size = font->MeasureString(text);
			}
			else
			{
				size = Vector2::Zero;
			}

			return GUIControl::createBoundingBox();
		}
		#pragma endregion
	}
}