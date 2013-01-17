#include "Core/SceneGraphElement.h"
#include "Core/GameObject.h"


namespace TikiEngine
{
	SceneGraphElement::SceneGraphElement()
		:go(0), width(1.0f), height(1.0f), isDynamic(false),
		IsCulled(false), boundingBox(0)
	{

	}

	void SceneGraphElement::SetGameObject( GameObject* go )
	{
		this->go = go;
		Vector3 pos = go->PRS.GPosition();
		this->Bounds = RectangleF::Create( pos.X - width * 0.5f, pos.Z - height * 0.5f, width, height);
		this->boundingBox = new Bounding(go->GetEngine());
		SetBounds( 1.0f, 1.0f);
	}

	SceneGraphElement::~SceneGraphElement()
	{	
		if(boundingBox)
		{
			delete boundingBox;
			boundingBox = 0;
		}
	}

	void SceneGraphElement::SetBounds( float width, float height )
	{
		this->min = Vector3( -width * 0.5f, 0, -width * 0.5f );
		this->max = Vector3( width * 0.5f, height, width * 0.5f );
	}

	void SceneGraphElement::Update()
	{
		Vector3 pos = go->PRS.GPosition();
		this->Bounds.X = pos.X - width * 0.5f;
		this->Bounds.Y = pos.Z - height * 0.5f;
		this->boundingBox->Set(pos + this->min, pos + this->max);
	}

	bool SceneGraphElement::IsInsideFrustum(Frustum& frustum)
	{
		//IsCulled = (frustum.PointInFrustum(go->PRS.GPosition()) == 0);
		IsCulled = (frustum.BoxInFrustum(boundingBox) == 0);
		return !IsCulled;
	}
	
}