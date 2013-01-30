#pragma once

#include "Core/Engine.h"
#include "Core/HelperLog.h"
#include "Core/IConstantBuffer.h"

#include "Graphics/DllMain.h"

namespace TikiEngine
{
	namespace Graphics
	{
		template <typename T>
		class ConstantBuffer : public IConstantBuffer
		{
		public:

			#pragma region Class
			ConstantBuffer(Engine* engine, UInt32 size = 0)
				: IConstantBuffer(engine), buffer(0), size(size)
			{
				if (!this->size) this->size = sizeof(T);

				createBuffer();
			}

			~ConstantBuffer()
			{
				releaseBuffer();
			}
			#pragma endregion

			#pragma region Member
			inline void* Map()
			{
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
				glBindBuffer(GL_UNIFORM_BUFFER, buffer);
				void* mapped = glMapBuffer(GL_UNIFORM_BUFFER, GL_WRITE_ONLY);

				HRESULT r = (mapped != 0 ? S_OK : -1);
#endif

				if (FAILED(r))
				{
					engine->HLog.WriteError("Can't map ConstantBuffer", 0);
				}

#if TIKI_DX10 || TIKI_OGL
				return (T*)mapped;
#elif TIKI_DX11
				return (T*)mapped.pData;
#endif
			}

			inline T* MapTI()
			{
				return (T*)this->Map();
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
					glUnmapBuffer(GL_UNIFORM_BUFFER);
					glBindBuffer(GL_UNIFORM_BUFFER, 0);
				}
#endif
			}

			inline void* GBuffer() { return (void*)buffer; }
			inline UInt32 GSize() { return size; }
			#pragma endregion

		private:

			UInt32 size;
#if TIKI_OGL
			TDX_Buffer buffer;
#else
			TDX_Buffer* buffer;
#endif

			#pragma region Private - Create/Release - OpenGL
#if TIKI_OGL
			void createBuffer()
			{
				glGenBuffers(1, &buffer);
				glBindBuffer(GL_UNIFORM_BUFFER, buffer);
				glBufferData(GL_UNIFORM_BUFFER, sizeof(T), 0, GL_DYNAMIC_DRAW);
			}

			void releaseBuffer()
			{
				glDeleteBuffers(1, &buffer);
			}
#endif
			#pragma endregion

			#pragma region Private - Create/Release - DirectX
#if TIKI_DX10 || TIKI_DX11
			void createBuffer()
			{
#if TIKI_DX10
				D3D10_BUFFER_DESC desc;
				desc.Usage = D3D10_USAGE_DYNAMIC;
				desc.BindFlags = D3D10_BIND_CONSTANT_BUFFER;
				desc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
#else
				D3D11_BUFFER_DESC desc;
				desc.Usage = D3D11_USAGE_DYNAMIC;
				desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
				desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
				desc.StructureByteStride = 0;
#endif
				desc.ByteWidth = size;
				desc.MiscFlags = 0;

				HRESULT r = DllMain::Device->CreateBuffer(
					&desc,
					0,
					&buffer
				);

				if (FAILED(r)) 
				{
					engine->HLog.WriteError("Can't create ConstantBuffer", 0);
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