
#include "Core/Material.h"
#include "Core/GameObject.h"

#include "Graphics/Shader.h"

#if TIKI_OGL
#include "Graphics/OGLGraphicsModule.h"
#else
#include "Graphics/GraphicsModule.h"
#endif

#include "Graphics/CBObjectData.h"

namespace TikiEngine
{
	namespace Resources
	{
		void Shader::ApplyVars(GameObject* gameObject, Material* material, const Matrix& localMatrix)
		{
			if (type == ST_Object)
			{
				CBObjectData* objData = DllMain::ModuleGraphics->GetCBufferObject()->MapT<CBObjectData>();

				gameObject->PRS.FillWorldMatrix(&objData->WorldM);
				objData->WorldM = Matrix::Multiply(objData->WorldM, localMatrix);

				objData->WorldMIT = Matrix::Transpose(
					Matrix::Invert(objData->WorldM)
					);

				if (material)
				{
					objData->UseDiffuse = (material->TexDiffuse != 0);
					objData->UseLightMap = (material->TexLightMap != 0);
					objData->UseNormalMap = (material->TexNormalMap != 0);
					objData->UseSpecularMap = (material->TexSpecularMap != 0);
					//objData->FlipTexcoordV = material->FlipTexcorrdV;

					if (objData->UseDiffuse) this->SetTexture("TexDiffuse", material->TexDiffuse);
					if (objData->UseLightMap) this->SetTexture("TexLightMap", material->TexLightMap);
					if (objData->UseNormalMap) this->SetTexture("TexNormalMap", material->TexNormalMap);
					if (objData->UseSpecularMap) this->SetTexture("TexSpecularMap", material->TexSpecularMap);
				}

				DllMain::ModuleGraphics->GetCBufferObject()->Unmap();
			}
		}

		ShaderType Shader::GetShaderType()
		{
			return type;
		}
	}
}