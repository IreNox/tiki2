#pragma once

#include "Core/GUIControl.h"

#include "Core/IFont.h"

namespace TikiEngine
{
	namespace UserInterface
	{
		using TikiEngine::Resources::IFont;

		class GUILabel : public GUIControl
		{
		public:

			GUILabel(Engine* engine);
			~GUILabel();

			IFont* GetFont() const;
			void SetFont(IFont* font);

			const wstring Text() const;
			wstring& Text();

			void Draw(const DrawArgs& args);

			bool GetReady();

		protected:

			RectangleF createBoundingBox();

		private:

			IFont* font;
			wstring text;

		};
	}
}