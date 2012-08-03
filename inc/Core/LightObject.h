#pragma once

#include "Core/GameObject.h"
#include "Core/Light.h"

namespace TikiEngine
{
	namespace Objects
	{
		class LightObject : public GameObject
		{
		public:

			LightObject(Engine* engine);
			~LightObject();

			Light* GetLight();

		private:

			Light* light;
		};
	}
}
