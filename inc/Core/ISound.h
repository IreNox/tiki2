#pragma once

#include "Core/IModule.h"

namespace TikiEngine
{
	namespace Modules
	{
		class ISound : public IModule
		{
		public:

			ISound(Engine* engine) : IModule(engine) {}
			~ISound() {}

			virtual void Bla() = 0;

		};
	}
}