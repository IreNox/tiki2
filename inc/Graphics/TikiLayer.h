#pragma once

#include "Graphics/TikiAnimation.h"

#include "Core/TikiObject.h"
#include "Core/TypeGlobals.h"
#include "Core/Matrix.h"
#include "Core/Vector3.h"
#include "Core/Quaternion.h"


namespace TikiEngine
{
	namespace Resources
	{
		class TikiLayer : public TikiObject
		{
		public:
			TikiLayer();
			~TikiLayer();

			void Update(TikiAnimation* animation);

			List<Vector3>& GetTranslation();
			List<Quaternion>& GetQuaternion();

			Vector3 LocalTranslation(int left, int right, float koeff);
			Quaternion LocalQuaternion(int left, int right, float koeff);

			Vector3 LocalTranslation(TikiAnimation* animation);
			Quaternion LocalQuaternion(TikiAnimation* animation);

			Matrix LocalTransform(const double& time = -1.0);

		private:

			List<Vector3> translation;
			List<Quaternion> quaternionen;

			Matrix transformMatrix;

		};
	}
}