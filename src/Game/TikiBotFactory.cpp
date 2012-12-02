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
			
			interval = 30.0;
			elapsed = 0;
		}

		TikiBotFactory::~TikiBotFactory()
		{
		}

		void TikiBotFactory::Init()
		{
			const List<LevelPoint*>& points = gameState->GetScene()->GPoints();

			UInt32 i = 0;
			while (i < points.Count())
			{
				switch (points[i]->GType())
				{
				case 0:
					break;
				case 2:
					wayPoints.push_back(points[i]->GPosition());
					break;
				case 3:
					spawnPoints.Add(Vector3(points[i]->GPosition().X, gameState->GetScene()->GLevel()->GetTerrain()->GElevation(), points[i]->GPosition().Y));
					break;
				}

				i++;
			}		
		}

		void TikiBotFactory::SetSpawnInterval( double interval )
		{
			this->interval = interval;
		}

		void TikiBotFactory::CreateEnemy1(GameObject* go)
		{
			// Set Model
			go->SModel(gameState->GetEngine()->content->LoadModel(L"soldier"));
			go->GModel()->AnimationHandler.AddHandler(new AnimationHandlerDefaultUnit(go->GModel()));

			// Create bot
			TikiBotDescription botDesc;
			botDesc.Faction = 1;
			botDesc.Height = 9.0f;
			botDesc.Radius = 3.5f;
			botDesc.MaxHealth = 100;			

			TikiBot* bot = new TikiBot(gameState, go, botDesc);
			bot->SetScale(0.06f);
			bot->CreateNav(gameState->GetNavMesh());

			if (count(wayPoints.begin(), wayPoints.end(), 1) != 0)
			{
				bot->GetBrain()->AddGoalPatrol(wayPoints);
			}

			gameState->GetScene()->AddElement(go);
		}

		void TikiBotFactory::CreatePlayerMop(GameObject* go)
		{
			// Set Model
			go->SModel(gameState->GetEngine()->content->LoadModel(L"marine_l"));
			go->GModel()->AnimationHandler.AddHandler(new AnimationHandlerDefaultUnit(go->GModel()));

			// Create bot
			TikiBotDescription botDesc;
			botDesc.Faction = 0;
			botDesc.Height = 9.0f;
			botDesc.Radius = 3.5f;
			botDesc.MaxHealth = 500;

			TikiBot* bot = new TikiBot(gameState, go, botDesc);
			bot->SetScale(0.06f);
			bot->CreateNav(gameState->GetNavMesh());

			gameState->GetScene()->AddElement(go);
		}

		void TikiBotFactory::Update( const UpdateArgs& args )
		{
			//if (spawnRegulator->IsReady())
			//elapsed += args.Time.ElapsedTime;

			if (elapsed > interval)
			{
				elapsed -= interval;

				// spawn from three sides
				UInt32 i = 0;
				while (i < spawnPoints.Count())
				{
					GameObject* go = new GameObject(gameState->GetEngine());
					go->PRS.SPosition() = spawnPoints[i];
					CreateEnemy1(go);

					i++;
				}
			}

#if _DEBUG
			if (args.Input.GetKeyPressed(KEY_F5))
			{
				GameObject* go = new GameObject(gameState->GetEngine());
				go->PRS.SPosition() = spawnPoints[0];
				CreateEnemy1(go);
			}

			if (args.Input.GetKeyPressed(KEY_F8))
			{
				GameObject* go = new GameObject(gameState->GetEngine());
				go->PRS.SPosition() = Vector3(0, gameState->GetScene()->GLevel()->GetTerrain()->GElevation(), 0);
				CreatePlayerMop(go);
			}
#endif
		}
	}
}