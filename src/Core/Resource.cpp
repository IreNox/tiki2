#pragma once

#include "Core/Resource.h"

namespace TikiEngine
{
	namespace Resources
	{
		Resource::Resource(Engine* engine)
			: EngineObject(engine)
		{
		}

		Resource::~Resource()
		{
		}

		void Resource::LoadFromFile(wstring fileName)
		{

		}

		void Resource::SaveToFile(wstring fileName)
		{

		}
	}
}