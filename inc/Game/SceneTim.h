#pragma once

#include "Core/Scene.h"

#include "Core/LightObject.h"
#include "Core/CameraObject.h"

#include "Core/IBoxCollider.h"

namespace TikiEngine
{
	namespace Game
	{
		using namespace TikiEngine::Objects;

		class SceneTim : public Scene
		{
		public:

			SceneTim(Engine* engine);
			~SceneTim();
	
			void Initialize(const InitializationArgs& args);

			void Draw(const DrawArgs& args);
			void Update(const UpdateArgs& args);

		private:

			LightObject* light;

			ITexture* tex;
		};
	}
}