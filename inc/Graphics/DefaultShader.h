
#include "Shader.h"

namespace TikiEngine
{
	class Engine;

	namespace Effects
	{
		class DefaultShader : public Shader
		{
		public:
			DefaultShader(Engine* g);
			~DefaultShader();
		};
	}
}