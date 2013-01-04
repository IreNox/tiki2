#pragma once

#include "Core/TypeDef.h"

namespace TikiEngine
{
	class Interpolator
	{
	public:

		float ValueInit;
		float ValueMiddle;
		float ValueFinal;

		float MiddlePosition;

		Interpolator()
			: ValueInit(0.0f), ValueMiddle(1.0f), ValueFinal(0.0f), MiddlePosition(0.5f)
		{ 
		}

		float GetValue(float age)
		{
			if (age < this->MiddlePosition)
			{
				return this->ValueInit + ((this->ValueMiddle - this->ValueInit) * (age / this->MiddlePosition));
			}
			else
			{
				return this->ValueMiddle + ((this->ValueFinal - this->ValueMiddle) * ((age - this->MiddlePosition) / (1.0f - this->MiddlePosition)));
			}
		}
	}
}