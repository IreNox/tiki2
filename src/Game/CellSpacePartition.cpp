#include "Game/CellSpacePartition.h"
#include "Game/TikiBot.h"
#include "Core/TypeGlobals.h"
#include "Core/LibraryManager.h"

namespace TikiEngine
{
	namespace AI
	{
		// template instantiation
		template class CellSpacePartition<TikiBot*>;

		template <class entity>
		CellSpacePartition<entity>::CellSpacePartition(Engine* engine, float width, float height, int cellsX, int cellsY, int maxEntitys) : 
			neighbors(maxEntitys, entity()),
			spaceWidth(width), 
			spaceHeight(height),
			numCellsX(cellsX), 
		    numCellsY(cellsY)
		{
			this->engine = engine;
			cellMinZ = 0;
			cellMaxZ = 32;
			// create queryBox used to calc neighbors
			queryBox = engine->librarys->CreateResource<IBoundingBox>();

			// calc cell bounds
			cellSizeX = width / cellsX;
			cellSizeY = height / cellsY;

			// create cells
			for(int y = 0; y < numCellsY; ++y)
			{
				for(int x = 0; x < numCellsX; ++x)
				{
					float left = x * cellSizeX;
					float right = left + cellSizeX;
					float top = y * cellSizeY;
					float bot = top + cellSizeY;

					cells.push_back(Cell<entity>(engine, 
												Vector3(left, cellMinZ, top), 
												Vector3(right, cellMaxZ, bot)));
				} // for(x)
			} // for(y)

		}

		template<class entity>
		int CellSpacePartition<entity>::PositionToIndex(const Vector2& pos)
		{
			int idx = (int)(numCellsX * pos.X / spaceWidth) +
					  ((int)((numCellsY) * pos.Y / spaceHeight) * numCellsX);

			//if the entity's position is equal to vector2(spaceWidth, spaceHeight)
			//then the index will overshoot. We need to check for this and adjust.
			if (idx > (int)cells.size()-1)
				idx = (int)cells.size()-1;

			return idx;
		}

		template<class entity>
		void CellSpacePartition<entity>::AddEntity(const entity& ent)
		{
			assert(ent);

			int sz = cells.size();
			int idx = PositionToIndex(ent->Pos());

			cells[idx].Members.push_back(ent);
		}

		template<class entity>
		void CellSpacePartition<entity>::UpdateEntity(const entity& ent, Vector2 oldPos)
		{
			// if the index for the old pos and the new pos are not equal then the entity has moved to another cell.
			int oldIdx = PositionToIndex(oldPos);
			int newIdx = PositionToIndex(ent->Pos());

			if (newIdx == oldIdx)
				return;

			 // the entity has moved into another cell so delete from current cell and add to new one
			cells[oldIdx].Members.remove(ent);
			cells[newIdx].Members.push_back(ent);
		}

		template<class entity>
		void CellSpacePartition<entity>::CalculateNeighbors(Vector2 targetPos, float queryRadius)
		{
			// create an iterator and set it to the beginning of the neighbor vector
			std::vector<entity>::iterator curNbor = neighbors.begin();

			//create the query box that is the bounding box of the target's query area
			queryBox->Set(Vector3(targetPos.X - queryRadius, cellMinZ, targetPos.Y - queryRadius),
                          Vector3(targetPos.X + queryRadius, cellMaxZ, targetPos.Y + queryRadius));

			// iterate through each cell and test to see if its bounding box overlaps
			// with the query box. If it does and it also contains entities then make further proximity tests.
			std::vector<Cell<entity> >::iterator curCell;
			for(curCell = cells.begin(); curCell != cells.end(); ++curCell)
			{
				//test to see if this cell contains members and if it overlaps the query box
				if (curCell->BBox->Intersects(*queryBox) && 
				    !curCell->Members.empty())
				{
					//add any entities found within query radius to the neighbor list
					std::list<entity>::iterator it = curCell->Members.begin();
					for (it; it != curCell->Members.end(); ++it)
					{
						if (Vector2::DistanceSquared((*it)->Pos(), targetPos) < queryRadius * queryRadius)
							*curNbor++ = *it;
					}
				}
			}	

			// mark end of list with zero
			*curNbor = 0;
		}

		template<class entity>
		void CellSpacePartition<entity>::EmptyCells()
		{
			std::vector<Cell<entity> >::iterator it = cells.begin();
			for (it; it != cells.end(); ++it)
			{
				it->Members.clear();
				it->Dispose();
			}

			SafeRelease(&queryBox);
		}

		template<class entity>
		void CellSpacePartition<entity>::RenderCells() const
		{
			// draw all cells
			std::vector<Cell<entity> >::const_iterator curCell;
			for(curCell = cells.begin(); curCell != cells.end(); ++curCell)
				curCell->BBox->DrawDebug(Color(1, 1, 0, 1));
			
		    // and the queryBox
			queryBox->DrawDebug(Color::Green);
		}

	}
}