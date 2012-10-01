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

			virtual bool GetIndexData(UInt32** indices, UInt32* size) = 0;
			virtual bool GetVertexData(void** vertices, UInt32* size) = 0;

		};
	}
}