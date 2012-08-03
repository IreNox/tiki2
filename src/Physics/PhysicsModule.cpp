#include "Physics/PhysicsModule.h"
#include "Physics/DllMain.h"

namespace TikiEngine
{
	namespace Modules
	{
		using namespace TikiEngine::Physics;

		PhysicsModule::PhysicsModule(Engine* engine)
			: IPhysics(engine)
		{
			pause = false;
			tikiEngine = engine;
		}

		PhysicsModule::~PhysicsModule()
		{
			if (physicsSDK != 0)
			{
				// release scene
				if (scene != 0)
					physicsSDK->releaseScene(*scene);
				scene = 0;

				// release SDK
				NxReleasePhysicsSDK(physicsSDK);
				physicsSDK = 0;
			}
		}

		void PhysicsModule::Dispose()
		{
		}

		bool PhysicsModule::Initialize(EngineDescription& desc)
		{
			Console::Write("Initializing");

			// init PhysX SDK
			NxPhysicsSDKDesc sdkDesc;
			//sdkDesc.flags &= ~NX_SDKF_NO_HARDWARE; // enables HardWare support
			NxSDKCreateError errorCode = NXCE_NO_ERROR;

			ErrorStream errorStream;
			physicsSDK = NxCreatePhysicsSDK(NX_PHYSICS_SDK_VERSION, NULL, &errorStream, sdkDesc, &errorCode);
			if (physicsSDK == 0)
			{
				Console::Write("Unable to initialize the PhysX SDK, exiting." + errorStream.GetNxSDKCreateError(errorCode));
				return false;
			}

			// Connect to the Visual Remote Debugger. The settings for the VRD host and port are found in VRDSettings.h
#if USE_VRD
			if (physicsSDK->getFoundationSDK().getRemoteDebugger())
				physicsSDK->getFoundationSDK().getRemoteDebugger()->connect(VRD_HOST, VRD_PORT, VRD_EVENTMASK);
#endif
			// Create the PhysX Scene and set the current one
			NxSceneDesc sceneDesc;
			sceneDesc.gravity = NxVec3(0.0f, -9.81f, 0.0f);
			scene = physicsSDK->createScene(sceneDesc);
			if (scene == NULL)
			{
				Console::Write("Error: Unable to create a PhysX scene, exiting.");
				return false;
			}

			// TODO : if debug, set some Visualization Flags


			//bool hardware = IsHardwarePresent();
			// assign the scene and physX sdks to dllMain
			DllMain::Scene = scene;
			DllMain::PhysicsSDK = physicsSDK;

			// Create ground plane with material for testing
			NxPlaneShapeDesc planeDesc;
			NxActorDesc actorDesc;
			actorDesc.shapes.pushBack(&planeDesc);
			scene->createActor(actorDesc);

			// BoxCollider Unit Test:
			// by default they can be set to static or dynamic objects
			// everytime we change static to dynamic, or center/size, we recreate the Actor.
			// When recreating, the class also keeps track if the Collider was a trigger or kinematic actor
			// and raises the flags respectively.
			box = new BoxCollider(tikiEngine, 0);
			box->SetCenter(Vector3(0, 5, 0));
			box->SetSize(Vector3(2, 2, 2));
			box->SetDynamic(false);
			
			// BoxCollider flags that can be set at runtime:

			// set Kinematic Trigger, kinematic actors must be specified as dynamic
			box->SetDynamic(true);
			box->SetTriggerFlag(true);
			box->SetKinematicFlag(true);
			// Create static trigger
			//box->SetTriggerFlag(true);

			// Create dynamic trigger, TODO: Handle Collision Groups, else collision detection won't work for the plane!
			//box->SetDynamic(true);
			//box->SetTriggerFlag(true);
		

			
			Vector3 boxCenter = box->GetCenter();
			Vector3 boxSize = box->GetSize();
			bool isDynamic = box->GetDynamic();

			// RigidBodys won't work for non dynamic actors
			//box->GetRigidBody().SetMass(10.0f);
			//Single mass = box->GetRigidBody().GetMass();

			return true;
		}

		bool PhysicsModule::IsHardwarePresent()
		{
			return physicsSDK->getHWVersion() != NX_HW_VERSION_NONE;
		}

		NxScene* PhysicsModule::GetScene()
		{
			return scene; 
		}

		void PhysicsModule::Begin()
		{
			if (scene && !pause)
			{
				// the new method to start the SDK
				scene->simulate(1.0f / 60.0f); 
				scene->flushStream();

				// in here we can do computations which depend only on the old state of the scene "actors". 
				// Writing to the scene is not allowed. Write calls in here are skipped.

				// ... 
			}

		}

		void PhysicsModule::End()
		{
			if (scene && !pause)
			{
				// method to sync with the SDK after it has finished.it waits (non)blocking for the end of a given NxSimulationStatus, 
				// if the end is reached it swaps the buffers, fires the callbacks and removes the writelock, 
				// if all simulations of the scene have reached its end. at the moment there is only a NX_RIGID_BODY_FINISHED status.
				scene->fetchResults(NX_RIGID_BODY_FINISHED, true);

				// we could also do this with non blocking calls
				//while(!scene->fetchResults(NX_RIGID_BODY_FINISHED, false))
				//{
				//     compute something till rigid body simulation has finished
				//}

			}

			// then we can use isWritable() to test if we fetched  all simulation results and made the scene writable again.
			// Since there is only one status flag it is obvious that we fetched everything and the scene is writable.
			NX_ASSERT(scene->isWritable());


		}



	}
}