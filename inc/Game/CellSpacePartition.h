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
			CellSpacePartition(Engine* engine, float width, float height, int cellsX, int cellsY, int maxEntitys);

			// adds entities to the class by allocating them to the appropriate cell
			void AddEntity(const entity& ent);

			IBoundingBox* GetQuerybox() const { return queryBox; }

			//update an entity's cell by calling this from your entity's Update method 
			void UpdateEntity(const entity& ent, Vector2 oldPos);

			// this method calculates all a target's neighbors and stores them in
			// the neighbor vector. After you have called this method use the begin, 
			// next and end methods to iterate through the vector.
			void CalculateNeighbors(Vector2 targetPos, float queryRadius);

			// returns a reference to the entity at the front of the neighbor vector
			inline entity& begin() { curNeighbor = neighbors.begin(); return *curNeighbor; }
			
			// this returns the next entity in the neighbor vector
			inline entity& next(){ ++curNeighbor; return *curNeighbor; }
			
			// returns true if the end of the vector is found (a zero value marks the end)
			inline bool end(){ return (curNeighbor == neighbors.end()) || (*curNeighbor == 0); }  

			// Clears the cells of all entities
			void EmptyCells();

		    // renders the cell edges
		    void RenderCells() const;

		private:
			// given a position in the game space this method determines the relevant cell's index
			int PositionToIndex(const Vector2& pos);

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