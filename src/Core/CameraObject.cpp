
#include "Core/CameraObject.h"
#include "Core/TypeGlobals.h"

namespace TikiEngine
{
	namespace Objects
	{
		CameraObject::CameraObject(Engine* engine)
			: GameObject(engine)
		{
			camera = TIKI_NEW Camera(engine, this);
			camera->AddRef();
		}

		CameraObject::~CameraObject()
		{
			SafeRelease(&camera);
		}

		Camera* CameraObject::GetCameraComponent()
		{
			return camera;
		}
	}
}