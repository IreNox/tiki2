
#include "Game/GameState.h"
#include "Game/TikiBot.h"
#include "Game/SceneLevel.h"
#include "Game/UnitSelection.h"

#include "Core/IPhysics.h"
#include "Core/IGraphics.h"
#include "Core/ISpriteBatch.h"

#include "Game/GoalThink.h"
#include "Game/Bullet.h"
#include "Game/AnimationHandlerDefaultUnit.h"


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

			spawnRegulator = new Regulator(0.01);

		}

		GameState::~GameState()
		{
			projectiles.Clear();

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

		void GameState::AddProjectile(GameObject* go)
		{
			projectiles.Add(go);
		}

		void GameState::AddBot(const Vector3& pos)
		{
			// Create go
			GameObject* botGo = new GameObject(engine);
			botGo->SModel(engine->content->LoadModel(L"soldier_enemy"));
			botGo->GModel()->animationEvent->SetHandlerOnly(new AnimationHandlerDefaultUnit(botGo->GModel()));

			botGo->PRS.SPosition() = pos;

			// Create bot
			TikiBotDescription botDesc;
			botDesc.Faction = 1;
			(new TikiBot(this, botGo, botDesc));

			TikiBot* bot = botGo->GetComponent<TikiBot>();
			bot->SetScale(0.06f);
			bot->CreateNav(navMesh);
			//bot->GetController()->SetCenter(pos);


			// set list of waypoints
			std::list<Vector2> wayPoints;
			wayPoints.push_back(Vector2(0, -100));
			wayPoints.push_back(Vector2(100, -100));
			wayPoints.push_back(Vector2(100, 100));
			wayPoints.push_back(Vector2(-100, 100));
			wayPoints.push_back(Vector2(-100, -100));
			bot->GetBrain()->AddGoalPatrol(wayPoints);

			scene->AddElement(botGo);
		}

		#pragma endregion

		#pragma region Member - Load/Dispose
		bool GameState::LoadLevel(Level* level)
		{			
			navMesh->Clear();
			navMesh->Load(
				L"navmesh/navmesh_" + StringAtoW(scene->GetLevel()->GetName()),
				Matrix::CreateTranslation(Vector3(0, 6, 0))
			);

			//TikiBotDescription desc;

			UInt32 i = 0;
			while (i < scene->objects.Count())
			{
				TikiBot* bot = scene->objects[i]->GetComponent<TikiBot>();

				if (bot != 0)
				{
					//bot->Init(desc);
					bot->CreateNav(navMesh);
 					Vector3 pos = bot->GetGameObject()->PRS.GPosition();
 					pos = pos + Vector3(0, 30, 0);
 					bot->GetController()->SetCenter(pos);

					// if we have a patrol bot, set the wayPoints.
                    if (bot->GetFaction() == 1)
                    {
                        std::list<Vector2> wayPoints;
                        wayPoints.push_back(Vector2(0, -100));
                        wayPoints.push_back(Vector2(100, -100));
                        wayPoints.push_back(Vector2(100, 100));
                        wayPoints.push_back(Vector2(-100, 100));
                        wayPoints.push_back(Vector2(-100, -100));
                        bot->GetBrain()->AddGoalPatrol(wayPoints);
                    }
                   // if (bot->GetFaction() == 0)
                    //    bot->TakePossession();


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
			// spawn bots if it's time
			//if (spawnRegulator->IsReady())
			if (args.Input.GetKeyPressed(KEY_F5))
			{
				AddBot(Vector3(150, 50, 150));
			}


			hud->Update(args);
			unitSelection->Update(args);


			for(UInt32 i = 0; i < projectiles.Count(); i++)
			{
				GameObject* go = projectiles[i];

				if (go != 0)
				{
					go->Update(args);

					Projectile* p = go->GetComponent<Projectile>();
					if (p != 0 && p->IsDead())
					{
						projectiles.Remove(go);
						SafeRelease(&go);
					}
				}
			}

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
								if (args.Input.GetKey(KEY_T))
									bot->GetBrain()->QueueGoalAttackMove(info.Point);
								else
									bot->GetBrain()->QueueGoalMoveToPosition(info.Point);
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
										engine->HLog.Write("Target found.");
										bot->GetBrain()->AddGoalAttackGlobalTarget(target);

									}
								}
								else
								{
									bot->GetBrain()->RemoveAllSubgoals();
									bot->GetBrain()->AddGoalMoveToPosition(info.Point);
								}

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
