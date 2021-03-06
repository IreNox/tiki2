#pragma once

#include "Core/ISound.h"
#include "fmod/fmod.hpp"

namespace TikiEngine
{
	namespace Resources
	{
		class Sound : public ISound
		{
		public:

			Sound(Engine* engine);
			~Sound();

			void* GetNativeResource();
			bool GetReady();

		protected:

			void loadFromStream(wcstring fileName, Stream* stream);
			void saveToStream(wcstring fileName, Stream* stream);

		private:

			char* data;


		};
	}
}