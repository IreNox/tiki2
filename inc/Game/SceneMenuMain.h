#pragma once

#include "Core/Scene.h"
#include "Core/GUIImage.h"
#include "Core/GUIButton.h"
#include "Core/CameraObject.h"

#include "Core/EventScreenSizeChanged.h"

#include "Game/SceneLevel.h"

namespace TikiEngine
{
	namespace Game
	{
		using namespace TikiEngine::Objects;
		using namespace TikiEngine::UserInterface;

		class SceneMenuMain : public Scene, public ScreenSizeChangedEventHandler
		{
		public:

			SceneMenuMain(Engine* engine);
			~SceneMenuMain();

			void Initialize(const InitializationArgs& args);

			void Draw(const DrawArgs& args);
			void Update(const UpdateArgs& args);

			void Handle(IGraphics* sender, const ScreenSizeChangedArgs& args);

		private:

			SceneLevel* sceneLevel;

			List<GUIButton*> buttons;
			List<GUIControl*> controls;

		};
	}
}