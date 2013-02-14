
#include "Sound/Sound3D.h"
#include "Sound/DllMain.h"

#include "Core/TypeGlobals.h"

namespace TikiEngine
{
	namespace Resources
	{
		#pragma region Class
		Sound3D::Sound3D(Engine* engine)
			: ISound3D(engine), data(0)
		{
		}

		Sound3D::~Sound3D()
		{
			SafeDeleteArray(&data);
		}

		void Sound3D::CreateInstance(ISound3D* obj)
		{

		}
		#pragma endregion

		#pragma region Member
		float Sound3D::GetDuration()
		{
			return 0.0f;
		}

		void* Sound3D::GetNativeResource()
		{
			return data;
		}

		bool Sound3D::GetReady()
		{
			return true;
		}
		#pragma endregion

		#pragma region Member - Protected Member
		void Sound3D::loadFromStream(wcstring fileName, Stream* stream)
		{
			data = TIKI_NEW char[stream->GetLength() + 4];
			*(UInt32*)data = stream->GetLength();
			stream->Read(data + 4, 0, stream->GetLength());
		}

		void Sound3D::saveToStream(wcstring fileName, Stream* stream)
		{
			throw "Not implemented";
		}
		#pragma endregion
	}
}