#pragma once

#include "Core/Scene.h"

#include "Core/IBoxCollider.h"
#include "Core/ISphereCollider.h"
#include "Core/ICharacterController.h"


#include "Core/IFont.h"

namespace TikiEngine
{
	namespace Game
	{
		class SceneMark : public Scene
		{
		public:

			SceneMark(Engine* engine);
			~SceneMark();

			void Initialize(const InitializationArgs& args);

			void Draw(const DrawArgs& args);
			void Update(const UpdateArgs& args);

		private:
			IBoxCollider* dynamicBox;
			IBoxCollider* staticBox;
			IBoxCollider* kinematicBox;

			ISphereCollider* triggerSphere;

			IPhysicsMaterial* material; 
			ICharacterController* controller;

			IFont* font;
		};
	}
}