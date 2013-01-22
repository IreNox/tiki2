
#include "Graphics/DebugLineRenderer.h"
#include "Graphics/GraphicsModule.h"

#include "Core/IContentManager.h"

namespace TikiEngine
{
	DebugLineRenderer::DebugLineRenderer(Engine* engine)
		: EngineObject(engine)
	{
		shader = (Shader*)engine->content->LoadShader(L"os_color");
		shader->SetMatrix("worldMatrix", Matrix::Identity);
		shader->AddRef();

		List<InputElement> elements = List<InputElement>(ColorVertex::Declaration, ColorVertex::DeclarationCount, true);
		decl = new VertexDeclaration(engine, shader, &elements);

		vertexBuffer = new DynamicBuffer<ColorVertex, TIKI_VERTEX_BUFFER>(engine);
	}

	DebugLineRenderer::~DebugLineRenderer()
	{
		SafeRelease(&decl);
		SafeRelease(&shader);
		SafeRelease(&vertexBuffer);
	}

	void DebugLineRenderer::Begin()
	{
		vertices.Clear();
	}

	void DebugLineRenderer::DrawLine(const Vector3& start, const Vector3& end, const Color& color)
	{
		ColorVertex data[2] = {
			{ start.X, start.Y, start.Z, color.R, color.G, color.B, color.A },
			{ end.X,   end.Y,   end.Z,   color.R, color.G, color.B, color.A },
		};

		vertices.Add(data[0]);
		vertices.Add(data[1]);
	}

	void DebugLineRenderer::DrawLine(List<Vector3>* points, const Color& color, bool lastToFirst)
	{
		UInt32 i = 1;
		while (i < points->Count())
		{
			Vector3 pos1 = points->Get(i - 1);
			Vector3 pos2 = points->Get(i);
			ColorVertex vertex[2] = {
				{ pos1.X, pos1.Y, pos1.Z, color.R, color.G, color.B, color.A },
				{ pos2.X, pos2.Y, pos2.Z, color.R, color.G, color.B, color.A }
			};

			vertices.Add(vertex[0]);
			vertices.Add(vertex[1]);

			i++;
		}

		if (lastToFirst)
		{
			Vector3 pos1 = points->Get(i - 1);
			Vector3 pos2 = points->Get(0);
			ColorVertex vertex[2] = {
				{ pos1.X, pos1.Y, pos1.Z, color.R, color.G, color.B, color.A },
				{ pos2.X, pos2.Y, pos2.Z, color.R, color.G, color.B, color.A }
			};

			vertices.Add(vertex[0]);
			vertices.Add(vertex[1]);
		}
	}

	void DebugLineRenderer::End()
	{
		UInt32 count = vertices.Count();
		if (count == 0) return;

		ColorVertex* data = vertices.ToArray();
		ColorVertex* bufferData = vertexBuffer->Map(count);

		memcpy(
			bufferData,
			data,
			sizeof(ColorVertex) * count
		);

		vertexBuffer->Unmap();
		delete[](data);

		DllMain::Context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINELIST);

		vertexBuffer->Apply();
		shader->Apply();
		decl->Apply();

		DllMain::ModuleGraphics->GetInterfaceTarget()->Apply(0);
		DllMain::Context->Draw(count, 0);
	}


}