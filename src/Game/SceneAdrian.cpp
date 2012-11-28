
#include "Game/SceneAdrian.h"

#include "Core/IMeshRenderer.h"
#include "Core/LibraryManager.h"

#include "Core/DefaultVertex.h"

#include "Core/CameraObject.h"

#include "Core/IContentManager.h"

#include "Game/CameraFly.h"

#include "Core/ISpriteBatch.h"
#include "Core/IGraphics.h"

#include "Core/LightObject.h"

namespace TikiEngine
{
	namespace Game
	{
		using namespace TikiEngine::Scripts;
		using namespace TikiEngine::Objects;
		using namespace TikiEngine::Vertices;
		using namespace TikiEngine::Components;

		SceneAdrian::SceneAdrian(Engine* engine)
			: Scene(engine)
		{
		}

		SceneAdrian::~SceneAdrian()
		{
			SafeRelease(&light);

		}

		void SceneAdrian::Initialize(const InitializationArgs& args)
		{
			GameObject* go = new GameObject(engine);

			go->SModel(args.Content->LoadModel(L"soldier")); //soldier_l_testForAgga10

			this->model = go->GModel();

			IAnimation* walk = go->GModel()->GetAnimation("walk");
			IAnimation* attack = go->GModel()->GetAnimation("attack");
			IAnimation* death = go->GModel()->GetAnimation("death");
			IAnimation* run = go->GModel()->GetAnimation("run");
			IAnimation* breakdance = go->GModel()->GetAnimation("breakdance");

			//bone = model->GetBone("R_hand_bn");
			//if(bone == 0)
			//	_CrtDbgBreak();


			//walk->SetNextAnimation(attack);
			//attack->SetNextAnimation(death02);
			//death02->SetNextAnimation(walk);

			//walk->SetLoop(false);
			//attack->SetLoop(false);
			//death02->SetLoop(false);

			//this->animations.Add(walk);
			this->animations.Add(attack);
			this->animations.Add(death);
			this->animations.Add(run);
			//this->animations.Add(breakdance);

			this->animationId = 0;

			this->model->BlendToAnimation(walk);

			go->PRS.SScale() = Vector3(0.01f);

			this->AddElement(go);

			light = new LightObject(engine);
			light->AddRef();
			light->GetLight()->SetColor(Color(1, 1, 1, 1));
			light->GetLight()->SetRange(750.0f);
			light->PRS.SRotation() = Quaternion::CreateFromYawPitchRoll(-1.59f, -0.92f, 0);
			this->AddElement(light);

			go = new CameraObject(engine);
			go->PRS.SPosition() = Vector3(0, 0, 5.0f);

			CameraFly* fly = new CameraFly(engine, go);
			//fly->Release();

			this->AddElement(go);
			//go->Release();



			Scene::Initialize(args);
		}

		void SceneAdrian::Draw(const DrawArgs& args)
		{
			Scene::Draw(args);

			engine->sprites->Draw(
				engine->graphics->GetDepthTarget(),
				Rectangle(10, 10, 200, 180)
			);

			engine->sprites->Draw(
				engine->graphics->GetNormalTarget(),
				Rectangle(10, 200, 200, 180)
				);


		}

		void SceneAdrian::Update(const UpdateArgs& args)
		{
			Scene::Update(args);
			
			if(args.Input.GetKeyPressed(TikiEngine::KEY_SPACE))
			{
  				this->animationId = (animationId + 1) % this->animations.Count();
				//this->model->SetAnimation(this->animations[animationId]);
				this->model->BlendToAnimation(this->animations[animationId]);
			}

			if(args.Input.GetKeyPressed(KEY_NUMPAD0))
			{
				bone->IgnoreUpdate(true);
			}
			if(args.Input.GetKeyPressed(KEY_NUMPAD1))
			{
				bone->IgnoreUpdate(false);
			}
		}
	}
}
