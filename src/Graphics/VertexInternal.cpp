﻿
#include "Graphics/ParticleVertex.h"
#include "Graphics/SpriteBatchVertex.h"

#include "Graphics/VertexDeclaration.h"
#include "Graphics/DllMain.h"

namespace TikiEngine
{
	namespace Vertices
	{
		#pragma region VertexFormats
		InputElement ParticleVertex::Declaration[3] = {
			InputElement(IST_Position,	0, IEF_Float, 3),
			InputElement(IST_Color,		0, IEF_Float, 4),
			InputElement(IST_TexCoord,	0, IEF_Float, 3)
		};

		UInt32 ParticleVertex::DeclarationCount = 3;

		bool SpriteBatchVertex::operator==(const SpriteBatchVertex& rhs)
		{
			return (this->Position[0] == rhs.Position[0]) &&
				   (this->Position[1] == rhs.Position[1]) &&
  				   (this->Position[2] == rhs.Position[2]) &&
				   (this->UV[0] == rhs.UV[0]) &&
				   (this->UV[1] == rhs.UV[1]) &&
				   (this->Color[0] == rhs.Color[0]) &&
				   (this->Color[1] == rhs.Color[1]) &&
				   (this->Color[2] == rhs.Color[2]) &&
				   (this->Color[3] == rhs.Color[3]);
		}

		InputElement SpriteBatchVertex::Declaration[3] = {
			InputElement(IST_Position, 0, IEF_Float, 3),
			InputElement(IST_TexCoord, 0, IEF_Float, 2),
			InputElement(IST_Color,    0, IEF_Float, 4)
		};

		UInt32 SpriteBatchVertex::DeclarationCount = 3;
		#pragma endregion

		#pragma region VertexDeclaration
		#pragma region Class
		VertexDeclaration::VertexDeclaration(Engine* engine, IShader* shader, List<InputElement>* elements)
			: EngineObject(engine)
		{
			SafeAddRef(shader, &this->shader);
			createInputLayout(elements->GetInternalData(), elements->Count());
		}

		VertexDeclaration::VertexDeclaration(Engine* engine, IShader* shader, const InputElement* elements, UInt32 elementsCount)
			: EngineObject(engine)
		{
			SafeAddRef(shader, &this->shader);
			createInputLayout(elements, elementsCount);
		}

		VertexDeclaration::~VertexDeclaration()
		{
			SafeRelease(&shader);

#if TIKI_DX10 || TIKI_DX11
			SafeRelease(&inputLayout);
#endif
		}
		#pragma endregion

		#pragma region Member - Get
		UINT VertexDeclaration::GetElementSize()
		{
			return this->elementSize;
		}

		ULONG VertexDeclaration::GetDeclarationHash()
		{
			return this->hash;
		}

		IShader* VertexDeclaration::GetShader()
		{
			return shader;
		}
		#pragma endregion

		#pragma region Member - Apply
		void VertexDeclaration::Apply() 
		{
#if TIKI_DX10 || TIKI_DX11
			DllMain::Context->IASetInputLayout(
				this->inputLayout
			);
#elif TIKI_OGL
			UInt32 i = 0;
			Byte* offset = 0;
			while (i < inputLayout.Count())
			{
				GLenum type;

				switch (inputLayout[i].ElementFormat)
				{
				case IEF_Float:
					type = GL_FLOAT;
					break;
				case IEF_UInt:
					type = GL_UNSIGNED_INT;
					break;
				}

				glEnableVertexAttribArray(i);
				glVertexAttribPointer(i, inputLayout[i].ElementSize, type, false, elementSize, offset);

				offset += 4 * inputLayout[i].ElementSize;
				i++;
			}


			int on;
			Int32 count;
			Int32 b = 0;
			glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &count);

			while (b < count)
			{
				glGetVertexAttribiv(b, GL_VERTEX_ATTRIB_ARRAY_ENABLED, &on);

				if (!on)
					break;

				glDisableVertexAttribArray(b);

				b++;
			}
#endif
		}
		#pragma endregion

		#pragma region Private Member - CreateInputLayout
		void VertexDeclaration::createInputLayout(const InputElement* decl, UInt32 count)
		{
			elementSize = 0;

#if TIKI_OGL
			inputLayout = List<InputElement>(decl, count, true);

			UInt32 i = 0;
			while (i < count)
			{
				switch (decl[i].ElementFormat)
				{
				case IEF_Bool:
					elementSize += decl[i].ElementSize;
					break;
				case IEF_UInt:
				case IEF_Float:
					elementSize += decl[i].ElementSize * 4;
					break;
				}

				i++;
			}
#elif TIKI_DX10 || TIKI_DX11
			TDX_Input_Element_desc* elements = TIKI_NEW TDX_Input_Element_desc[count];

			UInt32 i = 0;
			while (i < count)
			{
				InputElement input = decl[i];
				TDX_Input_Element_desc element;

				switch (input.SemanticType)
				{
				case IST_Position:
					element.SemanticName = "POSITION";
					break;
				case IST_Normal:
					element.SemanticName = "NORMAL";
					break;
				case IST_TexCoord:
					element.SemanticName = "TEXCOORD";
					break;
				case IST_Tangent:
					element.SemanticName = "TANGENT";
					break;
				case IST_Color:
					element.SemanticName = "COLOR";
					break;
				case IST_Binormal:
					element.SemanticName = "BINORMAL";
					break;
				case IST_SV_RenderTargetArrayIndex:
					element.SemanticName = "SV_RenderTargetArrayIndex";
					break;
				case IST_BlendWeight:
					element.SemanticName = "BLENDWEIGHT";
					break;
				case IST_BlendIndices:
					element.SemanticName = "BLENDINDICES";
					break;
				}
				element.SemanticIndex = input.SemanticIndex;

				switch (input.ElementFormat)
				{
				case IEF_UInt:
					switch (input.ElementSize)
					{
					case 1:
						element.Format = DXGI_FORMAT_R32_UINT;
						break;
					case 2:
						element.Format = DXGI_FORMAT_R32G32_UINT;
						break;
					case 3:
						element.Format = DXGI_FORMAT_R32G32B32_UINT;
						break;
					case 4:
						element.Format = DXGI_FORMAT_R32G32B32A32_UINT;
						break;
					}

					elementSize += 4 * input.ElementSize;
					break;					
				case IEF_Float:
					switch (input.ElementSize)
					{
					case 1:
						element.Format = DXGI_FORMAT_R32_FLOAT;
						break;
					case 2:
						element.Format = DXGI_FORMAT_R32G32_FLOAT;
						break;
					case 3:
						element.Format = DXGI_FORMAT_R32G32B32_FLOAT;
						break;
					case 4:
						element.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
						break;
					}

					elementSize += 4 * input.ElementSize;
					break;
				case IEF_Bool:
					element.Format = DXGI_FORMAT_R8_UINT;
					elementSize += input.ElementSize;
					break;
				}

				element.InputSlot = 0;
				element.InstanceDataStepRate = 0;

#ifdef TIKI_DX10
				element.AlignedByteOffset = D3D10_APPEND_ALIGNED_ELEMENT;
				element.InputSlotClass = D3D10_INPUT_PER_VERTEX_DATA;
#else
				element.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
				element.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
#endif


				elements[i] = element;

				i++;
			}

			((Shader*)shader)->CreateLayout(
				elements,
				count,
				&inputLayout,
				&hash
			);

			delete[](elements);
#endif
		}
		#pragma endregion
		#pragma endregion
	}
}

