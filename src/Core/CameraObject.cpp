
#include "Core/CameraObject.h"

namespace TikiEngine
{
	namespace Objects
	{
		CameraObject::CameraObject(Engine* engine)
			: GameObject(engine)
		{
			camera = new Camera(engine, this);
		}

		CameraObject::~CameraObject()
		{
		}

		Camera* CameraObject::GetCameraComponent()
		{
			return camera;
		}
	}
}