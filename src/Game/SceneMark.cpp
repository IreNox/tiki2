
#include "Game/SceneMark.h"

#include "Core/LibraryManager.h"
//#include "Core/IRigidBody.h"

//#include "assert.h"

#include "Core/IPhysicsMaterial.h"
#include "Core/DebugPhysicsRenderer.h"
#include "Core/CameraObject.h"

#include "Game/CameraFly.h"
#include "Core/ISpriteBatch.h"
#include <sstream>


namespace TikiEngine
{
	namespace Game
	{
		using namespace TikiEngine::Objects;
		using namespace TikiEngine::Scripts;

		SceneMark::SceneMark(Engine* engine)
			: Scene(engine)
		{
		}

		SceneMark::~SceneMark()
		{
			SafeRelease(&kinematicBox);
			SafeRelease(&staticBox);
			SafeRelease(&dynamicBox);
			SafeRelease(&triggerSphere);
			SafeRelease(&controller);
			SafeRelease(&material);
		
			SafeRelease(&bounds1);
			SafeRelease(&bounds2);

			SafeRelease(&bot);

			SafeRelease(&font);
		}

		void SceneMark::Initialize(const InitializationArgs& args)
		{


			GameObject* go = new GameObject(engine);
			//TODO: EntityMgr->RegisterMovingEntity(go); //, desc

			// Create TikiBot and set some target poition to seek
			bot = new TikiBot(engine, go);
			bot->GetSteering()->SetTarget(Vector2(5, -5));
			bot->GetSteering()->ArriveOn();
			//bot->GetSteering()->SeekOn();
			this->AddElement(go);
			go->Release();

			// init BoundingBox
			bounds1 = engine->librarys->CreateResource<IBoundingBox>();
			bounds1->Set(Vector3(0, 0, 0), Vector3(10, 10, 10));

			bounds2 = engine->librarys->CreateResource<IBoundingBox>();
			bounds2->Set(Vector3(-1, -1, -1), Vector3(5, 5, 5));

			//IPhysicsMaterial* material; 
			//material = engine->content->LoadPhysicsMaterial(L"TODO");
			material = engine->librarys->CreateResource<IPhysicsMaterial>();
			material->SetRestitution(0.7f);
			material->SetDynamicFriction(0.7f);
			material->SetStaticFriction(0.5f); // static friction may be higher than 1.

			// Init Colliders
			// by default these can be set to static or dynamic objects
			// every time we change static to dynamic, or center/size, we recreate the Actor.
			// When recreating, the class also keeps track if the Collider was a trigger
			// and raises the flags respectively.
			go = new GameObject(engine);
			dynamicBox = engine->librarys->CreateComponent<IBoxCollider>(go);
			dynamicBox->SetMaterial(material->GetIndex()); // 0 = default material	
			dynamicBox->SetCenter(Vector3(0, 3, -4));
			dynamicBox->SetSize(Vector3(1, 1, 1));
			dynamicBox->SetDynamic(true);
			// assign collision groups after object is created, else it won't work!
			dynamicBox->SetGroup(CG_Collidable_Pushable);
			this->AddElement(go);
			go->Release();

			// init box plane
			go = new GameObject(engine);
			staticBox = engine->librarys->CreateComponent<IBoxCollider>(go);
			staticBox->SetMaterial(material->GetIndex()); // 0 = default material	
			staticBox->SetCenter(Vector3(0, 0, 0));
			staticBox->SetSize(Vector3(10, 0.1f, 10));
			staticBox->SetDynamic(false);
			staticBox->SetGroup(CG_Collidable_Non_Pushable);
			this->AddElement(go);
			go->Release();

			// Init kinematic actor
			go = new GameObject(engine);
			kinematicBox = engine->librarys->CreateComponent<IBoxCollider>(go);
			kinematicBox->SetMaterial(material->GetIndex()); // 0 = default material	
			kinematicBox->SetCenter(Vector3(0, 5, 0));
			kinematicBox->SetSize(Vector3(1, 1, 1));
			kinematicBox->SetDynamic(true);
			kinematicBox->GetRigidBody()->SetKinematic(true);
			this->AddElement(go);
			go->Release();

			// init static sphere trigger 
			go = new GameObject(engine);
			triggerSphere = engine->librarys->CreateComponent<ISphereCollider>(go);
			triggerSphere->SetMaterial(material->GetIndex()); // 0 = default material	
			triggerSphere->SetCenter(Vector3(3, 2, 0));
			triggerSphere->SetRadius(1.0f);
			triggerSphere->SetDynamic(false);
			triggerSphere->SetTrigger(true);
			triggerSphere->SetGroup(CG_Collidable_Non_Pushable);
			this->AddElement(go);
			go->Release();

			// init CharacterController
			go = new GameObject(engine);
			controller = engine->librarys->CreateComponent<ICharacterController>(go);
			controller->SetCenter(Vector3(0, 5, 0));
			controller->SetRadius(0.25f);
			controller->SetHeight(1.0f);
			controller->SetSlopeLimit(45.0f);
			controller->SetStepOffset(0.5f);
			controller->SetGroup(CG_Collidable_Non_Pushable);
			this->AddElement(go);
			go->Release();


			go = new CameraObject(engine);
			go->PRS.Position = Vector3(0, 3, 7);
			//go->PRS.Rotation = Quaternion::CreateFromYawPitchRoll(3.14159f, 0, 0);
			this->AddElement(go);
			go->Release();

			CameraFly* fly = new CameraFly(engine, go);
			fly->Release();

#if _DEBUG
			go = new DebugPhysicRenderer(engine);
			this->AddElement(go);
			go->Release();
#endif

			font = engine->librarys->CreateResource<IFont>();
			font->Create(L"Arial", 10);



			// Test if the box is dynamic to move it around
			if (dynamicBox->GetDynamic())
			{
				// set some mass, this won't affect kinematic actors.
				dynamicBox->GetRigidBody()->SetMass(5);
				//assert(box->GetRigidBody()->GetMass() == 5);

				// give this tiny box a force pointing upwards
				dynamicBox->GetRigidBody()->SetVelocity(Vector3(0, 11, 0));

				// and set an angular velocity on the Y-Axis
				dynamicBox->GetRigidBody()->SetAngularVelocity(Vector3(0, 5, 0));
			}

			Scene::Initialize(args);
		}

