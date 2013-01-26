#pragma once

#include "Core/TikiObject.h"
#include "Core/Engine.h"

namespace TikiEngine
{
	class EngineObject : public TikiObject
	{
	public:

		EngineObject(Engine* engine) : engine(engine) { }
		~EngineObject() { }

		inline Engine* GetEngine()
		{
			return engine;
		}

	protected:

		Engine* engine;
	};
}