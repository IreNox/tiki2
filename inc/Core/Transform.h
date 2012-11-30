#pragma once

#include "Core/Matrix.h"
#include "Core/Vector3.h"
#include "Core/Quaternion.h"

namespace TikiEngine
{	
	class GameObject;

	class Transform
	{
		friend class GameObject;

	public:
		
		~Transform();

		Vector3 GetForward();
		Vector3 GetUp();
		Vector3 GetLeft();

		const Vector3& GPosition() const;
		const Vector3& GScale() const;
		const Quaternion& GRotation() const;

		Vector3& SPosition();
		Vector3& SScale();
		Quaternion& SRotation();

		bool IsDirty();
		void MarkAsClean();

		void FillWorldMatrix(Matrix* worldMatrix);

	private:

		GameObject* gameObject;

		//GameObject* parent;
		//List<GameObject*> childs;

		bool isDirty;
		Matrix goWorld;
		Matrix totalWorld;

		Vector3 position;
		Quaternion rotation;
		Vector3 scale;

		Transform();
		Transform(GameObject* gameObject);

		void checkWorldMatrix();

	};
}