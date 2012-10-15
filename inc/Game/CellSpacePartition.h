#pragma once

#include <vector>
#include <list>
#include <cassert>
#include "Core/IBoundingBox.h"

namespace TikiEngine
{
	namespace AI
	{
		using namespace TikiEngine::Resources;

		/* defines a cell containing a list of pointers to entities */
		template <class entity>
		struct Cell
		{
			// all the entities inhabiting this cell
			std::list<entity> Members;

			// the cells bounding box
			IBoundingBox* BBox;

			// reference to the engine object
			Engine* engine;

			Cell(Engine* engine, const Vector3& minimum, const Vector3& maximum)
			{
				this->engine = engine;
				BBox = engine->librarys->CreateResource<IBoundingBox>();
				BBox->Set(minimum, maximum);
			}

			void Dispose() { SafeRelease(&BBox); }
		};

		template <class entity>
		class CellSpacePartition
		{
		public:
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

			// adds entities to the class by allocating them to the appropriate cell
			void CellSpacePartition<entity>::AddEntity(const entity& ent)
			{
				assert(ent);

				int sz = cells.size();
				int idx = PositionToIndex(ent->Pos());

				cells[idx].Members.push_back(ent);
			}

			//update an entity's cell by calling this from your entity's Update method 
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

			// this method calculates all a target's neighbors and stores them in
			// the neighbor vector. After you have called this method use the begin, 
			// next and end methods to iterate through the vector.
			void CellSpacePartition<entity>::CalculateNeighbors(Vector2 targetPos, float queryRadius)
			{
				// create an iterator and set it to the beginning of the neighbor vector
				std::vector<entity>::iterator curNbor = neighbors.begin();

				//create the query box that is the bounding box of the target's query area
				queryBox->Set(Vector3(targetPos.X - queryRadius, cellMinZ, targetPos.Y - queryRadius),
							  Vector3(targetPos.X + queryRadius, cellMaxZ, targetPos.Y + queryRadius));

				// pre-compute queryradius in squared space
				float doubleRadius = queryRadius * queryRadius;

				// iterate through each cell and test to see if its bounding box overlaps
				// with the query box. If it does and it also contains entities then make further proximity tests.
				std::vector<Cell<entity> >::iterator curCell;
				for(curCell = cells.begin(); curCell != cells.end(); ++curCell)
				{
					//test to see if this cell contains members and if it overlaps the query box
					if (curCell->BBox->Intersects(queryBox) && 
						!curCell->Members.empty())
					{
						//add any entities found within query radius to the neighbor list
						std::list<entity>::iterator it = curCell->Members.begin();
						for (it; it != curCell->Members.end(); ++it)
						{
							if (Vector2::DistanceSquared((*it)->Pos(), targetPos) < doubleRadius)
								*curNbor++ = *it;
						}
					}
				}	

				// mark end of list with zero
				*curNbor = 0;
			}

			// returns a reference to the entity at the front of the neighbor vector
			inline entity& begin() { curNeighbor = neighbors.begin(); return *curNeighbor; }
			
			// this returns the next entity in the neighbor vector
			inline entity& next(){ ++curNeighbor; return *curNeighbor; }
			
			// returns true if the end of the vector is found (a zero value marks the end)
			inline bool end(){ return (curNeighbor == neighbors.end()) || (*curNeighbor == 0); }  

			// returns the BoundingBox used to Query the cellspace
			IBoundingBox* GetQuerybox() const { return queryBox; }

			// Clears the cells of all entities
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

		    // renders the cell edges
		    void CellSpacePartition<entity>::RenderCells() const
			{
				// draw all cells
				std::vector<Cell<entity> >::const_iterator curCell;
				for(curCell = cells.begin(); curCell != cells.end(); ++curCell)
					curCell->BBox->DrawDebug(Color(1, 1, 0, 1));
			
				// and the queryBox
				queryBox->DrawDebug(Color::Green);
			}


		private:
			// given a position in the game space this method determines the relevant cell's index
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

			// reference to the engine object
			Engine* engine;

			// Bounding box used to query in CalculateNeighbors
			IBoundingBox* queryBox;

			// the required amount of cells in the space
			std::vector<Cell<entity>> cells;

			// store any valid neighbors when an entity searches its neighboring space
			std::vector<entity> neighbors;

			// iterator used by the methods next and begin to traverse through the above vector of neighbors
			typename std::vector<entity>::iterator curNeighbor;

			// the width and height of the world space the entities inhabit
			float spaceWidth;
			float spaceHeight;

			// the number of cells the space is going to be divided up into
			int numCellsX;
			int numCellsY;

			float cellSizeX;
			float cellSizeY;

			float cellMinZ;
			float cellMaxZ;
		};
	}
}