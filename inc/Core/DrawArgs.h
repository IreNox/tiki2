#pragma once

#include "Core/GameTime.h"
#include "Core/DrawContext.h"

namespace TikiEngine
{
	namespace Modules
	{
		class IGraphics;
	}
	using TikiEngine::Modules::IGraphics;

	struct DrawArgs
	{
		GameTime Time;
		DrawContext Context;

		IGraphics* Graphics;

		DrawArgs(GameTime time, DrawContext context, IGraphics* graphics)
			: Time(time), Context(context), Graphics(graphics)
		{
		}

		~DrawArgs()
		{
		}
	};
}