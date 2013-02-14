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

			virtual void Play(ISound* sound, bool loop = false) = 0;
			virtual void Play3D(ISound* sound, const Vector3& position, bool loop = false) = 0;

			virtual void SetListenerPosition(
				const Vector3& position, 
				const Vector3& velocity, 
				const Vector3& forward, 
				const Vector3& up) = 0;

		};
	}
}