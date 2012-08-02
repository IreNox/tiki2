#pragma once

#include "Core/EngineObject.h"
#include "Core/Stream.h"

namespace TikiEngine
{
	namespace Resources
	{
		using TikiEngine::IO::Stream;

		class IResource : public EngineObject
		{
		public:

			IResource(Engine* engine);
			~IResource();

			virtual void LoadFromFile(wcstring fileName);
			virtual void SaveToFile(wcstring fileName);

			virtual void* GetNativeResource() = 0;

			virtual bool GetReady() = 0;

		protected:

			virtual void loadFromStream(wcstring fileName, Stream* stream) = 0;
			virtual void saveToStream(wcstring fileName, Stream* stream) = 0;
		};
	}
}