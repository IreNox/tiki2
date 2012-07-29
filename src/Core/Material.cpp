
#include "Core/Material.h"

namespace TikiEngine
{
	namespace Graphics
	{
		Material::Material(Engine* engine)
			: EngineObject(engine)
		{
		}

		Material::~Material()
		{
			if (shader != 0)
			{
				shader->Release();
			}
		}

		void Material::Apply()
		{
			shader->Apply();
		}

		void Material::UpdateDrawArgs(const DrawArgs& args)
		{
			//TODO: Update shader vars
		}

		IShader* Material::GetShader()
		{
			return shader;
		}

		void Material::SetShader(IShader* shader)
		{
			if (this->shader != 0)
			{
				this->shader->Release();
			}

			this->shader = shader;

			if (this->shader != 0)
			{
				this->shader->AddRef();
			}
		}

		bool Material::GetReady()
		{
			return shader->GetReady();
		}
	}
}