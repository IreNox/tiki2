#pragma once

#include "Core/EngineObject.h"
#include "Core/IFont.h"

#include "Core/Vector2.h"
#include "Core/RectangleF.h"

#include "Core/DrawArgs.h"
#include "Core/UpdateArgs.h"

#include "Core/EventControls.h"

namespace TikiEngine
{
	namespace UserInterface
	{
		using TikiEngine::Resources::IFont;

		class GUIControl : public EngineObject
		{
		public:

			ClickEvent Click;
			void* UserData;

			GUIControl(Engine* engine);
			~GUIControl();

			const Vector2& GPosition() const;
			Vector2& SPosition();

			const Vector2& GSize() const;
			Vector2& SSize();
			
			void AddChild(GUIControl* child);
			bool RemoveChild(GUIControl* child);
			const List<GUIControl*>& ChildControls();

			virtual bool Clicked();

			virtual void Draw(const DrawArgs& args);
			virtual void Update(const UpdateArgs& args);
			
			virtual bool GetReady();

			inline GUIControl* GetParent() { return parent; }

			inline RectangleF GetBoundingBox() { return boundingBox; }

			static IFont* GetDefaultFont();
			static void SetDefaultFont(IFont* font);

		protected:

			Vector2 position;
			Vector2 size;
			RectangleF boundingBox;

			bool isDirty;
			bool mouseOver;
			bool mouseClicked;
			
			virtual RectangleF createBoundingBox();

			static IFont* defaultFont;

		private:

			GUIControl* parent;
			List<GUIControl*> childs;
			List<GUIControl*> childsToRemove;

		};
	}
}