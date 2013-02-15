
#include "Game/SceneCredits.h"

#include "Core/LibraryManager.h"

#include "Core/GUILabel.h"
#include "Core/GUIImage.h"

#include "Core/LightObject.h"
#include "Core/CameraObject.h"
#include "Core/ISoundSystem.h"
#include "Core/IMeshRenderer.h"

#include "Game/CameraFly.h"

namespace TikiEngine
{
	namespace Game
	{
		using namespace TikiEngine::Scripts;
		using namespace TikiEngine::Objects;

		SceneCredits::SceneCredits(Engine* engine)
			: Scene(engine)
		{
		}

		SceneCredits::~SceneCredits()
		{
			FOREACH_CODE(controls, SafeRelease(&controls[i]));

			SafeRelease(&font14);
			SafeRelease(&font24);
		}

		void SceneCredits::Initialize(const InitializationArgs& args)
		{
			engine->sound->Play(
				engine->content->LoadSound(L"ambient"), true
			);

			font24 = engine->librarys->CreateResource<IFont>();			
			font24->Create(L"segoewp", 32.0f);

			font14 = engine->librarys->CreateResource<IFont>();			
			font14->Create(L"calibri", 16.0f);

			float x1 = 25.0f;
			float x2 = 40.0f;
			float y = engine->graphics->GetViewPort()->Height + 25.0f;

			GUIImage* img = TIKI_NEW GUIImage(engine);
			img->SetTexture(engine->content->LoadTexture(L"logo"));
			img->SPosition() = Vector2(x1, y);
			controls.Add(img);
			y += 220.0f;

			GUILabel* label = TIKI_NEW GUILabel(engine);
			label->SetFont(font14);
			label->Text() = L"Made by TikiTek";
			label->SPosition() = Vector2(x1, y);
			controls.Add(label);
			y += 150.0f;

			label = TIKI_NEW GUILabel(engine);
			label->SetFont(font24);
			label->Text() = L"Team Lead";
			label->SPosition() = Vector2(x1 , y);
			controls.Add(label);
			y += 50.0f;
			
			label = TIKI_NEW GUILabel(engine);
			label->SetFont(font14);
			label->Text() = L"Tim Boden";
			label->SPosition() = Vector2(x2 , y);
			controls.Add(label);
			y += 75.0f;

			label = TIKI_NEW GUILabel(engine);
			label->SetFont(font24);
			label->Text() = L"Programming";
			label->SPosition() = Vector2(x1 , y);
			controls.Add(label);
			y += 50.0f;

			label = TIKI_NEW GUILabel(engine);
			label->SetFont(font14);
			label->Text() = L"Adrian Lück";
			label->SPosition() = Vector2(x2 , y);
			controls.Add(label);
			y += 30.0f;

			label = TIKI_NEW GUILabel(engine);
			label->SetFont(font14);
			label->Text() = L"Mark Reichert";
			label->SPosition() = Vector2(x2 , y);
			controls.Add(label);
			y += 30.0f;

			label = TIKI_NEW GUILabel(engine);
			label->SetFont(font14);
			label->Text() = L"Tim Boden";
			label->SPosition() = Vector2(x2 , y);
			controls.Add(label);
			y += 75.0f;

			label = TIKI_NEW GUILabel(engine);
			label->SetFont(font24);
			label->Text() = L"Art";
			label->SPosition() = Vector2(x1 , y);
			controls.Add(label);
			y += 50.0f;

			label = TIKI_NEW GUILabel(engine);
			label->SetFont(font14);
			label->Text() = L"Daniel Leusch";
			label->SPosition() = Vector2(x2 , y);
			controls.Add(label);
			y += 30.0f;

			label = TIKI_NEW GUILabel(engine);
			label->SetFont(font14);
			label->Text() = L"Florian Rudolf";
			label->SPosition() = Vector2(x2 , y);
			controls.Add(label);
			y += 30.0f;

			label = TIKI_NEW GUILabel(engine);
			label->SetFont(font14);
			label->Text() = L"Patrick Metz";
			label->SPosition() = Vector2(x2 , y);
			controls.Add(label);
			y += 75.0f;

			label = TIKI_NEW GUILabel(engine);
			label->SetFont(font24);
			label->Text() = L"External Support";
			label->SPosition() = Vector2(x1 , y);
			controls.Add(label);
			y += 75.0f;

			label = TIKI_NEW GUILabel(engine);
			label->SetFont(font24);
			label->Text() = L"Game Design";
			label->SPosition() = Vector2(x1 , y);
			controls.Add(label);
			y += 50.0f;

			label = TIKI_NEW GUILabel(engine);
			label->SetFont(font14);
			label->Text() = L"Amadeus Weidmann";
			label->SPosition() = Vector2(x2 , y);
			controls.Add(label);
			y += 30.0f;

			label = TIKI_NEW GUILabel(engine);
			label->SetFont(font14);
			label->Text() = L"Marco Busse";
			label->SPosition() = Vector2(x2 , y);
			controls.Add(label);
			y += 30.0f;

			label = TIKI_NEW GUILabel(engine);
			label->SetFont(font14);
			label->Text() = L"Robin Field";
			label->SPosition() = Vector2(x2 , y);
			controls.Add(label);
			y += 75.0f;

			label = TIKI_NEW GUILabel(engine);
			label->SetFont(font24);
			label->Text() = L"Sound and Voice";
			label->SPosition() = Vector2(x1 , y);
			controls.Add(label);
			y += 50.0f;

			label = TIKI_NEW GUILabel(engine);
			label->SetFont(font14);
			label->Text() = L"Benny Temin";
			label->SPosition() = Vector2(x2 , y);
			controls.Add(label);
			y += 30.0f;

			label = TIKI_NEW GUILabel(engine);
			label->SetFont(font14);
			label->Text() = L"Florian Bradfisch";
			label->SPosition() = Vector2(x2 , y);
			controls.Add(label);
			y += 30.0f;

			label = TIKI_NEW GUILabel(engine);
			label->SetFont(font14);
			label->Text() = L"Juliet Homer";
			label->SPosition() = Vector2(x2 , y);
			controls.Add(label);
			y += 30.0f;


			label = TIKI_NEW GUILabel(engine);
			label->SetFont(font14);
			label->Text() = L"Thorsten Röpke";
			label->SPosition() = Vector2(x2 , y);
			controls.Add(label);
			y += 75.0f;

			label = TIKI_NEW GUILabel(engine);
			label->SetFont(font24);
			label->Text() = L"Terrorbus";
			label->SPosition() = Vector2(x1 , y);
			controls.Add(label);
			y += 50.0f;

			label = TIKI_NEW GUILabel(engine);
			label->SetFont(font14);
			label->Text() = L"Heico Purwin";
			label->SPosition() = Vector2(x2 , y);
			controls.Add(label);
			y += 75.0f;

			label = TIKI_NEW GUILabel(engine);
			label->SetFont(font24);
			label->Text() = L"Ham";
			label->SPosition() = Vector2(x1 , y);
			controls.Add(label);
			y += 50.0f;

			label = TIKI_NEW GUILabel(engine);
			label->SetFont(font14);
			label->Text() = L"Felix Lukas";
			label->SPosition() = Vector2(x2 , y);
			controls.Add(label);
			y += 30.0f;


			auto light = TIKI_NEW LightObject(engine);
			light->GetLight()->SetColor(Color(1, 1, 1, 1));
			light->GetLight()->SetRange(75.0f);
			light->PRS.SPosition() = Vector3(2.4059510f, -2.6930294f, -2.5655684f);
			light->PRS.SRotation() = Quaternion(0.30284923f, 0.31876498f, 0.10827491f, -0.89159840f);
			light->AddRef();
			this->AddElement(light);

			auto camera = TIKI_NEW CameraObject(engine);			
			camera->PRS.SPosition() = Vector3(-2.7662525f, 3.5698438f, 2.8218701f);
			camera->PRS.SRotation() = Quaternion(-0.38001660f, -0.35851005f, -0.16277219f, 0.83699650f);
			camera->AddRef();
			this->AddElement(camera);

			// Box
			go = TIKI_NEW GameObject(engine);
			auto renP = engine->librarys->CreateComponent<IMeshRenderer>(go);
			renP->SetMaterial(engine->content->LoadMaterial(L"os_simple"));
			renP->GetMaterial()->TexDiffuse = engine->content->LoadTexture(L"credits");
			renP->SetMesh(engine->content->LoadMesh(L"box"));
			go->PRS.SScale() = Vector3(1.0f, -1.0f, 1.0f);
			this->AddElement(go);

			go = TIKI_NEW GameObject(engine);
			go->SModel(engine->content->LoadModel(L"schinken"));
			go->PRS.SScale() = Vector3(0.01f);
			this->AddElement(go);
		}

		void SceneCredits::Draw(const DrawArgs& args)
		{
			FOREACH_PTR_CALL(controls, Draw(args));

			Scene::Draw(args);
		}

		void SceneCredits::Update(const UpdateArgs& args)
		{
			float y = (float)args.Time.ElapsedTime * 50.0f;

			for (UInt32 i = 0; i < controls.Count(); i++)
			{
				controls[ i ]->SPosition().Y -= y;
				controls[ i ]->Update(args);
			}

			go->PRS.SPosition() = Vector3(
				sinf((float)args.Time.TotalTime) * 2.5f,
				0,
				cosf((float)args.Time.TotalTime) * 2.5f
			);

			Vector3 shere = Vector3::Normalize(go->PRS.SPosition());
			go->PRS.SRotation() = Quaternion::CreateFromYawPitchRoll(
				(float)((MATH_TWOPI - atan2(shere.Z, shere.X)) - MATH_PI),
				0.0f,
				0.0f
			);

			Scene::Update(args);
		}

	}
}