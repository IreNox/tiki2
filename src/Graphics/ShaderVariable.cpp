
#include "Graphics/Shader.h"

namespace TikiEngine
{
	namespace Effects
	{
		#pragma region Class
		Shader::Variable::Variable(ID3DX11Effect* effect, const char* key)
		{
			this->var = effect->GetVariableByName(key);
		}

		Shader::Variable::~Variable()
		{
		}
		#pragma endregion

		#pragma region Member - Get
		int Shader::Variable::GetInt()
		{
			int* value = 0;
			auto scalar = var->AsScalar();

			scalar->GetInt(value);
	
			return *value;
		}

		float Shader::Variable::GetFloat()
		{
			float* value = 0;
			auto scalar = var->AsScalar();

			scalar->GetFloat(value);
	
			return *value;
		}

		Matrix Shader::Variable::GetMatrix()
		{
			float data[16];
			auto matrix = var->AsMatrix();

			matrix->GetMatrix(data);
	
			return Matrix(data);
		}

		Vector2 Shader::Variable::GetVector2()
		{
			float data[2];
			auto scalar = var->AsScalar();

			scalar->GetFloatArray(data, 0, 2);
	
			return Vector2(data);
		}

		Vector3 Shader::Variable::GetVector3()
		{
			float data[3];
			auto scalar = var->AsScalar();

			scalar->GetFloatArray(data, 0, 3);
	
			return Vector3(data);
		}

		Vector4 Shader::Variable::GetVector4()
		{
			float data[4];
			auto scalar = var->AsScalar();

			scalar->GetFloatArray(data, 0, 4);
	
			return Vector4(data);
		}
		#pragma endregion

		#pragma region Member - Set
		void Shader::Variable::SetInt(int value)
		{
			auto cv = var->AsScalar();

			cv->SetInt(value);
		}

		void Shader::Variable::SetFloat(float value)
		{
			auto cv = var->AsScalar();

			cv->SetFloat(value);
		}

		void Shader::Variable::SetMatrix(const Matrix& value)
		{
			auto cv = var->AsMatrix();

			cv->SetMatrix((float*)&value);
		}

		void Shader::Variable::SetVector2(const Vector2& value)
		{
			auto cv = var->AsScalar();

			cv->SetFloatArray((float*)&value, 0, 2);
		}

		void Shader::Variable::SetVector3(const Vector3& value)
		{
			auto cv = var->AsScalar();

			cv->SetFloatArray((float*)&value, 0, 3);
		}

		void Shader::Variable::SetVector4(const Vector4& value)
		{
			auto cv = var->AsScalar();

			cv->SetFloatArray((float*)&value, 0, 4);
		}

		void Shader::Variable::SetTexture(Texture* texture)
		{
			var->AsShaderResource()->SetResource(
				texture->GetTexture()
			);
		}
		#pragma endregion
	}
}