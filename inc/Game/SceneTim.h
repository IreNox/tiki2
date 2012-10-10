#pragma once

#include "Core/Scene.h"

#include "Core/LightObject.h"
#include "Core/CameraObject.h"

#include "Core/IFont.h"

#include "Game/PPBlur.h"
#include "Game/PPScreenSpaceAmbientOcclusion.h"

namespace TikiEngine
{
	namespace Game
	{
		using namespace TikiEngine::Objects;
		using namespace TikiEngine::Graphics;

		class SceneTim : public Scene
		{
		public:

			SceneTim(Engine* engine);
			~SceneTim();
	
			void Initialize(const InitializationArgs& args);

			void Draw(const DrawArgs& args);
			void Update(const UpdateArgs& args);

		private:

			IFont* font;

			LightObject* light;

			ITexture* tex;

			PPScreenSpaceAmbientOcclusion* ssao;

			Vector3 tmp;

		};
	}
}