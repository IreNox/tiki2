#pragma once

#include "Core/DrawArgs.h"
#include "Core/IComponent.h"

namespace TikiEngine
{
	namespace Components
	{
		class IRenderer : public IComponent
		{
		public:

			IRenderer(Engine* engine)
				: IComponent(engine)
			{
			}
			virtual ~IRenderer() {}

			virtual void Draw(const DrawArgs& args) = 0;
		};
	}
}

