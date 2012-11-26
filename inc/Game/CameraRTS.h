#pragma once

#include "Core/IScript.h"
#include "Core/ITerrainRenderer.h"

namespace TikiEngine
{
	namespace Scripts
	{
		class CameraRTS : public IScript
		{
		public:

			CameraRTS(GameObject* gameObject, ITerrainRenderer* terrain);
			~CameraRTS();

			void Draw(const DrawArgs& args);
			void Update(const UpdateArgs& args);

		private:

			float zoom;
			float targetZoom;

			ITerrainRenderer* terrain;

		};
	}
}