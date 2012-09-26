#pragma once

#include "Core/GameTime.h"
#include "Core/List.h"

namespace TikiEngine
{
	namespace Components
	{
		class Light;
		class Camera;
	}
	using TikiEngine::Components::Light;
	using TikiEngine::Components::Camera;

	namespace Modules
	{
		class IGraphics;
		class ISpriteBatch;
	}
	using TikiEngine::Modules::IGraphics;
	using TikiEngine::Modules::ISpriteBatch;

	struct DrawArgs
	{
		GameTime Time;

		Camera* CurrentCamera;
		List<Light*>* AllLights;

		IGraphics* Graphics;
		ISpriteBatch* SpriteBatch;

		DrawArgs()
			: Time(0, 0), CurrentCamera(0), Graphics(0), SpriteBatch(0), AllLights(0)
		{
		}

		DrawArgs(GameTime time, Camera* camera, List<Light*>* allLights, IGraphics* graphics, ISpriteBatch* spriteBatch)
			: Time(time), CurrentCamera(camera), AllLights(allLights), Graphics(graphics), SpriteBatch(spriteBatch)
		{
		}

		~DrawArgs()
		{
		}
	};
}
