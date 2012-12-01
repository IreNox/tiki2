#pragma once

#include "Core/EngineObject.h"

namespace TikiEngine
{
	namespace Graphics
	{
		class IConstantBuffer : public EngineObject
		{
		public:

			IConstantBuffer(Engine* engine) : EngineObject(engine) {}
			virtual ~IConstantBuffer() {}

			template <typename T>
			inline T* MapT()
			{
#if _DEBUG
				if (sizeof(T) != this->GSize()) throw "Wrong size!";
#endif

				return (T*)this->Map();
			}

			virtual void* Map() = 0;
			virtual void Unmap() = 0;

			virtual void* GBuffer() = 0;
			virtual UInt32 GSize() = 0;

		};
	}
}