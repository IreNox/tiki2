
#include "Sound/Sound.h"
#include "Sound/DllMain.h"

#include "Core/TypeGlobals.h"

namespace TikiEngine
{
	namespace Resources
	{
		#pragma region Class
		Sound::Sound(Engine* engine)
			: ISound(engine), data(0)
		{
		}

		Sound::~Sound()
		{
			SafeDeleteArray(&data);
		}
		#pragma endregion

		#pragma region Member


		void* Sound::GetNativeResource()
		{
			return data;
		}

		bool Sound::GetReady()
		{
			return true;
		}
		#pragma endregion

		#pragma region Member - Protected Member
		void Sound::loadFromStream(wcstring fileName, Stream* stream)
		{
			data = TIKI_NEW char[stream->GetLength() + 4];
			*(UInt32*)data = (UInt32)stream->GetLength();
			stream->Read(data + 4, 0, stream->GetLength());
			//sound = DllMain::Module->LoadSound(stream);
		}

		void Sound::saveToStream(wcstring fileName, Stream* stream)
		{
			throw "Not implemented";
		}
		#pragma endregion
	}
}