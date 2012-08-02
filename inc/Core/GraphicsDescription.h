#pragma once

#include "Core/ViewPort.h"

namespace TikiEngine
{
	namespace Description
	{
		struct GaphicsDescription
		{
			/*!
			 * @brief The resolution width.
			 */
			int Width;

			/*!
			 * @brief The resolution height.
			 */
			int Height;

			/*!
			 * @brief The Graphics ViewPort.
			 */
			ViewPort ViewPort;

			GaphicsDescription()
				: Width(800), Height(600)
			{
			}
		};
	}
}