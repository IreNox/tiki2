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

			FMOD::Sound* LoadSound(Stream* stream);

		private:

			System* system;

			float musicVolume;
			float voiceVolume;
			float effectVolume;

		};
	}
}