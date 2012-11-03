#include "Physics/PhysicsModule.h"
#include "Physics/DllMain.h"
#include "Core/IGraphics.h"

namespace TikiEngine
{
	namespace Modules
	{
		#pragma region Class
		PhysicsModule::PhysicsModule(Engine* engine)
			: IPhysics(engine), cooking(0)
		{
			pause = false;
			userAllocator = 0;
			physicsSDK = 0;
			scene = 0;
			controllerManager = 0;
			userAllocator = 0;
			frameCnt = 0;
			timeSinceLastUpdate = 0;
		}

		PhysicsModule::~PhysicsModule()
		{
		}

		void PhysicsModule::Dispose()
		{
			if (physicsSDK != 0)
			{
				if (cooking != 0)
				{
					cooking->NxCloseCooking();
				}

				// release ControllerManager
				if (controllerManager != 0)
					NxReleaseControllerManager(controllerManager);
				controllerManager = 0;

				// release scene
				if (scene != 0)
					physicsSDK->releaseScene(*scene);
				scene = 0;

				// release SDK
				NxReleasePhysicsSDK(physicsSDK);
				physicsSDK = 0;

				// release allocator
				if(userAllocator != NULL)
				{
					delete userAllocator;
					userAllocator = NULL;
				}

			}
		}
		#pragma endregion

