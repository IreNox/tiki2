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

			bool Initialize(const InitializationArgs& args);

		private:

			Camera* camera;
		};
	}
}