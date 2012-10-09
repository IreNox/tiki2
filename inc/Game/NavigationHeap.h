#pragma once
#include <vector>
#include <list>
#include <algorithm>
#include "Game/NavigationCell.h"

namespace TikiEngine
{
	namespace AI
	{
		class NavigationCell;

		#pragma region Navigation Node
		/* 	A NavigationNode represents an entry in the NavigationHeap. It provides some simple
		 *	operators to classify it against other NavigationNodes when the heap is sorted. 
		 */
		class NavigationNode
		{
		public:
			NavigationNode(): cell(0), cost(0){}
			~NavigationNode() {}

			NavigationCell* cell; // pointer to the cell in question
			float cost;        // (g + h) in A* represents the cost of traveling through this cell

			inline bool operator < (const NavigationNode& b )
			{
				// To compare two nodes, we compare the cost or `f' value, which is the
				// sum of the g and h values defined by A*.
				return (cost < (b.cost));
			}

			inline bool operator > (const NavigationNode& b )
			{
				// To compare two nodes, we compare the cost or `f' value, which is the
				// sum of the g and h values defined by A*.
				return (cost > (b.cost));
			}

			inline bool operator == (const NavigationNode& b )
			{
				// Two nodes are equal if their components are equal
				return ((cell == b.cell) && (cost == b.cost));
			}
		};

		// The STL requires some external operators as well
		inline bool operator < ( const NavigationNode& a, const NavigationNode& b )
		{
			return (a.cost < b.cost);
		}

		inline bool operator > ( const NavigationNode& a, const NavigationNode& b )
		{
			return (a.cost > b.cost);
		}

		inline bool operator == ( const NavigationNode& a, const NavigationNode& b )
		{
			return ((a.cell == b.cell) && (a.cost == b.cost));
		}
		#pragma endregion

		/* A NavigationHeap is a priority-ordered list facilitated by the STL heap functions.
		* This class is also used to hold the current path finding session ID and the desired 
		* goal point for NavigationCells to query. Thanks to Amit J. Patel for detailing the use
		* of STL heaps in this way. It's much faster than a linked list or multimap approach. 
		*/
		class NavigationHeap
		{
		public:
			// greater<NavigationNode> is an STL thing to create a 'comparison' object out of
			// the greater-than operator, and call it comp.
			typedef std::vector<NavigationNode> Container;
			std::greater<NavigationNode> comp;

			// ctor/dtor
			NavigationHeap();
			~NavigationHeap();

			// Initialize the heap and record our new session info
			void Setup(int SessionID, const Vector3& Goal);

			//´Add a cell to the heap, sorting it in by it's cost value 
			void AddCell(NavigationCell* cell);

			// Adjust a cell in the heap to reflect it's updated cost value.  NOTE: Cells may only sort up in the heap. 
			void AdjustCell(NavigationCell* cell);


			// Returns true if the heap is not empty 
			bool NotEmpty() const;

			// Pop the top off the heap and remove the best value for processing. 
			void GetTop(NavigationNode& n);

			int SessionID() const;
			const Vector3& Goal() const;

		private:
			//	Search the container for a given cell. May be slow, so don't do this unless nessesary. 
			Container::iterator FindNodeInterator(NavigationCell* cell);

			Container nodes;
			int sessionID;
			Vector3 goal;

			// unimplemented
			NavigationHeap( const NavigationHeap& Src);
			NavigationHeap& operator=( const NavigationHeap& Src);

		};

	}
}