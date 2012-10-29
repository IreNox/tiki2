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
		GUIControl* Control;

		ClickEventArgs(GUIControl* control) : Control(control) {}
	};

	typedef Event<GUIControl, ClickEventArgs> ClickEvent;
	typedef EventHandler<GUIControl, ClickEventArgs> ClickEventHandler;
}