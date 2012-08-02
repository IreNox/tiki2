#pragma once

#include "Core/GameObject.h"
#include "Core/Camera.h"

namespace TikiEngine
{
	namespace Objects
	{
		class CameraObject : public GameObject
		{
		public:

			CameraObject(Engine* engine);
			~CameraObject();

			Camera* GetCameraComponent();

		private:

			Camera* camera;
		};
	}
}