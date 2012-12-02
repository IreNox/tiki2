#pragma once

#include "Core/ICollider.h"

namespace TikiEngine
{
	namespace Components
	{
		struct HeightFieldDesc
		{
			UInt32 Columns;
			UInt32 Rows;

			Single ColumnScale;
			Single RowScale;
			Single HeightScale;
		};

		class IHeightFieldCollider : public ICollider
		{
		public:

			IHeightFieldCollider(Engine* engine, GameObject* gameObject) : ICollider(engine, gameObject) {}
			virtual ~IHeightFieldCollider() {}

			virtual void SetHeightField(UInt16* height, const HeightFieldDesc& desc) = 0;

		};
	}
}
