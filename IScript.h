#pragma once

#include "Core/Component.h"

namespace TikiEngine
{
	namespace Components
	{
		class IScript : public Component
		{
		public:

			IScript(Engine* engine)
				: Component(engine)
			{
			}
			~IScript() {}
		};
	}
}