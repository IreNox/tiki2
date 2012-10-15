
#include "Core/GUIControl.h"
#include "Core/TypeGlobals.h"

namespace TikiEngine
{
	namespace UserInterface
	{
		#pragma region Class
		GUIControl::GUIControl(Engine* engine)
			: EngineObject(engine), isDirty(true), mouseOver(false)
		{
		}

		GUIControl::~GUIControl()
		{
		}
		#pragma endregion

		#pragma region Member
		void GUIControl::Click()
		{
			bool test = false;

			if (test)
			{
				this->GetReady();
			}
		}

		bool GUIControl::GetReady()
		{
			return true;
		}
		#pragma endregion

		#pragma region Member - Get/Set
		Vector2 GUIControl::Position() const
		{
			return position;
		}

		Vector2& GUIControl::Position()
		{
			isDirty = true;
			return position;
		}

		Vector2 GUIControl::Size() const
		{
			return size;
		}

		Vector2& GUIControl::Size()
		{
			isDirty = true;
			return size;
		}
		#pragma endregion

		#pragma region Member - Draw/Update
		void GUIControl::Draw(const DrawArgs& args)
		{
		}

		void GUIControl::Update(const UpdateArgs& args)
		{
			if (isDirty)
			{
				boundingBox = createBoundingBox();
				isDirty = false;
			}

			mouseOver = boundingBox.Contains(args.Input.MousePositionDisplay);

			if (args.Input.MouseButtons[0] && mouseOver)
			{
				this->Click();
			}
		}
		#pragma endregion

		#pragma region Static Member
		IFont* GUIControl::defaultFont = 0;

		IFont* GUIControl::GetDefaultFont()
		{
			return defaultFont;
		}

		void GUIControl::SetDefaultFont(IFont* font)
		{
			SafeRelease(&defaultFont);
			SafeAddRef(font, &defaultFont);
		}
		#pragma endregion

		#pragma region Protected Member
		RectangleF GUIControl::createBoundingBox()
		{
			return RectangleF(
				position.X,
				position.Y,
				size.X,
				size.Y
			);
		}
		#pragma endregion
	}
}