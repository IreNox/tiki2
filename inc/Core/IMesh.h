#pragma once

#include "Core/EngineObject.h"
#include "Core/InputElement.h"

namespace TikiEngine
{
	namespace Graphics
	{
		using TikiEngine::Vertices::InputElement;

		class IMesh : public EngineObject
		{
		public:

			IMesh(Engine* engine) 
				: EngineObject(engine)
			{
			}
			virtual ~IMesh() {}

			virtual void SetVertexData(void* data, UInt32 dataLength) = 0;
			virtual void SetVertexDeclaration(InputElement* elements, UInt32 count) = 0;

			virtual bool GetReady() = 0;
		};
	}
}

