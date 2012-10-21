#pragma once

#include "Core/Event.h"
#include "Core/ViewPort.h"

namespace TikiEngine
{
	namespace Modules
	{
		class IGraphics;
	}

	struct ScreenSizeChangedArgs 
	{
		IGraphics* Graphics;
		ViewPort* CurrentViewPort;
		ScreenSizeChangedArgs(IGraphics* graphics, ViewPort* vp) : Graphics(graphics), CurrentViewPort(vp) {}
	};

	typedef Event<IGraphics, ScreenSizeChangedArgs> ScreenSizeChangedEvent;
	typedef EventHandler<IGraphics, ScreenSizeChangedArgs> ScreenSizeChangedEventHandler;
}