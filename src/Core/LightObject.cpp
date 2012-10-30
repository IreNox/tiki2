
#include "Core/LightObject.h"
#include "Core/TypeGlobals.h"

namespace TikiEngine
{
	namespace Objects
	{
		LightObject::LightObject(Engine* engine)
			: GameObject(engine), light(0)
		{
			light = new Light(engine, this);
			light->AddRef();
		}

		LightObject::~LightObject()
		{
			SafeRelease(&light);
		}

		Light* LightObject::GetLight()
		{
			return light;
		}
	}
}