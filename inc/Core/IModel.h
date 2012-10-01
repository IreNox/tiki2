#pragma once

#include "Core/IResource.h"

namespace TikiEngine
{
	namespace Resources
	{
		class IModel : public IResource
		{
		public:

			IModel(Engine* engine) : IResource(engine) {}
			~IModel() {}

		};
	}
}