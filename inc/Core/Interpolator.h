#pragma once

#include "Core/TypeDef.h"

namespace TikiEngine
{
	template <typename T>
	class Interpolator
	{
	public:

		T ValueInit;
		T ValueMiddle;
		T ValueFinal;

		float MiddlePosition;

		Interpolator()
			: MiddlePosition(0.5f)
		{ 
		}

		T GetValue(float age)
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
	};	
}