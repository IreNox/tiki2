#pragma once

#include "Core/TypeGlobals.h"
#include "Core/EngineObject.h"
#include "Core/HelperLog.h"

#include "Graphics/DllMain.h"

namespace TikiEngine
{
	namespace Graphics
	{
		template <class T, UINT TBinding>
		class DynamicBuffer : public EngineObject
		{
		public:

			#pragma region Class
			DynamicBuffer(Engine* engine)
				: EngineObject(engine), buffer(0), elementCount(0)
			{
			}

			~DynamicBuffer()
			{
				releaseBuffer();
			}
			#pragma endregion

			#pragma region Member
			T* Map(UInt32 count)
			{
				if (count == 0) return 0;

				if (count > elementCount)
				{
					elementCount = count;
					this->createBuffer();
				}

#if TIKI_DX10
				void* mapped;
				HRESULT r = buffer->Map(D3D10_MAP_WRITE_DISCARD, 0, &mapped);
#elif TIKI_DX11
				D3D11_MAPPED_SUBRESOURCE mapped;

				HRESULT r = DllMain::Context->Map(
					buffer,
					0,
					D3D11_MAP_WRITE_DISCARD,
					0,
					&mapped
				);
#elif TIKI_OGL
				glBindBuffer(TBinding, buffer);
				void* mapped = glMapBuffer(TBinding, GL_WRITE_ONLY);

				HRESULT r = (mapped != 0 ? S_OK : -1);
#endif

				if (FAILED(r))
				{
					engine->HLog.WriteError("Can't map DynamicBuffer", 0);
				}

#if TIKI_DX10 || TIKI_OGL
				return (T*)mapped;
#elif TIKI_DX11
				return (T*)mapped.pData;
#endif
			}

			void Unmap()
			{
#if TIKI_DX10
				if (buffer) buffer->Unmap();
#elif TIKI_DX11
				if (buffer) DllMain::Context->Unmap(buffer, 0);
#elif TIKI_OGL
				if (buffer)
				{
					glUnmapBuffer(TBinding);
					glBindBuffer(TBinding, 0);
				}
#endif
			}

			TDX_Buffer* GetBuffer()
			{
				return buffer;
			}
			#pragma endregion

			#pragma region Member - Apply
			inline void Apply()
			{
#if TIKI_DX10 || TIKI_DX11
				if (TBinding == TIKI_VERTEX_BUFFER)
				{
					UInt32 offset = 0;
					UInt32 stride = sizeof(T);
					TDX_Buffer* d3dbuffer = buffer;

					DllMain::Context->IASetVertexBuffers(0, 1, &d3dbuffer, &stride, &offset);
				}
				else if (TBinding == TIKI_INDEX_BUFFER)
				{
					DllMain::Context->IASetIndexBuffer(buffer, DXGI_FORMAT_R32_UINT, 0);
				}
#elif TIKI_OGL
				glBindBuffer(TBinding, buffer);
#endif
			}
			#pragma endregion

		private:

			UInt32 elementCount;
#if TIKI_OGL
			TDX_Buffer buffer;
#else
			TDX_Buffer* buffer;
#endif

			#pragma region Private Member - CreateBuffer/ReleaseBuffer - OpenGL
#if TIKI_OGL
			void createBuffer()
			{
				glGenBuffers(1, &buffer);
				glBindBuffer(TBinding, buffer);
				glBufferData(TBinding, elementCount * sizeof(T), 0, GL_DYNAMIC_DRAW);
			}

			void releaseBuffer()
			{
				glDeleteBuffers(1, &buffer);
			}
#endif
			#pragma endregion

			#pragma region Private Member - CreateBuffer/ReleaseBuffer - DirectX
#if TIKI_DX10 || TIKI_DX11
			void createBuffer()
			{
				if (buffer != 0)
					releaseBuffer();

#if TIKI_DX10
				D3D10_BUFFER_DESC desc;
				desc.Usage = D3D10_USAGE_DYNAMIC;
				desc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
#else
				D3D11_BUFFER_DESC desc;
				desc.Usage = D3D11_USAGE_DYNAMIC;
				desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
				desc.StructureByteStride = 0;
#endif
				desc.BindFlags = TBinding;
				desc.ByteWidth = sizeof(T) * elementCount;
				desc.MiscFlags = 0;
				
				HRESULT r = DllMain::Device->CreateBuffer(
					&desc,
					0,
					&buffer
				);

				if (FAILED(r)) 
				{
					engine->HLog.WriteError("Can't create FullSizeBuffer", 0);
				}
			}

			void releaseBuffer()
			{
				SafeRelease(&buffer);
			}
#endif
			#pragma endregion

		};
	}
}