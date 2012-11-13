#pragma once

#include "Core/Scene.h"
#include "Core/IFont.h"
#include "Core/IBoxCollider.h"
#include "Core/ISphereCollider.h"
#include "Core/ICharacterController.h"
#include "Core/CameraObject.h"

#include "Game/GameState.h"
#include "Game/TikiBot.h"
#include "Game/NavigationMesh.h"
//#include "Game/OcTree.h"


namespace TikiEngine
{
	namespace Game
	{
		using namespace TikiEngine::Objects;
		using namespace TikiEngine::AI;


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

			CameraObject* camera;
      
			 Vector3 orig;
			 Vector3 dir;
			 Vector3 impact;


			 bool drawCellSpace;

			 GameState* state;

			 //OcTree* tree;
 			// TRI tris[191]; // = TotalCells

			 NavigationMesh* naviMesh; 
			 bool showNaviMesh;

		};
	}
}