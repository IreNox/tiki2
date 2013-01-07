#pragma once

#include "Core/IResource.h"

#include "Core/Stream.h"
#include "Core/FileStream.h"

#include "Core/IContentManager.h"

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
			if (engine) engine->content->ReleaseResource(this);
		}

		void IResource::LoadFromFile(wcstring fileName)
		{
			FileStream* stream = new FileStream(fileName, FM_Read);

			try
			{
				loadFromStream(fileName, stream);
				this->fileName = fileName;
			}
			catch (const char* e)
			{
				delete(stream);
				throw e;
			}
			
			delete(stream);
		}

		void IResource::LoadFromStream(wcstring fileName, Stream* stream)
		{
			this->loadFromStream(fileName, stream);
		}

		void IResource::SaveToFile(wcstring fileName)
		{
			FileStream* stream = new FileStream(fileName, FM_Write);

			saveToStream(fileName, stream);

			delete(stream);

			this->fileName = fileName;
		}

		void IResource::SaveToStream(wcstring fileName, Stream* stream)
		{
			this->saveToStream(fileName, stream);
		}

		wstring IResource::GetFileName()
		{
			return fileName;
		}
	}
}