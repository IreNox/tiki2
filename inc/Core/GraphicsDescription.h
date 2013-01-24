#pragma once

#include "Core/ViewPort.h"

namespace TikiEngine
{
	namespace Description
	{
		enum GraphicsModule
		{
			GM_OpenGL,
			GM_DirectX10,
			GM_DirectX11
		};

		struct GaphicsDescription
		{
			/*! @brief The resolution width. Ignored if Full screen is true */
			int Width;

			/*! @brief The resolution height. Ignored if Full screen is true */
			int Height;

			/*! @brief Full screen enabled */
			bool Fullscreen;

			/*! @brief VSync enabled. */
			bool VSync;

			/*! @brief The Graphics ViewPort. */
			ViewPort ViewPort;

			/*! @brief The Graphics Module. */
			UInt32 AdapterIndex;

			GraphicsModule Module;

			GaphicsDescription()
				: Width(800), Height(600), AdapterIndex(0), Fullscreen(false), VSync(false), Module(GM_DirectX11)
			{
			}
		};
	}
}