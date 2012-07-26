#pragma once

#include "Core/EngineObject.h"
#include "Core/IShader.h"

namespace TikiEngine
{
	namespace Graphics
	{
		class Material : public EngineObject
		{
		public:

			Material(Engine* engine);
			~Material();

			IShader* GetShader();
			void SetShader(IShader* shader);

			virtual bool GetReady();

		protected:

			IShader* shader;
		};
	}
}