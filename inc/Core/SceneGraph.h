#pragma once
#include "Core/List.h"
#include "Core/UpdateArgs.h"
#include "Core/DrawArgs.h"
#include "Core/SceneGraphNode.h"
#include "Core/Vector3.h"
#include "Core/Frustum.h"
#include <functional>

namespace TikiEngine
{


	class SceneGraph
	{
	public:
		SceneGraph();
		~SceneGraph();

		void Initialize(RectangleF& rect, int layerDepth);
		
		void Add(GameObject* go);
		bool Remove(GameObject* go);

		void Update(const UpdateArgs& args);
		void PerformCulling(Frustum& frustum);

		void Draw(const DrawArgs& args);

		void Do(function<void(GameObject*)> whatIWant);

		void Find(List<GameObject*>& result, RectangleF& rect , function<bool(GameObject*)> where = 0);
		void Find(List<GameObject*>& result, function<bool(GameObject*)> where = 0);
		void Find(List<GameObject*>& result, Frustum& frustum);
		void Find(List<GameObject*>& result, Vector3& point, float distance, function<bool(GameObject*)> where = 0);

		void FindInFrustum(List<GameObject*>& result, function<bool(GameObject*)> where = 0);

		List<GameObject*>& GetDefaultGOs();
		List<GameObject*>& GetStaticGOs();

	private:
		inline void Lock(){ this->locked = true; }
		void Unlock();
		inline bool IsLocked(){ return this->locked; }


		bool initialized;
		SceneGraphNode rootNode;

		List<GameObject*> defaultGOs;
		List<GameObject*> staticGOs;
		SceneGraphNode dynamicGOs;

		bool locked;
		List<GameObject*> removeList;
	};
}