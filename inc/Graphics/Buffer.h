#pragma once

#include "Core/Object.h"
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
			Buffer(Engine* engine, UINT size);
			virtual ~Buffer();

			void Apply(UINT offset) const;

			void Copy(void* data, UINT size, UINT index);
			void Allocate(void* data, UINT count, UINT* index);

			UINT GetElementSize() const;
			ID3D11Buffer* GetBuffer() const;

		protected:
			Engine* engine;

			ID3D11Buffer* buffer;
			ID3D11DeviceContext* context;

			virtual void fillBufferDesc(D3D11_BUFFER_DESC* desc) = 0;
			virtual ID3D11Buffer* createBuffer(UINT size, void* data) = 0;

		private:
			UINT bufferSize;
			UINT bufferUsage;

			UINT elementSize;

			D3D11_BUFFER_DESC bufferDesc;

			void writeBuffer(void* addData, UINT dataSize, UINT index);
			void resizeBuffer(void* addData, UINT dataSize);
		};
	}
}