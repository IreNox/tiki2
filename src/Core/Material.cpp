
#include "Core/TypeGlobals.h"
#include "Core/Material.h"

namespace TikiEngine
{
	namespace Graphics
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

		void Material::UpdateDrawArgs(const DrawArgs& args)
		{
			if (!this->GetReady()) return;

			Matrix* worldMatrix = new Matrix(Matrix::Identity); //element->PRS.GetWorldMatrix();

			shader->SetMatrix("worldMatrix", *worldMatrix);

			delete(worldMatrix);
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