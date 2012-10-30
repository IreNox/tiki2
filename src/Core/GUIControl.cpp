
#include "Core/GUIControl.h"
#include "Core/TypeGlobals.h"

namespace TikiEngine
{
	namespace UserInterface
	{
		#pragma region Class
		GUIControl::GUIControl(Engine* engine)
			: EngineObject(engine), isDirty(true), mouseOver(false), parent(0), UserData(0)
		{
		}

		GUIControl::~GUIControl()
		{
			UInt32 i = 0;
			while (i < childs.Count())
			{
				childs[i]->Release();
				i++;
			}
			childs.Clear();
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

		#pragma region Member - Childs
		void GUIControl::AddChild(GUIControl* child)
		{
			if (child->parent)
			{
				child->parent->RemoveChild(child);
			}

			child->parent = this;
			child->AddRef();
			childs.Add(child);
		}

		bool GUIControl::RemoveChild(GUIControl* child)
		{
			if (child->parent == this)
			{
				child->parent = 0;
				child->Release();
				return childs.Remove(child);
			}

			return false;
		}

		const List<GUIControl*>& GUIControl::ChildControls()
		{
			return childs;
		}
		#pragma endregion

		#pragma region Member - Get/Set
		const Vector2& GUIControl::GPosition() const
		{
			return position;
		}

		Vector2& GUIControl::SPosition()
		{
			isDirty = true;
			return position;
		}

		const Vector2& GUIControl::GSize() const
		{
			return size;
		}

		Vector2& GUIControl::SSize()
		{
			isDirty = true;
			return size;
		}
		#pragma endregion

		#pragma region Member - Draw/Update
		void GUIControl::Draw(const DrawArgs& args)
		{
			UInt32 i = 0;
			while (i < childs.Count())
			{
				childs[i]->Draw(args);
				i++;
			}
		}

		void GUIControl::Update(const UpdateArgs& args)
		{
			if (isDirty || (parent && parent->isDirty))
			{
				boundingBox = this->createBoundingBox();
			}

			mouseOver = boundingBox.Contains(args.Input.MousePositionDisplay);

			mouseClicked = (args.Input.GetMousePressed(MB_Left) && mouseOver);
			if (mouseClicked) this->Click.RaiseEvent(this, ClickEventArgs(this));

			UInt32 i = 0;
			while (i < childs.Count())
			{
				childs[i]->Update(args);
				i++;
			}

			isDirty = false;
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
			Vector2 base = (parent ? parent->position : Vector2::Zero);

			return RectangleF::Create(
				base.X + position.X,
				base.Y + position.Y,
				size.X,
				size.Y
			);
		}
		#pragma endregion
	}
}