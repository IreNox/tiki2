#pragma once

#include "Core/ISoundSystem.h"
#include "Core/Stream.h"
#include "fmod/fmod.hpp"

namespace TikiEngine
{
	namespace Modules
	{
		using namespace FMOD;
		using namespace TikiEngine::IO;

		class SoundModule : public ISoundSystem
		{
		public:

			SoundModule(Engine* engine);
			~SoundModule();

			bool Initialize(EngineDescription& desc);

			void Begin();
			void End();

			void Dispose();

			void Play(ISound* sound, bool loop = false);
			void Play3D(ISound* sound, const Vector3& position, bool loop = false);

			void SetListenerPosition(
				const Vector3& position, 
				const Vector3& velocity, 
				const Vector3& forward, 
				const Vector3& up);

		private:

			FMOD::Sound* CreateSound(ISound* sound);
			FMOD::Sound* CreateSound3D(ISound* sound);

			System* system;

			float musicVolume;
			float voiceVolume;
			float effectVolume;

		};
	}
}