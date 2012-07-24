#pragma once

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

			GaphicsDescription()
				: Width(800), Height(600)
			{
			}
		};
	}
}