
#include "Graphics/Quad.h"

#include "Graphics/DllMain.h"

namespace TikiEngine
{
	namespace Graphics
	{
		#pragma region Vars
		PostProcessVertex Quad::quadVertices[4] =
		{
			-1.0f,  1.0f, 0.0f, 0.0f, 0.0f, // TL
			 1.0f,  1.0f, 0.0f, 1.0f, 0.0f, // TR
			-1.0f, -1.0f, 0.0f, 0.0f, 1.0f, // BL
			 1.0f, -1.0f, 0.0f, 1.0f, 1.0f, // BR
		};

		D3D11_INPUT_ELEMENT_DESC Quad::quadVertexElements[2] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};
		#pragma endregion

		#pragma region Class
		Quad::Quad(Engine* engine)
			: EngineObject(engine), vertexBuffer(0), shader(0), inputLayout(0)
		{
			vertexBuffer = new StaticBuffer<D3D11_BIND_VERTEX_BUFFER>(engine, sizeof(PostProcessVertex), 4, Quad::quadVertices);
		}

		Quad::~Quad()
		{
			SafeRelease(&shader);
			SafeRelease(&inputLayout);
			SafeRelease(&vertexBuffer);
		}
		#pragma endregion

		#pragma region Member - Shader
		IShader* Quad::GetShader()
		{
			return shader;
		}

		void Quad::SetShader(IShader* shader)
		{
			UInt32 temp;

			SafeRelease(&this->inputLayout);
			SafeRelease(&this->shader);

			SafeAddRef(
				(Shader*)shader,
				&this->shader
			);

			if (this->shader != 0)
			{
				this->shader->CreateLayout(
					Quad::quadVertexElements,
					2,
					&inputLayout,
					&temp
				);
			}
		}
		#pragma endregion

		#pragma region Member - RenderTargets
		void Quad::SetInput(const Dictionary<cstring, IRenderTarget*>* input)
		{
			UInt32 i = 0;
			while (i < input->Count())
			{
				auto kvp  = input->GetKVP(i);
				shader->SetTexture(kvp.GetKey(), kvp.GetValue());

				i++;
			}
		}

		void Quad::SetOutput(const Dictionary<UInt32, IRenderTarget*>* output)
		{
			UInt32 i = 0;
			while (i < output->Count())
			{
				auto kvp  = output->GetKVP(i);
				kvp.GetValue()->Apply(kvp.GetKey());

				i++;
			}
		}
		#pragma endregion

		#pragma region Member - Apply/Draw
		void Quad::Draw()
		{
			shader->Apply();
			vertexBuffer->Apply();

			DllMain::Context->IASetInputLayout(inputLayout);
			DllMain::Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

			DllMain::Context->Draw(4, 0);
		}
		#pragma endregion
	}
}