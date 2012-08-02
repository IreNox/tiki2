#pragma once

#include "Core/EngineObject.h"
#include "Core/IShader.h"

namespace TikiEngine
{
	namespace Resources
	{
		class Material : public EngineObject
		{
		public:

			Material(Engine* engine);
			~Material();

			virtual void Apply();

			virtual void UpdateDrawArgs(const DrawArgs& args, GameObject* gameObject);

			IShader* GetShader();
			void SetShader(IShader* shader);

			virtual bool GetReady();

		protected:

			IShader* shader;
		};
	}
}