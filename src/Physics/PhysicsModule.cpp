

#include "Physics/PhysicsModule.h"
#include "Physics/DllMain.h"

namespace TikiEngine
{
	namespace Modules
	{
		using namespace TikiEngine::Physics;

		// implement static member
		//NxScene* PhysicsModule::currentScene = NULL;

		PhysicsModule::PhysicsModule(Engine* engine)
			: IPhysics(engine)
		{
			pause = false;
			tikiEngine = engine;
		}

		PhysicsModule::~PhysicsModule()
		{
			//if (box != NULL)
			//	delete box;
			//box = NULL;

			//if (box2 != NULL)
			//	delete box2;
			//box2 = NULL;

			if (physicsSDK != NULL)
			{
				// release scene
				if (scene != NULL)
					physicsSDK->releaseScene(*scene);
				scene = NULL;

				// release SDK
				NxReleasePhysicsSDK(physicsSDK);
				physicsSDK = NULL;
			}

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
			if (physicsSDK == NULL)
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
				Console::Write("Error: Unable to create a PhysX scene, exiting the sample.");
				return false;
			}
			//currentScene = scene;




			// Create ground plane with material
			NxPlaneShapeDesc planeDesc;
			//PhysicsMaterial mat;
			//mat.SetDynamicFriction(0.2f);
			//mat.SetStaticFriction(0.1f);
			//mat.SetRestitution(1.0f);
			//planeDesc.materialIndex = mat.GetIndex();
			NxActorDesc actorDesc;
			actorDesc.shapes.pushBack(&planeDesc);
			scene->createActor(actorDesc);

			//bool hardware = IsHardwarePresent();

			//// Create
			//box = new BoxCollider(tikiEngine, 0, scene, 
			//	NxVec3(0, 10, 0), NxVec3(2, 2 ,2));
			//box->GetReady();

			//// Create static Trigger
			//box2 = new BoxCollider(tikiEngine, 0, scene, 
			//	NxVec3(5, 5, 0), NxVec3(1, 1 ,1), true);
			//box2->GetReady();


      DllMain::Scene = scene;
      DllMain::PhysicsSDK = physicsSDK;

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

		void PhysicsModule::DoWhatIWant()
		{
		}

		void PhysicsModule::Dispose()
		{
		}
	}
}