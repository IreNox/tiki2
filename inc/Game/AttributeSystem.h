#pragma once

#include "Core/EngineObject.h"

#include "Game/TikiAtt.h"

namespace TikiEngine
{
	namespace AI
	{
		class TikiBot;

		class AttributeSystem : public EngineObject
		{
		public:

			AttributeSystem(TikiBot* owner);
			~AttributeSystem();

			void AddModifiert(TikiAttModifier* mod);
			void RemoveModifier(TikiAttModifier* mod);

			TikiAtt& operator[](Attributes att);

		private:

			Dictionary<Attributes, TikiAtt> attributes;
			
		};
	}
}