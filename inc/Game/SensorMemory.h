#pragma once


#include <map>
#include <list>
#include "Core/Vector3.h"
#include "Core/UpdateArgs.h"
#include "Core/DrawArgs.h"

namespace TikiEngine
{
	namespace AI
	{
		class TikiBot;

		// Each time a bot encounters a TIKI_NEW opponent, an instance of a MemoryRecord
		// is created and added to the memory map. Once a record has been made,
		// whenever the corresponding opponent is heard or seen its record is updated
		// with the relevant information
		class MemoryRecord
		{
		public:
			// records the time the opponent was last sensed (seen or heard). This
			// is used to determine if a bot can 'remember' this record or not. 
			// (if Current Time - TimeLastSensed is greater than the bot's
			// memory span, the data in this record is made unavailable to clients)
			double TimeLastSensed;

			// it can be useful to know how long an opponent has been visible. This 
			// variable is tagged with the current time whenever an opponent first becomes
			// visible. It's then a simple matter to calculate how long the opponent has
			// been in view (Current Time - TimeBecameVisible)
			double TimeBecameVisible;

			// it can also be useful to know the last time an opponent was seen
			double TimeLastVisible;

			// a vector marking the position where the opponent was last sensed. This can
			// be used to help hunt down an opponent if it goes out of view
			Vector3 lastSensedPosition;

			// set to true if opponent is within the field of view of the owner
			bool WithinFOV;

			// set to true if there is no obstruction between the opponent and the owner, permitting a shot.
			bool Shootable;

			MemoryRecord()
			{
				TimeLastSensed	  = -999;
				TimeBecameVisible = -999;
				TimeLastVisible	  = 0;

				WithinFOV = false;
				Shootable = false;
			}

		};

		class SensorMemory
		{

		public:
			SensorMemory(TikiBot* bot, double memSpan);

			// this removes a bot's record from memory
			void RemoveBotFromMemory(TikiBot* bot);

			// this method iterates through all the opponents in the game world and 
			// updates the records of those that are in the owner's FOV
			void UpdateVision(const UpdateArgs& args);

			// returns true if the bot given as a parameter can be shot (ie. its not obscured by walls or terrain)
			bool IsOpponentShootable(TikiBot* opponent) const;

			// returns true if the bot given as a parameter is within FOV
			bool IsOpponentWithinFOV(TikiBot* opponent) const;

			// returns the last recorded position of the bot
			Vector3 GetLastRecordedPositionOfOpponent(TikiBot* opponent) const;

			//  returns the amount of time the given bot has been visible
			double GetTimeOpponentHasBeenVisible(TikiBot* opponent, const GameTime& time) const;

			// returns the amount of time the given opponent has remained out of view
			// returns a high value if opponent has never been seen or not present
			double GetTimeOpponentHasBeenOutOfView(TikiBot* opponent, const GameTime& time) const;

			// returns the amount of time the given bot has been visible
			double GetTimeSinceLastSensed(TikiBot* opponent, const GameTime& time) const;

			// this method returns a list of all the opponents that have had their
			// records updated within the last memorySpan seconds.
			std::list<TikiBot*> GetListOfRecentlySensedOpponents(const GameTime& time) const;

			void Draw(const DrawArgs& args);

		private:
			typedef std::map<TikiBot*, MemoryRecord> MemoryMap;

			// this methods checks to see if there is an existing record for the bot. If
			// not a TIKI_NEW MemoryRecord record is made and added to the memory map.(called by UpdateVision)
			void MakeTIKI_NEWRecordIfNotAlreadyPresent(TikiBot* opponent);

			// the owner of this instance
			TikiBot* owner;

			// used to simulate memory of sensory events. A MemoryRecord
			// is created for each opponent in the environment. Each record is updated 
			// whenever the opponent is encountered. when it is seen
			MemoryMap memoryMap;

			// how long (in seconds) a bot's sensory memory persists
			// a bot has a memory span equivalent to this value. When a bot requests a 
			// list of all recently sensed opponents this value is used to determine if 
			// the bot is able to remember an opponent or not.
			double memorySpan;



		};


	}
}