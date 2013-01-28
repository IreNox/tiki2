
#include "Graphics/SpriteBatchModule.h"
#include "Graphics/GraphicsModule.h"

namespace TikiEngine
{
	namespace Modules
	{
		void SpriteBatchModule::End()
		{
			if (spriteInfos.Count() == 0) return;
			spriteInfos.Sort();

			DllMain::ModuleGraphics->SetStateAlphaBlend(BSM_Interface);
			DllMain::ModuleGraphics->GetInterfaceTarget()->ApplyFirstAndOnly();

			SpriteBatchVertex* vertices = buffer->Map(spriteVertices.Count());
			memcpy(vertices, spriteVertices.GetInternalData(), sizeof(SpriteBatchVertex) * spriteVertices.Count());
			buffer->Unmap();

			declaration->Apply();
			buffer->Apply();

			UInt32 i = 0;
			Sprite& info = Sprite();
			while (i < spriteInfos.Count())
			{
				info = spriteInfos.GetRef(i);

				DllMain::Context->IASetPrimitiveTopology(
					(info.Lines ? D3D_PRIMITIVE_TOPOLOGY_LINELIST : D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP)				
					);

				shader->SetSingle("value", info.Value);
				if (info.Texture != 0) shader->SetTexture("tex", info.Texture);
				shader->Apply();

				DllMain::Context->Draw(info.VertexCount, info.BufferIndex);

				i++;
			}

			DllMain::ModuleGraphics->SetStateAlphaBlend(BSM_Disable);
		}
	}
}