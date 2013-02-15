#pragma once

#include "Core/Scene.h"
#include "Core/IFont.h"
#include "Core/GUIControl.h"

namespace TikiEngine
{
	namespace Game
	{
		using namespace TikiEngine::UserInterface;

		class SceneCredits : public Scene
		{
		public:

			SceneCredits(Engine* engine);
			~SceneCredits();

			void Initialize(const InitializationArgs& args);

			void Draw(const DrawArgs& args);
			void Update(const UpdateArgs& args);
			
		private:

			Vector2 pos;

			IFont* font24;
			IFont* font14;

			GameObject* go;
			
			List<GUIControl*> controls;
		};
	}
}