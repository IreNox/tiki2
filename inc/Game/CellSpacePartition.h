#pragma once

#include <vector>
#include <list>

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

			Cell(Engine* engine, const Vector3& minimum, const Vector3& maximum)
			{
				BBox = engine->librarys->CreateResource<IBoundingBox>();
				BBox->Set(minimum, maximum);
			}
		};

		template <class entity>
		class CellSpacePartition
		{
		public:
			CellSpacePartition<entity>(Engine* engine, float width, float height, int cellsX, int cellsY, int maxEntitys);


		private:
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


		};

		template <class entity>
		CellSpacePartition<entity>::CellSpacePartition(Engine* engine, float width, float height, int cellsX, int cellsY, int maxEntitys)
			: neighbors(maxEntitys, entity()),
			  spaceWidth(width), 
			  spaceHeight(height),
			  numCellsX(cellsX), 
		      numCellsY(cellsY)
		{
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
												Vector3(left, 0, top), 
												Vector3(right, 50, bot)));
				}

			}

		}

	}
}