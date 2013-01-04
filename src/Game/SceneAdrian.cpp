
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
#if TIKI_USE_SCENEGRAPH
			SceneGraph.Initialize(RectangleF::Create(-50,-50, 100, 100), 6);
#endif

			GameObject* go = new GameObject(engine);

			go->SModel(args.Content->LoadModel(L"spidermine")); //soldier_l_testForAgga10

			this->model = go->GModel();
			this->spidermine = go;
			//this->model->AnimationHandler.AddHandler(new AnimationHandlerDefaultUnit(this->model));

			//this->bone = this->model->GetBone("weapon_MgTip_bn");

			go->PRS.SScale() = Vector3(0.01f);

			//sceneGraph.Add(go);
			this->AddElement(go);

			light = new LightObject(engine);
			light->AddRef();
			light->GetLight()->SetColor(Color(1, 1, 1, 1));
			light->GetLight()->SetRange(750.0f);
			light->PRS.SPosition() = Vector3(-5, 5, 1.5);
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

			engine->sprites->Draw(
				engine->graphics->GetScreenTarget(),
				Rectangle(10, 390, 200, 180)
				);

			List<Vector3> pos;

			for(int i = 0;  i < 12; i++)
			{
				pos.Add(
					Vector3::TransformCoordinate(
					Vector3(0.5f,0,0), 
					Matrix::CreateRotationY(i * 0.0174532925f * 360 / 12)));
			}

			for(int i = 0; i < 12; i++)
				args.Graphics->DrawLine(pos[i%12], pos[(i+1)% 12], Color::Black);

		}

		void SceneAdrian::Update(const UpdateArgs& args)
		{

			Scene::Update(args);

			//this->drawBla.Clear();
			//this->SceneGraph.Find(drawBla, 
			//	Vector3(0.0f), 
			//	0.5f, 
			//	[](GameObject* go) -> bool { return go->PRS.GPosition().X < 0; } 
			//);
			
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

			if(args.Input.GetMousePressed(MB_Left))
			{
				GameObject* go = new GameObject(this->engine);
				Vector2 pos = args.Input.MousePosition;
				pos *= 100;
				pos += Vector2(-50);
				go->PRS.SPosition() = Vector3(pos.X, 0, pos.Y);
				go->Update(args);

#if TIKI_USE_SCENEGRAPH
				SceneGraph.Add(go);
#endif
			}
		}
	}
}
