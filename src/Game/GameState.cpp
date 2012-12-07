
#include "Game/GameState.h"
#include "Game/TikiBot.h"
#include "Game/SceneLevel.h"
#include "Game/UnitSelection.h"
#include "Game/ProjectileManager.h"

#include "Core/IPhysics.h"
#include "Core/IGraphics.h"
#include "Core/ISpriteBatch.h"

#include "Game/GoalThink.h"
#include "Game/Bullet.h"
#include "Game/AnimationHandlerDefaultUnit.h"
#include "Game/BuildSlot.h"

#include "Game/TikiBotFactory.h"

namespace TikiEngine
{
	namespace Game
	{
		#pragma region Class
		GameState::GameState(Engine* engine, SceneLevel* scene)
			: EngineObject(engine), scene(scene), resource(0.0)
#if _DEBUG
			, DrawNavMesh(false), DrawRenderTarget(false), DrawPhysX(false)
#endif
		{
			hud = new GameHud(this);
			navMesh = new NavigationMesh(engine);
			unitSelection = new UnitSelection(this);
			projectiles = new ProjectileManager(this);

			botFactory = new TikiBotFactory(this);
		}

		GameState::~GameState()
		{
			SafeDelete(&navMesh);
			SafeDelete(&botFactory);
			SafeDelete(&unitSelection);

			SafeRelease(&hud);
			SafeRelease(&projectiles);
		}
		#pragma endregion

		#pragma region Member - Load/Dispose
		void GameState::LoadLevel(Level* level)
		{			
			navMesh->Clear();
			navMesh->Load(
				L"navmesh/navmesh_" + StringAtoW(scene->GLevel()->GetName()),
				Matrix::CreateTranslation(Vector3(0, 6, 0))
			);

			botFactory->Init();

			//UInt32 i = 0;
			//while (i < scene->GetElements().Count())
			//{
			//	TikiBot* bot = scene->GetElements()[i]->GetComponent<TikiBot>();

			//	if (bot != 0)
			//	{
			//		bot->CreateNav(navMesh);
 			//		Vector3 pos = bot->GetGameObject()->PRS.GPosition();
 			//		pos = pos + Vector3(0, 30, 0);
 			//		bot->GetController()->SetCenter(pos);

			//		// if we have a patrol bot, set the wayPoints.
			//      if (bot->GetFaction() == 1)
			//      {
			//			std::list<Vector2> wayPoints;
			//			wayPoints.push_back(Vector2(0, -100));
			//			wayPoints.push_back(Vector2(100, -100));
			//			wayPoints.push_back(Vector2(100, 100));
			//			wayPoints.push_back(Vector2(-100, 100));
			//			wayPoints.push_back(Vector2(-100, -100));
			//			bot->GetBrain()->AddGoalPatrol(wayPoints);
			//		}
			//	}

			//	i++;
			//}
		}

		void GameState::DisposeLevel()
		{
		}
		#pragma endregion

		#pragma region Member - Draw/Update
		void GameState::Draw(const DrawArgs& args)
		{
			hud->Draw(args);
			projectiles->Draw(args);
			unitSelection->Draw(args);

			#if _DEBUG
			if (DrawNavMesh) navMesh->Draw(args);

			if (DrawRenderTarget)
			{
				engine->sprites->Draw(scene->temp, Rectangle(10, 10, 200, 180));
				engine->sprites->Draw(engine->graphics->GetNormalTarget(), Rectangle(10, 200, 200, 180));
				engine->sprites->Draw(engine->graphics->GetScreenTarget(), Rectangle(10, 400, 200, 180));
			}

			if (DrawPhysX) engine->physics->DrawDebug();
			#endif
		}

		void GameState::Update(const UpdateArgs& args)
		{
			//// spawn bots if it's time
			////if (spawnRegulator->IsReady())
 			//if (args.Input.GetKeyPressed(KEY_F5))
 			//{
 			//	GameObject* go = new GameObject(engine);
 			//	go->PRS.SPosition() = Vector3(150, 50, 150);
 			//	botFactory->CreateEnemy1(go);
 			//	//AddBot(Vector3(150, 50, 150));
 			//}
			
			hud->Update(args);
			botFactory->Update(args);
			projectiles->Update(args);
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
					TikiBot* target = 0;

					ICollider* coll = info.Collider;
					if (coll)
					{
						target = coll->GetGameObject()->GetComponent<TikiBot>();

						if(coll->GetDynamic())
						{
							coll->GetRigidBody()->SetVelocity(Vector3(0, 10, 0));
							coll->GetRigidBody()->SetAngularVelocity(Vector3(5, 10, 0));
						}
					}
					
					UInt32 i = 0;
					while (i < unitSelection->GetSelectedUnits()->Count())
					{
						TikiBot* bot = unitSelection->GetSelectedUnits()->Get(i)->GetComponent<TikiBot>();

						if (bot != 0)
						{
							//bot->TakePossession();

							// if the shift key is pressed down at the same time as clicking then the
							// movement command will be queued
							if (args.Input.GetKey(KEY_LSHIFT))
							{
								if (bot->EntityType() != ET_Tower)
								{
									if (args.Input.GetKey(KEY_T))
										bot->GetBrain()->QueueGoalAttackMove(info.Point);
									else
										bot->GetBrain()->QueueGoalMoveToPosition(info.Point);
								}

							}
							else if (args.Input.GetKey(KEY_T))
							{
								bot->GetBrain()->RemoveAllSubgoals();
								bot->GetBrain()->AddGoalAttackMove(info.Point);
							}
							else
							{
								if (target != 0)
								{
									// don't attack yourself dude
									if (target->ID() != bot->ID())
									{
										bot->GetBrain()->RemoveAllSubgoals();
										//engine->HLog.Write("Target found.");
										bot->GetBrain()->AddGoalAttackGlobalTarget(target);

									}
								}
								else
								{
									if (bot->EntityType() != ET_Tower)
									{
										bot->GetBrain()->RemoveAllSubgoals();
										bot->GetBrain()->AddGoalMoveToPosition(info.Point);
									}
								}

							}

						}

						i++;
					}
				}
			}


			// Handle tower 
			if (args.Input.GetKeyPressed(KEY_F9))
			{
				UInt32 i = 0;
				while (i < unitSelection->GetSelectedSlots()->Count())
				{
					GameObject* go = unitSelection->GetSelectedSlots()->Get(i);
					BuildSlot* slot = go->GetComponent<BuildSlot>();
					
					// only create once
					if (slot->Enabled())
					{
						slot->Disable();
						botFactory->CreatePlayerTower(go);
					}

					i++;
				}
			}


			if (args.Input.GetKeyPressed(KEY_F6))
			{
				UInt32 i = 0;
				while (i < unitSelection->GetSelectedSlots()->Count())
				{
					GameObject* go = unitSelection->GetSelectedSlots()->Get(i);
					TikiBot* b = go->GetComponent<TikiBot>();
					b->ReduceHealth(100);

					i++;
				}
			}



		}
		#pragma endregion
	}
}
