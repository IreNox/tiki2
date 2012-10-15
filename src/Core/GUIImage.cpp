
#include "Core/GUIImage.h"

#include "Core/TypeGlobals.h"
#include "Core/ISpriteBatch.h"

namespace TikiEngine
{
	namespace UserInterface
	{
		#pragma region Class
		GUIImage::GUIImage(Engine* engine)
			: GUIControl(engine), texture(0), textureSize()
		{
		}

		GUIImage::~GUIImage()
		{
		}
		#pragma endregion

		#pragma region Member
		bool GUIImage::GetReady()
		{
			return (texture != 0);
		}
		#pragma endregion

		#pragma region Member - Get/Set
		ITexture* GUIImage::GetTexture()
		{
			return texture;
		}

		void GUIImage::SetTexture(ITexture* texture)
		{
			SafeRelease(&this->texture);
			SafeAddRef(texture, &this->texture);

			if (texture)
			{
				isDirty = true;
				size = texture->GetSize();
				textureSize = size;
			}
		}
		#pragma endregion

		#pragma region Member - Draw
		void GUIImage::Draw(const DrawArgs& args)
		{
			engine->sprites->Draw(
				texture,
				position,
				0,
				Vector2::Zero,
				Vector2(
					textureSize.X / size.X,
					textureSize.Y / size.Y
				),
				1.0f
			);
		}
		#pragma endregion
	}
}