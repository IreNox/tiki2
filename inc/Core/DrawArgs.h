#pragma once

#include "Core/GameTime.h"

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

	struct DrawArgs
	{
		GameTime Time;

		Camera* CurrentCamera;

		IGraphics* Graphics;
		ISpriteBatch* SpriteBatch;

		DrawArgs(GameTime time, Camera* camera, IGraphics* graphics, ISpriteBatch* spriteBatch)
			: Time(time), CurrentCamera(camera), Graphics(graphics), SpriteBatch(spriteBatch)
		{
		}

		~DrawArgs()
		{
		}
	};
}