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

			void SetCameraTarget(GameObject* go);
			void ClearCameraTarget();

			void SetDistanceToTarget(float distanceToTarget);

		private:

#if _DEBUG
			bool useMouse;
			bool useRealCamera;
#endif

			float zoom;
			float targetZoom;
			float height;

			ITerrainRenderer* terrain;

			GameObject* cameraTarget;
			Vector3 ownTargetPosition;

			float distanceToTarget;

		};
	}
}