#pragma once

#include "Core/IPhysicsMaterial.h"
#include "PhysX/Physics/NxPhysics.h"

namespace TikiEngine
{
	namespace Physics
	{
		using namespace TikiEngine::Resources;

		/*! @brief Physics material describes how to handle 
		 *	colliding objects (friction, bounciness).
		 */
		class PhysicsMaterial : public IPhysicsMaterial
		{

		public:
			/*! @brief Creates a new material. */
			PhysicsMaterial(Engine* engine);
			~PhysicsMaterial();


			/*! @brief The friction used when already moving. This value has to be between 0 and 1. */
			void SetDynamicFriction(Single dynFriction);
			Single GetDynamicFriction();

			/*! @brief The friction used when an object is lying on a surface. Usually a value from 0 to 1. but it may also be > 1 here. */
			void SetStaticFriction(Single staFriction);
			Single GetStaticFriction();

			/*! @brief How bouncy is the surface? A value of 0 will not bounce.
			 * A value of 1 will bounce without any loss of energy.
			 */
			void SetRestitution(Single restitution);
			Single GetRestitution();

			/*! @brief Gets the Material Index the PhysX SDK generates when we create a material */
			UInt16 GetIndex();

			
			// TODO!
			#pragma region IResource Members
			void* GetNativeResource() { return (void*)material; }
			bool GetReady() { return true; }

		protected:
			void loadFromStream(wcstring fileName, Stream* stream) {}
			void saveToStream(wcstring fileName, Stream* stream)  {}
			#pragma endregion

		private:
			UInt16 index;
			NxMaterialDesc desc;
			NxMaterial* material;
		};
	}
}

