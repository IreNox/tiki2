#pragma once

#include "Core/List.h"

#include "Core/GameTime.h"
#include "Core/UpdateArgs.h"
#include "Core/DrawLightArgs.h"

namespace TikiEngine
{
	namespace Components
	{
		class Camera;
	}
	using TikiEngine::Components::Camera;

	namespace Modules
	{
		class IGraphics;
		class ISpriteBatch;
	}
	using TikiEngine::Modules::IGraphics;
	using TikiEngine::Modules::ISpriteBatch;

	// Implementation in AllArgs.cpp
	struct DrawArgs
	{
		static DrawArgs Empty;

		GameTime Time;

		Camera* CurrentCamera;

		IGraphics* Graphics;
		ISpriteBatch* SpriteBatch;

		UpdateArgs& Update;
		DrawLightArgs& Lights;

		DrawArgs(GameTime time, Camera* camera, IGraphics* graphics, ISpriteBatch* spriteBatch, UpdateArgs& updateArgs, DrawLightArgs& lights)
			: Time(time), CurrentCamera(camera), Graphics(graphics), SpriteBatch(spriteBatch), Update(updateArgs), Lights(lights)
		{
		}

		~DrawArgs()
		{
		}

		DrawArgs& operator=(const DrawArgs& rhs)
		{
			return *this;
		}
	
	private:

		static UpdateArgs UpdateEmpty;
		static DrawLightArgs DrawLightEmpty;
		
		DrawArgs()
			: Time(0, 0), CurrentCamera(0), Graphics(0), SpriteBatch(0), Update(UpdateEmpty), Lights(DrawLightEmpty)
		{
		}

	};
}
