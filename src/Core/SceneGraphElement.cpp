#include "Core/SceneGraphElement.h"
#include "Core/GameObject.h"


namespace TikiEngine
{
	SceneGraphElement::SceneGraphElement()
	{

	}

	SceneGraphElement::SceneGraphElement(GameObject* go)
		:go(go), width(1.0f), height(1.0f), isDynamic(false)
	{
		Vector3 pos = go->PRS.GPosition();
		this->Bounds = RectangleF::Create(pos.X - width * 0.5f, pos.Z - height * 0.5f, width, height);
	}

	SceneGraphElement::~SceneGraphElement()
	{

	}

	void SceneGraphElement::Update()
	{
		Vector3 pos = go->PRS.GPosition();
		this->Bounds.X = pos.X - width * 0.5f;
		this->Bounds.Y = pos.Z - height * 0.5f;
	}

	bool SceneGraphElement::IsInsideFrustum(Frustum& frustum)
	{
		return !frustum.PointInFrustum(go->PRS.GPosition());
	}
	
}