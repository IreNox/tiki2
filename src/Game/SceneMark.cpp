
#include "Game/SceneMark.h"

#include "Core/LibraryManager.h"
//#include "Core/IRigidBody.h"

//#include "assert.h"

#include "Core/IPhysicsMaterial.h"

namespace TikiEngine
{
	namespace Game
	{

		SceneMark::SceneMark(Engine* engine)
			: Scene(engine)
		{
		}

		SceneMark::~SceneMark()
		{
			delete box;
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

			IPhysicsMaterial* material; 
			material = engine->content->LoadPhysicsMaterial(L"TODO");
			material->SetRestitution(1.0f);
			material->SetDynamicFriction(0.5f);
			material->SetStaticFriction(0.5f); // static friction may be higher than 1.

			// init
			box = engine->librarys->CreateComponent<IBoxCollider>(go);
			box->SetMaterial(material->GetIndex()); // 0 = default material	
			box->SetCenter(Vector3(5, 5, 0));
			box->SetSize(Vector3(1, 1, 1));
			box->SetDynamic(true);
			//box->GetRigidBody()->SetKinematic(true);

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
					box->GetRigidBody()->SetVelocity(Vector3(0, 11, 0));

					// and set an angular velocity on the Y-Axis
					box->GetRigidBody()->SetAngularVelocity(Vector3(0, 5, 0));
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
				box->GetRigidBody()->MovePosition(Vector3(0, 0.0005f, 0));
				box->GetRigidBody()->MoveRotation(Quaternion(0, 0.0005f, 0, 0));
			}

			Scene::Update(args);



		}
	}
}