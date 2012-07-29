
#include "Physics/PhysicsModule.h"

namespace TikiEngine
{
	namespace Modules
	{
		PhysicsModule::PhysicsModule(Engine* engine)
			: IPhysics(engine)
		{

		}

		PhysicsModule::~PhysicsModule()
		{

		}

		bool PhysicsModule::Initialize(EngineDescription& desc)
		{
			return true;
		}

		void PhysicsModule::Begin()
		{
		}

		void PhysicsModule::End()
		{
		}

		void PhysicsModule::DoWhatIWant()
		{

		}

		void PhysicsModule::Dispose()
		{
		}
	}
}