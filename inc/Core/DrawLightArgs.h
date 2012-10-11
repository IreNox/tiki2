#pragma once

#include "Core/List.h"

#include "Core/LightProperties.h"

namespace TikiEngine
{
	namespace Components
	{
		class Light;
	}
	using TikiEngine::Components::Light;

	using TikiEngine::Graphics::LightProperties;

	// Implementation in AllArgs.cpp
	struct DrawLightArgs
	{
		static const DrawLightArgs Empty;

		bool IsDirty;

		Int32 MainLightIndex;

		List<Light*>* SceneLights;
		LightProperties Properties;

		DrawLightArgs(bool isDirty, List<Light*>* sceneLights, Int32 mainLight, LightProperties properties)
			: IsDirty(isDirty), SceneLights(sceneLights), MainLightIndex(mainLight), Properties(properties)
		{
		}

	private:

		DrawLightArgs()
			: IsDirty(false), SceneLights(0), Properties(), MainLightIndex(-1)
		{
		}

	};
}