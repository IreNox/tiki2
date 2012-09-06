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

			UInt32 AdapterIndex;

			GaphicsDescription()
				: Width(800), Height(600), AdapterIndex(0)
			{
			}
		};
	}
}