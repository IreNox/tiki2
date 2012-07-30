#pragma once

#include "Core/EngineObject.h"
#include "Core/Stream.h"

namespace TikiEngine
{
	namespace Resources
	{
		using TikiEngine::IO::Stream;

		class Resource : public EngineObject
		{
		public:

			Resource(Engine* engine);
			~Resource();

			virtual void LoadFromFile(wstring fileName);
			virtual void SaveToFile(wstring fileName);

			virtual void* GetNativeResource() = 0;

			virtual bool GetReady() = 0;

		protected:

			virtual void loadFromStream(Stream* stream) = 0;
			virtual void saveToStream(Stream* stream) = 0;
		};
	}
}