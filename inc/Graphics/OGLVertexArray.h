#pragma once

#include "Core/Engine.h"
#include "Core/InputElement.h"

#include "Graphics/DllMain.h"

namespace TikiEngine
{
	using namespace TikiEngine::Vertices;

	template<typename T>
	class OGLVertexArray : public EngineObject
	{
	public:

		OGLVertexArray(Engine* engine, InputElement* elements, UInt32 elementCount)
			: EngineObject(engine), vertexId(0), indexId(0)
		{
			DllMain::Info.glGenVertexArrays(1, &arrayId);
		}

		~OGLVertexArray()
		{
			if (vertexId)
			{
				//DllMain::Info.
			}
		}

	private:

		UInt32 arrayId;

		UInt32 vertexId;
		UInt32 indexId;

	};
}