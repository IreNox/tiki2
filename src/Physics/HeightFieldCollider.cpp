
#include "Physics/HeightFieldCollider.h"
#include "Physics/DllMain.h"

namespace TikiEngine
{
	namespace Physics
	{
		HeightFieldCollider::HeightFieldCollider(Engine* engine, GameObject* gameObject)
			: IHeightFieldCollider(engine, gameObject), Collider(), heightField(0)
		{
		}

		HeightFieldCollider::~HeightFieldCollider()
		{
		}

		void HeightFieldCollider::SetHeightField(UInt16* height, const HeightFieldDesc& desc)
		{
			NxHeightFieldDesc nxDesc;
			nxDesc.nbColumns = desc.Columns;
			nxDesc.nbRows = desc.Rows;
			nxDesc.convexEdgeThreshold = 0;

			NxU32 i = 0;
			NxU32 c = desc.Columns * desc.Rows;
			NxU32* current = TIKI_NEW NxU32[desc.Columns * desc.Rows];

			nxDesc.samples = current;
			nxDesc.sampleStride = sizeof(NxU32);
			
			int matInt = (material == 0 ? -1 : material->GetIndex());
			while (i < c)
			{
				NxHeightFieldSample* sam = (NxHeightFieldSample*)current;

				sam->height = height[i];
				sam->tessFlag = 0;
				sam->materialIndex0 = matInt;
				sam->materialIndex1 = matInt;

				current++;
				i++;
			}

			heightField = DllMain::PhysicsSDK->createHeightField(nxDesc);
			delete[](nxDesc.samples);

			NxHeightFieldShapeDesc shapeDesc;
			shapeDesc.heightField	= heightField;
			shapeDesc.shapeFlags	= NX_SF_FEATURE_INDICES | NX_SF_VISUALIZATION;
			shapeDesc.heightScale	= desc.HeightScale / 65536.0f;
			shapeDesc.columnScale	= desc.ColumnScale;
			shapeDesc.rowScale		= desc.RowScale;
			shapeDesc.holeMaterial	= 0;
			shapeDesc.group			= CG_Collidable_Non_Pushable;
			shapeDesc.materialIndexHighBits	= 0;

			actorDescription.shapes.pushBack(&shapeDesc);
			actorDescription.userData = dynamic_cast<ICollider*>(this);
			actorDescription.globalPose.t = center;

			actor = DllMain::Scene->createActor(actorDescription);
		}
	}
}