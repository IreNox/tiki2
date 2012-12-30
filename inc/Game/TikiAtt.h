#pragma once

#include "Core/TypeInc.h"

#include "Game/Attributes.h"
#include "Game/TikiAttModifier.h"

namespace TikiEngine
{
	namespace AI
	{
		class TikiAtt
		{
			friend class AttributeSystem;

		public:

			TikiAtt() {}
			TikiAtt(Attributes att) : att(att), baseValue(0.0), currentValue(0.0) {}

			inline double BaseValue() const { return baseValue; }

			void operator=(double baseVal) { baseValue = baseVal; update(); }
			operator double() const { return currentValue; }

		private:

			Attributes att;

			double baseValue;
			double currentValue;

			List<TikiAttModifier*> modifier;

			void addModifier(TikiAttModifier* mod)
			{
				if (!modifier.Contains(mod))
				{
					modifier.Add(mod);
					update();
				}
			}

			void removeModifier(TikiAttModifier* mod)
			{
				if (modifier.Remove(mod))
				{
					update();
				}
			}

			void update()
			{
				currentValue = baseValue;
				FOREACH(modifier, currentValue += modifier[i]->Calculate(currentValue))
			}

		};
	}
}