
#include "Core/Mesh.h"
#include "Core/Engine.h"

namespace TikiEngine
{
	namespace Elements
	{
		#pragma region Class
		Mesh::Mesh(Engine* engine)
			: Element(engine), data(0)
		{
		}

		Mesh::~Mesh()
		{
		}
		#pragma endregion

		#pragma region Member
		void Mesh::Init(VertexDeclaration* decl)
		{
			if (this->data != 0) return;

			shader = decl->GetShader();

			this->data = new VertexData(
				engine,
				shader,
				decl
			);
		}

		void Mesh::Dispose()
		{
			if (this->data != 0)
			{
				delete(this->data);
			}			
		}
		#pragma endregion

		#pragma region Member - Draw
		void Mesh::Draw(const FrameArgs& args)
		{
			data->Apply();
			
			context->DrawIndexed(
				data->countIndex,
				data->indexIndex,
				data->indexVertex
			);
		}
		#pragma endregion

		#pragma region Member - Update
		void Mesh::Update(const FrameArgs& args)
		{
			shader->ApplyVars(this);
		}
		#pragma endregion
	}
}