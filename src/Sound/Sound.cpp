
#include "Sound/Sound.h"
#include "Sound/DllMain.h"

#include "Core/TypeGlobals.h"

namespace TikiEngine
{
	namespace Resources
	{
		#pragma region Class
		Sound::Sound(Engine* engine)
			: ISound(engine), sound(0)
		{
		}

		Sound::~Sound()
		{
		}
		#pragma endregion

		#pragma region Member
		float Sound::GetDuration()
		{
			UInt32 length;			
			sound->getLength(&length, FMOD_TIMEUNIT_MS);

			return (float)length / 1000.0f;
		}

		void* Sound::GetNativeResource()
		{
			return sound;
		}

		bool Sound::GetReady()
		{
			return (sound != 0);
		}
		#pragma endregion

		#pragma region Member - Protected Member
		void Sound::loadFromStream(wcstring fileName, Stream* stream)
		{
			/*UInt32 len = stream->GetLength();
			char* data = new char[len];
			stream->Read(data, 0, len);*/

			//string str = StringWtoA(fileName);

			sound = DllMain::Module->LoadSound(stream); //str.c_str()

			//delete(sound);
		}

		void Sound::saveToStream(wcstring fileName, Stream* stream)
		{
			throw "Not implemented";
		}
		#pragma endregion
	}
}