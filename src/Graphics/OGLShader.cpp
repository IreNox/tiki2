
#include "Graphics/Shader.h"

namespace TikiEngine
{
	namespace Resources
	{
		#pragma region Class
		Shader::Shader(Engine* engine)
			: IShader(engine), vertexShader(0), pixelShader(0), shaderProgram(0)
		{
		}

		Shader::~Shader()
		{
			//glDetachShader(shaderProgram, vertexShader);
			//glDetachShader(shaderProgram, pixelShader);

			//glDeleteShader(vertexShader);
			//glDeleteShader(pixelShader);

			//glDeleteProgram(shaderProgram);
		}
		#pragma endregion

		#pragma region Member
		void Shader::Apply()
		{
			glUseProgram(shaderProgram);
		}
		#pragma endregion

		#pragma region Member - Select
		void Shader::SelectSubByIndex(UInt32 index)
		{
		}

		void Shader::SelectSubByName(cstring name)
		{
		}
		#pragma endregion
		
		#pragma region Member - Get
		Int32 Shader::GetInt(cstring key)
		{
			Int32 value;

			UInt32 loc = glGetUniformLocation(shaderProgram, key);
			if (loc) glGetUniformiv(shaderProgram, loc, &value);

			return value;
		}

		Single Shader::GetSingle(cstring key)
		{
			float value;

			UInt32 loc = glGetUniformLocation(shaderProgram, key);
			if (loc) glGetUniformfv(shaderProgram, loc, &value);

			return value;
		}

		Boolean Shader::GetBoolean(cstring key)
		{
			return false;
		}

		Vector2 Shader::GetVector2(cstring key)
		{
			Vector2 value;

			UInt32 loc = glGetUniformLocation(shaderProgram, key);
			if (loc) glGetUniformfv(shaderProgram, loc, value.arr);

			return value;
		}

		Vector3 Shader::GetVector3(cstring key)
		{
			Vector3 value;

			UInt32 loc = glGetUniformLocation(shaderProgram, key);
			if (loc) glGetUniformfv(shaderProgram, loc, value.arr);

			return value;
		}

		Vector4 Shader::GetVector4(cstring key)
		{
			Vector4 value;

			UInt32 loc = glGetUniformLocation(shaderProgram, key);
			if (loc) glGetUniformfv(shaderProgram, loc, value.arr);

			return value;
		}

		Matrix Shader::GetMatrix(cstring key)
		{
			Matrix value;

			UInt32 loc = glGetUniformLocation(shaderProgram, key);
			if (loc) glGetUniformfv(shaderProgram, loc, value.n);

			return value;
		}
		#pragma endregion

		#pragma region Member - Set
		void Shader::SetInt(cstring key, Int32 value)
		{
			UInt32 loc = glGetUniformLocation(shaderProgram, key);
			if (loc) glUniform1i(loc, value);
		}

		void Shader::SetSingle(cstring key, Single value)
		{
			UInt32 loc = glGetUniformLocation(shaderProgram, key);
			if (loc) glUniform1f(loc, value);
		}

		void Shader::SetBoolean(cstring key, Boolean value)
		{

		}

		void Shader::SetVector2(cstring key, const Vector2& value)
		{
			UInt32 loc = glGetUniformLocation(shaderProgram, key);
			if (loc) glUniform2fv(loc, 1, value.arr);
		}

		void Shader::SetVector3(cstring key, const Vector3& value)
		{
			UInt32 loc = glGetUniformLocation(shaderProgram, key);
			if (loc) glUniform3fv(loc, 1, value.arr);
		}

		void Shader::SetVector4(cstring key, const Vector4& value)
		{
			UInt32 loc = glGetUniformLocation(shaderProgram, key);
			if (loc) glUniform4fv(loc, 1, value.arr);
		}

		void Shader::SetMatrix(cstring key, const Matrix& value)
		{
			//UInt32 loc = glGetUniformLocation(shaderProgram, key);
			//if (loc) glUniformMatrix4fv(loc, 1, false, value.n);
		}

		void Shader::SetTexture(cstring key, ITexture* value)
		{

		}

		void Shader::SetTextureArray(cstring key, List<ITexture*>& array)
		{

		}

		void Shader::SetConstantBuffer(cstring key, IConstantBuffer* constantBuffer)
		{

		}
		#pragma endregion

		#pragma region Member - IResource
		void* Shader::GetNativeResource()
		{
			return (void*)shaderProgram;
		}
		bool Shader::GetReady()
		{
			return shaderProgram != 0;
		}
		#pragma endregion

		#pragma region Member - Load/Save
		void Shader::loadFromStream(wcstring fileName, Stream* stream)
		{

		}

		void Shader::saveToStream(wcstring fileName, Stream* stream)
		{

		}
		#pragma endregion
	}
}