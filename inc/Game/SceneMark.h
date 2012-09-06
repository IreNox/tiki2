#pragma once

#include "Core/Scene.h"

#include "Core/IBoxCollider.h"
#include "Core/ICharacterController.h"

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
			IBoxCollider* box;
			IPhysicsMaterial* material; 
			ICharacterController* controller;
		};
	}
}