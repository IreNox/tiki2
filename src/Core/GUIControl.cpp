
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
		bool GUIControl::Clicked()
		{
			return mouseClicked;
		}

		bool GUIControl::GetReady()
		{
			return true;
		}
		#pragma endregion

		#pragma region Member - Get/Set
		const Vector2 GUIControl::Position() const
		{
			return position;
		}

		Vector2& GUIControl::Position()
		{
			isDirty = true;
			return position;
		}

		const Vector2 GUIControl::Size() const
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
				boundingBox = this->createBoundingBox();
				isDirty = false;
			}

			mouseOver = boundingBox.Contains(args.Input.MousePositionDisplay);
			mouseClicked = (args.Input.GetMousePressed(MB_Left) && mouseOver);
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