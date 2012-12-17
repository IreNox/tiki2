
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
			this->sceneGraph.Initialize(RectangleF::Create(-50,-50, 100, 100), 10);
			this->selectionRectangle = RectangleF::Create(0,0,50,50);
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

#if _DEBUG
			this->sceneGraph.Draw(args);

			args.Graphics->DrawLine(selectionRectangle.TopLeft(), selectionRectangle.TopRight(), Color::Black);
			args.Graphics->DrawLine(selectionRectangle.TopRight(), selectionRectangle.BottomRight(), Color::Black);
			args.Graphics->DrawLine(selectionRectangle.BottomRight(), selectionRectangle.BottomLeft(), Color::Black);
			args.Graphics->DrawLine(selectionRectangle.BottomLeft(), selectionRectangle.TopLeft(), Color::Black);
#endif
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

			//links
			if(args.Input.GetKey(KEY_NUMPAD4))
			{
				this->selectionRectangle.X -= 10.0f * (float)args.Time.ElapsedTime;
			}

			//rechts
			if(args.Input.GetKey(KEY_NUMPAD6))
			{
				this->selectionRectangle.X += 10.0f * (float)args.Time.ElapsedTime;
			}

			//hoch
			if(args.Input.GetKey(KEY_NUMPAD8))
			{
				this->selectionRectangle.Y -= 10.0f * (float)args.Time.ElapsedTime;
			}

			//runter
			if(args.Input.GetKey(KEY_NUMPAD5))
			{
				this->selectionRectangle.Y += 10.0f * (float)args.Time.ElapsedTime;
			}

			if(args.Input.GetKeyPressed(KEY_RETURN))
			{
				sceneGraph.Intersect(this->selectionRectangle);
			}


			if(args.Input.GetMousePressed(MB_Left))
			{
				GameObject* go = new GameObject(this->engine);
				Vector2 pos = args.Input.MousePosition;
				pos *= 100;
				pos += Vector2(-50);
				go->PRS.SPosition() = Vector3(pos.X, 0, pos.Y);
				go->Update(args);

				sceneGraph.Insert(go);
			}
		}
	}
}
