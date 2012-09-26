#pragma once

#include "Core/Component.h"

namespace TikiEngine
{
	namespace Components
	{
		class ITerrainRenderer : public Component
		{
		public:

			ITerrainRenderer(Engine* engine, GameObject* gameObject)
				: Component(engine, gameObject, CT_Renderer)
			{
			}

			~ITerrainRenderer() {}
			
		};
	}
}