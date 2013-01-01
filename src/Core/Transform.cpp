
#include "Core/Transform.h"
#include "Core/GameObject.h"

namespace TikiEngine
{
	#pragma region Class
	Transform::Transform()
	{
	}

	Transform::Transform(GameObject* gameObject)
		: position(0.0f), rotation(Quaternion::Identity), scale(1.0f), isDirty(true), isSGDirty(true), gameObject(gameObject)
	{
	}

	Transform::~Transform()
	{
	}
	#pragma endregion

	#pragma region Member
	void Transform::MarkAsClean()
	{
		isDirty = false;
	}

	void Transform::FillWorldMatrix(Matrix* worldMatrix)
	{
		checkWorldMatrix();

		*worldMatrix = totalWorld;
	}
	#pragma endregion

	#pragma region Private Member
	void Transform::checkWorldMatrix()
	{
		if (isDirty)
		{
			Matrix rot = Matrix::CreateFromQuaternion(this->rotation);
			Matrix scale = Matrix::CreateScaleMatrix(this->scale);
			Matrix trans = Matrix::CreateTranslation(this->position);

			goWorld = Matrix::Transpose(scale * rot * trans);
		}

		if (gameObject->parent && gameObject->parent->PRS.isDirty)
		{
			totalWorld = gameObject->parent->PRS.totalWorld * goWorld;
		}
		else if (isDirty)
		{
			totalWorld = goWorld;
		}

		isDirty = false;
	}
	#pragma endregion
}