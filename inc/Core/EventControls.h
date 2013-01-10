#pragma once

#include "Core/Event.h"

namespace TikiEngine
{
	namespace UserInterface
	{
		class GUIControl;
	}
	using namespace TikiEngine::UserInterface;

	struct ClickEventArgs 
	{
		MouseButtons Button;
		Vector2 ClickPosition;

		ClickEventArgs(MouseButtons button, Vector2 clickPos) : Button(button), ClickPosition(clickPos) {}
	};

	typedef Event<GUIControl, ClickEventArgs> ClickEvent;
	typedef EventHandler<GUIControl, ClickEventArgs> ClickEventHandler;
}