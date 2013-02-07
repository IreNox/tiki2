
#include "Core/SceneGraphElement.h"

#if TIKI_USE_SCENEGRAPH
#include "Core/GameObject.h"

namespace TikiEngine
{
	SceneGraphElement::SceneGraphElement()
		:go(0), width(1.0f), height(1.0f), radius(0.5f), isDynamic(false),
		IsCulled(false), boundingBox(0), visibleTimer(1.5)
	{

	}

	void SceneGraphElement::SetGameObject( GameObject* go )
	{
		this->go = go;
		Vector3 pos = go->PRS.GPosition();
		this->Bounds = RectangleF::Create( pos.X - width * 0.5f, pos.Z - height * 0.5f, width, height);
		this->boundingBox = TIKI_NEW Bounding(go->GetEngine());

		SetBoundingVolume(Vector2::One);
		SetCullingBounds(Vector3::One);
	}

	SceneGraphElement::~SceneGraphElement()
	{
		SafeDelete(&boundingBox);
	}

	void SceneGraphElement::SetBoundingVolume(const Vector2& size)
	{
		this->Bounds.Width = this->width = size.X;
		this->Bounds.Height = this->height = size.X;
		this->radius = size.X * 0.5f;
	}

	void SceneGraphElement::SetCullingBounds(const Vector3& size, const Vector3& offset)
	{
		this->boundingBox->SetOffset(offset);
		this->min = Vector3( -size.X * 0.5f, 0, -size.Z * 0.5f );
		this->max = Vector3( size.X * 0.5f, size.Y, size.Z * 0.5f );
	}

	void SceneGraphElement::Update(const UpdateArgs& args)
	{
		Vector3 pos = go->PRS.GPosition();
		this->Bounds.X = pos.X - width * 0.5f;
		this->Bounds.Y = pos.Z - height * 0.5f;
		this->boundingBox->Set(pos + this->min, pos + this->max);
		this->IsCulled = false;

		if(isDynamic)
		{
			this->visibleTimer += args.Time.ElapsedTime;
		}
	}

	bool SceneGraphElement::IsInsideFrustum(Frustum& frustum)
	{
		//IsCulled = (frustum.PointInFrustum(go->PRS.GPosition()) == 0);
		IsCulled = (frustum.BoxInFrustum(boundingBox) == 0);
		return !IsCulled;
	}
	
}
#else
bool emptySceneGraphElement = true;
#endif