		void SceneMark::Draw(const DrawArgs& args)
		{
			std::wostringstream s;
			s << "ControllerPos (" << controller->GetCenter().X << ", " << controller->GetCenter().Y  << ", " << controller->GetCenter().Z << ")";
			wstring str = s.str();
			engine->sprites->DrawString(font, str, Vector2(1, 80));

			std::wostringstream s2;
			s2 << "BoundingBox Intersects" << bounds1->Intersects(*bounds2);
			str = s2.str();
			engine->sprites->DrawString(font, str, Vector2(1, 100));

			Scene::Draw(args);
		}

		void SceneMark::Update(const UpdateArgs& args)
		{
			// Update Controller movement
			Vector3 displacement(0, -9.8f, 0);
			if (args.Input.GetKey(KEY_I))
				displacement -= Vector3(0, 0, 1);
			if (args.Input.GetKey(KEY_K))
				displacement += Vector3(0, 0, 1);
			if (args.Input.GetKey(KEY_J))
				displacement -= Vector3(1, 0, 0);
			if (args.Input.GetKey(KEY_L))
				displacement += Vector3(1, 0, 0);
			if (args.Input.GetKey(KEY_SPACE))
				controller->SetCenter(Vector3(0, 2, 0));

			// we can also determine which parts of the collider collided with another one.
			CollisionFlags cf;
			cf = controller->Move(displacement * (float)args.Time.ElapsedTime);
			bool isGrounded = (cf & CF_Down) != 0;
			bool collidedSides = (cf & CF_Sides) != 0;
			bool collidedAbove = (cf & CF_Up) != 0;

				// if it is dynamic and also kinematic, use following functions to move/rotate:
			if (kinematicBox->GetDynamic() && kinematicBox->GetRigidBody()->GetKinematic())
			{
			
				//box->GetRigidBody()->MovePosition(Vector3(0, 0.0005f, 0));
				
				Vector3 eulerAngles(0.01f, 0.01f, 0.01f);

				Quaternion q1 = q1.CreateFromAxisAngle(Vector3(1, 0, 0), eulerAngles.X);
				Quaternion q2 = q2.CreateFromAxisAngle(Vector3(0, 1, 0), eulerAngles.Y);
				Quaternion q3 = q3.CreateFromAxisAngle(Vector3(0, 0, 1), eulerAngles.Z);

				// PhysX does its rotations in a right-handed manner. 
				//box->GetRigidBody()->MoveRotation(q3 * q2 * q1); // rotating objects araound the global axes
				//box->GetRigidBody()->MoveRotation(q1 * q2 * q3); // rotating objects around the local axes
				kinematicBox->GetRigidBody()->MoveRotation(Quaternion::CreateFromYawPitchRoll(0, 0, (float)args.Time.ElapsedTime));
			}

			Scene::Update(args);



		}
	}
}