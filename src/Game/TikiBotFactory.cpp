#include "Game/TikiBotFactory.h"

#include "Game/TikiBot.h"
#include "Game/GoalThink.h"
#include "Game/AnimationHandlerDefaultUnit.h"
#include "Game/SceneLevel.h"

#include "Core/IContentManager.h"

namespace TikiEngine
{
	namespace Game
	{
		TikiBotFactory::TikiBotFactory(GameState* gameState)
		{
			this->gameState = gameState;
			
			interval = 10.0;
			elapsed = 0;

			// default waypoints
			wayPoints.push_back(Vector2(0, -100));
			wayPoints.push_back(Vector2(100, -100));
			wayPoints.push_back(Vector2(100, 100));
			wayPoints.push_back(Vector2(-100, 100));
			wayPoints.push_back(Vector2(-100, -100));


			// set spawnPoints
			spawnPoint1 = Vector3(150, 50, 150);
			spawnPoint2 = Vector3(-150, 50, -150);
			spawnPoint3 = Vector3(-150, 50, 150);
		}

		TikiBotFactory::~TikiBotFactory()
		{
		}

		void TikiBotFactory::SetSpawnInterval( double interval )
		{
			this->interval = interval;
		}

		void TikiBotFactory::CreateEnemy1(GameObject* go)
		{
			// Set Model
			go->SModel(gameState->GetEngine()->content->LoadModel(L"soldier_enemy"));
			go->GModel()->AnimationHandler.AddHandler(new AnimationHandlerDefaultUnit(go->GModel()));

			// Create bot
			TikiBotDescription botDesc;
			botDesc.Faction = 1;

			TikiBot* bot = new TikiBot(gameState, go, botDesc);
			bot->SetScale(0.06f);
			bot->CreateNav(gameState->GetNavMesh());
			bot->GetBrain()->AddGoalPatrol(wayPoints);

			gameState->GetScene()->AddElement(go);
		}

		void TikiBotFactory::CreatePlayerMop(GameObject* go)
		{
			// Set Model
			go->SModel(gameState->GetEngine()->content->LoadModel(L"soldier"));
			go->GModel()->AnimationHandler.AddHandler(new AnimationHandlerDefaultUnit(go->GModel()));

			// Create bot
			TikiBotDescription botDesc;
			botDesc.Faction = 0;

			TikiBot* bot = new TikiBot(gameState, go, botDesc);
			bot->SetScale(0.06f);
			bot->CreateNav(gameState->GetNavMesh());

			gameState->GetScene()->AddElement(go);
		}

		void TikiBotFactory::Update( const UpdateArgs& args )
		{
			//if (spawnRegulator->IsReady())
			elapsed += args.Time.ElapsedTime;

			if (elapsed > interval)
			{
				elapsed -= interval;

				// spawn from three sides
				GameObject* go = new GameObject(gameState->GetEngine());
				go->PRS.SPosition() = spawnPoint1;
				CreateEnemy1(go);

				GameObject* go2 = new GameObject(gameState->GetEngine());
				go2->PRS.SPosition() = spawnPoint2;
				CreateEnemy1(go2);

				GameObject* go3 = new GameObject(gameState->GetEngine());
				go3->PRS.SPosition() = spawnPoint3;
				CreateEnemy1(go3);
			}

			if (args.Input.GetKeyPressed(KEY_F5))
			{
				GameObject* go = new GameObject(gameState->GetEngine());
				go->PRS.SPosition() = spawnPoint1;
				CreateEnemy1(go);
			}

			if (args.Input.GetKeyPressed(KEY_F6))
			{
				GameObject* go = new GameObject(gameState->GetEngine());
				go->PRS.SPosition() = spawnPoint2;
				CreateEnemy1(go);
			}

			if (args.Input.GetKeyPressed(KEY_F7))
			{
				GameObject* go = new GameObject(gameState->GetEngine());
				go->PRS.SPosition() = spawnPoint3;
				CreateEnemy1(go);
			}

			if (args.Input.GetKeyPressed(KEY_F8))
			{
				GameObject* go = new GameObject(gameState->GetEngine());
				go->PRS.SPosition() = Vector3(0, 50, 0);
				CreatePlayerMop(go);
			}



		}



	}
}