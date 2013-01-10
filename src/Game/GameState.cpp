
#include "Game/GameState.h"
#include "Game/TikiBot.h"

#include "Game/GameHud.h"
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

#include "Game/Rocket.h"


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
			engine->HLog.ConsoleCommand.AddHandler(this);

			hud = new GameHud(this);
			navMesh = new NavigationMesh(engine);
			unitSelection = new UnitSelection(this);
			projectiles = new ProjectileManager(this);

			botFactory = new TikiBotFactory(this);

			defaultMaterial = engine->librarys->CreateResource<IPhysicsMaterial>();
			defaultMaterial->SetRestitution(0.2f);
			defaultMaterial->SetDynamicFriction(0.7f);
			defaultMaterial->SetStaticFriction(0.5f);
			defaultMaterial->AddRef();
		}

		GameState::~GameState()
		{
			SafeDelete(&navMesh);
			SafeDelete(&botFactory);
			SafeDelete(&unitSelection);

			SafeRelease(&hud);
			SafeRelease(&projectiles);

			SafeRelease(&defaultMaterial);

			FOREACH(gameParts, SafeRelease(&gameParts[i]));
		}
		#pragma endregion

		#pragma region Member - Load/Dispose
		void GameState::LoadLevel(Level* level)
		{			
			navMesh->Clear();
			navMesh->Load(
				L"navmesh/navmesh_" + StringAtoW(scene->GLevel()->GetName()),
				Matrix::CreateTranslation(Vector3(0, 0.2f, 0))
			);
		}

		void GameState::InitLevel()
		{
			hud->Init();
			botFactory->Init();
		}

		void GameState::DisposeLevel()
		{
		}
		#pragma endregion

		#pragma region Member - Draw
		void GameState::Draw(const DrawArgs& args)
		{
			hud->Draw(args);
			projectiles->Draw(args);
			unitSelection->Draw(args);

			#if _DEBUG
			if (DrawNavMesh)
			{
				navMesh->Draw(args);

				UInt32 i = 0;
				while (i < scene->GPoints().Count())
				{
					Vector2 pos1 = scene->GPoints()[i]->GPosition();
					Vector3 pos = Vector3(pos1.X, 0, pos1.Y);
					pos.Y = scene->GLevel()->GetTerrain()->SampleHeight(pos);

					// Axis align
					engine->graphics->DrawLine(
						pos - Vector3(-1.0f, 0, 0), pos + Vector3(-1.0f, 0, 0), Color::Yellow
					);

					engine->graphics->DrawLine(
						pos - Vector3(0, -1.0f, 0), pos + Vector3(0, -1.0f, 0), Color::Yellow
					);

					engine->graphics->DrawLine(
						pos - Vector3(0, 0, -1.0f), pos + Vector3(0, 0, -1.0f), Color::Yellow
					);

					i++;
				}
			}

			if (DrawRenderTarget)
			{
				engine->sprites->Draw(engine->graphics->GetDepthTarget(), Rectangle(10, 10, 200, 180));
				engine->sprites->Draw(engine->graphics->GetNormalTarget(), Rectangle(10, 200, 200, 180));
				engine->sprites->Draw(engine->graphics->GetScreenTarget(), Rectangle(10, 400, 200, 180));
			}

			if (DrawPhysX) engine->physics->DrawDebug();
			#endif
		}
		#pragma endregion

		#pragma region Member - Update
		void GameState::Update(const UpdateArgs& args)
		{
			hud->Update(args);
			botFactory->Update(args);
			projectiles->Update(args);
			unitSelection->Update(args);

            FOREACH_PTR_CALL(gameParts, Update(args))

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

					unitSelection->MoveCommand(target, info.Point, args.Input.GetKey(KEY_T), args.Input.GetKey(KEY_LSHIFT));
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
				Ray ray = scene->mainCamera->ScreenPointToRay(args.Input.MousePositionDisplay);
				RaycastHit info;
				if (engine->physics->RayCast(ray, &info))
				{
					GameObject* go = new GameObject(engine);
					go->PRS.SPosition() = info.Point + Vector3(0, 10, 0);
					botFactory->CreateEnemyBuilding(go);
				}
			}

			#pragma region Skills
			// Aoe Damage
			if (args.Input.GetKeyPressed(KEY_R))
			{
				Vector3 target = Vector3::Zero;
				Ray ray = scene->mainCamera->ScreenPointToRay(args.Input.MousePositionDisplay);
				RaycastHit info;
				if (engine->physics->RayCast(ray, &info))
					target = info.Point;

				for (UInt32 i = 0; i < unitSelection->GetSelectedUnits()->Count(); i++)
				{
					TikiBot* bot = unitSelection->GetSelectedUnits()->Get(i)->GetComponent<TikiBot>();
					if (bot != 0 && bot->EntityType() == ET_Hero)
					{
						ProjectileDescription desc;
						desc.Target = target; 
						desc.Shooter = bot;
						desc.Origin = bot->Pos3D();
						desc.Heading = bot->Heading();
						desc.ShooterID = bot->ID();
						desc.Damage = 20; 
						desc.LifeTime = 10.0f;
						GameObject* go = new GameObject(engine);
						Rocket* proj = new Rocket(this, go);
						proj->Init(desc, 30, false);
						projectiles->AddProjectile(proj);
					}
				}
			}

			// AoeHeal
			if (args.Input.GetKeyPressed(KEY_E))
			{
				Vector3 target = Vector3::Zero;
				Ray ray = scene->mainCamera->ScreenPointToRay(args.Input.MousePositionDisplay);
				RaycastHit info;
				if (engine->physics->RayCast(ray, &info))
					target = info.Point;

				for (UInt32 i = 0; i < unitSelection->GetSelectedUnits()->Count(); i++)
				{
					TikiBot* bot = unitSelection->GetSelectedUnits()->Get(i)->GetComponent<TikiBot>();
					if (bot != 0 && bot->EntityType() == ET_Hero)
					{
						ProjectileDescription desc;
						desc.Target = target;
						desc.Shooter = bot;
						desc.Origin = bot->Pos3D();
						desc.Heading = bot->Heading();
						desc.ShooterID = bot->ID();
						desc.Damage = 20; 
						desc.LifeTime = 10.0f;
						GameObject* go = new GameObject(engine);
						Rocket* proj = new Rocket(this, go);
						proj->Init(desc, 30, true);
						projectiles->AddProjectile(proj);
					}
				}
			}
			#pragma endregion

		}
		#pragma endregion

		#pragma region Member - Console
		void GameState::Handle(const HelperLog* sender, const wstring& args)
		{
			if (args == L"exit")
			{
				engine->Exit();
			}
		}
		#pragma endregion
	}
}
