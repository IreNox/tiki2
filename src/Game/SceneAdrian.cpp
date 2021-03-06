
#if _DEBUG
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

#include "Game/AnimationHandler.h"

#include "Core/EventAnimation.h"

#include "Core/RectangleF.h"
#include "Core/ISoundSystem.h"

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
			SceneGraph.Initialize(RectangleF::Create(-50,-50, 100, 100), 6);


			//GameObject* go = TIKI_NEW GameObject(engine);

#if TIKI_USE_SCENEGRAPH
			//go->GetSceneGraphElement().SetDynamic();
#endif


			/*	go->SModel(args.Content->LoadModel(L"unit_soldier"));

			this->model = go->GModel();
			int count = this->model->AnimationCount();

			auto ah = TIKI_NEW AnimationHandlerDefaultUnit(go->GModel());
			go->GModel()->SetAnimationHandler(ah);

			go->PRS.SScale() = Vector3(0.01f);*/
			//this->AddElement(go);
			GameObject* go = 0;

			for(int i =  -5; i < 6 ; i++)
			{
				go = new GameObject(engine);
				go->SModel(args.Content->LoadModel(L"schinken"));
				IAnimation* anim = go->GModel()->GetAnimation(0);
				anim->SetAnimationSpeed(5.0);
				go->PRS.SScale() = Vector3(0.01f);
				go->PRS.SPosition() = Vector3((float)i , 0, 0);
				go->GetSceneGraphElement().SetDynamic();

				this->AddElement(go);
			}



			//go->GModel()->GetMesh("LP_Backpack")->SetVisible(false);
			//go->GModel()->GetMesh("heavyPlasma")->SetVisible(false);
			//go->GModel()->GetMesh("standartMG")->SetVisible(false);
			//go->GModel()->GetMesh("Laser")->SetVisible(false);

	/*		auto ha = TIKI_NEW AnimationHandlerResearchBuilding(go->GModel());
			go->GModel()->SetAnimationHandler(ha);*/



			//this->model = go->GModel();



			light = TIKI_NEW LightObject(engine);
			light->AddRef();
			light->GetLight()->SetColor(Color(1, 1, 1, 1));
			light->GetLight()->SetRange(750.0f);
			light->PRS.SPosition() = Vector3(-5, 5, 1.5);
			light->PRS.SRotation() = Quaternion::CreateFromYawPitchRoll(-1.59f, -0.92f, 0);

			this->AddElement(light);

			go = TIKI_NEW CameraObject(engine);

			go->PRS.SPosition() = Vector3(0, 0, 5.0f);

			CameraFly* fly = TIKI_NEW CameraFly(engine, go);
			//fly->Release();

			this->AddElement(go);
			//go->Release();

			Scene::Initialize(args);
		}

		void SceneAdrian::Draw(const DrawArgs& args)
		{
//#if TIKI_CULLING
//			for(UINT i = 0; i < drawContent.Count(); i++)
//				drawContent[i]->Draw(args);
//#else
			Scene::Draw(args);
//#endif

			

			engine->sprites->Draw(
				engine->graphics->GetNormalTarget(),
				Rectangle(10, 10, 200, 180)
			);

			engine->sprites->Draw(
				engine->graphics->GetLightTarget(),
				Rectangle(10, 200, 200, 180)
			);

			engine->sprites->Draw(
				engine->graphics->GetScreenTarget(),
				Rectangle(10, 390, 200, 180)
				);

#if _DEBUG
			//engine->graphics->DrawLine(Vector3::Zero, Vector3::UnitX, Color::Red);
			//engine->graphics->DrawLine(Vector3::Zero, Vector3::UnitY, Color::Green);
			//engine->graphics->DrawLine(Vector3::Zero, Vector3::UnitZ, Color::Blue);
#endif

		}

		void SceneAdrian::Update(const UpdateArgs& args)
		{
			GameObject* go = GetMainCamera()->GetGameObject();

			engine->sound->SetListenerPosition(
				go->PRS.GPosition(),
				Vector3::Zero, 
				go->PRS.GetForward(),
				go->PRS.GetUp());


			if(args.Input.GetKeyPressed(KEY_ALPHA8))
			{
				engine->sound->Play(engine->content->LoadSound(L"ambient"), true);
			}

			if(args.Input.GetKeyPressed(KEY_ALPHA7))
			{
				engine->sound->Play3D(engine->content->LoadSound(L"mech_spawn"), Vector3::Zero, true);
			}


			//ANIMATION TIMING EXAMPLE

			//AnimationArgs animArgs(AT_Death);
			//this->model->AnimationHandler->RaiseAnimationEvent(this->model, AnimationArgs(AT_Death));
			//IAnimation* animation = animArgs.animation;

			//if(animation && animation->IsFinished())
			//{
			//	//do stuff at the end of the animation
			//}



#if TIKI_CULLING
			SceneGraph.Update(args);
			drawContent.Clear();
			SceneGraph.Find(drawContent, mainCamera->GetFrustum());
			SceneGraph.LateUpdate(args);
#else
			Scene::Update(args);
#endif

			

			if(args.Input.GetKey(KEY_ALPHA1))
			{
				this->model->AnimationHandler->RaiseAnimationEvent(this->model, AnimationArgs(AT_Idle));
			}
			if(args.Input.GetKey(KEY_ALPHA2))
			{
				this->model->AnimationHandler->RaiseAnimationEvent(this->model, AnimationArgs(AT_Attack));
			}
			if(args.Input.GetKey(KEY_ALPHA3))
			{
				this->model->AnimationHandler->RaiseAnimationEvent(this->model, AnimationArgs(AT_Run));
			}
			if(args.Input.GetKey(KEY_ALPHA4))
			{
				this->model->AnimationHandler->RaiseAnimationEvent(this->model, AnimationArgs(AT_Death));
			}
			if(args.Input.GetKey(KEY_ALPHA5))
			{
				this->model->AnimationHandler->RaiseAnimationEvent(this->model, AnimationArgs(AT_Rocket));
			}
		}
	}
}
#endif