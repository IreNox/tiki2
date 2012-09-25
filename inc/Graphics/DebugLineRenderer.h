#pragma once

#include "Core/EngineObject.h"
#include "Core/List.h"
#include "Core/ColorVertex.h"

#include "Graphics/Shader.h"
#include "Graphics/RenderTarget.h"
#include "Graphics/DynamicBuffer.h"
#include "Graphics/VertexDeclaration.h"
#include "Graphics/DllMain.h"

namespace TikiEngine
{
	using namespace TikiEngine::Vertices;
	using namespace TikiEngine::Graphics;

	class DebugLineRenderer : public EngineObject
	{
	public:

		DebugLineRenderer(Engine* engine);
		~DebugLineRenderer();

		void Begin();

		void DrawLine(const Vector3& start, const Vector3& end, const Color& color);
		void DrawLine(List<Vector3>* points, const Color& color, bool lastToFirst = false);

		void End();

	private:

		List<ColorVertex> vertices;

		Shader* shader;
		VertexDeclaration* decl;
		DynamicBuffer<ColorVertex, D3D11_BIND_VERTEX_BUFFER>* vertexBuffer;

		RenderTarget* renderTarget;

	};
}