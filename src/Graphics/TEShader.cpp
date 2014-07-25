
#include "Core/Material.h"
#include "Core/GameObject.h"

#include "Graphics/Shader.h"

#if TIKI_OGL
#include "Graphics/OGLGraphicsModule.h"
#else
#include "Graphics/DXGraphicsModule.h"
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

		void Shader::applyType(const wstring& fileName)
		{
			wstring file = engine->HPath.GetFilename(fileName);

			switch (file[0])
			{
			case 'o':
			case 'O':
				type = ST_Object;
				break;
			case 'p':
			case 'P':
				type = ST_PostProcess;
				break;
			default:
				type = ST_Unknown;
				break;
			}

			applyConstants();
		}
		
		void Shader::applyConstants()
		{
			switch ( type )
			{
			case ST_Object:
				this->SetConstantBuffer(
					"ObjectData",
					DllMain::ModuleGraphics->GetCBufferObject()
				);

				this->SetConstantBuffer(
					"LightBuffer",
					DllMain::ModuleGraphics->GetCBufferLight()
				);

				this->SetConstantBuffer(
					"MatrixBuffer",
					DllMain::ModuleGraphics->GetCBufferCamera()
				);
				break;
			case ST_PostProcess:
				this->SetConstantBuffer(
					"LightBuffer",
					DllMain::ModuleGraphics->GetCBufferLight()
				);
				break;
			default:
				break;
			}
		}
	}
}