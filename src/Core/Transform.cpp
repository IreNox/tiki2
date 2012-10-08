
#include "Core/Transform.h"

namespace TikiEngine
{
	#pragma region Class
	Transform::Transform(GameObject* gameObject)
		: position(0.0f), rotation(Quaternion::Identity), scale(1.0f), isDirty(true)
	{
	}

	Transform::~Transform()
	{
	}
	#pragma endregion

	#pragma region Member
	void Transform::FillWorldMatrix(Matrix* worldMatrix)
	{
		checkWorldMatrix();

		*worldMatrix = world;
	}
	#pragma endregion

	#pragma region  Member - Get Direction
	Vector3 Transform::GetForward()
	{
		return rotation * Vector3::ForwardRH;
	}

	Vector3 Transform::GetUp()
	{
		return rotation * Vector3::Up;
	}

	Vector3 Transform::GetLeft()
	{
		return rotation * Vector3::Left;
	}
	#pragma endregion

	#pragma region Member - Get/Set
	Vector3 Transform::GetPosition()
	{
		return position;
	}

	void Transform::SetPosition(const Vector3& pos)
	{
		this->position = pos;
		this->isDirty = true;
	}

	Vector3 Transform::GetScale()
	{
		return scale;
	}

	void Transform::SetScale(const Vector3& scale)
	{
		this->scale = scale;
		this->isDirty = true;
	}

	Quaternion Transform::GetRotation()
	{
		return rotation;
	}

	void Transform::SetRotation(const Quaternion& rot)
	{
		this->rotation = rot;
		this->isDirty = true;
	}
	#pragma endregion

	#pragma region Private Member
	void Transform::checkWorldMatrix()
	{
		if (!isDirty) return;

		Matrix rot = Matrix::CreateFromQuaternion(this->rotation);
		Matrix scale = Matrix::CreateScaleMatrix(this->scale);
		Matrix trans = Matrix::CreateTranslation(this->position);

		world = scale * rot * trans;
		isDirty = false;
	}
	#pragma endregion
}