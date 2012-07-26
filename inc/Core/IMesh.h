#pragma once

#include "Core/EngineObject.h"

namespace TikiEngine
{
	namespace Graphics
	{
		class IMesh : public EngineObject
		{
		public:

			virtual void SetVertexData(void* data, UInt32 dataLength) = 0;
			virtual void SetVertexDeclaration(void* data, UInt32 dataLength) = 0;

			virtual bool GetReady() = 0;
		};
	}
}

