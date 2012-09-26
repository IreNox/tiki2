
#include "Core/LightObject.h"

namespace TikiEngine
{
	namespace Objects
	{
		LightObject::LightObject(Engine* engine)
			: GameObject(engine), light(0)
		{
			light = new Light(engine, this);
		}

		LightObject::~LightObject()
		{
		}

		Light* LightObject::GetLight()
		{
			return light;
		}
	}
}