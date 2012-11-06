#pragma once

namespace TikiEngine
{
	namespace AI
	{

		// Use this class to regulate code flow (for an update function say)
		// Instantiate the class with the frequency you would like your code
		// section to flow (like 10 times per second) and then only allow 
		// the program flow to continue if Ready() returns true
		class Regulator
		{
		public:
			// The Regulator class automatically ensures updates are staggered over multiple
			// time steps by adding a small random offset (between 0 and 1 second)
			// to nextUpdateTime upon instantiation. (Without this offset, the same
			// component of all active agents will be updated on the same time step.)
			Regulator(double numUpdatesPerSecond);

			// returns true if the current time exceeds nextUpdateTime
			bool IsReady();


		private:
			// the time period between updates
			double updatePeriod;

			// the next time the regulator allows code flow
			unsigned long nextUpdateTime;

		};

	}
}