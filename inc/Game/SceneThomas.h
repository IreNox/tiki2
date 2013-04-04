#pragma once

#include "Core/Scene.h"
#include "Core/LightObject.h"
#include <Core/IFont.h>
#include <Graphics/TikiBone.h>

#include "Core/EventAnimation.h"
#include "PPScreenSpaceAmbientOcclusion.h"
#include "Core/SceneGraph.h"

namespace TikiEngine
{
	namespace Game
	{
		using namespace TikiEngine::Objects;

		class SceneThomas : public Scene
		{
		public:

			SceneThomas(Engine* engine);
			~SceneThomas();

			void Initialize(const InitializationArgs& args);

			void Draw(const DrawArgs& args);
			void Update(const UpdateArgs& args);

		private:

			LightObject* light;
			ITexture* tex;


			IModel* model;


			RectangleF selectionRectangle;

			List<GameObject*> drawContent;

		};
	}
}