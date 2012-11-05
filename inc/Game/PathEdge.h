#pragma once
#include "Core/Vector2.h"

namespace TikiEngine
{
    namespace AI
    {
		class PathEdge
		{
		public:
			PathEdge(Vector2 source, Vector2 destination)
			{
				this->source = source;
				this->destination = destination;
			}


			Vector2 Destination() const {return destination; }
			Vector2 Source() const { return source; }

		private:
			Vector2 source;
			Vector2 destination;
		};


	}
}