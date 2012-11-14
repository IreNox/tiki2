
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
			SafeRelease(&texture);
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
				RectangleF::Create(
					position.X,
					position.Y,
					size.X,
					size.Y
				),
				Color::White
			);
		}
		#pragma endregion
	}
}