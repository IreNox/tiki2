#pragma once

#include "Core/GameTime.h"

namespace TikiEngine
{
	class TikiTimer
	{
	public:

		double Interval;


		TikiTimer(double interval)
			: Interval(interval), elapsed(0)
		{
		}

		~TikiTimer() {}

		inline void Reset()
		{
			elapsed = 0;
		}

		inline void ResetToReady()
		{
			elapsed = this->Interval;
		}

		inline double GetCurrentState() const
		{
			return elapsed / Interval;
		}

		bool IsReady(const GameTime& time)
		{
			if (time.ElapsedTime < 0.25)
			{
				elapsed += time.ElapsedTime;
			}

			if (elapsed >= this->Interval)
			{
				elapsed -= this->Interval;
				return true;
			}

			return false;
		}

	private:

		double elapsed;

	};
}