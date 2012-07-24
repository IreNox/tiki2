
#include "Core/Engine.h"
#include "Graphics/DefaultShader.h"

namespace TikiEngine
{
	namespace Effects
	{
		DefaultShader::DefaultShader(Engine* engine)
			: Shader(engine, wstring(L"Data/Effects/default.fx"))
		{
		}
	}
}