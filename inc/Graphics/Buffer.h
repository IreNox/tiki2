#pragma once

#include "Core/TypeDef.h"
#include "Core/EngineObject.h"

#include "Graphics/VertexDeclaration.h"

namespace TikiEngine
{
	namespace Graphics
	{
		using namespace Vertices;

		class Buffer : public EngineObject
		{
		public:

			Buffer(Engine* engine, UInt32 size);
			virtual ~Buffer();

			void Apply(UInt32 offset) const;
			
			void Copy(void* data, UInt32 size, UInt32 index);
			void Allocate(void* data, UInt32 count, UInt32* index);

			UINT GetElementSize() const;
			ID3D11Buffer* GetBuffer() const;

		protected:

			ID3D11Buffer* buffer;

			virtual ID3D11Buffer* createBuffer(UInt32 size, void* data) = 0;

		private:

			UINT bufferSize;
			UINT bufferUsage;

			UINT elementSize;

			void writeBuffer(void* addData, UInt32 dataSize, UInt32 index);
			void resizeBuffer(void* addData, UInt32 dataSize);

		};
	}
}