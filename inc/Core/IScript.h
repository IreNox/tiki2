#pragma once

#include "Core/Component.h"

namespace TikiEngine
{
	namespace Scripts
	{
		using namespace TikiEngine::Components;

		class IScript : public Component
		{
		public:

			IScript(Engine* engine, GameObject* gameObject)
				: Component(engine, gameObject, CT_Script)
			{
			}
			~IScript() {}

			bool GetReady()
			{
				return true;
			}
		};
	}
}