
#include "Game/GameState.h"
#include "Game/TikiBot.h"
#include "Game/SceneLevel.h"

#include "Core/IPhysics.h"
#include "Core/IGraphics.h"
#include "Core/ISpriteBatch.h"

namespace TikiEngine
{
	namespace Game
	{
		#pragma region Class
		GameState::GameState(Engine* engine, SceneLevel* scene)
			: EngineObject(engine), scene(scene), resource1(0), resource2(0)
#if _DEBUG
			, drawNavMesh(false), drawRenderTarget(false)
#endif
		{
			hud = new GameHud(this);
			navMesh = new NavigationMesh(engine);
		}

		GameState::~GameState()
		{
			SafeRelease(&hud);
		}
		#pragma endregion

		#pragma region Member - Get
		Engine* GameState::GetEngine()
		{
			return engine;
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

			#if _DEBUG
			if (drawNavMesh) navMesh->Draw(args);

			if (drawRenderTarget)
			{
				engine->sprites->Draw(engine->graphics->GetDepthTarget(), Rectangle(10, 10, 200, 180));
				engine->sprites->Draw(engine->graphics->GetNormalTarget(), Rectangle(10, 200, 200, 180));
			}
			#endif
		}

		void GameState::Update(const UpdateArgs& args)
		{
			hud->Update(args);

			#if _DEBUG
			if (args.Input.GetKeyPressed(KEY_F2)) drawNavMesh = !drawNavMesh;
			if (args.Input.GetKeyPressed(KEY_F3)) drawRenderTarget = !drawRenderTarget;
			#endif

			if(args.Input.MouseButtons[1])
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
					
					UInt32 i = 0;
					while (i < scene->objects.Count())
					{
						TikiBot* bot = scene->objects[i]->GetComponent<TikiBot>();

						if (bot != 0)
						{
							bot->GotoLocation(info.Point);
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
