
#include "Graphics/SpriteBatchModule.h"

#include "Graphics/OGLGraphicsModule.h"

namespace TikiEngine
{
	namespace Modules
	{
		void SpriteBatchModule::End()
		{
			if (spriteInfos.Count() == 0) return;
			spriteInfos.Sort();

			DllMain::ModuleGraphics->SetStateAlphaBlend(BSM_Interface);
			//DllMain::ModuleGraphics->GetInterfaceTarget()->ApplyFirstAndOnly();

			SpriteBatchVertex* vertices = buffer->Map(spriteVertices.Count());
			memcpy(vertices, spriteVertices.GetInternalData(), sizeof(SpriteBatchVertex) * spriteVertices.Count());
			buffer->Unmap();

			//declaration->Apply();
			buffer->Apply();

			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);
			glEnableVertexAttribArray(2);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(SpriteBatchVertex), 0);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(SpriteBatchVertex), (void*)(3 * sizeof(float)));
			glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(SpriteBatchVertex), (void*)(5 * sizeof(float)));

			shader->SetMatrix("SBProjM", projMatrix);

			UInt32 i = 0;
			Sprite& info = Sprite();
			while (i < spriteInfos.Count())
			{
				info = spriteInfos.GetRef(i);

				//DllMain::Context->IASetPrimitiveTopology(
				//	(info.Lines ? D3D_PRIMITIVE_TOPOLOGY_LINELIST : D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP)				
				//);

				shader->SetSingle("value", info.Value);
				if (info.Texture != 0) shader->SetTexture("tex", info.Texture);
				shader->Apply();

				//DllMain::Context->Draw(info.VertexCount, info.BufferIndex);

				glDrawArrays(
					info.Lines ? GL_LINE : GL_TRIANGLE_STRIP,
					info.BufferIndex, 
					info.VertexCount
				);

				i++;
			}

			DllMain::ModuleGraphics->SetStateAlphaBlend(BSM_Disable);
		}
	}
}