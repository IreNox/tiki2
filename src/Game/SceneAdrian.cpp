
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

#include "Core/RectangleF.h"

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


			GameObject* go = TIKI_NEW GameObject(engine);
			go->GetSceneGraphElement().SetDynamic();

			//go->SModel(args.Content->LoadModel(L"spidermine")); //soldier_l_testForAgga10
			go->SModel(args.Content->LoadModel(L"unit_soldier"));

			this->model = go->GModel();
			int count = this->model->AnimationCount();
			this->model->AnimationHandler.AddHandler(TIKI_NEW AnimationHandlerDefaultUnit(this->model));
			this->spidermine = go;

			go->PRS.SScale() = Vector3(0.01f);

			//sceneGraph.Add(go);
			this->AddElement(go);

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
#if TIKI_CULLING
			for(UINT i = 0; i < drawContent.Count(); i++)
				drawContent[i]->Draw(args);
#else
			Scene::Draw(args);
#endif

			

			engine->sprites->Draw(
				engine->graphics->GetDepthTarget(),
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
			engine->graphics->DrawLine(Vector3::Zero, Vector3::UnitX, Color::Red);
			engine->graphics->DrawLine(Vector3::Zero, Vector3::UnitY, Color::Green);
			engine->graphics->DrawLine(Vector3::Zero, Vector3::UnitZ, Color::Blue);
#endif

		}

		void SceneAdrian::Update(const UpdateArgs& args)
		{
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
				this->model->AnimationHandler.RaiseEvent(this->model, AnimationArgs(Idle));
			}
			if(args.Input.GetKey(KEY_ALPHA2))
			{
				this->model->AnimationHandler.RaiseEvent(this->model, AnimationArgs(Walk));
			}
			if(args.Input.GetKey(KEY_ALPHA3))
			{
				this->model->AnimationHandler.RaiseEvent(this->model, AnimationArgs(Run));
			}
			if(args.Input.GetKey(KEY_ALPHA4))
			{
				this->model->AnimationHandler.RaiseEvent(this->model, AnimationArgs(Attack));
			}
			if(args.Input.GetKeyPressed(KEY_ALPHA5))
			{
				this->model->AnimationHandler.RaiseEvent(this->model, AnimationArgs(Death));
			}

			//links
			if(args.Input.GetKey(KEY_NUMPAD4))
			{
				//this->selectionRectangle.X -= 10.0f * (float)args.Time.ElapsedTime;
				this->spidermine->PRS.SPosition() += Vector3(-1,0,0) * (float)args.Time.ElapsedTime;
			}

			//rechts
			if(args.Input.GetKey(KEY_NUMPAD6))
			{
				//this->selectionRectangle.X += 10.0f * (float)args.Time.ElapsedTime;
				this->spidermine->PRS.SPosition() += Vector3(1,0,0) * (float)args.Time.ElapsedTime;
			}

			//hoch
			if(args.Input.GetKey(KEY_NUMPAD8))
			{
				//this->selectionRectangle.Y -= 10.0f * (float)args.Time.ElapsedTime;
				this->spidermine->PRS.SPosition() += Vector3(0,0,-1) * (float)args.Time.ElapsedTime;
			}

			//runter
			if(args.Input.GetKey(KEY_NUMPAD5))
			{
				//this->selectionRectangle.Y += 10.0f * (float)args.Time.ElapsedTime;
				this->spidermine->PRS.SPosition() += Vector3(0,0,1) * (float)args.Time.ElapsedTime;
			}
		}
	}
}
