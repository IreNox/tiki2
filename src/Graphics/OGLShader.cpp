
#include "Graphics/Shader.h"
#include "Core/NotSupportedException.h"

#include "glfx/glfx.h"


namespace TikiEngine
{
	namespace Resources
	{
		#pragma region Class
		Shader::Shader(Engine* engine)
			: IShader(engine), shaderProgram(0), effectId(0)
		{
		}

		Shader::~Shader()
		{
			glfxDeleteEffect(effectId); 
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
		Boolean Shader::GetBoolean(cstring key)
		{
			throw NotSupportedException();
		}

		Int32 Shader::GetInt(cstring key)
		{
			Int32 value;

			Int32 loc = glGetUniformLocation(shaderProgram, key);
			if (loc != -1) glGetUniformiv(shaderProgram, loc, &value);

			return value;
		}

		Single Shader::GetSingle(cstring key)
		{
			float value;

			Int32 loc = glGetUniformLocation(shaderProgram, key);
			if (loc != -1) glGetUniformfv(shaderProgram, loc, &value);

			return value;
		}

		Vector2 Shader::GetVector2(cstring key)
		{
			Vector2 value;

			Int32 loc = glGetUniformLocation(shaderProgram, key);
			if (loc != -1) glGetUniformfv(shaderProgram, loc, value.arr);

			return value;
		}

		Vector3 Shader::GetVector3(cstring key)
		{
			Vector3 value;

			Int32 loc = glGetUniformLocation(shaderProgram, key);
			if (loc != -1) glGetUniformfv(shaderProgram, loc, value.arr);

			return value;
		}

		Vector4 Shader::GetVector4(cstring key)
		{
			Vector4 value;

			Int32 loc = glGetUniformLocation(shaderProgram, key);
			if (loc != -1) glGetUniformfv(shaderProgram, loc, value.arr);

			return value;
		}

		Matrix Shader::GetMatrix(cstring key)
		{
			Matrix value;

			Int32 loc = glGetUniformLocation(shaderProgram, key);
			if (loc != -1) glGetUniformfv(shaderProgram, loc, value.n);

			return value;
		}
		#pragma endregion

		#pragma region Member - Set
		void Shader::SetBoolean(cstring key, Boolean value)
		{
			throw NotSupportedException();
		}

		void Shader::SetInt(cstring key, Int32 value)
		{
			Int32 loc = glGetUniformLocation(shaderProgram, key);
			if (loc != -1) glUniform1i(loc, value);
		}

		void Shader::SetSingle(cstring key, Single value)
		{
			Int32 loc = glGetUniformLocation(shaderProgram, key);
			if (loc != -1) glUniform1f(loc, value);
		}

		void Shader::SetVector2(cstring key, const Vector2& value)
		{
			Int32 loc = glGetUniformLocation(shaderProgram, key);
			if (loc != -1) glUniform2fv(loc, 1, value.arr);
		}

		void Shader::SetVector3(cstring key, const Vector3& value)
		{
			Int32 loc = glGetUniformLocation(shaderProgram, key);
			if (loc != -1) glUniform3fv(loc, 1, value.arr);
		}

		void Shader::SetVector4(cstring key, const Vector4& value)
		{
			Int32 loc = glGetUniformLocation(shaderProgram, key);
			if (loc != -1) glUniform4fv(loc, 1, value.arr);
		}

		void Shader::SetMatrix(cstring key, const Matrix& value)
		{
			Int32 loc = glGetUniformLocation(shaderProgram, key);
			if (loc != -1) glUniformMatrix4fv(loc, 1, false, value.n);
		}

		void Shader::SetTexture(cstring key, ITexture* value)
		{
			Int32 loc = glGetUniformLocation(shaderProgram, key);
			if (loc != -1) 
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, (GLuint)value->GetNativeResource());

				glUniform1i(loc, 0); //(GLint)value->GetNativeResource());
			}
		}

		void Shader::SetTextureArray(cstring key, List<ITexture*>& array)
		{
			throw NotSupportedException();
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
			effectId = glfxGenEffect();

			char* data = new char[stream->GetLength()];
			stream->Read(data, 0, stream->GetLength());

			if (!glfxParseEffectFromMemory(effectId, data))
			{
				delete[](data);

				string s = glfxGetEffectLog(effectId).c_str();
				engine->HLog.WriteError("Can't parse Effect. Error: " + s, 0);
			}
			delete[](data);

			shaderProgram = glfxCompileProgram(effectId, "tiki");

			if (shaderProgram < 0)
			{
				string s = glfxGetEffectLog(effectId).c_str();
				engine->HLog.WriteError("Can't compile Effect. Error: " + s, 0);
			}
		}

		void Shader::saveToStream(wcstring fileName, Stream* stream)
		{
			throw NotSupportedException();
		}
		#pragma endregion
	}
}