#pragma once

#include "Core/TypeInc.h"

namespace TikiEngine
{
	class SceneGraph
	{
	public:

		SceneGraph() {}
		~SceneGraph() {}

		void Do(function<void(GameObject*)> whatIWant)
		{
			FOREACH(gameObjects, whatIWant(gameObjects[i]))
		}

		void DoWithinRange(Vector3& point, float distance, function<void(GameObject*)> whatIWant)
		{
			UInt32 i = 0;
			while (i < gameObjects.Count())
			{
				if (Vector3::Distance(point, gameObjects[i]->PRS.GPosition()))
					whatIWant(gameObjects[i]);

				i++;
			}
		}

		void Find(List<GameObject*>& result, RectangleF& rect , function<bool(GameObject*)> where = 0)
		{
			UInt32 i = 0;
			while (i < gameObjects.Count())
			{
				if (rect.Contains(gameObjects[i]->PRS.GPosition().XZ()))
				{
					if (where == 0 || where(gameObjects[i]))
						result.Add(gameObjects[i]);
				}

				i++;
			}
		}

		void Find(List<GameObject*>& result, function<bool(GameObject*)> where = 0)
		{
			UInt32 i = 0;
			while (i < gameObjects.Count())
			{
				if (where == 0 || where(gameObjects[i]))
					result.Add(gameObjects[i]);

				i++;
			}
		}

		void Find(List<GameObject*>& result, Frustum& frustum)
		{
			result.AddRange(gameObjects);
		}

		void Find(List<GameObject*>& result, Vector3& point, float distance, function<bool(GameObject*)> where = 0)
		{
			UInt32 i = 0;
			while (i < gameObjects.Count())
			{
				if (Vector3::Distance(point, gameObjects[i]->PRS.GPosition()))
				{
					if (where == 0 || where(gameObjects[i]))
						result.Add(gameObjects[i]);
				}

				i++;
			}
		}

		void FindInFrustum(List<GameObject*>& result, function<bool(GameObject*)> where = 0)
		{
			UInt32 i = 0;
			while (i < gameObjects.Count())
			{
				if (where == 0 || where(gameObjects[i]))
					result.Add(gameObjects[i]);

				i++;
			}
		}

		inline List<GameObject*>& GetDefaultGOs() { return gameObjects; }
		inline List<GameObject*>& GetStaticGOs() { return gameObjects; }

	private:

		List<GameObject*> gameObjects;

	};
}