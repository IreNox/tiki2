
#include "Graphics/Quad.h"

#include "Graphics/DllMain.h"

namespace TikiEngine
{
	namespace Graphics
	{
		#pragma region Vars
		PostProcessVertex Quad::quadVertices[6] =
		{
			 1.0f,  1.0f, 0.0f, 1.0f, 0.0f, // TR
			-1.0f,  1.0f, 0.0f, 0.0f, 0.0f, // TL
			-1.0f, -1.0f, 0.0f, 0.0f, 1.0f, // BL
			 1.0f, -1.0f, 0.0f, 1.0f, 1.0f, // BR
			-1.0f, -1.0f, 0.0f, 0.0f, 1.0f, // BL
			 1.0f,  1.0f, 0.0f, 1.0f, 0.0f, // TR
		};

		D3D11_INPUT_ELEMENT_DESC Quad::quadVertexElements[2] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};
		#pragma endregion

		#pragma region Class
		Quad::Quad(Engine* Engine)
			: EngineObject(engine), vertexBuffer(0), shader(0), inputLayout(0), renderTarget(0)
		{
			UInt32 temp;

			vertexBuffer = new VertexBuffer(engine, sizeof(PostProcessVertex), false);
			vertexBuffer->Allocate(
				Quad::quadVertices,
				6,
				&temp
			);
		}

		Quad::~Quad()
		{
			SafeRelease(&shader);
			SafeRelease(&inputLayout);
			SafeRelease(&renderTarget);
			SafeRelease(&vertexBuffer);
		}
		#pragma endregion

		#pragma region Member - Get/Set
		IShader* Quad::GetShader()
		{
			return shader;
		}

		void Quad::SetShader(IShader* shader)
		{
			UInt32 temp;

			SafeRelease(&this->inputLayout);
			SafeRelease(&this->shader);

			this->shader = (Shader*)shader;

			if (this->shader != 0)
			{
				this->shader->AddRef();
				this->shader->CreateLayout(
					Quad::quadVertexElements,
					2,
					&inputLayout,
					&temp
				);
			}
		}

		IRenderTarget* Quad::GetRenderTerget()
		{
			return renderTarget;
		}

		void Quad::SetRenderTarget(IRenderTarget* renderTarget)
		{
			SafeRelease(&this->renderTarget);

			this->renderTarget = (RenderTarget*)renderTarget;
			SafeAddRef(&this->renderTarget);
		}
		#pragma endregion

		#pragma region Member - Draw
		void Quad::Draw()
		{
			renderTarget->Apply(0);
			shader->Apply();
			vertexBuffer->Apply(0);

			DllMain::Context->IASetInputLayout(inputLayout);
			DllMain::Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
			DllMain::Context->Draw(6, 0);
		}
		#pragma endregion
	}
}