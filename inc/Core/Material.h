#pragma once

#include "Core/EngineObject.h"
#include "Core/IShader.h"

namespace TikiEngine
{
	namespace Graphics
	{
		using namespace TikiEngine::Resources;

		class Material : public EngineObject
		{
		public:

			Material(Engine* engine);
			~Material();

			virtual void Apply();

			virtual void UpdateDrawArgs(const DrawArgs& args);

			IShader* GetShader();
			void SetShader(IShader* shader);

			virtual bool GetReady();

		protected:

			IShader* shader;
		};
	}
}