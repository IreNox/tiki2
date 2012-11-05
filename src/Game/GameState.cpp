
#include "Game/GameState.h"
#include "Game/TikiBot.h"
#include "Game/SceneLevel.h"
#include "Game/UnitSelection.h"

#include "Core/IPhysics.h"
#include "Core/IGraphics.h"
#include "Core/ISpriteBatch.h"

#include "Game/GoalThink.h"

namespace TikiEngine
{
	namespace Game
	{
		#pragma region Class
		GameState::GameState(Engine* engine, SceneLevel* scene)
			: EngineObject(engine), scene(scene), resource1(0), resource2(0)
#if _DEBUG
			, DrawNavMesh(false), DrawRenderTarget(false), DrawPhysX(false)
#endif
		{
			hud = new GameHud(this);
			navMesh = new NavigationMesh(engine);
			unitSelection = new UnitSelection(this);
		}

		GameState::~GameState()
		{
			SafeRelease(&hud);
			SafeDelete(&navMesh);
			SafeDelete(&unitSelection);
		}
		#pragma endregion

		#pragma region Member - Get
		Engine* GameState::GetEngine()
		{
			return engine;
		}

		SceneLevel* GameState::GetScene()
		{
			return scene;
		}


		UInt64 GameState::GetResource1()
		{
			return resource1;
		}

		UInt64 GameState::GetResource2()
		{
			return resource1;
		}
		#pragma endregion

		#pragma region Member - Load/Dispose
		bool GameState::LoadLevel(Level* level)
		{			
			navMesh->Clear();
			navMesh->Load(
				L"navmesh_" + StringAtoW(scene->GetLevel()->GetName()),
				Matrix::CreateTranslation(Vector3(0, 6, 0))
			);

			UInt32 i = 0;
			while (i < scene->objects.Count())
			{
				TikiBot* bot = scene->objects[i]->GetComponent<TikiBot>();

				if (bot != 0)
				{
					bot->CreateNav(navMesh);
 					Vector3 pos = bot->GetGameObject()->PRS.GPosition();
 					pos = pos + Vector3(0, 60, 0);
 					bot->GetController()->SetCenter(pos);
				}

				i++;
			}

			return true;
		}

		void GameState::DisposeLevel()
		{
		}
		#pragma endregion

		#pragma region Member - Draw/Update
		void GameState::Draw(const DrawArgs& args)
		{
			hud->Draw(args);
			unitSelection->Draw(args);
			#if _DEBUG
			if (DrawNavMesh) navMesh->Draw(args);

			if (DrawRenderTarget)
			{
				engine->sprites->Draw(engine->graphics->GetDepthTarget(), Rectangle(10, 10, 200, 180));
				engine->sprites->Draw(engine->graphics->GetNormalTarget(), Rectangle(10, 200, 200, 180));
				engine->sprites->Draw(engine->graphics->GetScreenTarget(), Rectangle(10, 400, 200, 180));
			}

			if (DrawPhysX) engine->physics->DrawDebug();
			#endif
		}

		void GameState::Update(const UpdateArgs& args)
		{
			hud->Update(args);
			unitSelection->Update(args);

			#if _DEBUG
			if (args.Input.GetKeyPressed(KEY_F2)) DrawNavMesh = !DrawNavMesh;
			if (args.Input.GetKeyPressed(KEY_F3)) DrawRenderTarget = !DrawRenderTarget;
			if (args.Input.GetKeyPressed(KEY_F4)) DrawPhysX = !DrawPhysX;
			#endif

			if(args.Input.GetMousePressed(MB_Right))
			{
				Ray ray = scene->mainCamera->ScreenPointToRay(args.Input.MousePositionDisplay);
				RaycastHit info;

				if (engine->physics->RayCast(ray, &info))
				{
					// 
					ICollider* coll = info.Collider;
					if (coll)
					{
						if(coll->GetDynamic())
						{
							coll->GetRigidBody()->SetVelocity(Vector3(0, 10, 0));
							coll->GetRigidBody()->SetAngularVelocity(Vector3(5, 10, 0));
						}
					}
					
					;

					UInt32 i = 0;
					while (i < unitSelection->GetSelectedUnits()->Count())
					{
						TikiBot* bot = unitSelection->GetSelectedUnits()->Get(i)->GetComponent<TikiBot>();

						if (bot != 0)
						{
							// if the shift key is pressed down at the same time as clicking then the
							// movement command will be queued
							if (args.Input.GetKey(KEY_LSHIFT))
							{
								bot->GetBrain()->QueueGoalMoveToPosition(info.Point);
							}
							else
							{
								bot->GetBrain()->RemoveAllSubgoals();
								bot->GetBrain()->AddGoalMoveToPosition(info.Point);
							}

						}

						i++;
					}
				}
			}
		}
		#pragma endregion


		/*void GetSelectedAvailableFunctions(List<UnitFunctions>* list);
		void ExecuteUnitFunction(UnitFunctions func);*/

	}
}
