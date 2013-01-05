#pragma once

#include "Core/ISoundSystem.h"
#include "fmod/fmod.hpp"

namespace TikiEngine
{
	namespace Modules
	{
		using namespace FMOD;

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

			FMOD::Sound* LoadSound(cstring fileName);

		private:

			System* system;

			float musicVolume;
			float voiceVolume;
			float effectVolume;

		};
	}
}