#pragma once

#include "Core/ISound.h"
#include "fmod/fmod.hpp"

namespace TikiEngine
{
	namespace Modules
	{
		using namespace FMOD;

		class SoundModule : public ISound
		{
		public:

			SoundModule(Engine* engine);
			~SoundModule();

			bool Initialize(EngineDescription& desc);

			void Begin();
			void End();

			void Dispose();

			void Bla();

		private:

			System* system;

		};
	}
}