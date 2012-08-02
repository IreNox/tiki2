
#include "Core/TypeGlobals.h"
#include "Core/Material.h"

namespace TikiEngine
{
	namespace Resources
	{
		Material::Material(Engine* engine)
			: EngineObject(engine), shader(0)
		{
		}

		Material::~Material()
		{
			SafeRelease(&shader);
		}

		void Material::Apply()
		{
			shader->Apply();
		}

		void Material::UpdateDrawArgs(const DrawArgs& args, GameObject* gameObject)
		{
			if (!this->GetReady()) return;

			shader->ApplyVars(gameObject);
		}

		IShader* Material::GetShader()
		{
			return shader;
		}

		void Material::SetShader(IShader* shader)
		{
			SafeRelease(&this->shader);
			this->shader = shader;
			SafeAddRef(&this->shader);
		}

		bool Material::GetReady()
		{
			return shader->GetReady();
		}
	}
}