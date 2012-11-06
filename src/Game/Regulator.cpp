#include "Game/Regulator.h"

#include <Windows.h>
#pragma comment(lib,"winmm.lib")
#include <MMSystem.h>
#include "Game/Utils.h"

namespace TikiEngine
{
	namespace AI
	{
		Regulator::Regulator(double numUpdatesPerSecond)
		{
			nextUpdateTime = (DWORD)(timeGetTime() + RandFloat() * 1000);
			
			if (numUpdatesPerSecond > 0)
				updatePeriod = 1000.0 / numUpdatesPerSecond;
			else if (IsEqual(0.0, numUpdatesPerSecond))
				updatePeriod = 0;
			else if (numUpdatesPerSecond < 0)
				updatePeriod = -1;
		}

		bool Regulator::IsReady()
		{
			// if a regulator is instantiated with a zero freq then it goes into stealth mode (doesn't regulate)
			if (IsEqual(0.0, updatePeriod))
				return true;

			// if the regulator is instantiated with a negative freq then it will never allow the code to flow
			if (updatePeriod < 0)
				return false;

			DWORD currentTime = timeGetTime();

			//the number of milliseconds the update period can vary per required
			//update-step. This is here to make sure any multiple clients of this class
			//have their updates spread evenly
			static const double updatePeriodVariator = 10.0;

			if (currentTime >= nextUpdateTime)
			{
				nextUpdateTime = (DWORD)(currentTime + updatePeriod + 
								 RandInRange(-updatePeriodVariator, updatePeriodVariator));
				return true;
			}

			return false;
		}


	}
}