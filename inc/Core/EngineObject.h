#pragma once

#include "Core/TikiObject.h"
#include "Core/Engine.h"

namespace TikiEngine
{
	class EngineObject : public TikiObject
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