
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

#include "Game/AnimationHandlerDefaultUnit.h"
#include "Core/EventAnimation.h"

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
			this->model->AnimationHandler.AddHandler(new AnimationHandlerDefaultUnit(this->model));

			this->bone = this->model->GetBone("weapon_MgTip_bn");

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

			if(bone != 0)
			{

				Vector3 pos = bone->Position() * 0.01f;
				args.Graphics->DrawLine(pos, pos + bone->Forward(), Color::Red);
			}
		}

		void SceneAdrian::Update(const UpdateArgs& args)
		{
			Scene::Update(args);
			
			if(args.Input.GetKeyPressed(KEY_ALPHA1))
			{
				this->model->AnimationHandler.RaiseEvent(this->model, AnimationArgs(Idle));
			}
			if(args.Input.GetKeyPressed(KEY_ALPHA2))
			{
				this->model->AnimationHandler.RaiseEvent(this->model, AnimationArgs(Walk));
			}
			if(args.Input.GetKeyPressed(KEY_ALPHA3))
			{
				this->model->AnimationHandler.RaiseEvent(this->model, AnimationArgs(Run));
			}
			if(args.Input.GetKeyPressed(KEY_ALPHA4))
			{
				this->model->AnimationHandler.RaiseEvent(this->model, AnimationArgs(Attack));
			}
			if(args.Input.GetKeyPressed(KEY_ALPHA5))
			{
				this->model->AnimationHandler.RaiseEvent(this->model, AnimationArgs(Death));
			}
		}
	}
}
