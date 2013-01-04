#pragma once

#include "Core/Scene.h"
#include "Core/LightObject.h"
#include "Core/CameraObject.h"

namespace TikiEngine
{
	namespace Game
	{
        using namespace TikiEngine::Objects;
        using namespace TikiEngine::Graphics;
        //using namespace TikiEngine::Particles;
        using namespace TikiEngine::Components;

		class SceneMark : public Scene
		{
		public:

			SceneMark(Engine* engine);
			~SceneMark();

			void Initialize(const InitializationArgs& args);

			void Draw(const DrawArgs& args);
			void Update(const UpdateArgs& args);

		private:
            LightObject* light;

            CameraObject* camera;

			GameObject* smokeEmitter;

			GameObject* fireEmitter;
		};
	}
}