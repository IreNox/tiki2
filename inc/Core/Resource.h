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

		protected:

			virtual void loadFromStream(IStream* stream) = 0;
			virtual void saveToStream(IStream* stream) = 0;
		};
	}
}