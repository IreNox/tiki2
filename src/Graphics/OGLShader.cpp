
#include "Graphics/Shader.h"
#include "Core/NotSupportedException.h"

namespace TikiEngine
{
	namespace Resources
	{
		#pragma region Class
		Shader::Shader(Engine* engine)
			: IShader(engine), shaderId(0), vsId(0), psId(0)
		{
		}

		Shader::~Shader()
		{
			glDetachShader(shaderId, vsId);
			glDetachShader(shaderId, psId);

			glDeleteShader(vsId);
			glDeleteShader(psId);

			glDeleteProgram(shaderId);
		}
		#pragma endregion

		#pragma region Member
		void Shader::Apply()
		{
			glUseProgram(shaderId);
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

			Int32 loc = glGetUniformLocation(shaderId, key);
			if (loc != -1) glGetUniformiv(shaderId, loc, &value);

			return value;
		}

		Single Shader::GetSingle(cstring key)
		{
			float value;

			Int32 loc = glGetUniformLocation(shaderId, key);
			if (loc != -1) glGetUniformfv(shaderId, loc, &value);

			return value;
		}

		Vector2 Shader::GetVector2(cstring key)
		{
			Vector2 value;

			Int32 loc = glGetUniformLocation(shaderId, key);
			if (loc != -1) glGetUniformfv(shaderId, loc, value.arr);

			return value;
		}

		Vector3 Shader::GetVector3(cstring key)
		{
			Vector3 value;

			Int32 loc = glGetUniformLocation(shaderId, key);
			if (loc != -1) glGetUniformfv(shaderId, loc, value.arr);

			return value;
		}

		Vector4 Shader::GetVector4(cstring key)
		{
			Vector4 value;

			Int32 loc = glGetUniformLocation(shaderId, key);
			if (loc != -1) glGetUniformfv(shaderId, loc, value.arr);

			return value;
		}

		Matrix Shader::GetMatrix(cstring key)
		{
			Matrix value;

			Int32 loc = glGetUniformLocation(shaderId, key);
			if (loc != -1) glGetUniformfv(shaderId, loc, value.n);

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
			Int32 loc = glGetUniformLocation(shaderId, key);
			if (loc != -1) glUniform1i(loc, value);
		}

		void Shader::SetSingle(cstring key, Single value)
		{
			Int32 loc = glGetUniformLocation(shaderId, key);
			if (loc != -1) glUniform1f(loc, value);
		}

		void Shader::SetVector2(cstring key, const Vector2& value)
		{
			Int32 loc = glGetUniformLocation(shaderId, key);
			if (loc != -1) glUniform2fv(loc, 1, value.arr);
		}

		void Shader::SetVector3(cstring key, const Vector3& value)
		{
			Int32 loc = glGetUniformLocation(shaderId, key);
			if (loc != -1) glUniform3fv(loc, 1, value.arr);
		}

		void Shader::SetVector4(cstring key, const Vector4& value)
		{
			Int32 loc = glGetUniformLocation(shaderId, key);
			if (loc != -1) glUniform4fv(loc, 1, value.arr);
		}

		void Shader::SetMatrix(cstring key, const Matrix& value)
		{
			Int32 loc = glGetUniformLocation(shaderId, key);
			if (loc == -1)
			{
				engine->HLog.Write(string("Can't find Uniform: ") + key);
				return;
			}	

			glUniformMatrix4fv(loc, 1, false, value.n);
		}

		void Shader::SetTexture(cstring key, ITexture* value)
		{
			Int32 loc = glGetUniformLocation(shaderId, key);
			if (loc == -1)
			{
				engine->HLog.Write(string("Can't find Uniform: ") + key);
				return;
			}	

			glActiveTexture(GL_TEXTURE0);

			GLint id = *((GLint*)value->GetNativeResource());
			glBindTexture(GL_TEXTURE_2D, id);

			glUniform1i(loc, 0); //(GLint)value->GetNativeResource());
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
			return (void*)shaderId;
		}
		bool Shader::GetReady()
		{
			return shaderId != 0;
		}
		#pragma endregion

		#pragma region Member - Load/Save
		void Shader::loadFromStream(wcstring fileName, Stream* stream)
		{
			UInt32 len = (UInt32)stream->GetLength();

			char* data = new char[len];
			stream->Read(data, 0, len);

			string code = string(data, len);
			string codeVS = "#define TIKI_VS" + code;
			string codePS = "#define TIKI_PS" + code;

			vsId = glCreateShader(GL_VERTEX_SHADER);
			psId = glCreateShader(GL_FRAGMENT_SHADER);

			const char* codeVSP = codeVS.CStr();
			const char* codePSP = codePS.CStr();

			glShaderSource(vsId, 1, &codeVSP, 0);
			glShaderSource(psId, 1, &codePSP, 0);

			glCompileShader(vsId);
			glCompileShader(psId);

			string error;
			if (getShaderInfo(vsId, error, false) || getShaderInfo(psId, error, false))
				throw error;

			shaderId = glCreateProgram();
			glAttachShader(shaderId, vsId);
			glAttachShader(shaderId, psId);
			
			glBindAttribLocation(shaderId, 0, "inPos");
			glBindAttribLocation(shaderId, 1, "inUV");
			glBindAttribLocation(shaderId, 2, "inColor");
			glLinkProgram(shaderId);

			if (getShaderInfo(shaderId, error, true))
				throw error;


			//effectId = glfxGenEffect();


			//if (!glfxParseEffectFromMemory(effectId, data))
			//{
			//	delete[](data);

			//	string s = glfxGetEffectLog(effectId).c_str();
			//	engine->HLog.WriteError("Can't parse Effect. Error: " + s, 0);
			//}
			//delete[](data);

			//shaderProgram = glfxCompileProgram(effectId, "tiki");

			//if (shaderProgram < 0)
			//{
			//	string s = glfxGetEffectLog(effectId).c_str();
			//	engine->HLog.WriteError("Can't compile Effect. Error: " + s, 0);
			//}
		}

		void Shader::saveToStream(wcstring fileName, Stream* stream)
		{
			throw NotSupportedException();
		}
		#pragma endregion

		#pragma region Private - Info
		bool Shader::getShaderInfo(int id, string& log, bool program)
		{
			int len = 0;
			(program ? glGetProgramiv : glGetShaderiv)(id, GL_INFO_LOG_LENGTH, &len);

			if (len > 0)
			{
				int charsWritten  = 0;
				char* cLog = new char[len];

				(program ? glGetProgramInfoLog : glGetShaderInfoLog)(id, len, &charsWritten, cLog);

				log += string(cLog, charsWritten);
				free(cLog);

				return true;
			}

			return false;
		}
		#pragma endregion
	}
}