		#pragma region Init
		bool PhysicsModule::Initialize(EngineDescription& desc)
		{
			HelperLog::Write("Initializing PhysicsModule");

			if (!userAllocator)
				userAllocator = new ControllerManagerAllocator();


			// init PhysX SDK
			NxPhysicsSDKDesc sdkDesc;
			sdkDesc.flags &= ~NX_SDKF_NO_HARDWARE; // enables HardWare support
			NxSDKCreateError errorCode = NXCE_NO_ERROR;

			ErrorStream errorStream;
			physicsSDK = NxCreatePhysicsSDK(NX_PHYSICS_SDK_VERSION, userAllocator, &errorStream, sdkDesc, &errorCode);
			if (physicsSDK == 0)
			{
				HelperLog::Write("Unable to initialize the PhysX SDK, exiting." + errorStream.GetNxSDKCreateError(errorCode));
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
            sceneDesc.flags &= ~NX_SF_SIMULATE_SEPARATE_THREAD;
            sceneDesc.flags |= NX_SF_ENABLE_MULTITHREAD;
            sceneDesc.internalThreadCount = 2;
			scene = physicsSDK->createScene(sceneDesc);
			if (scene == 0)
			{
				HelperLog::Write("Error: Unable to create a PhysX scene, exiting. \n");
				return false;
			}

			
			// perform 5/1 substeps? to advance simulation by 1/60th of a second.
			//scene->setTiming((1.0f/60.0f) / 5.0f, 5, NX_TIMESTEP_FIXED);
			scene->setTiming(1.0f/60.0f, 1, NX_TIMESTEP_FIXED);
			
#if _DEBUG
			// set some Visualization Flags, else debugRendering won't work.
			physicsSDK->setParameter(NX_SKIN_WIDTH, 0.025f);
			physicsSDK->setParameter(NX_VISUALIZATION_SCALE, 1.0f);
			physicsSDK->setParameter(NX_VISUALIZE_COLLISION_SHAPES, 1);
			physicsSDK->setParameter(NX_VISUALIZE_ACTOR_AXES, 1);
			//physicsSDK->setParameter(NX_VISUALIZE_CONTACT_POINT, 1);
			//physicsSDK->setParameter(NX_VISUALIZE_CONTACT_NORMAL, 1);
			//physicsSDK->setParameter(NX_VISUALIZE_CONTACT_FORCE, 1);
			//physicsSDK->setParameter(NX_VISUALIZE_BODY_LIN_VELOCITY, 1);
			//physicsSDK->setParameter(NX_VISUALIZE_BODY_ANG_FORCE, 1);
			//physicsSDK->setParameter(NX_VISUALIZE_COLLISION_DYNAMIC, 1);
			physicsSDK->setParameter(NX_VISUALIZE_COLLISION_VNORMALS, 1);
#endif

			// Also create the controller Manager.
			controllerManager = NxCreateControllerManager(userAllocator);

			cooking = NxGetCookingLib(NX_PHYSICS_SDK_VERSION);			
			if (!cooking->NxInitCooking()) //userAllocator, &errorStream
			{
				HelperLog::Write("Can't init Cooking Library.");
				return false;
			}

			//bool hardware = IsHardwarePresent();
			// assign statics to dllMain
			DllMain::Scene = scene;
			DllMain::Cooking = cooking;
			DllMain::PhysicsSDK = physicsSDK;
			DllMain::ControllerManager = controllerManager;

			return true;
		}
		#pragma endregion

		bool PhysicsModule::IsHardwarePresent()
		{
			return physicsSDK->getHWVersion() != NX_HW_VERSION_NONE;
		}

		NxScene* PhysicsModule::GetScene()
		{
			return scene; 
		}

		Boolean PhysicsModule::RayCast(Ray ray, RaycastHit* hitInfo, float distance)
		{
		  NxRay worldRay(ray.Origin.arr, Vector3::Normalize(ray.Direction).arr);
		  NxRaycastHit hit;

		  scene->raycastClosestShape(worldRay, NX_ALL_SHAPES, hit, 0xffffffff, distance);
      
		  if (hit.shape)
		  {
			hitInfo->Point = hit.worldImpact.get();
			hitInfo->Normal = hit.worldNormal.get();
			hitInfo->Distance = hit.distance;
				hitInfo->Collider = (ICollider*)hit.shape->getActor().userData;
			return true;
		  }

		  return false;
		}


		void PhysicsModule::Begin()
		{
			frameCnt++;

			if (scene && !pause && frameCnt > 1)
			{
				NxU32 errorCode = NXCE_NO_ERROR;
				scene->fetchResults(NX_RIGID_BODY_FINISHED, true);

				// Update controllers!
				NxReal maxTimestep;
				NxTimeStepMethod method;
				NxU32 maxIter, numSubSteps;
				scene->getTiming(maxTimestep, maxIter, method, &numSubSteps);
				if(numSubSteps)
				{
					controllerManager->updateControllers();
				}

				//frameCnt = 0;
			}
		}

		void PhysicsModule::End(const UpdateArgs& args)
		{
			// only update every 5th frame.
			timeSinceLastUpdate += (float)args.Time.ElapsedTime;
			if (scene && !pause) //&& frameCnt == 5
			{
				scene->simulate(timeSinceLastUpdate); 			
				scene->flushStream();
				// the new method to start the SDK				

				// in here we can do computations which depend only on the old state of the scene "actors". 
				// Writing to the scene is not allowed. Write calls in here are skipped.


				// method to sync with the SDK after it has finished.it waits (non)blocking for the end of a given NxSimulationStatus, 
				// if the end is reached it swaps the buffers, fires the callbacks and removes the writelock, 
				// if all simulations of the scene have reached its end. at the moment there is only a NX_RIGID_BODY_FINISHED status.
				//scene->fetchResults(NX_RIGID_BODY_FINISHED, true);

				// we could also do this with non blocking calls
				//while(!scene->fetchResults(NX_RIGID_BODY_FINISHED, false))
				//{
				//     compute something till rigid body simulation has finished
				//}

				// then we can use isWritable() to test if we fetched  all simulation results and made the scene writable again.
				// Since there is only one status flag it is obvious that we fetched everything and the scene is writable.
				//NX_ASSERT(scene->isWritable());

				timeSinceLastUpdate = 0;
			}
		}

		#pragma region Debug
#if _DEBUG
		void PhysicsModule::DrawDebug()
		{
			const NxDebugRenderable* debug = scene->getDebugRenderable();

			NxU32 i = 0;
			NxU32 count = debug->getNbLines();
			if (count > 0)
			{
				const NxDebugLine* lines = debug->getLines();

				while (i < count)
				{
					const NxDebugLine* line = lines + i;

					Vector3 start = physxToTiki(line->p0);
					Vector3 end = physxToTiki(line->p1);

					Color color = Color(
						(float)((line->color >> 16)&0xff)/255.0f,
						(float)((line->color >> 8)&0xff)/255.0f,
						(float)( line->color & 0xff)/255.0f,
						1.0f
					);

					engine->graphics->DrawLine(start, end, color);

					i++;
				}
			}

			i = 0;
			count = debug->getNbTriangles();
			if (count > 0)
			{
				const NxDebugTriangle* tris = debug->getTriangles();

				while (i < count)
				{
					const NxDebugTriangle* tri = tris + i;

					Vector3 p1 = physxToTiki(tri->p0);
					Vector3 p2 = physxToTiki(tri->p1);
					Vector3 p3 = physxToTiki(tri->p2);

					Color color = Color(
						(float)((tri->color >> 16)&0xff)/255.0f,
						(float)((tri->color >> 8)&0xff)/255.0f,
						(float)( tri->color & 0xff)/255.0f,
						1.0f
					);

					engine->graphics->DrawLine(p1, p2, color);
					engine->graphics->DrawLine(p2, p3, color);
					engine->graphics->DrawLine(p3, p1, color);

					i++;
				}
			}
		}

		Vector3 PhysicsModule::physxToTiki(const NxVec3& vector)
		{
			return Vector3(
				vector.x,
				vector.y,
				vector.z
			);
		}
#endif
		#pragma endregion
	}
}
