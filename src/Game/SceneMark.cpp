
#include "Game/SceneMark.h"

#include "Core/LibraryManager.h"
//#include "Core/IRigidBody.h"

//#include "assert.h"

#include "Core/IPhysicsMaterial.h"
#include "Core/DebugPhysicsRenderer.h"
#include "Core/CameraObject.h"

#include "Game/CameraFly.h"

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
			delete box;
			delete material;
		}

		void SceneMark::Initialize(const InitializationArgs& args)
		{
			// BoxCollider Unit Test:
			// by default they can be set to static or dynamic objects
			// every time we change static to dynamic, or center/size, we recreate the Actor.
			// When recreating, the class also keeps track if the Collider was a trigger
			// and raises the flags respectively.

			// Material, Center, Size, Dynamic must be set before the object gets created
			GameObject* go = new GameObject(engine);

			//IPhysicsMaterial* material; 
			material = engine->content->LoadPhysicsMaterial(L"TODO");
			material->SetRestitution(1.0f);
			material->SetDynamicFriction(0.5f);
			material->SetStaticFriction(0.5f); // static friction may be higher than 1.

			// init
			box = engine->librarys->CreateComponent<IBoxCollider>(go);
			box->SetMaterial(material->GetIndex()); // 0 = default material	
			box->SetCenter(Vector3(0, 5, 0));
			box->SetSize(Vector3(1, 1, 1));
			box->SetDynamic(true);
			//box->GetRigidBody()->SetKinematic(true);
			this->AddElement(go);
			go->Release();


			go = new GameObject(engine);
			box = engine->librarys->CreateComponent<IBoxCollider>(go);
			box->SetMaterial(material->GetIndex()); // 0 = default material	
			box->SetCenter(Vector3(5, 0, 0));
			box->SetSize(Vector3(1, 1, 1));
			box->SetDynamic(true);
			box->GetRigidBody()->SetKinematic(true);
			this->AddElement(go);
			go->Release();

			go = new CameraObject(engine);
			go->PRS.Position = Vector3(0, 0, 5);
			//go->PRS.Rotation = Quaternion::CreateFromYawPitchRoll(3.14159f, 0, 0);
			this->AddElement(go);
			go->Release();

			CameraFly* fly = new CameraFly(engine, go);
			go->AddComponent(fly);
			fly->Release();

			go = new DebugPhysicRenderer(engine);
			this->AddElement(go);
			go->Release();




			// BoxCollider flags that can be set at runtime:

			// Runtime: set Kinematic Trigger, kinematic actors must be specified as dynamic before!
			//box->SetTrigger(true);
			//box->GetRigidBody()->SetKinematic(true);

			// Runtime: Create static trigger
			//box->SetDynamic(false);		// recreate to static
			//box->SetTrigger(true);
		

			// Runtime: Create dynamic trigger, TODO: Handle Collision Groups, else collision detection won't work!
			//box->SetDynamic(true);
			//box->SetTrigger(true);

			// Test if the box is dynamic to move it around
			if (box->GetDynamic())
			{
				// set some mass, this won't affect kinematic actors.
				box->GetRigidBody()->SetMass(5);
				//assert(box->GetRigidBody()->GetMass() == 5);

				// case when we have a kinematic actor
				if (!box->GetRigidBody()->GetKinematic())
				{
					// give this tiny box a force pointing upwards
					//box->GetRigidBody()->SetVelocity(Vector3(0, 11, 0));

					// and set an angular velocity on the Y-Axis
					//box->GetRigidBody()->SetAngularVelocity(Vector3(0, 5, 0));
				}



			}

			Scene::Initialize(args);
		}

		void SceneMark::Draw(const DrawArgs& args)
		{

			Scene::Draw(args);
		}

		void SceneMark::Update(const UpdateArgs& args)
		{

			// if we have a dynamic actor
			if (box->GetDynamic())
			{
				// if it is kinematic, use following functions to move/rotate:

				//box->GetRigidBody()->MovePosition(Vector3(0, 0.0005f, 0));
				
				Vector3 eulerAngles(0.01f, 0.01f, 0.01f);

				Quaternion q1 = q1.CreateFromAxisAngle(Vector3(1, 0, 0), eulerAngles.X);
				Quaternion q2 = q2.CreateFromAxisAngle(Vector3(0, 1, 0), eulerAngles.Y);
				Quaternion q3 = q3.CreateFromAxisAngle(Vector3(0, 0, 1), eulerAngles.Z);

				// PhysX does its rotations in a right-handed manner. 
				//box->GetRigidBody()->MoveRotation(q3 * q2 * q1); // rotating objects araound the global axes
				//box->GetRigidBody()->MoveRotation(q1 * q2 * q3); // rotating objects around the local axes
				box->GetRigidBody()->MoveRotation(Quaternion::CreateFromYawPitchRoll(0, 0, args.Time.ElapsedTime));
			}

			Scene::Update(args);



		}
	}
}