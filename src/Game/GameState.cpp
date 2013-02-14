
#include "Game/GameState.h"
#include "Game/TikiBot.h"

#include "Game/Cheater.h"
#include "Game/GameHud.h"
#include "Game/SceneLevel.h"
#include "Game/DebugConsole.h"
#include "Game/UnitSelection.h"
#include "Game/ProjectileManager.h"

#include "Core/IPhysics.h"
#include "Core/IGraphics.h"
#include "Core/ISpriteBatch.h"
#include "Core/ISoundSystem.h"
#include "Core/IContentManager.h"

#include "Game/GoalThink.h"
#include "Game/Bullet.h"
#include "Game/AnimationHandler.h"
#include "Game/BuildSlot.h"

#include "Game/TikiBotFactory.h"

#include "Game/Rocket.h"
#include "Game/CameraRTS.h"

namespace TikiEngine
{
	using namespace TikiEngine::Scripts;

	namespace Game
	{
		#pragma region Class
		GameState::GameState(Engine* engine, SceneLevel* scene)
			: EngineObject(engine), scene(scene), resource(0.0), followHero(false)
#if _DEBUG
			, DrawNavMesh(false), DrawRenderTarget(false), DrawPhysX(false), DrawHud(true)
#endif
		{
			engine->HLog.ConsoleCommand.AddHandler(this);

			hud = TIKI_NEW GameHud(this);
			cheater = TIKI_NEW Cheater(this);
			console = TIKI_NEW DebugConsole(engine);
			navMesh = TIKI_NEW NavigationMesh(engine);
			unitSelection = TIKI_NEW UnitSelection(this);
			projectiles = TIKI_NEW ProjectileManager(this);

			botFactory = TIKI_NEW TikiBotFactory(this);

			defaultFont = engine->librarys->CreateResource<IFont>();
			defaultFont->Create(L"Calibri", 12);

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
			SafeRelease(&cheater);
			SafeRelease(&console);
			SafeRelease(&projectiles);

			SafeRelease(&defaultMaterial);

			FOREACH_CODE(gameParts, SafeRelease(&gameParts[i]));
		}
		#pragma endregion

		#pragma region Member - Load/Dispose
		void GameState::LoadLevel(Level* level)
		{			
			navMesh->Clear();
			navMesh->Load(
				L"navmesh/navmesh_" + StringAtoW(scene->GLevel()->GetName()),
				Matrix::CreateTranslation(0, 0.2f, 0)
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
#if _DEBUG
			if (DrawHud) hud->Draw(args);
#else
			hud->Draw(args);
#endif

			if (consoleEnabled)
				console->Draw(args);

			projectiles->Draw(args);
			unitSelection->Draw(args);

			FOREACH_PTR_CALL(gameParts, Draw(args))

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
#if _DEBUG
			if (DrawHud) hud->Update(args);
#else
			hud->Update(args);
#endif

			if (consoleEnabled)
				console->Update(args);

			botFactory->Update(args);
			projectiles->Update(args);
			unitSelection->Update(args);

            FOREACH_PTR_CALL(gameParts, Update(args))

			#if _DEBUG
			if (args.Input.GetKeyPressed(KEY_F2)) DrawNavMesh = !DrawNavMesh;
			if (args.Input.GetKeyPressed(KEY_F3)) DrawRenderTarget = !DrawRenderTarget;
			if (args.Input.GetKeyPressed(KEY_F4)) DrawPhysX = !DrawPhysX;
			if (args.Input.GetKeyPressed(KEY_F6)) DrawHud = !DrawHud;

			if (args.Input.GetKeyPressed(KEY_F7))
			{
				engine->sound->Play(engine->content->LoadSound(L"Mech_Spawn"));
			}
			#endif

			if (args.Input.GetKeyPressed(KEY_Z)) followHero = !followHero;

			CameraRTS* rtsCam = scene->GetMainCamera()->GetGameObject()->GetComponent<CameraRTS>();	
			TikiBot* heroBot = GetPart<PlayerBase>(0)->Hero->GetComponent<TikiBot>();
			if(heroBot->IsAlive() && (args.Input.GetKey(KEY_SPACE) || followHero))
				rtsCam->SetCameraTarget(heroBot->GetGameObject());
			else
				rtsCam->ClearCameraTarget();

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
					}

					unitSelection->MoveCommand(target, info.Point, args.Input.GetKey(KEY_T), args.Input.GetKey(KEY_LSHIFT));
				}
			}

// 			if (args.Input.GetKeyPressed(KEY_R))
// 			{
// 				Vector3 target = Vector3::Zero;
// 				Ray ray = scene->mainCamera->ScreenPointToRay(args.Input.MousePositionDisplay);
// 				RaycastHit info;
// 				if (engine->physics->RayCast(ray, &info))
// 					target = info.Point;
// 
// 				for (UInt32 i = 0; i < unitSelection->GetSelectedUnits()->Count(); i++)
// 				{
// 					TikiBot* bot = unitSelection->GetSelectedUnits()->Get(i)->GetComponent<TikiBot>();
// 					if (bot != 0 && bot->EntityType() == ET_Hero)
// 					{
// 						ProjectileDescription desc;
// 						desc.Target = target; 
// 						desc.Shooter = bot;
// 						desc.Origin = bot->Pos3D();
// 						desc.Heading = bot->Heading();
// 						desc.ShooterID = bot->ID();
// 						desc.Damage = 20; 
// 						desc.LifeTime = 10.0f;
// 						GameObject* go = TIKI_NEW GameObject(engine);
// 						Rocket* proj = TIKI_NEW Rocket(this, go);
// 						proj->Init(desc, 30, false);
// 						projectiles->AddProjectile(proj);
// 					}
// 				}
// 			}

		}
		#pragma endregion

		#pragma region Member - Console
		void GameState::Handle(const HelperLog* sender, const wstring& args)
		{
			cheater->DoCheat(args);

			if (args == L"exit")
			{
				engine->Exit();
			}
		}
		#pragma endregion
	}
}
