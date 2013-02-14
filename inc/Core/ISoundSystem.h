#pragma once

#include "Core/IModule.h"
#include "Core/ISound.h"
#include "Core/ISound3D.h"

namespace TikiEngine
{
	namespace Modules
	{
		using TikiEngine::Resources::ISound;
		using TikiEngine::Resources::ISound3D;

		class ISoundSystem : public IModule
		{
		public:

			ISoundSystem(Engine* engine) : IModule(engine) {}
			~ISoundSystem() {}

			virtual void Play(ISound* sound) = 0;
			virtual void Play3D(ISound3D* sound, const Vector3& position) = 0;

			virtual void SetListenerPosition(
				const Vector3& position, 
				const Vector3& velocity, 
				const Vector3& forward, 
				const Vector3& up) = 0;

		};
	}
}