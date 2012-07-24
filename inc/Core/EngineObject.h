#pragma once

#include "Core/Object.h"
#include "Core/Engine.h"

namespace TikiEngine
{
	class EngineObject : public Object
	{
	public:

		EngineObject(Engine* engine)
			: engine(engine)
		{
		}

		virtual ~EngineObject()
		{
		}

	protected:

		Engine* engine;
	};
}