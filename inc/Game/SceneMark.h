#pragma once

#include "Core/Scene.h"
#include "Core/IFont.h"
#include "Core/IBoxCollider.h"
#include "Core/ISphereCollider.h"
#include "Core/ICharacterController.h"

#include "Game/GameState.h"
#include "Game/TikiBot.h"
#include "Game/CameraFly.h"
#include "Game/CellSpacePartition.h"
#include "Game/NavigationMesh.h"

namespace TikiEngine
{
	namespace Game
	{
		using namespace TikiEngine::AI;
		using namespace TikiEngine::Scripts;


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

			TikiBot* bot;

			 CameraFly* fly;
      
			 Vector3 orig;
			 Vector3 dir;
			 Vector3 impact;

			 CellSpacePartition<TikiBot*>* cellSpace;
			 bool drawCellSpace;

			 GameState* state;

			 NavigationMesh naviMesh; 
			 bool showNaviMesh;

		};
	}
}