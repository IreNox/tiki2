#pragma once

#include "Core/EngineObject.h"
#include "Core/IFont.h"

#include "Core/Vector2.h"
#include "Core/RectangleF.h"

#include "Core/DrawArgs.h"
#include "Core/UpdateArgs.h"

namespace TikiEngine
{
	namespace UserInterface
	{
		using TikiEngine::Resources::IFont;

		class GUIControl : public EngineObject
		{
		public:

			GUIControl(Engine* engine);
			~GUIControl();

			const Vector2 Position() const;
			Vector2& Position();

			const Vector2 Size() const;
			Vector2& Size();

			virtual bool Clicked();

			virtual void Draw(const DrawArgs& args);
			virtual void Update(const UpdateArgs& args);

			virtual bool GetReady();

			static IFont* GetDefaultFont();
			static void SetDefaultFont(IFont* font);

		protected:

			Vector2 position;
			Vector2 size;
			RectangleF boundingBox;

			bool isDirty;
			bool mouseOver;
			bool mouseClicked;
			
			static IFont* defaultFont;

			virtual RectangleF createBoundingBox();

		};
	}
}