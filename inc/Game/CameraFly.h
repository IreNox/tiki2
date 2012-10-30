#pragma once

#include "Core/IScript.h"
#include "Core/Camera.h"

namespace TikiEngine
{
	namespace Scripts
	{
		using namespace TikiEngine::Components;

		class CameraFly : public IScript
		{
		public:

			CameraFly(Engine* engine, GameObject* gameObject);
			~CameraFly();

			void Draw(const DrawArgs& args);
			void Update(const UpdateArgs& args);

		private:

			Vector2 rot;
			
		};
	}
}