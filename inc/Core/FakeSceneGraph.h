#pragma once

#include "Core/TypeInc.h"

#include "Core/Frustum.h"
#include "Core/GameObject.h"

#include <functional>
using namespace std;

namespace TikiEngine
{
	class SceneGraph
	{
	public:

		#pragma region Class
		SceneGraph()
		{

		}

		~SceneGraph()
		{
			FOREACH_PTR_CALL(gameObjects, Release());
		}
		#pragma endregion

		#pragma region Init
		void Initialize(const RectangleF&, int)
		{
		}
		#pragma endregion

		#pragma region Member - Add/Remove/Draw/Update/LateUpdate
		void Add(GameObject* go)
		{
			gameObjects.Add(go);
			go->AddRef();
		}

		bool Remove(GameObject* go)
		{
			if (gameObjects.Remove(go))
			{
				removeList.Add(go);
				return true;
			}

			return false;
		}

		void Draw(const DrawArgs& args)
		{
			FOREACH_PTR_CALL(gameObjects, Draw(args))
		}

		void Update(const UpdateArgs& args)
		{
			UInt32 i = 0;
			while (i < removeList.Count())
			{
				gameObjects.Remove(removeList[i]);
				removeList[i]->Release();

				i++;
			}
			removeList.Clear();

			i = 0;
			while (i < gameObjects.Count())
			{
				gameObjects[i]->Update(args);

				i++;
			}
		}

		void LateUpdate(const UpdateArgs& args)
		{
			FOREACH_PTR_CALL(gameObjects, LateUpdate(args))
		}
		#pragma endregion

		#pragma region Member - Do
		void Do(function<void(GameObject*)> whatIWant)
		{
			FOREACH_CODE(gameObjects, whatIWant(gameObjects[i]))
		}

		void DoInFrustum(function<void(GameObject*)> whatIWant)
		{
			UInt32 i = 0;
			while (i < gameObjects.Count())
			{
				whatIWant(gameObjects[i]);

				i++;
			}
		}

		void DoWithinRange(const Vector3& point, float distance, function<void(GameObject*)> whatIWant)
		{
			UInt32 i = 0;
			while (i < gameObjects.Count())
			{
				if (Vector3::Distance(point, gameObjects[i]->PRS.GPosition()) < distance)
					whatIWant(gameObjects[i]);

				i++;
			}
		}
		#pragma endregion

		#pragma region Member - Find
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
				if (Vector3::Distance(point, gameObjects[i]->PRS.GPosition()) <= distance)
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
		#pragma endregion

		inline List<GameObject*>& GetDefaultGOs() { return gameObjects; }
		inline List<GameObject*>& GetStaticGOs() { return gameObjects; }
		inline List<GameObject*>& GetAllGameObjects() { return gameObjects; }

	private:

		List<GameObject*> gameObjects;
		List<GameObject*> removeList;

	};
}