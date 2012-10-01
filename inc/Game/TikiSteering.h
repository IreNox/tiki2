#pragma once



namespace TikiEngine
{
	namespace AI
	{
		//--------------------------- Constants ----------------------------------

		//the radius of the constraining circle for the wander behavior
		const double WanderRad    = 1.2;
		//distance the wander circle is projected in front of the agent
		const double WanderDist   = 2.0;
		//the maximum amount of displacement along the circle each frame
		const double WanderJitterPerSec = 40.0;

		class TikiSteering
		{
			public:
			  enum summing_method{weighted_average, prioritized, dithered};

			private:
			  enum behavior_type
			  {
				none               = 0x00000,
				seek               = 0x00002,
				arrive             = 0x00008,
				wander             = 0x00010,
				separation         = 0x00040,
				wall_avoidance     = 0x00200,
			  };



		};


	}
}