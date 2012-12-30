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

			AttributeSystem(Engine* engine);
			~AttributeSystem();

			void AddModifiert(TikiAttModifier* mod);
			void RemoveModifier(TikiAttModifier* mod);

			inline TikiAtt& operator[](Attributes att) { return attributes.GetRef(att); }
			inline const TikiAtt& operator[](Attributes att) const { return attributes.GetCRef(att); }

		private:

			Dictionary<Attributes, TikiAtt> attributes;
			
		};
	}
}