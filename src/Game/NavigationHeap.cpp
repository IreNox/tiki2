#include "Game/NavigationHeap.h"

namespace TikiEngine
{
	namespace AI
	{

		// Default Object Constructor / destructor
		inline NavigationHeap::NavigationHeap()
		{
		}

		inline NavigationHeap::~NavigationHeap()
		{
		}

		inline void NavigationHeap::Setup(int SessionID, const Vector3& Goal)
		{
			this->goal = Goal;
			this->sessionID = SessionID;
			this->nodes.clear();
		}
		
		void NavigationHeap::AddCell(NavigationCell* cell)
		{
			NavigationNode NewNode;

			NewNode.cell = cell;
			NewNode.cost = cell->PathfindingCost();

			nodes.push_back(NewNode);
			std::push_heap( nodes.begin(), nodes.end(), comp );
		}

		void NavigationHeap::AdjustCell(NavigationCell* cell)
		{
			Container::iterator iter = FindNodeInterator(cell);

			if (iter != nodes.end())
			{
				// update the node data
				(*iter).cell = cell;
				(*iter).cost = cell->PathfindingCost();
	
				// reorder the heap
				std::push_heap(nodes.begin(), iter+1, comp);
			}
		}

		inline bool NavigationHeap::NotEmpty()const
		{
			return(nodes.size() ? true : false);
		}

		inline void NavigationHeap::GetTop(NavigationNode& n)
		{
			n = nodes.front();
			std::pop_heap( nodes.begin(), nodes.end(), comp );
			nodes.pop_back();
		}

		inline NavigationHeap::Container::iterator NavigationHeap::FindNodeInterator(NavigationCell* cell)
		{
			for( Container::iterator i = nodes.begin(); i != nodes.end(); ++i )
			{
			  if( (*i).cell == cell )
				  return i;
			}
			return nodes.end();
		}

		int NavigationHeap::SessionID() const
		{
			return(sessionID);
		}

		const Vector3& NavigationHeap::Goal() const
		{
			return(goal);
		}

	}
}