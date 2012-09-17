#pragma once

#include "Core/IModule.h"
#include "Core/ISound.h"

namespace TikiEngine
{
	namespace Modules
	{
		using TikiEngine::Resources::ISound;

		class ISoundSystem : public IModule
		{
		public:

			ISoundSystem(Engine* engine) : IModule(engine) {}
			~ISoundSystem() {}

			virtual void PlaySound(ISound* sound) = 0;

		};
	}
}