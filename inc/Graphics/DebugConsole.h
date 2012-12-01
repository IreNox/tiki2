#pragma once

#include "Core/HelperLog.h"
#include "Core/GameObject.h"

#include "Core/EventLog.h"
#include "Core/EventScreenSizeChanged.h"

#include "Graphics/Font.h"
#include "Graphics/Texture.h"

namespace TikiEngine
{
	namespace Graphics
	{
		class DebugConsole : public GameObject, public MessageReceivedEventHandler, public ScreenSizeChangedEventHandler
		{
		public:

			DebugConsole(Engine* engine);
			~DebugConsole();

			void Draw(const DrawArgs& args);
			void Update(const UpdateArgs& args);

			void Handle(IGraphics* sender, const ScreenSizeChangedArgs& args);
			void Handle(const HelperLog* sender, const MessageReceivedArgs& args);

		private:
			
			bool enabled;

			Font* font;
			Texture* bgTexture;

			RectangleF bgRect;

			UInt32 lineIndex;
			Dictionary<wstring, double> lines;

			double lastTime;
			wstring cmdEnter;

			bool executeCommand();

		};
	}
}