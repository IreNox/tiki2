
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
		#pragma endregion

		#pragma region Class
		Quad::Quad(Engine* engine, IShader* shader)
			: EngineObject(engine), vertexBuffer(0), shader(shader), decl(0)
		{
			decl = TIKI_NEW VertexDeclaration(engine, shader, PostProcessVertex::Declaration, PostProcessVertex::DeclarationCount);
			vertexBuffer = TIKI_NEW StaticBuffer<TIKI_VERTEX_BUFFER>(engine, sizeof(PostProcessVertex), 4, Quad::quadVertices);
			shader->AddRef();
		}

		Quad::~Quad()
		{
			SafeRelease(&decl);
			SafeRelease(&shader);
			SafeRelease(&vertexBuffer);
		}
		#pragma endregion

		#pragma region Member - Shader
		IShader* Quad::GetShader()
		{
			return shader;
		}
		#pragma endregion

		#pragma region Member - RenderTargets
		void Quad::SetInput(const Dictionary<string, IRenderTarget*>& input)
		{
			UInt32 i = 0;
			while (i < input.Count())
			{
				const KeyValuePair<string, IRenderTarget*>& kvp = input.GetKVPCRef(i);
				shader->SetTexture(kvp.GetKey().CStr(), kvp.GetValue());

				i++;
			}
		}

		void Quad::SetOutput(const Dictionary<UInt32, IRenderTarget*>& output)
		{
			UInt32 i = 0;
			while (i < output.Count())
			{
				const KeyValuePair<UInt32, IRenderTarget*>& kvp = output.GetKVPCRef(i);
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
			decl->Apply();

#if TIKI_DX10 || TIKI_DX11
			DllMain::Context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

			DllMain::Context->Draw(4, 0);
#elif TIKI_OGL
			glDrawArrays(
				GL_TRIANGLE_STRIP,
				0,
				4
			);
#endif
		}
		#pragma endregion
	}
}