#pragma once

#include "Core/TypeDef.h"

#include "Game/Attributes.h"

namespace TikiEngine
{
	namespace AI
	{
		enum AttributeModifierType
		{
			AMT_PerValue,
			AMT_PerPercent
		};

		class TikiAttModifier
		{
		public:

			TikiAttModifier(Attributes att, AttributeModifierType type, double value, UInt32 priority)
				: att(att), type(type), value(value), priority(priority)
			{
			}

			~TikiAttModifier()
			{
			}

			double Calculate(double cValue)
			{
				switch (type)
				{
				case AMT_PerValue:
					return cValue + value;
					break;
				case AMT_PerPercent:
					return cValue + ((cValue / 100) * value);
					break;
				}

				throw "Unknown Error";
			}

			inline Attributes GetAttributeType() { return att; }
			inline AttributeModifierType GetType() { return type; }

			inline double GetValue() { return value; }
			inline void SetValue(double val) { value = val; }
			
			inline UInt32 GetPriority() { return priority; }

		private:

			Attributes att;

			AttributeModifierType type;
			double value;

			UInt32 priority;

		};
	}
}