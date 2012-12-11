#pragma once

#include "Core/Scene.h"

#include "Core/LightObject.h"
#include "Core/CameraObject.h"

#include "Core/IFont.h"

#include "Game/PPBlur.h"
#include "Game/PPScreenSpaceAmbientOcclusion.h"

#include "Core/IBoxCollider.h"
#include "Core/ITerrainRenderer.h"
#include "Core/ITriangleMeshCollider.h"

#include "Core/GUIButton.h"
#include "Game/PEShootMG.h"

namespace TikiEngine
{
	namespace Game
	{
		using namespace TikiEngine::Objects;
		using namespace TikiEngine::Graphics;
		using namespace TikiEngine::Particles;
		using namespace TikiEngine::Components;
		using namespace TikiEngine::UserInterface;

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

			CameraObject* camera;

			CameraObject* cameraLight;
			IRenderTarget* targetLight;

			//ITexture* tex;
			Vector3 tmp;
			//double lastTime;
			//IBoxCollider* dynamicBox;
			//ITerrainRenderer* terrain;
			//ITriangleMeshCollider* collider;

			PPScreenSpaceAmbientOcclusion* ssao;

		};
	}
}