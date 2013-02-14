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

			void Play(ISound* sound);
			void Play3D(ISound3D* sound, const Vector3& position);

			void SetListenerPosition(
				const Vector3& position, 
				const Vector3& velocity, 
				const Vector3& forward, 
				const Vector3& up);

			FMOD::Sound* LoadSound(Stream* stream);
			FMOD::Sound* LoadSound3D(Stream* stream);

		private:

			System* system;

			float musicVolume;
			float voiceVolume;
			float effectVolume;

		};
	}
}