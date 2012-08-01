#pragma once

#include "Core/IResource.h"

#include "Core/Stream.h"
#include "Core/FileStream.h"

namespace TikiEngine
{
	namespace Resources
	{
		using namespace TikiEngine::IO;

		IResource::IResource(Engine* engine)
			: EngineObject(engine)
		{
		}

		IResource::~IResource()
		{
		}

		void IResource::LoadFromFile(wcstring fileName)
		{
			FileStream* stream = new FileStream(fileName, FM_Read);

			loadFromStream(stream);

			delete(stream);
		}

		void IResource::SaveToFile(wcstring fileName)
		{
			FileStream* stream = new FileStream(fileName, FM_Write);

			saveToStream(stream);

			delete(stream);

		}
	}
}