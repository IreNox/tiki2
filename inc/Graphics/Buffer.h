#pragma once

#include "Core/TypeDef.h"
#include "Core/EngineObject.h"

#include "Graphics/VertexDeclaration.h"

namespace TikiEngine
{
	class Engine;

	namespace Buffer
	{
		using namespace Vertices;

		class Buffer : public Object
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
			Engine* engine;

			ID3D11Buffer* buffer;
			ID3D11DeviceContext* context;

			virtual void fillBufferDesc(D3D11_BUFFER_DESC* desc) = 0;
			virtual ID3D11Buffer* createBuffer(UInt32 size, void* data) = 0;

		private:
			UINT bufferSize;
			UINT bufferUsage;

			UINT elementSize;

			D3D11_BUFFER_DESC bufferDesc;

			void writeBuffer(void* addData, UInt32 dataSize, UInt32 index);
			void resizeBuffer(void* addData, UInt32 dataSize);
		};
	}
}