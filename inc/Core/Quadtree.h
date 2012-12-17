#pragma once
#include "Core/RectangleF.h"
#include "Core/GameObject.h"

namespace TikiEngine
{
	class QuadtreeNode;

	class Quadtree
	{
	public:
		Quadtree();
		Quadtree(const RectangleF& rect, int layerDepth);
		~Quadtree();

		void Create();
		void SetBound(RectangleF& rect);
		bool IsReady();
		
		void Insert(GameObject* go);

		void Intersects(List<GameObject*>& result, RectangleF& rect);

		void Draw(const DrawArgs& args);


	private:

		QuadtreeNode* node;

		int layerDepth;
		RectangleF bounds;
		bool created;

	};

	class QuadtreeNode
	{
	public: 
		QuadtreeNode(RectangleF& rect, int layerDepth);
		~QuadtreeNode();

		bool CreateSubdivision();
		
		RectangleF& Bounds();

		void Insert(GameObject* go);
		void Draw(const DrawArgs& args);

		List<GameObject*>& Content();
		void SubContent(List<GameObject*>& result);

		void Intersects(List<GameObject*>& result, RectangleF& rect);

		bool IsEmpty();

	private:
		RectangleF bounds;
		int layerDepth;

		List<QuadtreeNode*> childs;

		List<GameObject*> content;
	};
}