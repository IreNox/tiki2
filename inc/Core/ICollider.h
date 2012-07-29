#pragma once

#include "Core/EngineObject.h"

namespace TikiEngine
{
	namespace Components
	{
		class ICollider : public EngineObject
		{
		public:

			ICollider(Engine* engine)
				: EngineObject(engine)
			{
			}
			~ICollider() {}

			virtual void ReplaceMe() = 0;
		};
	}
}