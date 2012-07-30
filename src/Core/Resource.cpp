#pragma once

#include "Core/Resource.h"

#include "Core/Stream.h"
#include "Core/FileStream.h"

namespace TikiEngine
{
	namespace Resources
	{
		using namespace TikiEngine::IO;

		Resource::Resource(Engine* engine)
			: EngineObject(engine)
		{
		}

		Resource::~Resource()
		{
		}

		void Resource::LoadFromFile(wstring fileName)
		{
			WCHAR cd[MAX_PATH];

			_wgetcwd(cd, MAX_PATH);
			wstring path = wstring(cd) + L"\\" + fileName;

			FileStream stream = FileStream(path, FM_Read);

			loadFromStream(&stream);

			stream.Close();
		}

		void Resource::SaveToFile(wstring fileName)
		{

		}
	}
}