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

		void Reset()
		{
			elapsed = 0;
		}

		bool IsReady(const GameTime& time)
		{
			elapsed += time.ElapsedTime;

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