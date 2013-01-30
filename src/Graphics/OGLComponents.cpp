
#include "Graphics/MeshRenderer.h"
#include "Graphics/DllMain.h"
#include "Graphics/OGLGraphicsModule.h"

namespace TikiEngine
{
	namespace Components
	{
		const GLenum topologies[] = {
			0,
			GL_POINTS,
			GL_LINES,
			0,
			GL_TRIANGLES,
			GL_TRIANGLE_STRIP
		};

		#pragma region  MeshRenderer
		void MeshRenderer::Draw(const DrawArgs& args)
		{			
			if (!this->GetReady() || args.Mode == DM_Shadows) return;

			material->UpdateDrawArgs(args, gameObject);

			vertexBuffer->Apply();

			decl->Apply();
			material->Apply();

			if (indexBuffer != 0)
			{
				indexBuffer->Apply();

				glDrawElements(
					topologies[mesh->GetPrimitiveTopology()],
					indexBuffer->GetElementCount(),
					GL_UNSIGNED_INT,
					0
				);
			}
			else
			{
				glDrawArrays(
					topologies[mesh->GetPrimitiveTopology()],
					0,
					vertexBuffer->GetElementCount()
				);
			}
		}
		#pragma endregion
	}
}