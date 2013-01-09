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

#if _DEBUG
			bool useMouse;
			bool useRealCamera;
#endif

			float zoom;
			float targetZoom;
			float height;

			ITerrainRenderer* terrain;

		};
	}
}