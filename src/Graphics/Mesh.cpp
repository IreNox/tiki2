
#include "Core/Engine.h"
#include "Graphics/Mesh.h"

namespace TikiEngine
{
	namespace Graphics
	{
		#pragma region Class
		Mesh::Mesh(Engine* engine)
			: IMesh(engine), data(0), decl(0)
		{
		}

		Mesh::~Mesh()
		{
			if (this->data != 0)
			{
				delete(this->data);
			}	

			if (this->decl != 0)
			{
				delete(this->decl);
			}	
		}
		#pragma endregion

		#pragma region Member
		bool Mesh::GetReady()
		{
			return (data != 0) && (decl != 0);
		}
		#pragma endregion

		#pragma region Member
		void SetVertexData(void* data, UInt32 dataLength)
		{

		}

		void SetVertexDeclaration(void* data, UInt32 dataLength)
		{

		}

		//void Mesh::Init(VertexDeclaration* decl)
		//{
		//	if (this->data != 0) return;

		//	shader = decl->GetShader();

		//	this->data = new VertexData(
		//		engine,
		//		shader,
		//		decl
		//	);
		//}
		#pragma endregion

		#pragma region Member - Draw
		//void Mesh::Draw(const FrameArgs& args)
		//{
		//	data->Apply();
		//	
		//	context->DrawIndexed(
		//		data->countIndex,
		//		data->indexIndex,
		//		data->indexVertex
		//	);
		//}
		#pragma endregion
	}
}