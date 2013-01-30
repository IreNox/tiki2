#pragma once

#include "Core/HelperLog.h"
#include "Core/GameObject.h"

#include "Core/EventLog.h"
#include "Core/EventScreenSizeChanged.h"

#include "Core/IFont.h"
#include "Core/ITexture.h"

namespace TikiEngine
{
	namespace Game
	{
		using namespace  TikiEngine::Resources;

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

			IFont* font;
			ITexture* bgTexture;

			RectangleF bgRect;

			UInt32 lineIndex;
			Dictionary<wstring, double> lines;

			wstring cmdEnter;

			bool executeCommand();

		};
	}
}