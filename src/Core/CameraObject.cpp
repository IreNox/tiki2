
#include "Core/CameraObject.h"

namespace TikiEngine
{
	namespace Objects
	{
		CameraObject::CameraObject(Engine* engine)
			: GameObject(engine)
		{
		}

		CameraObject::~CameraObject()
		{
		}

		bool CameraObject::Initialize(const InitializationArgs& args)
		{
			camera = new Camera(engine, this);

			this->AddComponent(camera);

			GameObject::Initialize(args);

			return true;
		}

		Camera* CameraObject::GetCameraComponent()
		{
			return camera;
		}
	}
}